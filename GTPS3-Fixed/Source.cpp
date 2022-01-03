#include <string>
#include <io.h> 
#include <fstream>
#include <iostream>
#include <vector>
#include <iostream>
#include "enet/include/enet.h"
#include "json.hpp"
#include "Item.h"
#include "Base.h"
#include "Player.h"
#include "Packet.h"
#include "World.h"-
#include <sstream>

using namespace std::chrono;
#pragma comment( lib, "ws2_32.lib")
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")								
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")								
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
int main() {
	srand(unsigned int(time(nullptr)));
	if (items_dat() == -1)
		cout << "items.dat klaida" << endl;
	else {
		cout << items.size() << " items loaded" << endl;
	}
	if (init_enet(17091) == -1)
		cout << "enet klaida" << endl;
	ENetEvent event;
	cout << "ENetEvent event;" << endl;
	while (true) {
		while (enet_host_service(server, &event, 100) > 0) {
			try {
				ENetPeer* peer = event.peer;
				switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT:
				{
					if (saving_ or f_saving_) break;
					send_(peer, 1, nullptr, 0);
					peer->data = new Player;
					pInfo(peer)->id = peer->connectID;
					char clientConnection[16];
					enet_address_get_host_ip(&peer->address, clientConnection, 16); // issaugo real ip 
					pInfo(peer)->ip = clientConnection;
					cout << "New client: " << pInfo(peer)->ip << endl;
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE:
				{
					switch (message_(event.packet)) {
					case 2: // dialogs/buttons
					{
						string cch = text_(event.packet);
						if (cch == "action|getDRAnimations\n") {
							break;
						}
						if (pInfo(peer)->trading_with != -1 and cch.find("action|input") == string::npos and cch.find("action|trade_started") == string::npos and cch.find("action|dialog_return") == string::npos and cch.find("action|mod_trade") == string::npos and cch.find("action|rem_trade") == string::npos and cch.find("action|trade_accept") == string::npos and cch != "action|trade_cancel\n") {
							cancel_trade(peer, false, true);
							if (cch.find("action|respawn") == string::npos) break;
						}
						if (pInfo(peer)->world.empty() and not pInfo(peer)->tankIDName.empty() and cch != "action|enter_game\n" and cch != "action|refresh_item_data\n") break;
						if (pInfo(peer)->requestedName.empty()) {
							player_login(peer, cch);
						}
						else if (cch.find("action|input") != string::npos) {
							try {
								string msg = explode("\n", explode("|", cch).at(3)).at(0);
								if (msg.length() <= 0 || msg.length() > 120 || msg.empty() || std::all_of(msg.begin(), msg.end(), [](char c) {return std::isspace(c); })) continue;
								for (char c : msg) if (c < 0x20 || c>0x7A) continue;
								space_(msg);
								if (msg.at(0) == '/') {
									SendCmd(peer, msg);
								}
								else {
									if (msg.at(0) == '`' and msg.size() <= 2) break;
									if (has_playmod(pInfo(peer), "duct tape")) {
										string msg2 = "";
										for (int i = 0; i < msg.length(); i++) msg2 += i % 2 == 0 ? "m" : "f";
										msg = msg2;
									}
									string check_ = msg;
									transform(check_.begin(), check_.end(), check_.begin(), ::tolower);
									gamepacket_t p, p2;
									p.Insert("OnConsoleMessage");
									p.Insert("CP:_PL:0_OID:_CT:[W]_ `6<" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``>`` `$" + (pInfo(peer)->dev == 1 ? "`5" : (pInfo(peer)->mod == 1) ? "`^" : "`$") + msg + "`````");
									p2.Insert("OnTalkBubble");
									p2.Insert(pInfo(peer)->netID);
									string a = "";
									if (check_ != ":/" and check_ != ":p" and check_ != ":*" and check_ != ";)" and check_ != ":d" and check_ != ":o" and check_ != ":'(" and check_ != ":(") {
										p2.Insert("CP:_PL:0_OID:_player_chat=" + a + (pInfo(peer)->dev == 1 ? "`5" : (pInfo(peer)->mod == 1) ? "`^" : "`0") + msg);
									}
									else {
										p2.Insert(msg);
									}
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											bool muted_ = false;
											for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
												if (pInfo(currentPeer)->friends.at(c_).name == pInfo(peer)->tankIDName) {
													if (pInfo(currentPeer)->friends.at(c_).mute) {
														muted_ = true;
														break;
													}
												}
											} if (not muted_) {
												p.CreatePacket(currentPeer);
												p2.CreatePacket(currentPeer);
											}
										}
									}
								}
							}
							catch (out_of_range& klaida) {
								cout << "Chat klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|mod_trade") != string::npos or cch.find("action|rem_trade") != string::npos) {
							try {
								int item_id = atoi(explode("\n", explode("|", cch).at(2)).at(0).c_str()), c_ = 0;
								modify_inventory(peer, item_id, c_);
								if (c_ == 0) break;
								if (items.at(item_id).untradeable) {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You'd be sorry if you lost that!");
									p.CreatePacket(peer);
									break;
								} if (c_ == 1 or cch.find("action|rem_trade") != string::npos) {
									mod_trade(peer, item_id, c_, (cch.find("action|rem_trade") != string::npos ? true : false));
									break;
								} if (cch.find("action|rem_trade") == string::npos) {
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`2Trade`` `w" + items.at(item_id).name + "``|left|" + to_string(item_id) + "|\nadd_textbox|`2Trade how many?``|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(item_id) + "\nend_dialog|trade_item|Cancel|OK|");
									p.CreatePacket(peer);
								}
							}
							catch (out_of_range& klaida) {
								cout << "Mod trade klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|trade_accept") != string::npos) {
							try {
								if (pInfo(peer)->trading_with != -1) {
									string status_ = explode("\n", explode("|", cch).at(2)).at(0);
									if (status_ != "1" and status_ != "0") break;
									bool f_ = false;
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											if (pInfo(currentPeer)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(currentPeer)->trading_with) {
												string name_ = pInfo(peer)->world;
												vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
												if (p != worlds.end()) {
													World* world_ = &worlds.at(p - worlds.begin());
													if (status_ == "1")
														pInfo(peer)->trade_accept = 1;
													else
														pInfo(peer)->trade_accept = 0;
													if (pInfo(peer)->trade_accept and pInfo(currentPeer)->trade_accept) {
														// check inv space   
														if (not trade_space_check(peer, currentPeer)) {
															pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(peer)->netID);
															p.Insert("");
															p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|0");
															p.CreatePacket(peer);
															{
																gamepacket_t p;
																p.Insert("OnTradeStatus");
																p.Insert(pInfo(peer)->netID);
																p.Insert("");
																p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
																p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
																p.CreatePacket(currentPeer);
															}
															f_ = true;
															break;
														}
														else if (not trade_space_check(currentPeer, peer)) {
															pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(currentPeer)->netID);
															p.Insert("");
															p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\naccepted|0");
															p.CreatePacket(currentPeer);
															{
																gamepacket_t p;
																p.Insert("OnTradeStatus");
																p.Insert(pInfo(currentPeer)->netID);
																p.Insert("");
																p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
																p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
																p.CreatePacket(peer);
															}
															f_ = true;
															break;
														}
														{
															gamepacket_t p;
															p.Insert("OnForceTradeEnd");
															p.CreatePacket(peer);
														}
														send_trade_confirm_dialog(peer, currentPeer);
														break;
													}
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(peer)->netID);
													p.Insert("");
													p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
													p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|" + status_);
													p.CreatePacket(peer);
													{
														{
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(currentPeer)->netID);
															p.Insert("");
															p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
															p.Insert("locked|0\nreset_locks|1\naccepted|0");
															p.CreatePacket(currentPeer);
														}
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(currentPeer)->netID);
														p.Insert("");
														p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
														p.Insert("locked|0\naccepted|1");
														p.CreatePacket(currentPeer);
														{
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(currentPeer)->netID);
															p.Insert("");
															p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
															p.CreatePacket(currentPeer);
														}
														{
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(peer)->netID);
															p.Insert("");
															p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|" + status_);
															p.CreatePacket(currentPeer);
														}
													}
												}
												f_ = true;
												break;
											}
										}
									} if (not f_) {
										if (status_ == "1")
											pInfo(peer)->trade_accept = 1;
										else
											pInfo(peer)->trade_accept = 0;
									}
								}
							}
							catch (out_of_range& klaida) {
								cout << "Trade accept klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch == "action|trade_cancel\n") cancel_trade(peer);
						else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|newbie\n\n") pInfo(peer)->n = 1;
						else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|warp_to_") != string::npos) {
							if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
								string world_name = cch.substr(67, cch.length() - 67);
								replace_str(world_name, "\n", "");
								join_world(peer, world_name);
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|megaphone\nitemID|2480|\nwords|") != string::npos) {
							string text = cch.substr(62, cch.length() - 62).c_str();
							bool cansb = true;
							int c_ = 0;
							modify_inventory(peer, 2480, c_);
							if (c_ == 0) continue;
							if (has_playmod(pInfo(peer), "duct tape")) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`6>> That's sort of hard to do while duct-taped.``");
								p.CreatePacket(peer);
								cansb = false;
								continue;
							}
							if (has_playmod(pInfo(peer), "megaphone!")) {
								int time_ = 0;
								for (PlayMods peer_playmod : pInfo(peer)->playmods) {
									if (peer_playmod.id == 13) {
										time_ = peer_playmod.time - time(nullptr);
										break;
									}
								}
								packet_(peer, "action|log\nmsg|>> (" + to_playmod_time(time_) + "before you can broadcast again)", "");
								break;
							}
							if (cansb) {
								replace_str(text, "\n", "");
								modify_inventory(peer, 2480, c_ = -1);
								int currentmega = 0;
								modify_inventory(peer, 2480, currentmega);
								PlayMods new_playmod{};
								new_playmod.id = 13;
								new_playmod.time = time(nullptr) + 600;
								pInfo(peer)->playmods.push_back(new_playmod);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("Broadcasting to ALL! (`$Megaphone!`` mod added)");
									p.CreatePacket(peer);
								}
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`#Super-Broadcast sent. Used `$1 Megaphone``. (`$" + setGems(currentmega) + "`` left)`` (10 mins before you can broadcast again)");
									p.CreatePacket(peer);
								}
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds.at(p - worlds.begin());
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									if (pInfo(peer)->mod == 0 && pInfo(peer)->dev == 0) lastsbworld = pInfo(peer)->world;
									p.Insert("CP:_PL:0_OID:_CT:[SB]_ `5** from (`0" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`````5) in [```$" + (pInfo(peer)->m_h == 1 || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "```5] ** : ``" + (pInfo(peer)->mod + pInfo(peer)->dev == 0 ? "`$" : "`^") + "" + text + "``");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										p.CreatePacket(currentPeer);
									}
								}
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|cancel") != string::npos) send_wrench_self(peer);
						else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|clear") != string::npos) {
							pInfo(peer)->note = "";
							send_wrench_self(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|save\n\npersonal_note|") != string::npos) {
							string btn = cch.substr(81, cch.length() - 81).c_str();
							replace_str(btn, "\n", "");
							if (btn.length() > 128) continue;
							pInfo(peer)->note = btn;
							send_wrench_self(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|ban_") != string::npos) {
							if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->tankIDName == pInfo(peer)->last_wrenched) {
										int seconds = atoi(cch.substr(63, cch.length() - 63).c_str());
										add_ban(currentPeer, seconds, "No reason", pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
									}
								}
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|duc_") != string::npos) {
							if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->tankIDName == pInfo(peer)->last_wrenched) {
										int seconds = atoi(cch.substr(63, cch.length() - 63).c_str());
										add_mute(currentPeer, seconds, "No reason", pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
									}
								}
							}
						}
						else if (cch.find("action|drop") != string::npos) {
							try {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds.at(p - worlds.begin());
									int id_ = atoi(explode("\n", explode("|", cch).at(3)).at(0).c_str()), c_ = 0;
									if (id_ <= 0 or id_ >= items.size()) break;
									if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 4758) != world_->active_jammers.end()) {
										if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("The Mini-Mod says no dropping items in this world!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
											break;
										}
									}
									if (items.at(id_).untradeable or id_ == 1424) {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("You can't drop that.");
										p.CreatePacket(peer);
										break;
									}
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds.at(p - worlds.begin());
										int a_ = rand() % 12;
										int x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - (a_ + 20) : (pInfo(peer)->x + 20) + a_);
										int y = pInfo(peer)->y + rand() % 16;
										BlockTypes type_ = FOREGROUND;
										WorldBlock* block_ = &world_->blocks.at((pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100));
										if (items.at(block_->fg).collisionType == 1 || block_->fg == 6 || items.at(block_->fg).entrance || items.at(block_->fg).toggleable and is_false_state(world_->blocks.at((pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100)), 0x00400000)) {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(items.at(block_->fg).blockType == BlockTypes::MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
											p.CreatePacket(peer);
											break;
										}
										/*if (static_(type_, items.at(world_->blocks.at(((pInfo(peer)->state == 16 ? pInfo(peer)->x - 18 : pInfo(peer)->x + 22) / 32) + ((y / 32) * 100)).fg)) or static_(type_, items.at(world_->blocks.at(((pInfo(peer)->state == 16 ? pInfo(peer)->x - 24 : pInfo(peer)->x + 42) / 32) + ((y / 32) * 100)).fg))) {
											if (items.at(block_->fg).collisionType == 1) {
												gamepacket_t p;
												p.Insert("OnTextOverlay");
												p.Insert(type_ == MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
												p.CreatePacket(peer);
												break;
											}
										}*/
										int count_ = 0;
										for (int i_ = 0; i_ < world_->drop.size(); i_++) {
											if (abs(world_->drop.at(i_).y - y) <= 16 and abs(world_->drop.at(i_).x - x) <= 16) {
												count_ += 1;
											}
										} if (count_ > 20) {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("You can't drop that here, find an emptier spot!");
											p.CreatePacket(peer);
											break;
										}
									}
									modify_inventory(peer, id_, c_);
									{
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(id_).name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to drop?|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(id_) + "\nadd_textbox|If you are trying to trade an item with another player, use your wrench on them instead to use our Trade System! `4Dropping items is not safe!``|left|\nend_dialog|drop_item|Cancel|OK|");
										p.CreatePacket(peer);
									}
								}
							}
							catch (out_of_range& klaida) {
								cout << "Drop klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|setSkin") != string::npos) {
							try {
								string id_ = explode("\n", explode("|", cch).at(2)).at(0);
								if (not isdigit(id_[0])) break;
								char* endptr = NULL;
								unsigned int skin_ = strtoll(id_.c_str(), &endptr, 10);
								if (skin_ != 1348237567 and skin_ != 1685231359 and skin_ != 2022356223 and skin_ != 2190853119 and skin_ != 2527912447 and skin_ != 2864971775 and skin_ != 3033464831 and skin_ != 3370516479) break;
								pInfo(peer)->skin = skin_;
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnChangeSkin");
								p.Insert(pInfo(peer)->skin);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == pInfo(peer)->world) {
										p.CreatePacket(currentPeer);
									}
								}
							}
							catch (out_of_range& klaida) {
								cout << "setSkin klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|trash") != string::npos) {
							try {
								int id_ = atoi(explode("\n", explode("|", cch).at(3)).at(0).c_str()), c_ = 0;
								if (id_ <= 0 or id_ >= items.size()) break;
								gamepacket_t p;
								if (id_ == 18 || id_ == 32 || id_ == 6336) {
									packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
									p.Insert("OnTextOverlay");
									p.Insert("You'd be sorry if you lost that!");
									p.CreatePacket(peer);
									break;
								}
								modify_inventory(peer, id_, c_); // gauna itemo kieki 
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Trash`` `w" + items.at(id_).name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to `4destroy``? (you have " + to_string(c_) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
								p.CreatePacket(peer);
							}
							catch (out_of_range& klaida) {
								cout << "Trash klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|info") != string::npos) {
							try {
								int id_ = atoi(explode("\n", explode("|", cch).at(3)).at(0).c_str());
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								string extra_ = "\nadd_textbox|";
								if (id_ == 18) {
									extra_ += "You've punched `w" + to_string(pInfo(peer)->punch_count) + "`` times.";
								} if (items.at(id_).blockType == BlockTypes::LOCK) {
									extra_ += "A lock makes it so only you (and designated friends) can edit an area.";
								} if (items.at(id_).r_1 == 0 or items.at(id_).r_2 == 0) {
									extra_ += "<CR>This item can't be spliced.";
								}
								else {
									extra_ += "Rarity: `w" + to_string(items.at(id_).rarity) + "``<CR><CR>To grow, plant a `w" + items.at(id_ + 1).name + "``.   (Or splice a `w" + items.at(items.at(id_).r_1).name + "`` with a `w" + items.at(items.at(id_).r_2).name + "``)<CR>";
								} if (items.at(id_).properties & Property_Dropless or items.at(id_).rarity == 999) {
									extra_ += "<CR>`1This item never drops any seeds.``";
								} if (items.at(id_).properties & Property_Untradable) {
									extra_ += "<CR>`1This item cannot be dropped or traded.``";
								} if (items.at(id_).properties & Property_AutoPickup) {
									extra_ += "<CR>`1This item can't be destroyed - smashing it will return it to your backpack if you have room!``";
								} if (items.at(id_).properties & Property_Wrenchable) {
									extra_ += "<CR>`1This item has special properties you can adjust with the Wrench.``";
								} if (items.at(id_).properties & Property_MultiFacing) {
									extra_ += "<CR>`1This item can be placed in two directions, depending on the direction you're facing.``";
								} if (items.at(id_).properties & Property_NoSelf) {
									extra_ += "<CR>`1This item has no use... by itself.``";
								}
								extra_ += "|left|";
								if (extra_ == "\nadd_textbox||left|") extra_ = "";
								else extra_ = replace_str(extra_, "add_textbox|<CR>", "add_textbox|");
								p.Insert("set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items.at(id_).name + "``|left|" + to_string(id_) + "|" + to_string(items.at(id_).chi) + "|\nadd_spacer|small|\nadd_textbox|" + items.at(id_).description + "|left|\nadd_spacer|small|" + extra_ + "\nadd_spacer|small|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|continue||OK|\n");
								p.CreatePacket(peer);
							}
							catch (out_of_range& klaida) {
								cout << "Info klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|wrench") != string::npos) {
							try {
								int netID = atoi(explode("\n", explode("|", cch).at(3)).at(0).c_str());
								if (pInfo(peer)->netID == netID) {
									send_wrench_self(peer);
								}
								else {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->netID == netID and pInfo(currentPeer)->world == pInfo(peer)->world) {
											bool already_friends = false, trade_blocked = false, muted = false;
											for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
												if (pInfo(peer)->friends.at(c_).name == pInfo(currentPeer)->tankIDName) {
													already_friends = true;
													if (pInfo(peer)->friends.at(c_).block_trade)
														trade_blocked = true;
													if (pInfo(peer)->friends.at(c_).mute)
														muted = true;
													break;
												}
											}
											pInfo(peer)->last_wrenched = pInfo(currentPeer)->tankIDName;
											string name_ = pInfo(peer)->world;
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds.at(p - worlds.begin());
												string msg2 = "";
												for (int i = 0; i < to_string(pInfo(currentPeer)->level).length(); i++) msg2 += "?";
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("embed_data|netID|" + to_string(pInfo(peer)->netID) + "\nset_default_color|`o\nadd_label_with_icon|big|" + (pInfo(currentPeer)->mod == 1 || pInfo(currentPeer)->dev == 1 ? pInfo(currentPeer)->name_color : "`0") + "" + pInfo(currentPeer)->tankIDName + "`` `0(```2" + (pInfo(currentPeer)->dev == 1 ? msg2 : to_string(pInfo(currentPeer)->level)) + "```0)``|left|18|\nembed_data|netID|" + to_string(netID) + "\nadd_spacer|small|" + (trade_blocked ? "\nadd_button||`4Trade Blocked``|disabled|||" : "\nadd_button|trade|`wTrade``|noflags|0|0|") + "\nadd_textbox|(No Battle Leash equipped)|left|\nadd_textbox|Your opponent needs a valid license to battle!|left|" + (world_->owner_name == pInfo(peer)->tankIDName or (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) or pInfo(peer)->dev + pInfo(peer)->mod > 0 ? "\nadd_button|kick|`4Kick``|noflags|0|0|\nadd_button|pull|`5Pull``|noflags|0|0|\nadd_button|worldban|`4World Ban``|noflags|0|0|" : "") + "" + (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1 ? "\nadd_button|punish_view|`5Punish/View``|noflags|0|0|" : "") + "" + (!already_friends ? "\nadd_button|friend_add|`wAdd as friend``|noflags|0|0|" : "") + (muted ? "\nadd_button|unmute_player|`wUnmute``|noflags|0|0|" : (already_friends ? "\nadd_button|mute_player|`wMute``|noflags|0|0|" : "")) + "\nadd_button|ignore_player|`wIgnore Player``|noflags|0|0|\nadd_button|report_player|`wReport Player``|noflags|0|0|\nadd_spacer|small|\nend_dialog|popup||Continue|\nadd_quick_exit|");
												p.CreatePacket(peer);
											}
											break;
										}
									}
								}
							}
							catch (out_of_range& klaida) {
								cout << "Wrench klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch.find("action|friends") != string::npos) send_social(peer);
						else if (cch == "action|store\nlocation|bottommenu\n" || cch == "action|store\nlocation|gem\n" || cch == "action|store\nlocation|pausemenu\n") {
							gamepacket_t p;
							p.Insert("OnStoreRequest");
							p.Insert("set_description_text|Welcome to the `2Growtopia Store``! Select the item you'd like more info on.`o `wWant to get `5Supporter`` status? Any Gem purchase (or `520000`` Gems earned with free `5Tapjoy`` offers) will make you one. You'll get new skin colors, the `5Recycle`` tool to convert unwanted items into Gems, and more bonuses!\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||1|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_banner|interface/large/gui_shop_featured_header.rttex|0|1|\nadd_button|valentine_goodies|`oValentine's Goodies``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 5 Golden Booty Chest and Valentine's Card. <CR><CR>`5Description:`` Contains 5 Golden Booty Chests and a bonus Valentine's Card to share the love. Smash the Golden Booty Chests to find a random assortment of Valentine's surprises.|0|4|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|science_pack|`oMad Science Kit``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Science Station, 1 Laboratory, 1 LabCoat, 1 Combover Hair, 1 Goggles, 5 Chemical R, 10 Chemical G, 5 Chemical Y, 5 Chemical B, 5 Chemical P and 1 `#Rare`` `2Death Ray``.<CR><CR>`5Description:`` It's SCIENCE! Defy the natural order with a Science Station that produces chemicals, a Laboratory in which to mix them and a full outfit to do so safely! You'll also get a starter pack of assorted chemicals. Mix them up! Special bonus: A `#Rare`` `2Death Ray`` to make your science truly mad!|0|3|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|music_pack|`oComposer's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 20 Sheet Music: Blank, 20 Sheet Music: Piano Note, 20 Sheet Music: Bass Note, 20 Sheet Music Drums, 5 Sheet Music: Sharp Piano, 5 Sheet Music: Flat Piano, 5 Sheet Music: Flat Bass and 5 Sheet Music: Sharp Bass .<CR><CR>`5Description:`` With these handy blocks, you'll be able to compose your own music, using your World-Locked world as a sheet of music. Requires a World Lock (sold separately!).|0|0|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|patrick_pack|`oSt. Patrick's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` Leprechaun outfit, Pot O' Gold and 6 Green Beer. <CR><CR>`5Description:`` Celebrate the greenest of holidays with a complete Leprechaun outfit, your own personal Pot O' Gold, and a six-pack of Green Beer!|0|1|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|farm_pack|`oFarm Pack``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Cow, 1 Chicken, 10 Wheat, 10 Barn Block, 10 Red Wood Walls, 1 Barn Door, 1 Straw Hat, 1 Overalls, 1 Pitchfork, 1 Farmgirl Hair, 1 `#Rare`` `2Dear John Tractor``.<CR><CR>`5Description:`` Put the `2Grow`` in Growtopia with this pack, including a Cow you can milk, a Chicken that lays eggs and a farmer's outfit. Best of all? You get a `#Rare`` `2Dear John Tractor`` you can ride that will mow down trees!|0|0|15000|0|||-1|-1||-1|-1||1||||||0|0|\n");
							p.CreatePacket(peer);
						}
						else if (cch == "action|storenavigate\nitem|main\nselection|gems_rain\n") {
							gamepacket_t p;
							p.Insert("OnStoreRequest");
							p.Insert("set_description_text|Welcome to the `2Growtopia Store``! Select the item you'd like more info on.`o `wWant to get `5Supporter`` status? Any Gem purchase (or `520000`` Gems earned with free `5Tapjoy`` offers) will make you one. You'll get new skin colors, the `5Recycle`` tool to convert unwanted items into Gems, and more bonuses!\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||1|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_banner|interface/large/gui_shop_featured_header.rttex|0|1|\nadd_button|valentine_goodies|`oValentine's Goodies``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 5 Golden Booty Chest and Valentine's Card. <CR><CR>`5Description:`` Contains 5 Golden Booty Chests and a bonus Valentine's Card to share the love. Smash the Golden Booty Chests to find a random assortment of Valentine's surprises.|0|4|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|science_pack|`oMad Science Kit``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Science Station, 1 Laboratory, 1 LabCoat, 1 Combover Hair, 1 Goggles, 5 Chemical R, 10 Chemical G, 5 Chemical Y, 5 Chemical B, 5 Chemical P and 1 `#Rare`` `2Death Ray``.<CR><CR>`5Description:`` It's SCIENCE! Defy the natural order with a Science Station that produces chemicals, a Laboratory in which to mix them and a full outfit to do so safely! You'll also get a starter pack of assorted chemicals. Mix them up! Special bonus: A `#Rare`` `2Death Ray`` to make your science truly mad!|0|3|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|music_pack|`oComposer's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 20 Sheet Music: Blank, 20 Sheet Music: Piano Note, 20 Sheet Music: Bass Note, 20 Sheet Music Drums, 5 Sheet Music: Sharp Piano, 5 Sheet Music: Flat Piano, 5 Sheet Music: Flat Bass and 5 Sheet Music: Sharp Bass .<CR><CR>`5Description:`` With these handy blocks, you'll be able to compose your own music, using your World-Locked world as a sheet of music. Requires a World Lock (sold separately!).|0|0|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|patrick_pack|`oSt. Patrick's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` Leprechaun outfit, Pot O' Gold and 6 Green Beer. <CR><CR>`5Description:`` Celebrate the greenest of holidays with a complete Leprechaun outfit, your own personal Pot O' Gold, and a six-pack of Green Beer!|0|1|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|farm_pack|`oFarm Pack``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Cow, 1 Chicken, 10 Wheat, 10 Barn Block, 10 Red Wood Walls, 1 Barn Door, 1 Straw Hat, 1 Overalls, 1 Pitchfork, 1 Farmgirl Hair, 1 `#Rare`` `2Dear John Tractor``.<CR><CR>`5Description:`` Put the `2Grow`` in Growtopia with this pack, including a Cow you can milk, a Chicken that lays eggs and a farmer's outfit. Best of all? You get a `#Rare`` `2Dear John Tractor`` you can ride that will mow down trees!|0|0|15000|0|||-1|-1||-1|-1||1||||||0|0|\n");
							p.CreatePacket(peer);
						}
						else if (cch == "action|storenavigate\nitem|locks\nselection|upgrade_backpack\n") {
							gamepacket_t p;
							p.Insert("OnStoreRequest");
							string a = "";
							p.Insert("set_description_text|`2Locks And Stuff!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||1|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|" + a + "" + (pInfo(peer)->inv.size() < 186 ? "\nadd_button|upgrade_backpack|`0Upgrade Backpack`` (`w10 Slots``)|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 10 Additional Backpack Slots.<CR><CR>`5Description:`` Sewing an extra pocket onto your backpack will allow you to store `$10`` additional item types.  How else are you going to fit all those toilets and doors?|0|1|" + to_string(inventory_price(pInfo(peer)->inv.size())) + "|0|||-1|-1||-1|-1||1||||||0|0|" : "") + "\nadd_button|clothes|`oClothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Wearble Items.<CR><CR>`5Description:`` Why not look the part? Some may even have special powers...|0|0|50|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|rare_clothes|`oRare Clothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Chosen Wearbale Items.<CR><CR>`5Description:`` Enjoy the garb of kings! Some may even have special powers...|0|1|500|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|transmutation_device|`oTransmutabooth``|interface/large/store_buttons/store_buttons27.rttex|`2You Get:`` 1 Transmutabooth.<CR><CR>`5Description:`` Behold! A wondrous technological achievement from the innovative minds at GrowTech, the Transmutabooth allows you to merge clothing items, transferring the visual appearance of one onto another in the same slot! If you've ever wanted your Cyclopean Visor to look like Shades (while keeping its mod), now you can!|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|"*/""/*\nadd_button|contact_lenses|`oContact Lens Pack``|interface/large/store_buttons/store_buttons22.rttex|`2You Get:`` 20 Random Contact Lens Colors.<CR><CR>`5Description:`` Need a colorful new look? This pack includes 20 random Contact Lens colors (and may include Contact Lens Cleaning Solution, to return to your natural eye color)!|0|7|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|eye_drops|`oEye Drop Pack``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 `#Rare Bathroom Mirror`` and 10 random Eye Drop Colors.<CR><CR>`5Description:`` Need a fresh new look?  This pack includes a 10 random Eye Drop Colors (may include Eye Cleaning Solution, to leave your eyes sparkly clean)!|0|6|30000|0|||-1|-1||-1|-1||1||||||0|0|*/"\nadd_button|nyan_hat|`oTurtle Hat``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Turtle Hat.<CR><CR>`5Description:`` It's the greatest hat ever. It bloops out bubbles as you run! `4Not available any other way!``|0|2|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|tiny_horsie|`oTiny Horsie``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Tiny Horsie.<CR><CR>`5Description:`` Tired of wearing shoes? Wear a Tiny Horsie instead! Or possibly a large dachshund, we're not sure. Regardless, it lets you run around faster than normal, plus you're on a horse! `4Not available any other way!``|0|5|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|star_ship|`oPleiadian Star Ship``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 1 Pleiadian Star Ship.<CR><CR>`5Description:`` Float on, my brother. It's all groovy. This star ship can't fly, but you can still zoom around in it, leaving a trail of energy rings and moving at enhanced speed. Sponsored by Pleiadian. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dragon_hand|`oDragon Hand``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Dragon Hand.<CR><CR>`5Description:`` Call forth the dragons of legend!  With the Dragon Hand, you will command your own pet dragon. Instead of punching blocks or players, you can order your dragon to incinerate them! In addition to just being awesome, this also does increased damage, and pushes other players farther. `4Not available any other way!``|0|1|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|corvette|`oLittle Red Corvette``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Little Red Corvette.<CR><CR>`5Description:`` Cruise around the neighborhood in style with this sweet convertible. It moves at enhanced speed and leaves other Growtopians in your dust. `4Not available any other way!``|0|1|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|stick_horse|`oStick Horse``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Stick Horse.<CR><CR>`5Description:`` Nobody looks cooler than a person bouncing along on a stick with a fake horse head attached. NOBODY. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ambulance|`oAmbulance``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Ambulance.<CR><CR>`5Description:`` Rush to the scene of an accident while lawyers chase you in this speedy rescue vehicle. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|raptor|`oRiding Raptor``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Riding Raptor.<CR><CR>`5Description:`` Long thought to be extinct, it turns out that these dinosaurs are actually alive and easily tamed. And riding one lets you run around faster than normal! `4Not available any other way!``|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|owl|`oMid-Pacific Owl``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Mid-Pacific Owl.<CR><CR>`5Description:`` This owl is a bit lazy - if you stop moving around, he'll land on your head and fall asleep. Dedicated to the students of the Mid-Pacific Institute. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|unicorn|`oUnicorn Garland``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Unicorn Garland.<CR><CR>`5Description:`` Prance about in the fields with your very own pet unicorn! It shoots `1R`2A`3I`4N`5B`6O`7W`8S``. `4Not available any other way!``|0|4|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|starboard|`oStarBoard``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 StarBoard.<CR><CR>`5Description:`` Hoverboards are here at last! Zoom around Growtopia on this brand new model, which is powered by fusion energy (that means stars spit out of the bottom). Moves faster than walking. Sponsored by Miwsky, Chudy, and Dawid. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|motorcycle|`oGrowley Motorcycle``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Growley Motorcycle.<CR><CR>`5Description:`` The coolest motorcycles available are Growley Dennisons. Get a sporty blue one today! It even moves faster than walking, which is pretty good for a motorcycle. `4Not available any other way!``|0|6|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|monkey_on_back|`oMonkey On Your Back``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Monkey On Your Back.<CR><CR>`5Description:`` Most people work really hard to get rid of these, but hey, if you want one, it's available! `4But not available any other way!`` Sponsored by SweGamerHD's subscribers, Kizashi, and Inforced. `#Note: This is a neck item, not a back item. He's grabbing your neck!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|carrot_sword|`oCarrot Sword``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Carrot Sword.<CR><CR>`5Description:`` Razor sharp, yet oddly tasty. This can carve bunny symbols into your foes! `4Not available any other way!`` Sponsored by MrMehMeh.|0|3|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|red_bicycle|`oRed Bicycle``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Red Bicycle.<CR><CR>`5Description:`` It's the environmentally friendly way to get around! Ride this bicycle at high speed hither and zither throughout Growtopia. `4Not available any other way!``|0|5|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fire_truck|`oFire Truck``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Fire Truck.<CR><CR>`5Description:`` Race to the scene of the fire in this speedy vehicle! `4Not available any other way!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|pet_slime|`oPet Slime``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Pet Slime.<CR><CR>`5Description:`` What could be better than a blob of greasy slime that follows you around? How about a blob of greasy slime that follows you around and spits corrosive acid, melting blocks more quickly than a normal punch? `4Not available any other way!``|0|4|100000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dabstep_shoes|`oDabstep Low Top Sneakers``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Dabstep Low Top Sneakers.<CR><CR>`5Description:`` Light up every footfall and move to a better beat with these dabulous shoes! When you're wearing these, the world is your dance floor! `4Not available any other way!``|0|2|30000|0|||-1|-1||-1|-1||1||||||0|0|\nselect_item|upgrade_backpack\n");
							p.CreatePacket(peer);
						}
						else if (cch.find("action|buy") != string::npos) {
							try {
								string item = explode("\n", explode("|", cch).at(2)).at(0);
								int price = 0, free = get_free_slots(pInfo(peer)), slot = 1, getcount = 0, get_counted = 0, random_pack = 0, token = 0;
								gamepacket_t p, p2;
								p.Insert("OnStorePurchaseResult");
								p2.Insert("OnStoreRequest");
								string a = "";
								if (item == "main") p2.Insert("set_description_text|Welcome to the `2Growtopia Store``! Select the item you'd like more info on.`o `wWant to get `5Supporter`` status? Any Gem purchase (or `520000`` Gems earned with free `5Tapjoy`` offers) will make you one. You'll get new skin colors, the `5Recycle`` tool to convert unwanted items into Gems, and more bonuses!\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||1|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_banner|interface/large/gui_shop_featured_header.rttex|0|1|\nadd_button|valentine_goodies|`oValentine's Goodies``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 5 Golden Booty Chest and Valentine's Card. <CR><CR>`5Description:`` Contains 5 Golden Booty Chests and a bonus Valentine's Card to share the love. Smash the Golden Booty Chests to find a random assortment of Valentine's surprises.|0|4|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|science_pack|`oMad Science Kit``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Science Station, 1 Laboratory, 1 LabCoat, 1 Combover Hair, 1 Goggles, 5 Chemical R, 10 Chemical G, 5 Chemical Y, 5 Chemical B, 5 Chemical P and 1 `#Rare`` `2Death Ray``.<CR><CR>`5Description:`` It's SCIENCE! Defy the natural order with a Science Station that produces chemicals, a Laboratory in which to mix them and a full outfit to do so safely! You'll also get a starter pack of assorted chemicals. Mix them up! Special bonus: A `#Rare`` `2Death Ray`` to make your science truly mad!|0|3|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|music_pack|`oComposer's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 20 Sheet Music: Blank, 20 Sheet Music: Piano Note, 20 Sheet Music: Bass Note, 20 Sheet Music Drums, 5 Sheet Music: Sharp Piano, 5 Sheet Music: Flat Piano, 5 Sheet Music: Flat Bass and 5 Sheet Music: Sharp Bass .<CR><CR>`5Description:`` With these handy blocks, you'll be able to compose your own music, using your World-Locked world as a sheet of music. Requires a World Lock (sold separately!).|0|0|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|patrick_pack|`oSt. Patrick's Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` Leprechaun outfit, Pot O' Gold and 6 Green Beer. <CR><CR>`5Description:`` Celebrate the greenest of holidays with a complete Leprechaun outfit, your own personal Pot O' Gold, and a six-pack of Green Beer!|0|1|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|farm_pack|`oFarm Pack``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Cow, 1 Chicken, 10 Wheat, 10 Barn Block, 10 Red Wood Walls, 1 Barn Door, 1 Straw Hat, 1 Overalls, 1 Pitchfork, 1 Farmgirl Hair, 1 `#Rare`` `2Dear John Tractor``.<CR><CR>`5Description:`` Put the `2Grow`` in Growtopia with this pack, including a Cow you can milk, a Chicken that lays eggs and a farmer's outfit. Best of all? You get a `#Rare`` `2Dear John Tractor`` you can ride that will mow down trees!|0|0|15000|0|||-1|-1||-1|-1||1||||||0|0|\n");
								else if (item == "locks") p2.Insert("set_description_text|`2Locks And Stuff!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||1|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|" + a + "" + (pInfo(peer)->inv.size() < 186 ? "\nadd_button|upgrade_backpack|`0Upgrade Backpack`` (`w10 Slots``)|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 10 Additional Backpack Slots.<CR><CR>`5Description:`` Sewing an extra pocket onto your backpack will allow you to store `$10`` additional item types.  How else are you going to fit all those toilets and doors?|0|1|" + to_string(inventory_price(pInfo(peer)->inv.size())) + "|0|||-1|-1||-1|-1||1||||||0|0|" : "") + "\nadd_button|clothes|`oClothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Wearble Items.<CR><CR>`5Description:`` Why not look the part? Some may even have special powers...|0|0|50|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|rare_clothes|`oRare Clothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Chosen Wearbale Items.<CR><CR>`5Description:`` Enjoy the garb of kings! Some may even have special powers...|0|1|500|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|transmutation_device|`oTransmutabooth``|interface/large/store_buttons/store_buttons27.rttex|`2You Get:`` 1 Transmutabooth.<CR><CR>`5Description:`` Behold! A wondrous technological achievement from the innovative minds at GrowTech, the Transmutabooth allows you to merge clothing items, transferring the visual appearance of one onto another in the same slot! If you've ever wanted your Cyclopean Visor to look like Shades (while keeping its mod), now you can!|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|"*/""/*\nadd_button|contact_lenses|`oContact Lens Pack``|interface/large/store_buttons/store_buttons22.rttex|`2You Get:`` 20 Random Contact Lens Colors.<CR><CR>`5Description:`` Need a colorful new look? This pack includes 20 random Contact Lens colors (and may include Contact Lens Cleaning Solution, to return to your natural eye color)!|0|7|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|eye_drops|`oEye Drop Pack``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 `#Rare Bathroom Mirror`` and 10 random Eye Drop Colors.<CR><CR>`5Description:`` Need a fresh new look?  This pack includes a 10 random Eye Drop Colors (may include Eye Cleaning Solution, to leave your eyes sparkly clean)!|0|6|30000|0|||-1|-1||-1|-1||1||||||0|0|*/"\nadd_button|nyan_hat|`oTurtle Hat``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Turtle Hat.<CR><CR>`5Description:`` It's the greatest hat ever. It bloops out bubbles as you run! `4Not available any other way!``|0|2|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|tiny_horsie|`oTiny Horsie``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Tiny Horsie.<CR><CR>`5Description:`` Tired of wearing shoes? Wear a Tiny Horsie instead! Or possibly a large dachshund, we're not sure. Regardless, it lets you run around faster than normal, plus you're on a horse! `4Not available any other way!``|0|5|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|star_ship|`oPleiadian Star Ship``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 1 Pleiadian Star Ship.<CR><CR>`5Description:`` Float on, my brother. It's all groovy. This star ship can't fly, but you can still zoom around in it, leaving a trail of energy rings and moving at enhanced speed. Sponsored by Pleiadian. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dragon_hand|`oDragon Hand``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Dragon Hand.<CR><CR>`5Description:`` Call forth the dragons of legend!  With the Dragon Hand, you will command your own pet dragon. Instead of punching blocks or players, you can order your dragon to incinerate them! In addition to just being awesome, this also does increased damage, and pushes other players farther. `4Not available any other way!``|0|1|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|corvette|`oLittle Red Corvette``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Little Red Corvette.<CR><CR>`5Description:`` Cruise around the neighborhood in style with this sweet convertible. It moves at enhanced speed and leaves other Growtopians in your dust. `4Not available any other way!``|0|1|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|stick_horse|`oStick Horse``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Stick Horse.<CR><CR>`5Description:`` Nobody looks cooler than a person bouncing along on a stick with a fake horse head attached. NOBODY. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ambulance|`oAmbulance``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Ambulance.<CR><CR>`5Description:`` Rush to the scene of an accident while lawyers chase you in this speedy rescue vehicle. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|raptor|`oRiding Raptor``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Riding Raptor.<CR><CR>`5Description:`` Long thought to be extinct, it turns out that these dinosaurs are actually alive and easily tamed. And riding one lets you run around faster than normal! `4Not available any other way!``|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|owl|`oMid-Pacific Owl``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Mid-Pacific Owl.<CR><CR>`5Description:`` This owl is a bit lazy - if you stop moving around, he'll land on your head and fall asleep. Dedicated to the students of the Mid-Pacific Institute. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|unicorn|`oUnicorn Garland``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Unicorn Garland.<CR><CR>`5Description:`` Prance about in the fields with your very own pet unicorn! It shoots `1R`2A`3I`4N`5B`6O`7W`8S``. `4Not available any other way!``|0|4|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|starboard|`oStarBoard``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 StarBoard.<CR><CR>`5Description:`` Hoverboards are here at last! Zoom around Growtopia on this brand new model, which is powered by fusion energy (that means stars spit out of the bottom). Moves faster than walking. Sponsored by Miwsky, Chudy, and Dawid. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|motorcycle|`oGrowley Motorcycle``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Growley Motorcycle.<CR><CR>`5Description:`` The coolest motorcycles available are Growley Dennisons. Get a sporty blue one today! It even moves faster than walking, which is pretty good for a motorcycle. `4Not available any other way!``|0|6|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|monkey_on_back|`oMonkey On Your Back``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Monkey On Your Back.<CR><CR>`5Description:`` Most people work really hard to get rid of these, but hey, if you want one, it's available! `4But not available any other way!`` Sponsored by SweGamerHD's subscribers, Kizashi, and Inforced. `#Note: This is a neck item, not a back item. He's grabbing your neck!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|carrot_sword|`oCarrot Sword``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Carrot Sword.<CR><CR>`5Description:`` Razor sharp, yet oddly tasty. This can carve bunny symbols into your foes! `4Not available any other way!`` Sponsored by MrMehMeh.|0|3|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|red_bicycle|`oRed Bicycle``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Red Bicycle.<CR><CR>`5Description:`` It's the environmentally friendly way to get around! Ride this bicycle at high speed hither and zither throughout Growtopia. `4Not available any other way!``|0|5|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fire_truck|`oFire Truck``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Fire Truck.<CR><CR>`5Description:`` Race to the scene of the fire in this speedy vehicle! `4Not available any other way!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|pet_slime|`oPet Slime``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Pet Slime.<CR><CR>`5Description:`` What could be better than a blob of greasy slime that follows you around? How about a blob of greasy slime that follows you around and spits corrosive acid, melting blocks more quickly than a normal punch? `4Not available any other way!``|0|4|100000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dabstep_shoes|`oDabstep Low Top Sneakers``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Dabstep Low Top Sneakers.<CR><CR>`5Description:`` Light up every footfall and move to a better beat with these dabulous shoes! When you're wearing these, the world is your dance floor! `4Not available any other way!``|0|2|30000|0|||-1|-1||-1|-1||1||||||0|0|\n");
								else if (item == "itempack") {
									string second = "\nadd_button|signal_jammer|`oSignal Jammer``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Signal Jammer.<CR><CR>`5Description:`` Get off the grid! Install a `$Signal Jammer``! A single punch will cause it to whir to life, tireless hiding your world and its population from pesky snoopers - only those who know the world name will be able to enter. `5It's a perma-item, is never lost when destroyed.``|1|6|2000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|punch_jammer|`oPunch Jammer``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Punch Jammer.<CR><CR>`5Description:`` Tired of getting bashed around? Set up a Punch Jammer in your world, and people won't be able to punch each other! Can be turned on and off as needed. `5It's a perma-item, is never lost when destroyed.``|0|4|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|zombie_jammer|`oZombie Jammer``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Zombie Jammer.<CR><CR>`5Description:`` Got a parkour or race that you don't want slowed down? Turn this on and nobody can be infected by zombie bites in your world. It does not prevent direct infection by the g-Virus itself though. `5It's a perma-item, is never lost when destroyed.``|0|5|15000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|starship_blast|`oImperial Starship Blast``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Imperial Starship Blast.<CR><CR>`5Description:`` Command your very own Starship and explore the cosmos! This blast contains one of 3 possible Imperial ship types - which will you get? Note: Each Starship comes with a full tank of gas, an Imperial Helm - Mk. I, Imperial Reactor - Mk. I and an Imperial Viewscreen - Mk. I, so you'll be all set for your adventure among the stars! Note: A Starship also comes with an assortment of space-age blocks!|0|1|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|surg_blast|`oSurgWorld Blast``|interface/large/store_buttons/store_buttons27.rttex|`2You Get:`` 1 SurgWorld Blast and 1 Caduceaxe.<CR><CR>`5Description:`` Your gateway to a world of medical wonders! SurgWorld is a place of care and healing, with all kinds of interesting blocks, top tips on how to treat people with surgery, and an increased chance of getting maladies while you work! Also comes with 1 Caduceaxe to extract Vaccine Drops from blocks. `6Warning:`` May break when extracting vaccine.|0|2|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|bountiful_blast|`oBountiful Blast``|interface/large/store_buttons/store_buttons27.rttex|`2You Get:`` 1 Bountiful Blast.<CR><CR>`5Description:`` Enter a world of fertile soil, cheerful sunshine and lush green hills, and bountiful new trees! This blast is your ticket to a different kind of farming!|0|3|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|thermo_blast|`oThermonuclear Blast``|interface/large/store_buttons/store_buttons8.rttex|`2You Get:`` 1 Thermonuclear Blast.<CR><CR>`5Description:`` This supervillainous device will blast you to a new world that has been scoured completely empty - it contains nothing but Bedrock and a White Door. Remember: When using this, you are creating a NEW world by typing in a new name. It would be irresponsible to let you blow up an entire existing world.|0|5|15000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|antigravity_generator|`oAntigravity Generator``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 Antigravity Generator.<CR><CR>`5Description:`` Disables gravity in your world when activated! Well, it reduces gravity, and lets everybody jump as much as they want! `5It's a perma-item - never lost when destroyed! `4Not available any other way!````|0|3|450000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|building_blocks_machine|`oBuilding Blocks Machine``|interface/large/store_buttons/store_buttons26.rttex|`2You Get:`` 1 Building Blocks Machine.<CR><CR>`5Description:`` Eager to add some new building materials to your construction stockpile? Tired of collecting them from random worlds and weirdos? Well, pop this beauty in your world and it'll start cranking out awesome blocks in no time! Contains the `5RARE Creepy Baby Block and Digital Dirt`` amongst a heap of other new blocks! Careful, though - blocks don't just come from nothing, and this machine will eventually run out of power once it makes a bunch!|0|3|8000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|builders_lock|`oBuilder's Lock``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 Builders Lock.<CR><CR>`5Description:`` Protect up to `$200`` tiles. Wrench the lock to limit it - it can either only allow building, or only allow breaking! `5It's a perma-item, is never lost when destroyed.``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|weather_sunny|`oWeather Machine - Sunny``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Weather Machine - Sunny.<CR><CR>`5Description:`` You probably don't need this one... but if you ever have a desire to turn a sunset or desert world back to normal, grab a Sunny Weather Machine to restore the default Growtopia sky! `5It's a perma-item, is never lost when destroyed.``|0|5|1000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_night|`oWeather Machine - Night``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Weather Machine - Night.<CR><CR>`5Description:`` You might not call it weather, but we do! This will turn the background of your world into a lovely night scene with stars and moon. `5It's a perma-item, is never lost when destroyed.``|0|6|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_arid|`oWeather Machine - Arid``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Weather Machine - Arid.<CR><CR>`5Description:`` Want your world to look like a cartoon desert? This will turn the background of your world into a desert scene with all the trimmings. `5It's a perma-item, is never lost when destroyed.``|0|7|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_rainy|`oWeather Machine - Rainy City``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Weather Machine - Rainy City.<CR><CR>`5Description:`` This will turn the background of your world into a dark, rainy city scene complete with sound effects. `5It's a perma-item, is never lost when destroyed.``|0|5|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_warp|`oWeather Machine - Warp Speed``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Weather Machine - Warp Speed.<CR><CR>`5Description:`` This Weather Machine will launch your world through space at relativistic speeds, which will cause you to age more slowly, as well as see stars flying by rapidly in the background. `5It's a perma-item, is never lost when destroyed.``|0|3|10000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|mars_blast|`oMars Blast``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Mars Blast.<CR><CR>`5Description:`` Blast off to Mars!  This powerful rocket ship will launch you to a new world set up like the surface of Mars, with a special martian sky background, and unique terrain not found elsewhere in the solar system. Mars even has lower gravity than Growtopia normally does! Remember: When using this, you are creating a NEW world by typing in a new name. You can't convert an existing world to Mars, that would be dangerous.|0|7|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|undersea_blast|`oUndersea Blast``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Undersea Blast.<CR><CR>`5Description:`` Explore the ocean!  This advanced device will terraform a new world set up like the bottom of the ocean, with a special ocean background, and special blocks like Seaweed, Coral, Jellyfish, Sharks, and maybe a special surprise... Remember, by using this you are creating a NEW world by typing in a new name. You can't convert an existing world to an ocean, that would be dangerous.|0|7|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|cave_blast|`oCave Blast``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 Cave Blast.<CR><CR>`5Description:`` This explosive device will punch a hole in the ground, giving you a dark cavern to explore. There are even rumors of treasure and the entrance to ancient mines, hidden deep in the caves... but make sure you bring a World Lock. The blasted world is not locked when it's created, so lock it before somebody shows up! Remember: When using this, you are creating a NEW world by typing in a new name. You can't convert an existing world to a cave, that would be dangerous.|0|2|30000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|weather_stuff|`oWeather Machine - Stuff``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 Weather Machine - Stuff.<CR><CR>`5Description:`` This is the most fun weather imaginable - Choose any item from your inventory, adjust some settings, and watch it rain down from the sky! Or up, if you prefer reversing the gravity. `5It's a perma-item, is never lost when destroyed.``|0|6|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_jungle|`oWeather Machine - Jungle``|interface/large/store_buttons/store_buttons16.rttex|`2You Get:`` 1 Weather Machine - Jungle.<CR><CR>`5Description:`` This weather machine will turn the background of your world into a steamy jungle. `5It's a perma-item, is never lost when destroyed.``|0|5|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|weather_backgd|`oWeather Machine - Background``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 Weather Machine - Background.<CR><CR>`5Description:`` This amazing device can scan any Background Block, and will make your entire world look like it's been filled with that block. Also handy for hiding music notes! `5It's a perma-item, is never lost when destroyed.``|0|1|150000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|digital_rain_weather|`oWeather Machine - Digital Rain``|interface/large/store_buttons/store_buttons22.rttex|`2You Get:`` 1 Weather Machine - Digital Rain.<CR><CR>`5Description:`` Take the grow pill, and we'll show you how deep the rabbit hole goes! Splash the scrolling code of creation across the skies of your worlds. They say you learn to understand it after a while... Note: You can only have one of these per world. `5It's a perma-item, is never lost when destroyed.``|0|6|30000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|treasure_blast|`oTreasure Blast``|interface/large/store_buttons/store_buttons26.rttex|`2You Get:`` 1 Treasure Blast.<CR><CR>`5Description:`` Enter a world of snow-capped peaks and long-forgotten mysteries! Riddles and secrets - and a ton of treasure - await those who brave this blast's blocks! Remember, when you use this, it'll create a new world by typing in a new name! No sense in searching for clues to great treasures in well-trod worlds, is there?|0|6|10000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|infinity_weather_machine|`oInfinity Weather Machine``|interface/large/store_buttons/store_buttons32.rttex|`2You Get:`` 1 Infinity Weather Machine.<CR><CR>`5Description:`` Imagine being able to predict the weather?! Well, with the Infinity Weather Machine you can! Add multiple Weather Machines to this machine and have them play on a loop, like a weather mix tape, kind of!|0|3|50000|0|||-1|-1||-1|-1||1||||||0|0|\n";
									p2.Insert("set_description_text|`2Item Packs!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||1|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_button|world_lock|`oWorld Lock``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 World Lock.<CR><CR>`5Description:`` Become the undisputed ruler of your domain with one of these babies.  It works like a normal lock except it locks the `$entire world``!  Won't work on worlds that other people already have locks on. You can even add additional normal locks to give access to certain areas to friends. `5It's a perma-item, is never lost when destroyed.``  `wRecycles for 200 Gems.``|0|7|2000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|world_lock_10_pack|`oWorld Lock Pack``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 10 World Locks.<CR><CR>`5Description:`` 10-pack of World Locks. Become the undisputed ruler of up to TEN kingdoms with these babies. Each works like a normal lock except it locks the `$entire world``!  Won't work on worlds that other people already have locks on. You can even add additional normal locks to give access to certain areas to friends. `5It's a perma-item, is never lost when destroyed.`` `wEach recycles for 200 Gems.``|0|3|20000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|small_lock|`oSmall Lock``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Small Lock.<CR><CR>`5Description:`` Protect up to `$10`` tiles.  Can add friends to the lock so others can edit that area as well. `5It's a perma-item, is never lost when destroyed.``|1|3|50|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|big_lock|`oBig Lock``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Big Lock.<CR><CR>`5Description:`` Protect up to `$48`` tiles.  Can add friends to the lock so others can edit that area as well. `5It's a perma-item, is never lost when destroyed.``|1|1|200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|huge_lock|`oHuge Lock``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Huge Lock.<CR><CR>`5Description:`` Protect up to `$200`` tiles.  Can add friends to the lock so others can edit that area as well. `5It's a perma-item, is never lost when destroyed.``|0|4|500|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|door_pack|`oDoor And Sign Hello Pack``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Door and 1 Sign.<CR><CR>`5Description:`` Own your very own door and sign! This pack comes with one of each. Leave cryptic messages and create a door that can open to, well, anywhere.|0|3|15|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|door_mover|`oDoor Mover``|interface/large/store_buttons/store_buttons8.rttex|`2You Get:`` 1 Door Mover.<CR><CR>`5Description:`` Unsatisfied with your world's layout?  This one-use device can be used to move the White Door to any new location in your world, provided there are 2 empty spaces for it to fit in. Disappears when used. `2Only usable on a world you have World Locked.``|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|vending_machine|`oVending Machine``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Vending Machine.<CR><CR>`5Description:`` Tired of interacting with human beings? Try a Vending Machine! You can put a stack of items inside it, set a price in World Locks, and people can buy from the machine while you sit back and rake in the profits! `5It's a perma-item, is never lost when destroyed, and it is not available any other way.``|0|6|8000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|digi_vend|`oDigiVend Machine``|interface/large/store_buttons/store_buttons29.rttex|`2You Get:`` 1 DigiVend Machine.<CR><CR>`5Description:`` Get with the times and go digital! This wired vending machine can connect its contents to Vending Hubs AND the multiversal economy, providing a unified shopping experience along with price checks to help you sell your goods! All that, and still no human-related hassle! Use your wrench on this to stock it with an item and set a price in World Locks. Other players will be able to buy from it! Only works in World-Locked worlds.|0|2|12000|0|||-1|-1||-1|-1||1||||||0|0|"*/""/*"\nadd_button|checkout_counter|`oVending Hub - Checkout Counter``|interface/large/store_buttons/store_buttons29.rttex|`2You Get:`` 1 Vending Hub.<CR><CR>`5Description:`` Your one-stop shop! This vending hub will collect and display (and let shoppers buy) the contents of ALL DigiVends in its row or column (wrench it to set which the direction)! Wow! Now that's a shopping experience we can all enjoy! Note: Only works in World-Locked worlds.|0|3|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|change_addr|`oChange of Address``|interface/large/store_buttons/store_buttons12.rttex|`2You Get:`` 1 Change of Address.<CR><CR>`5Description:`` Don't like the name of your world? You can use up one of these to trade your world's name with the name of any other world that you own. You must have a `2World Lock`` in both worlds. Go lock up that empty world with the new name you want and swap away!|0|6|20000|0|||-1|-1||-1|-1||1||||||0|0|"*/"" + second);
								}
								else if (item == "bigitems") p2.Insert("set_description_text|`2Awesome Items!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||1|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_button|5seed|`oSmall Seed Pack``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 1 Small Seed Pack.<CR><CR>`5Description:`` Contains one Small Seed Pack. Open it for `$5`` randomly chosen seeds, including 1 rare seed! Who knows what you'll get?!|1|4|100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ssp_10_pack|`oSmall Seed Pack Collection``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 10 Small Seed Packs.<CR><CR>`5Description:`` Open each one for `$5`` randomly chosen seeds apiece, including 1 rare seed per pack! Who knows what you'll get?!|0|4|1000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|rare_seed|`oRare Seed Pack``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 5 Randomly Chosen Rare Seeds.<CR><CR>`5Description:`` Expect some wondrous crops with these!|1|7|1000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|grow_spray|`o5-pack of Grow Spray Fertilizer``|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 5 Grow Spray Fertilizers.<CR><CR>`5Description:`` Why wait?!  Treat yourself to a `$5-pack`` of amazing `wGrow Spray Fertilizer`` by GrowTech Corp.  Each bottle instantly ages a tree by `$1 hour``.|0|6|200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|deluxe_grow_spray|`oDeluxe Grow Spray``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Deluxe Grow Spray.<CR><CR>`5Description:`` GrowTech's new `$Deluxe`` `wGrow Spray`` instantly ages a tree by `$24 hours`` per bottle! That's somewhere around 25 times as much as regular Grow Spray!|0|2|900|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|bountiful_seed_pack|`oBountiful Seed Pack``|interface/large/store_buttons/store_buttons28.rttex|`2You Get:`` 1 Bountiful Seed Pack.<CR><CR>`5Description:`` Contains `$5`` randomly chosen bountiful seeds, including 1 rare seed! Who knows what you'll get?!|0|4|1000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|basic_splice|`oBasic Splicing Kit``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 10 Rock Seeds and 10 Random Seeds of Rarity 2.<CR><CR>`5Description:`` The basic seeds every farmer needs.|0|3|200|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|surgical_kit|`oSurgical Kit``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 `#Rare Heart Monitor``, 1 Hospital Bed, 1 Train-E Bot, 5 of each of the 13 different Surical Tools and 10 Med-a-Checks.<CR><CR>`5Description:`` Get all the tools you need to become Chief of Surgery at Growtopia General Hospital! `#Rare`` Heart Monitor that lets people know when you are online, Hospital Bed that lets you perform surgery on anybody laying (or standing) on it, Med-a-Checks to identify patients with maladies, The Train-E bot to practice on, and 5 each of the thirteen different Surgical Tools you'll need to do that surgery!|0|2|12000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|star_supplies|`oGalactic Goodies``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 60 Star Tools and 25 Star Fuel.<CR><CR>`5Description:`` Get all the Star Tools you need to boldly go where no Growtopian has gone! Use these to help you command a starship and seek victory in the Galactic Nexus! You'll get 5 each of the 12 Star Tools you'll need to complete missions and some bonus Star Fuel to help power a Starship!|0|0|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fishin_pack|`oFishin' Pack``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Fishing Rod, 5 Wiggly Worms, 1 Hand Drill, 1 Nuclear Detonator,  1 `#Rare Tackle Box``, 10 Fish Tanks and 1 `#Rare Fish Tank Port`` .<CR><CR>`5Description:`` Relax and sit by the shore... this pack includes a Fishing Rod, Wiggly Worms for bait, Hand Drill, Nuclear Detonator, and a `#Rare`` Tackle Box which provides you with more free bait every two days, Fish Tanks, and a `#Rare`` Fish Tank Port to put the fish you catch into your fish tank!|0|0|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fish_training_pack|`oFish Trainin' Pack``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 2 Fish Flakes, 2 Fish Medicine, AND 1 `#Rare Training Port``.<CR><CR>`5Description:`` Get ready to train your favorite fish! Use the Training Port to put a perfect fish into your fish tank for training!|0|7|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fish_flakes|`oFish Flakes``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 5 Fish Flakes.<CR><CR>`5Description:`` Every fish adores these tasty flakes! Give a pinch to your Training Fish and fill their scaly bellies with aquatic goodness! Take the guesswork out of finnicky feedings with a treat you know they'll love!|0|2|7500|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fish_medicine|`oFish Medicine``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 1 Fish Medicine.<CR><CR>`5Description:`` Make a sick Training Fish bright and healthy with this healing potion. One dose is enough to make even the sickest fish all better!|0|0|1500|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fish_reviver|`oFish Reviver``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 1 `#Rare Fish Reviver``.<CR><CR>`5Description:`` Resurrect a dead Training Fish with a revivifying zap from this `#Rare`` Fish Reviver! One dose is enough to reach beyond the veil and bring a fish back from the dead! Comes with a 100% zombie-free guarantee!|0|1|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|crime_wave|`oCrime Wave``|interface/large/store_buttons/store_buttons12.rttex|`2You Get:`` 5 Random Superpower Cards and 1 `#Rare Crime Wave``.<CR><CR>`5Description:`` Get powered up with random Superpower Cards, and what good would that be without a `#Rare`` Crime Wave to use them on? A Crime Wave is a one-use item that calls four villains to your world for you to battle. `6Beware:`` Villains only stick around for 24 hours once they appear.|0|5|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|silkworm|`oSilkworm``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Silk Worm.<CR><CR>`5Description:`` It's the newest cuddly pet from Growtech Pharma! Thanks to genetic engineering, you can now raise your own giant mutant silkworm. They'll eat almost any food, but don't forget to give them water too! And if they get sick, you'll need to have some Antidotes on hand. `6Warning:`` `9Silkworms are living creatures. They will not live forever! Take good care of them, and enjoy them while you can.`` `4Not available any other way``.|0|7|7000|0|||-1|-1||-1|-1||1||||||0|0|"*/"\nadd_button|geiger|`oGeiger Counter``|interface/large/store_buttons/store_buttons12.rttex|`2You Get:`` 1 Geiger Counter.<CR><CR>`5Description:`` With this fantabulous device, you can detect radiation around you. It bleeps red, then yellow, then green as you get closer to the source. Who knows what you might find? `4Not available any other way!``|0|1|25000|0|||-1|-1||-1|-1||1||||||0|0|"/*"\nadd_button|zombie_pack|`oZombie Defense Pack``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 1 `#Rare Sawed-Off Shotgun``, 1 Combat Vest, 1 Zombie Stompin' Boots, 3 Traffic Barricades, 1 Military Radio, 1 Antidote, 3 Toxic Waste Barrels, 3 Biohazard Signs, 3 Tombstones and 1 `#Rare Deadly G-Virus``!.<CR><CR>`5Description:`` The zombie invasion has come! Protect yourself with all the esential zombie fighting gear and best of all, you get an Antidote to cure yourself! Also includes the deadly g-Virus itself to infect your friends with!|0|4|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|boo_pack|`oB.O.O. Training Pack``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 `#Rare Spectral Goggles``, 1 Neutron Gun, 1 Neutron Pack and 10 Ghost Jars <CR><CR>`5Description:`` It looks like Growtopia is under siege by ghosts! Well, the `9Battlers Of the Otherworldly`` are hiring! You'll have to earn your uniform, but this pack includes all the tools you need to actually capture ghosts! Including `#Rare`` Spectral Goggles (all the better to see them with!)and a Neutron Pack to corral the ghosts, of course 10 Ghost Jars to catch them in.|0|4|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ectojuicer|`oEctoJuicer``|interface/large/store_buttons/store_buttons20.rttex|`2You Get:`` 1 EctoJuicer.<CR><CR>`5Description:`` Infuse your muscles with the unearthly might of the Other Side! This spectral potion gives you the strength to wring every last drop of ectoplasm from a defeated Boss Ghost, granting you an EXTRA Boss Goo after a successful banishing!|0|0|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ghost_hunting|`oGhost Hunter's Pack``|interface/large/store_buttons/store_buttons19.rttex|`2You Get:`` At least 5 Ghost Jars and 1 Bonus Item.<CR><CR>`5Description:`` Essentials for Ghost Hunting! Guaranteed to have at least 5x Ghost Jars, plus one or more bonus items! Prizes can include: Neutron Focus Cores, Containment Field Power Nodes, EXTRA Ghost Jars, Ghost Traps, Spirit Boards, and maybe even a Dark Spirit Board!|0|7|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|chemsynth|`oChemsynth Pack``|interface/large/store_buttons/store_buttons16.rttex|`2You Get:`` 1 `#Rare Chemsynth Processor``, 10 Chemsynth Tanks and 1 Chemsynth Replicator, 1 Chemsynth Catalyst, 1 Chemsynth Solvent, 1 Chemsynth Centrifuge, 1 Chemsynth Stirrer.<CR><CR>`5Description:`` Tired of the lousy chemicals nature has to offer? Create new synthetic ones! With a `#Rare`` Chemsynth Processor, Chemsynth Tanks, and one each of the five Chemsynth tools, you can be whipping up Synthetic Chemicals in no time. `6Warning:`` Chemsynth solving is a pretty tricky puzzle, and it costs a whole bunch of the five basic chemicals (R, G, B, P, and Y) to complete.|0|4|10000|0|||-1|-1||-1|-1||1|||||"*/"|0|0|\n");
								else if (item == "weather") p2.Insert("set_description_text|`2Weather Machines!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|1|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|\nadd_button|race_pack|`oRacing Action Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 1 Racing Start Flag, 1 Racing End Flag, 2 Checkpoints, 2 Big Old Sideways Arrows, 1 Big Old Up Arrow, 1 Big Old Down Arrow, 1 WristBand, 1 HeadBand, 1 Sports Ball Jersey and 1 Air Robinsons.<CR><CR>`5Description:`` Get all you need to host races in your worlds! You'll win the races too, with new Air Robinsons that make you run faster!|0|7|3500|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|school_pack|`oEducation Pack``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 10 ChalkBoards, 3 School Desks, 20 Red Bricks, 1 Bulletin Board, 10 Pencils, 1 Growtopia Lunchbox, 1 Grey Hair Bun, 1 Apple and 1 Random School Uniform Item.<CR><CR>`5Description:`` If you want to build a school in Growtopia, here's what you need!|0|0|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dungeon_pack|`oDungeon Pack``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 20 Grimstone, 20 Blackrock Wall, 20 Iron Bars, 3 Jail Doors, 3 Skeletons, 1 Headsman's Axe, 1 Worthless Rags. 5 Torches and a `#Rare Iron Mask!``.<CR><CR>`5Description:`` Lock up your enemies in a dank dungeon! Of course they can still leave whenever they want. But they won't want to, because it looks so cool! Iron Mask muffles your speech!|0|1|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fantasy_pack|`oFantasy Pack``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Mystical Wizard Hat Seed, 1 Wizards Robe, 1 Golden Sword, 1 Elvish Longbow, 10 Barrels, 3 Tavern Signs, 3 Treasure Chests and 3 Dragon Gates.<CR><CR>`5Description:`` Hear ye, hear ye! It's a pack of magical wonders!|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|vegas_pack|`oVegas Pack``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 10 Neon Lights, 1 Card Block Seed, 1 `#Rare Pink Cadillac`` 4 Flipping Coins, 1 Dice Block, 1 Gamblers Visor, 1 Slot Machine, 1 Roulette Wheel and 1 Showgirl Hat, 1 Showgirl top and 1 Showgirl Leggins.<CR><CR>`5Description:`` What happens in Growtopia stays in Growtopia!|0|5|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|city_pack|`oCity Pack``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 10 Sidewalks, 3 Street Signs, 3 Streetlamps, 10 Gothic Building tiles, 10 Tenement Building tiles, 10 Fire Escapes, 3 Gargoyles, 10 Hedges, 1 Blue Mailbox, 1 Fire Hydrant and A `#Rare`` `2ATM Machine``.<CR><CR>`5Description:`` Life in the big city is rough but a `#Rare`` `2ATM Machine`` that dishes out gems once a day is very nice!|0|0|8000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|west_pack|`oWild West Pack``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Cowboy Hat, 1 Cowboy Boots, 1 War Paint, 1 Face Bandana, 1 Sheriff Vest, 1 Layer Cake Dress,  1 Corset, 1 Kansas Curls, 10 Western Building 1 Saloon Doors, 5 Western Banners, 1 Buffalo, 10 Rustic Fences, 1 Campfire and 1 Parasol.<CR><CR>`5Description:`` Yippee-kai-yay! This pack includes everything you need to have wild time in the wild west! The Campfire plays cowboy music, and the `#Parasol`` lets you drift down slowly. Special bonus: A `#Rare`` `2Six Shooter`` to blast criminals with!|0|2|8000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|astro_pack|`oAstro Pack``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Astronaut Helmet, 1 Space Suit, 1 Space Pants, 1 Moon Boots, 1 Rocket Thruster, 1 Solar Panel, 6 Space Connectors, 1 Porthole, 1 Compu Panel, 1 Forcefield and 1 `#Rare`` `2Zorbnik DNA``.<CR><CR>`5Description:`` Boldly go where no Growtopian has gone before with an entire Astronaut outfit. As a special bonus, you can have this `#Rare`` `2Zorbnik DNA`` we found on a distant planet. It doesn't do anything by itself, but by trading with your friends, you can collect 10 of them, and then... well, who knows?|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|prehistoric_pack|`oPrehistoric Pack``|interface/large/store_buttons/store_buttons8.rttex|`2You Get:`` 1 Caveman Club, 1 Cave Woman Hair, 1 Caveman Hair, 1 Sabertooth Toga, 1 Fuzzy Bikini Top, 1 Fuzzy Bikni Bottom, 1 Cavewoman Outfit, 10 Cliffside, 5 Rock Platforms, 1 Cave Entrance, 3 Prehistoric Palms and 1 `#Rare Sabertooth Growtopian``.<CR><CR>`5Description:`` Travel way back in time with this pack, including full Caveman and Cavewoman outfits and `#Rare Sabertooth Growtopian`` (that's a mask of sorts). Unleash your inner monster!|0|0|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|shop_pack|`oShop Pack``|interface/large/store_buttons/store_buttons8.rttex|`2You Get:`` 4 Display Boxes, 1 For Sale Sign, 1 Gem Sign, 1 Exclamation Sign, 1 Shop Sign, 1 Open Sign, 1 Cash Register, 1 Mannequin and 1 Security Camera.<CR><CR>`5Description:`` Run a fancy shop with these new items! Advertise your wares with an Open/Closed Sign you can switch with a punch, a Cash Register, a Mannequin you can dress up to show off clothing, and a `#Rare`` Security Camera, which reports when people enter and take items!|0|7|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|home_pack|`oHome Pack``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Television, 4 Couches, 2 Curtains, 1 Wall Clock, 1 Microwave, 1 Meaty Apron, 1 Ducky Pants, 1 Ducky top and 1 Eggs Benedict.<CR><CR>`5Description:`` Welcome home to Growtopia! Decorate with a Television, Window Curtains, Couches, a `#Rare`` Wall Clock that actually tells time, and a Microwave to cook in. Then dress up in a Meaty Apron and Ducky Pajamas to sit down and eat Eggs Benedict, which increases the amount of XP you earn!|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|cinema_pack|`oCinema Pack``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 ClapBoard, 1 Black Beret, 1 3D Glasses, 6 Theater Curtains, 6 Marquess Blocks, 1 Directors Chair, 4 Theater Seats, 6 Movie Screens, 1 Movie Camera and 1 `#Rare GHX Speaker``.<CR><CR>`5Description:`` It's movie time! Everything you need for the big screen experience including a `#Rare GHX Speaker`` that plays the score from Growtopia: The Movie.|0|2|6000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|adventure_pack|`oAdventure Pack``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 4 Gateways to Adventure, 4 Path Markers, 1 Lazy Cobra, 1 Adventure Brazier, 4 Adventure Barriers, 1 Rope, 1 Torch, 1 Key, 1 Golden Idol, 1 `#Rare Adventuring Mustache``, 1 Explorer's Ponytail and 1 Sling Bag .<CR><CR>`5Description:`` Join Dr. Exploro and her father (also technically Dr. Exploro) as they seek out adventure! You can make your own adventure maps with the tools in this pack.|0|7|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|rockin_pack|`oRockin' Pack``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 3 `#Rare Musical Instruments`` Including A Keytar, a Bass Guitar and Tambourine, 1 Starchild Make Up, 1 Rockin' Headband, 1 Leopard Leggings, 1 Shredded Ts-Shirt, 1 Drumkit, 6 Stage Supports, 6 Mega Rock Speakers and 6 Rock n' Roll Wallpaper.<CR><CR>`5Description:`` ROCK N' ROLL!!! Play live music in-game! We Formed a Band! Growtopia makes me want to rock out.|0|0|9999|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|game_pack|`oGame Pack``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 `#Rare Game Generator``,  4 Game Blocks, 4 Game Flags, 4 Game Graves and 4 Game Goals.<CR><CR>`5Description:`` Growtopia's not all trading and socializing! Create games for your friends with the Game Pack (and a lot of elbow grease).|0|6|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|superhero|`oSuperhero Pack``|interface/large/store_buttons/store_buttons12.rttex|`2You Get:`` 1 Mask, 1 Shirt, 1 Boots, 1 Tights, 1 Cape, `#Rare Super Logos`` or `#Rare Utility Belt`` and 1 `2Phone Booth``.<CR><CR>`5Description:`` Battle the criminal element in Growtopia with a complete random superhero outfit including a cape that lets you double jump. Each of these items comes in one of six random colors. You also get one of 5 `#Rare`` Super Logos, which automatically match the color of any shirt you wear or a `#Rare`` Utility Belt... of course use the `2Phone Booth`` to change into your secret identity!|0|0|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fashion_pack|`oFashion Pack``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 3 Random Clothing Items, 3 Jade Blocks and 1 `#Rare Spotlight``.<CR><CR>`5Description:`` The hottest new looks for the season are here now with 3 random Fashion Clothing (dress, shoes, or purse), Jade Blocks to pose on, and a `#Rare`` Spotlight to shine on your fabulousness.|0|0|6000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|sportsball_pack|`oSportsball Pack``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 2 Basketball Hoops, 2 Sporty Goals, 5 Stadiums, 5 Crowded Stadiums, 10 Field Grass, 1 Football Helmet, 1 Growies Cap, 1 Ref's Jersey, 1 World Cup Jersey, 1 `#Rare Sports Item`` or `#Rare Growmoji!``.<CR><CR>`5Description:`` We like sports and we don't care who knows! This pack includes everything you need to get sporty! Use the Sports Items to launch Sportsballs at each other.|0|1|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|firefighter|`oFirefighter Pack``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Yellow Helmet, 1 Yellow Jacket, 1 Yellow Pants, 1 Firemans Boots, 1 Fire Hose, and 1 `#Rare Firehouse`` .<CR><CR>`5Description:`` Rescue Growtopians from the fire! Includes a full Yellow Firefighter Outfit, Fire Hose and a `#Rare Firehouse``, which will protect your own world from fires.|0|1|10000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|steampack|`oSteampack``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 10 Steam Tubes, 2 Steam Stompers, 2 Steam Organs, 2 Steam Vents, 2 Steam Valves and 1 `#Rare Steampunk Top Hat``.<CR><CR>`5Description:`` Steam! It's a wondrous new technology that lets you create paths of Steam Blocks, then jump on a Steam Stomper to launch a jet of steam through the path, triggering steam-powered devices. Build puzzles, songs, parkour challenges, and more!|0|6|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|paintbrush|`oPainter's Pack``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 `#Rare Paintbrush`` and 20 Random Colored Paint Buckets.<CR><CR>`5Description:`` Want to paint your world? This pack includes 20 buckets of random paint colors (may include Varnish, to clean up your messes)! You can paint any block in your world different colors to personalize it.|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|paleo_kit|`oPaleontologist's Kit``|interface/large/store_buttons/store_buttons16.rttex|`2You Get:`` 5 Fossil Brushes, 1 Rock Hammer, 1 Rock Chisel, 1 Blue Hardhat and 1 `#Rare Fossil Prep Station``.<CR><CR>`5Description:`` If you want to dig up fossils, this is the kit for you! Includes everything you need! Use the prepstation to get your fossils ready for display.|0|0|20000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|robot_starter_pack|`oCyBlocks Starter Pack``|interface/large/store_buttons/store_buttons18.rttex|`2You Get:`` 1 `5Rare ShockBot`` and 10 random movement commands.<CR><CR>`5Description:`` CyBlocks Starter Pack includes one `5Rare`` ShockBot and 10 random movement commands to use with it. `5ShockBot`` is a perma-item, is never lost when destroyed.|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|robot_command_pack|`oCyBlocks Command Pack``|interface/large/store_buttons/store_buttons19.rttex|`2You Get:`` 10 Random CyBlock Commands.<CR><CR>`5Description:`` Grants 10 random CyBlock Commands to help control your CyBots!|0|2|2000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|robot_pack|`oCyBot Pack``|interface/large/store_buttons/store_buttons19.rttex|`2You Get:`` 1 `5Rare CyBot``!<CR><CR>`5Description:`` Grants one random `5Rare`` CyBot! Use CyBlock Commands to send these mechanical monsters into action! `5Note: Each CyBot is a perma-item, and will never be lost when destroyed.``|0|3|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|gang_pack|`oGangland Style``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 1 Fedora, 1 Dames Fedora, 1 Pinstripe Suit with Pants, 1 Flapper Headband with Dress, 1 Cigar, 1 Tommy Gun, 1 Victola and 10 Art Deco Blocks .<CR><CR>`5Description:`` Step into the 1920's with a Complete Outfit, a Tommygun, a Victrola that plays jazz music, and 10 Art Deco Blocks. It's the whole package!|0|6|5000|0|||-1|-1||-1|-1||1||||||0|0|\n");
								else if (item == "token") p2.Insert("set_description_text|`2Spend your Growtokens!`` (You have `50``) You earn Growtokens from Crazy Jim and Sales-Man. Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||0|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||1|2|0|0||||-1|-1|||0|0|\nadd_button|challenge_timer|`oChallenge Timer``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 Challenge Timer.<CR><CR>`5Description:`` Get more people playing your parkours with this secure prize system. You'll need a `#Challenge Start Flag`` and `#Challenge End Flag`` as well (not included). Stock prizes into the Challenge Timer, set a time limit, and watch as players race from start to end. If they make it in time, they win a prize!|0|5|-5|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|xp_potion|`oExperience Potion``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Experience Potion.<CR><CR>`5Description:`` This `#Untradeable`` delicious fizzy drink will make you smarter! 10,000 XP smarter instantly, to be exact.|0|2|-10|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|megaphone|`oMegaphone``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 Megaphone.<CR><CR>`5Description:`` You like broadcasting messages, but you're not so big on spending gems? Buy a Megaphone with Growtokens! Each Megaphone can be used once to send a super broadcast to all players in the game.|0|7|-10|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|i_love_dirt_shirt|`oI love Dirt Shirt``|interface/large/store_buttons/store_buttons37.rttex|`2You Get:`` 1 I love Dirt Shirt.<CR><CR>`5Description:`` Some people like things to be clean, you're not one of them are you? This item is `#Untradeable``.|4|0|-10|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|growmoji_pack|`oGrowmoji Mystery Box``|interface/large/store_buttons/store_buttons19.rttex|`2You Get:`` 1 Growmoji.<CR><CR>`5Description:`` Express yourself! This mysterious box contains one of five fun growmojis you can use to spice up your chat! Which will you get?|0|1|-15|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|mini_mod|`oMini-Mod``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 Mini-Mod.<CR><CR>`5Description:`` Oh no, it's a Mini-Mod! Punch him to activate (you'll want to punch him!). When activated, he won't allow anyone to drop items in your world.|0|0|-20|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|derpy_star|`oDerpy Star Block``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Derpy Star Block.<CR><CR>`5Description:`` DER IM A SUPERSTAR. This is a fairly ordinary block, except for the derpy star on it. Note: it is not permanent, and it doesn't drop seeds. So use it wisely!|0|3|-30|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dirt_gun|`oBLYoshi's Free Dirt``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 BLYoshi's Free Dirt.<CR><CR>`5Description:`` \"Free\" might be stretching it, but hey, once you buy this deadly rifle, you can spew out all the dirt you want for free! Note: the dirt is launched at high velocity and explodes on impact. Sponsored by BLYoshi.|0|4|-40|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|nothingness|`oWeather Machine - Nothingness``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Weather Machine - Nothingness.<CR><CR>`5Description:`` Tired of all that fancy weather?  This machine will turn your world completely black. Yup, that's it. Not a single pixel in the background except pure blackness.|0|3|-50|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|spike_juice|`oSpike Juice``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Spike Juice.<CR><CR>`5Description:`` It's fresh squeezed, with little bits of spikes still in it! Drinking this `#Untradeable`` one-use potion will make you immune to Death Spikes and Lava for 5 seconds.|0|5|-60|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|doodad|`oDoodad``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Doodad.<CR><CR>`5Description:`` I have no idea what this thing does. It's something electronic? Maybe?|0|5|-75|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|crystal_cape|`oCrystal Cape``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Crystal Cape.<CR><CR>`5Description:`` This cape is woven of pure crystal, which makes it pretty uncomfortable. But it also makes it magical! It lets you double-jump off of an imaginary Crystal Block in mid-air. Sponsored by Edvoid20, HemeTems, and Aboge.|0|5|-90|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|focused_eyes|`oFocused Eyes``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Focused Eyes.<CR><CR>`5Description:`` This `#Untradeable`` item lets you shoot electricity from your eyes! Wear them with pride, and creepiness.|0|4|-100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|grip_tape|`oGrip Tape``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Grip Tape.<CR><CR>`5Description:`` This is handy for wrapping around the handle of a weapon or tool. It can improve your grip, as well as protect you from cold metal handles. If you aren't planning to craft a weapon that requires Grip Tape, this does you no good at all!|0|5|-100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|cat_eyes|`oCat Eyes``|interface/large/store_buttons/store_buttons23.rttex|`2You Get:`` 1 Cat Eyes.<CR><CR>`5Description:`` Wow, pawesome! These new eyes are the cat's meow, and the purrfect addition to any style.|0|5|-100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|riding_cloud|`oRiding Cloud``|interface/large/store_buttons/store_buttons37.rttex|`2You Get:`` 1 Riding Cloud.<CR><CR>`5Description:`` Bringing the sky to the ground! This item is `#Untradeable``.|3|1|-100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|grow_boy|`oGrowBoy``|interface/large/store_buttons/store_buttons32.rttex|`2You Get:`` 1 Growboy.<CR><CR>`5Description:`` Bask in the nostalgic green screened goodness of the Growboy! A portable gaming device that packs a punch. Now you're playing with GrowPower! Note: The Growboy is `#UNTRADEABLE``.|0|2|-100|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|night_vision|`oNight Vision Goggles``|interface/large/store_buttons/store_buttons15.rttex|`2You Get:`` 1 Night Vision Goggles.<CR><CR>`5Description:`` Scared of the dark? We have a solution. You can wear these goggles just to look cool, but if you also happen to have a D Battery (`4batteries not included``) on you, you will be able to see through darkness like it's not even there! Each D Battery can power your goggles for 1 minute. `2If you are in a world you own, the goggles will not require batteries!`` Note: you can't turn the goggles off without removing them, so you'll be wasting your battery if you wear them in daylight while carrying D Batteries.|0|3|-110|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|muddy_pants|`oMuddy Pants``|interface/large/store_buttons/store_buttons12.rttex|`2You Get:`` 1 Muddy Pants.<CR><CR>`5Description:`` Well, this is just a pair of muddy pants. But it does come with a super secret bonus surprise that is sure to blow your mind!|0|7|-125|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|piranha|`oCuddly Piranha``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Cuddly Piranha.<CR><CR>`5Description:`` This friendly pet piranha won't stay in its bowl!  It just wants to snuggle with your face!|0|0|-150|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|tsed|`oTactical Stealth Espionage Device``|interface/large/store_buttons/store_buttons32.rttex|`2You Get:`` 1 Tactical Stealth Espionage Device.<CR><CR>`5Description:`` This is Growtech's latest innovation on tactical espionage! Using the latest in scientific breakthroughs this device allows you to seamlessly disguise yourself as... a cardboard box! Note: The Tactical Stealth Espionage Device is `#UNTRADEABLE``.|0|1|-150|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|puddy_leash|`oPuddy Leash``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Puddy Leash.<CR><CR>`5Description:`` Puddy is a friendly little kitten who will follow you around forever.|0|7|-180|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|anime_action_hair|`oAnime Action Hair``|interface/large/store_buttons/store_buttons37.rttex|`2You Get:`` 1 Anime Action Hair.<CR><CR>`5Description:`` Lights, camera, ANIME ACTION HAIR! Feel the power from root to tip every time you punch! This item is `#Untradeable``.|4|1|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|golden_axe|`oGolden Pickaxe``|interface/large/store_buttons/store_buttons9.rttex|`2You Get:`` 1 Golden Pickaxe.<CR><CR>`5Description:`` Get your own sparkly pickaxe! This `#Untradeable`` item is a status symbol! Oh sure, it isn't any more effective than a normal pickaxe, but it sparkles!|0|1|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|puppy_leash|`oPuppy Leash``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Puppy Leash.<CR><CR>`5Description:`` Get your own pet puppy! This little dog will follow you around forever, never wavering in her loyalty, thus making her `#Untradeable``.|0|4|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|diggers_spade|`oDigger's Spade``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Digger's Spade.<CR><CR>`5Description:`` This may appear to be a humble shovel, but in fact it is enchanted with the greatest magic in Growtopia. It can smash Dirt or Cave Background in a single hit! Unfortunately, it's worthless at digging through anything else. Note: The spade is `#UNTRADEABLE``.|0|7|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|meow_ears|`oMeow Ears``|interface/large/store_buttons/store_buttons22.rttex|`2You Get:`` 1 Meow Ears.<CR><CR>`5Description:`` Meow's super special ears that everyone can now get! Note: These ears are `#UNTRADEABLE``.|0|0|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|frosty_hair|`oFrosty Hair``|interface/large/store_buttons/store_buttons23.rttex|`2You Get:`` 1 Frosty Hair.<CR><CR>`5Description:`` Coldplay is cold, but you can be freezing! Note: The frosty hair is `#UNTRADEABLE``.|0|0|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|zerkon_helmet|`oEvil Space Helmet``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Evil Space Helmet.<CR><CR>`5Description:`` Zerkon commands a starship too small to actually board - pah, time to rule the galaxy properly! Note: The evil space helmet is `#UNTRADEABLE``.|0|6|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|seils_magic_orb|`oSeil's Magic Orbs``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Seil's Magic Orbs.<CR><CR>`5Description:`` Seil is some kind of evil wizard, now you can be too! Note: These magic orbs are `#UNTRADEABLE``.|0|7|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|atomic_shadow_scythe|`oAtomic Shadow Scythe``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Atomic Shadow Scythe.<CR><CR>`5Description:`` AtomicShadow might actually be evil, now you can try it out! Note: The shadow scythe is `#UNTRADEABLE``.|0|5|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|poseidon_diggers_trident|`oPoseidon's Digger's Trident``|interface/large/store_buttons/store_buttons25.rttex|`2You Get:`` 1 Poseidon's Digger's Trident.<CR><CR>`5Description:`` A gift from the gods. This may appear to be a humble trident, but in fact it has the power of Poseidon himself. It can smash `8Deep Sand`` or `8Ocean Rock`` in a single hit. Unfortunately, you don't get to wield the full might of Poseidon... the trident is worthless at smashing anything else. Note: The trident is `#UNTRADEABLE``.|0|6|-200|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|really_dangerous_pet_llama|`oReally Dangerous Pet Llama``|interface/large/store_buttons/store_buttons32.rttex|`2You Get:`` 1 Really Dangerous Pet Llama.<CR><CR>`5Description:`` This Llama is ready for anything Growtopia throws at it! Armed with a silo of Growtech Missiles, experimental Growtech hardened steel armor and a rather snazzy helmet (Llama's own) this Llama is Dangerous with a capital D! Note: This Really Dangerous Pet Llama is `#UNTRADEABLE``.|0|0|-200|0|||-1|-1||-1|-1||1||||||0|0|\n");
								else if (item == "upgrade_backpack") {
									price = inventory_price(pInfo(peer)->inv.size());
									if (price > pInfo(peer)->gems) {
										packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
										p.Insert("You can't afford `0Upgrade Backpack`` (`w10 Slots``)!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short.");
									}
									else {
										if (pInfo(peer)->inv.size() < 186) {
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You've purchased `0Upgrade Backpack`` (`010 Slots``) for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.");
												p.CreatePacket(peer);
											}
											p.Insert("You've purchased `0Upgrade Backpack (10 Slots)`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.\n\n`5Received: ```0Backpack Upgrade``\n");
											pInfo(peer)->gems -= price;
											{
												packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
												gamepacket_t p;
												p.Insert("OnSetBux");
												p.Insert(pInfo(peer)->gems);
												p.Insert(1);
												p.CreatePacket(peer);
											}
											for (int i_ = 0; i_ < 10; i_++) { // default inv dydis
												Items itm_{};
												itm_.id = 0, itm_.count = 0;
												pInfo(peer)->inv.push_back(itm_);
											}
											send_inventory(peer);
											update_clothes(peer);
											p2.Insert("set_description_text|`2Locks And Stuff!``  Select the item you'd like more info on, or BACK to go back.\nenable_tabs|1\nadd_tab_button|main_menu|Home|interface/large/btn_shop2.rttex||0|0|0|0||||-1|-1|||0|0|\nadd_tab_button|locks_menu|Locks And Stuff|interface/large/btn_shop2.rttex||1|1|0|0||||-1|-1|||0|0|\nadd_tab_button|itempack_menu|Item Packs|interface/large/btn_shop2.rttex||0|3|0|0||||-1|-1|||0|0|\nadd_tab_button|bigitems_menu|Awesome Items|interface/large/btn_shop2.rttex||0|4|0|0||||-1|-1|||0|0|\nadd_tab_button|weather_menu|Weather Machines|interface/large/btn_shop2.rttex|Tired of the same sunny sky?  We offer alternatives within...|0|5|0|0||||-1|-1|||0|0|\nadd_tab_button|token_menu|Growtoken Items|interface/large/btn_shop2.rttex||0|2|0|0||||-1|-1|||0|0|" + a + "" + (pInfo(peer)->inv.size() < 186 ? "\nadd_button|upgrade_backpack|`0Upgrade Backpack`` (`w10 Slots``)|interface/large/store_buttons/store_buttons.rttex|`2You Get:`` 10 Additional Backpack Slots.<CR><CR>`5Description:`` Sewing an extra pocket onto your backpack will allow you to store `$10`` additional item types.  How else are you going to fit all those toilets and doors?|0|1|" + to_string(inventory_price(pInfo(peer)->inv.size())) + "|0|||-1|-1||-1|-1||1||||||0|0|" : "") + "\nadd_button|clothes|`oClothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Wearble Items.<CR><CR>`5Description:`` Why not look the part? Some may even have special powers...|0|0|50|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|rare_clothes|`oRare Clothes Pack``|interface/large/store_buttons/store_buttons2.rttex|`2You Get:`` 3 Randomly Chosen Wearbale Items.<CR><CR>`5Description:`` Enjoy the garb of kings! Some may even have special powers...|0|1|500|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|transmutation_device|`oTransmutabooth``|interface/large/store_buttons/store_buttons27.rttex|`2You Get:`` 1 Transmutabooth.<CR><CR>`5Description:`` Behold! A wondrous technological achievement from the innovative minds at GrowTech, the Transmutabooth allows you to merge clothing items, transferring the visual appearance of one onto another in the same slot! If you've ever wanted your Cyclopean Visor to look like Shades (while keeping its mod), now you can!|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|"/*\nadd_button|contact_lenses|`oContact Lens Pack``|interface/large/store_buttons/store_buttons22.rttex|`2You Get:`` 20 Random Contact Lens Colors.<CR><CR>`5Description:`` Need a colorful new look? This pack includes 20 random Contact Lens colors (and may include Contact Lens Cleaning Solution, to return to your natural eye color)!|0|7|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|eye_drops|`oEye Drop Pack``|interface/large/store_buttons/store_buttons17.rttex|`2You Get:`` 1 `#Rare Bathroom Mirror`` and 10 random Eye Drop Colors.<CR><CR>`5Description:`` Need a fresh new look?  This pack includes a 10 random Eye Drop Colors (may include Eye Cleaning Solution, to leave your eyes sparkly clean)!|0|6|30000|0|||-1|-1||-1|-1||1||||||0|0|*/"\nadd_button|nyan_hat|`oTurtle Hat``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Turtle Hat.<CR><CR>`5Description:`` It's the greatest hat ever. It bloops out bubbles as you run! `4Not available any other way!``|0|2|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|tiny_horsie|`oTiny Horsie``|interface/large/store_buttons/store_buttons3.rttex|`2You Get:`` 1 Tiny Horsie.<CR><CR>`5Description:`` Tired of wearing shoes? Wear a Tiny Horsie instead! Or possibly a large dachshund, we're not sure. Regardless, it lets you run around faster than normal, plus you're on a horse! `4Not available any other way!``|0|5|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|star_ship|`oPleiadian Star Ship``|interface/large/store_buttons/store_buttons4.rttex|`2You Get:`` 1 Pleiadian Star Ship.<CR><CR>`5Description:`` Float on, my brother. It's all groovy. This star ship can't fly, but you can still zoom around in it, leaving a trail of energy rings and moving at enhanced speed. Sponsored by Pleiadian. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dragon_hand|`oDragon Hand``|interface/large/store_buttons/store_buttons5.rttex|`2You Get:`` 1 Dragon Hand.<CR><CR>`5Description:`` Call forth the dragons of legend!  With the Dragon Hand, you will command your own pet dragon. Instead of punching blocks or players, you can order your dragon to incinerate them! In addition to just being awesome, this also does increased damage, and pushes other players farther. `4Not available any other way!``|0|1|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|corvette|`oLittle Red Corvette``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Little Red Corvette.<CR><CR>`5Description:`` Cruise around the neighborhood in style with this sweet convertible. It moves at enhanced speed and leaves other Growtopians in your dust. `4Not available any other way!``|0|1|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|stick_horse|`oStick Horse``|interface/large/store_buttons/store_buttons6.rttex|`2You Get:`` 1 Stick Horse.<CR><CR>`5Description:`` Nobody looks cooler than a person bouncing along on a stick with a fake horse head attached. NOBODY. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|ambulance|`oAmbulance``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Ambulance.<CR><CR>`5Description:`` Rush to the scene of an accident while lawyers chase you in this speedy rescue vehicle. `4Not available any other way!``|0|3|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|raptor|`oRiding Raptor``|interface/large/store_buttons/store_buttons7.rttex|`2You Get:`` 1 Riding Raptor.<CR><CR>`5Description:`` Long thought to be extinct, it turns out that these dinosaurs are actually alive and easily tamed. And riding one lets you run around faster than normal! `4Not available any other way!``|0|7|25000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|owl|`oMid-Pacific Owl``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Mid-Pacific Owl.<CR><CR>`5Description:`` This owl is a bit lazy - if you stop moving around, he'll land on your head and fall asleep. Dedicated to the students of the Mid-Pacific Institute. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|unicorn|`oUnicorn Garland``|interface/large/store_buttons/store_buttons10.rttex|`2You Get:`` 1 Unicorn Garland.<CR><CR>`5Description:`` Prance about in the fields with your very own pet unicorn! It shoots `1R`2A`3I`4N`5B`6O`7W`8S``. `4Not available any other way!``|0|4|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|starboard|`oStarBoard``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 StarBoard.<CR><CR>`5Description:`` Hoverboards are here at last! Zoom around Growtopia on this brand new model, which is powered by fusion energy (that means stars spit out of the bottom). Moves faster than walking. Sponsored by Miwsky, Chudy, and Dawid. `4Not available any other way!``|0|1|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|motorcycle|`oGrowley Motorcycle``|interface/large/store_buttons/store_buttons11.rttex|`2You Get:`` 1 Growley Motorcycle.<CR><CR>`5Description:`` The coolest motorcycles available are Growley Dennisons. Get a sporty blue one today! It even moves faster than walking, which is pretty good for a motorcycle. `4Not available any other way!``|0|6|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|monkey_on_back|`oMonkey On Your Back``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Monkey On Your Back.<CR><CR>`5Description:`` Most people work really hard to get rid of these, but hey, if you want one, it's available! `4But not available any other way!`` Sponsored by SweGamerHD's subscribers, Kizashi, and Inforced. `#Note: This is a neck item, not a back item. He's grabbing your neck!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|carrot_sword|`oCarrot Sword``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Carrot Sword.<CR><CR>`5Description:`` Razor sharp, yet oddly tasty. This can carve bunny symbols into your foes! `4Not available any other way!`` Sponsored by MrMehMeh.|0|3|15000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|red_bicycle|`oRed Bicycle``|interface/large/store_buttons/store_buttons13.rttex|`2You Get:`` 1 Red Bicycle.<CR><CR>`5Description:`` It's the environmentally friendly way to get around! Ride this bicycle at high speed hither and zither throughout Growtopia. `4Not available any other way!``|0|5|30000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|fire_truck|`oFire Truck``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Fire Truck.<CR><CR>`5Description:`` Race to the scene of the fire in this speedy vehicle! `4Not available any other way!``|0|2|50000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|pet_slime|`oPet Slime``|interface/large/store_buttons/store_buttons14.rttex|`2You Get:`` 1 Pet Slime.<CR><CR>`5Description:`` What could be better than a blob of greasy slime that follows you around? How about a blob of greasy slime that follows you around and spits corrosive acid, melting blocks more quickly than a normal punch? `4Not available any other way!``|0|4|100000|0|||-1|-1||-1|-1||1||||||0|0|\nadd_button|dabstep_shoes|`oDabstep Low Top Sneakers``|interface/large/store_buttons/store_buttons21.rttex|`2You Get:`` 1 Dabstep Low Top Sneakers.<CR><CR>`5Description:`` Light up every footfall and move to a better beat with these dabulous shoes! When you're wearing these, the world is your dance floor! `4Not available any other way!``|0|2|30000|0|||-1|-1||-1|-1||1||||||0|0|\n");
											p2.CreatePacket(peer);
										}
									}
									p.CreatePacket(peer);
								}
								else {
									try {
										vector<int> list;
										vector<vector<int>> itemai;
										string item_name = "";
										ifstream ifs("db/shop/" + item + ".json");
										if (ifs.is_open()) {
											json j;
											ifs >> j;
											price = j["g"].get<int>();
											item_name = j["p"].get<string>();
											if (j.find("itemai") != j.end()) { // mano sistema
												if (pInfo(peer)->gems < price) {
													packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
													p.Insert("You can't afford `o" + item_name + "``!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short."), p.CreatePacket(peer);
													break;
												}
												itemai = j["itemai"].get<vector<vector<int>>>();
												int reik_slots = itemai.size();
												int turi_slots = get_free_slots(pInfo(peer));
												for (vector<int> item_info : itemai) {
													int turi_dabar = 0;
													modify_inventory(peer, item_info.at(0), turi_dabar);
													if (turi_dabar != 0) reik_slots--;
													if (turi_dabar + item_info.at(1) > 200) goto fail;
												}
												if (turi_slots < reik_slots) goto fail;
												{
													pInfo(peer)->gems -= price;
													gamepacket_t gem_upd;
													gem_upd.Insert("OnSetBux"), gem_upd.Insert(pInfo(peer)->gems), gem_upd.Insert(0), gem_upd.Insert(1), gem_upd.CreatePacket(peer);
													vector<string> received_items{}, received_items2{};
													for (vector<int> item_info : itemai) {
														uint32_t item_id = item_info.at(0);
														int item_count = item_info.at(1);
														modify_inventory(peer, item_id, item_count);
														received_items.push_back("Got " + to_string(item_info.at(1)) + " `#" + items.at(item_id).name + "``."), received_items2.push_back(to_string(item_info.at(1)) + " " + items.at(item_id).name);
													}
													packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
													gamepacket_t p_;
													p_.Insert("OnConsoleMessage"), p_.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n" + join(received_items, "\n")), p_.CreatePacket(peer);
													p.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n\n`5Received: ``" + join(received_items2, ", ") + "\n"), p.CreatePacket(peer);
													break;
												}
											fail:
												packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
												p.Insert("You don't have enough space in your inventory to buy that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
												p.CreatePacket(peer);
												break;
											}
											list = j["i"].get<vector<int>>();
											getcount = j["h"].get<int>();
											get_counted = j["h"].get<int>();
											slot = j["c"].get<int>();
											token = j["t"].get<int>();
											random_pack = j["random"].get<int>();
											int totaltoken = 0, tokencount = 0, mega_token = 0, inventoryfull = 0;
											modify_inventory(peer, 1486, tokencount);
											modify_inventory(peer, 6802, mega_token);
											totaltoken = tokencount + (mega_token * 100);
											vector<pair<int, int>> receivingitems;
											if (token == 0 ? price > pInfo(peer)->gems : token > totaltoken) {
												packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
												p.Insert("You can't afford `o" + item_name + "``!  You're `$" + (token == 0 ? "" + setGems(price - pInfo(peer)->gems) + "`` Gems short." : "" + setGems(token - totaltoken) + "`` Growtokens short."));
											}
											else {
												if (free >= slot) {
													string received = "", received2 = "";
													if (item == "basic_splice") {
														slot++;
														receivingitems.push_back(make_pair(11, 10));
													}
													if (item == "race_packa") {
														slot++;
														receivingitems.push_back(make_pair(11, 10));
													}
													for (int i = 0; i < slot; i++) receivingitems.push_back(make_pair((random_pack == 1 ? list[rand() % list.size()] : list[i]), getcount));
													for (int i = 0; i < slot; i++) {
														int itemcount = 0;
														modify_inventory(peer, receivingitems[i].first, itemcount);
														if (itemcount + getcount > 200) inventoryfull = 1;
													}
													if (inventoryfull == 0) {
														int i = 0;
														for (i = 0; i < slot; i++) {
															received += (i != 0 ? ", " : "") + items.at(receivingitems[i].first).name;
															received2 += "Got " + to_string(receivingitems[i].second) + " `#" + items.at(receivingitems[i].first).name + "``." + (i == (slot - 1) ? "" : "\n") + "";
															modify_inventory(peer, receivingitems[i].first, receivingitems[i].second);
														}
													}
													else {
														packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
														p.Insert("You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
														p.CreatePacket(peer);
														break;
													}
													{
														gamepacket_t p;
														p.Insert("OnConsoleMessage");
														p.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n" + received2);
														p.CreatePacket(peer);
													}
													p.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n\n`5Received: ``" + (get_counted <= 1 ? "" : "`0" + to_string(get_counted)) + "`` " + received + "\n");
													if (token == 0) {
														pInfo(peer)->gems -= price;
														gamepacket_t p;
														p.Insert("OnSetBux");
														p.Insert(pInfo(peer)->gems);
														p.Insert(1);
														p.CreatePacket(peer);
													}
													else {
														if (tokencount >= token) modify_inventory(peer, 1486, token *= -1);
														else {
															modify_inventory(peer, 1486, tokencount *= -1);
															modify_inventory(peer, 6802, mega_token *= -1);
															int givemegatoken = (totaltoken - token) / 100;
															int givetoken = (totaltoken - token) - (givemegatoken * 100);
															modify_inventory(peer, 1486, givetoken);
															modify_inventory(peer, 6802, givemegatoken);
														}
													}
													packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
												}
												else {
													packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
													p.Insert(slot > 1 ? "You'll need " + to_string(slot) + " slots free to buy that! You have " + to_string(free) + " slots." : "You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
												}
											}
										}
										else {
											packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
											p.Insert("This item was not found. Server error.");
										}
										p.CreatePacket(peer);
									}
									catch (exception) {
										cout << "something failed" << endl;
									}
								}
								if (price == 0) p2.CreatePacket(peer);
							}
							catch (out_of_range& klaida) {
								cout << "Buy klaida -> " << klaida.what() << endl;
							}
						}
						else if (cch == "action|AccountSecurity\nlocation|pausemenu\n") {
							gamepacket_t p(500);
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAdvanced Account Protection ``|left|3732|\nadd_textbox|`1You are about to enable the Advanced Account Protection.``|left|\nadd_textbox|`1After that, every time you try to log in from a new device and IP you will receive an email with a login confirmation link.``|left|\nadd_textbox|`1This will significantly increase your account security.``|left|\nend_dialog|secureaccount|Cancel|Ok|");
							p.CreatePacket(peer);
						}
						else if (cch.find("action|respawn") != string::npos) SendRespawn(peer, 0, (cch.find("action|respawn_spike") != string::npos) ? false : true);
						else if (cch == "action|refresh_item_data\n") {
							ENetPacket* packet = enet_packet_create(item_data, item_data_size + 60, ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							//enet_peer_disconnect_later(peer, 0);
						}
						else if (cch == "action|enter_game\n") {
							if (pInfo(peer)->tankIDName.empty()) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert(r_dialog(""));
								p.CreatePacket(peer);
							}
							else {
								gamepacket_t p;
								p.Insert("SetHasAccountSecured");
								if (pInfo(peer)->aap == "notenabled") p.Insert(0);
								else p.Insert(1);
								p.CreatePacket(peer);
								{
									int on_ = 0;
									vector<string> friends_;
									for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
										friends_.push_back(pInfo(peer)->friends.at(c_).name);
									} for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
											if (pInfo(currentPeer)->show_friend_notifications_) {
												packet_(currentPeer, "action|play_sfx\nfile|audio/friend_logon.wav\ndelayMS|0");
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`3FRIEND ALERT:`` " + pInfo(peer)->tankIDName + " has `2logged on``.");
												p.CreatePacket(currentPeer);
											}
											on_++;
										}
									}
									//pInfo(peer)->level = 50 * ((pInfo(peer)->level * pInfo(peer)->level) + 2);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									pInfo(peer)->name_color = (pInfo(peer)->dev == 1 ? "`6@" : (pInfo(peer)->mod == 1) ? "`#@" : "`0");
									if (pInfo(peer)->supp == 0 && pInfo(peer)->mod + pInfo(peer)->dev != 0) pInfo(peer)->supp = 1;
									p.Insert("Welcome back, `w" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "````." + (pInfo(peer)->friends.size() == 0 ? "" : (on_ != 0 ? " `w" + to_string(on_) + "`` friend is online." : " No friends are online.")));
									p.CreatePacket(peer);
									{
										{
											gamepacket_t p;
											p.Insert("OnEmoticonDataChanged");
											p.Insert(151749376);
											p.Insert("(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ġ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&(eyes)|ķ|1&(weary)|ĸ|1&");
											p.CreatePacket(peer);
										}
										/*gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`3Limited time event``: Everyone gets double gems (gems)!");
										p.CreatePacket(peer);*/
									}
									{
										int w_c = 0, s_c = 0, net_ = 0;
										get_players(pInfo(peer)->world, w_c, s_c, net_);
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("Where would you like to go? (`w" + to_string(s_c) + "`` online)");
										p.CreatePacket(peer);
									}
								}
								world_menu(peer);
								news(peer);
							}
						}
						else if (cch.find("action|dialog_return") != string::npos) {
							call_dialog(peer, cch);
						}
						break;
					}
					case 3: // world/enter
					{
						if (pInfo(peer)->trading_with != -1) {
							cancel_trade(peer, false);
						}
						string cch = text_(event.packet);
						if (cch == "action|quit") { // kai quit issaugo dar bus settings ar captcha bypassed disconnect
							if (not pInfo(peer)->tankIDName.empty()) // jeigu yra growid   
								save_player(pInfo(peer)); // issaugoti zaidejo json   
							if (pInfo(peer)->trading_with != -1) {
								cancel_trade(peer, false);
							}
							enet_peer_disconnect_now(peer, 0); // turetu nesuveikti tada antra karta save
							delete peer->data;
							peer->data = NULL;
						}
						else if (cch == "action|quit_to_exit") {
							exit_(peer);
						}
						else if (cch.find("action|join_request") != string::npos) {
							try {
								string world_name = explode("\n", explode("|", cch).at(2)).at(0);
								transform(world_name.begin(), world_name.end(), world_name.begin(), ::toupper);
								join_world(peer, world_name);
							}
							catch (out_of_range& klaida) {
								cout << "World error -> " << klaida.what() << endl;
							}
						}
						break;
					}
					case 4:
					{
						if (pInfo(peer)->world.empty()) break;
						BYTE* data = get_struct(event.packet);
						if (data == nullptr) {
							cout << "crash attempt: data was nullptr" << endl;
							break;
						}
						PlayerMoving* p_ = unpackPlayerMoving(data);
						//cout << p_->packetType << endl;
						if (pInfo(peer)->trading_with != -1 and p_->packetType != 0 and p_->packetType != 18) {
							cancel_trade(peer, false, true);
							break;
						}
						switch (p_->packetType) {
						case 0: /*Kai zaidejas pajuda*/
						{
							if ((int)p_->characterState == 268435472 || (int)p_->characterState == 268435488 || (int)p_->characterState == 268435504 || (int)p_->characterState == 268435616 || (int)p_->characterState == 268435632 || (int)p_->characterState == 268435456 || (int)p_->characterState == 224 || (int)p_->characterState == 112 || (int)p_->characterState == 80 || (int)p_->characterState == 96 || (int)p_->characterState == 224 || (int)p_->characterState == 65584 || (int)p_->characterState == 65712 || (int)p_->characterState == 65696 || (int)p_->characterState == 65536 || (int)p_->characterState == 65552 || (int)p_->characterState == 65568 || (int)p_->characterState == 65680 || (int)p_->characterState == 192 || (int)p_->characterState == 65664 || (int)p_->characterState == 65600 || (int)p_->characterState == 67860 || (int)p_->characterState == 64) {
								if (pInfo(peer)->lava_time + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
									pInfo(peer)->lavaeffect = 0;
									pInfo(peer)->lava_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								}
								else {
									if (pInfo(peer)->lavaeffect >= (pInfo(peer)->feet == 250 ? 7 : 3)) {
										pInfo(peer)->lavaeffect = 0;
										SendRespawn(peer, 0, true);
									}
									else pInfo(peer)->lavaeffect++;
								}
							}
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds.at(p - worlds.begin());
								if (pInfo(peer)->x != -1 and pInfo(peer)->y != -1) {
									try {
										WorldBlock* block_ = &world_->blocks.at((pInfo(peer)->state == 16 ? (int)p_->x / 32 : round((double)p_->x / 32)) + ((int)p_->y / 32 * 100));
										if (pInfo(peer)->c_x * 32 != (int)p_->x and pInfo(peer)->c_y * 32 != (int)p_->y and not pInfo(peer)->ghost) {
											bool impossible = ar_turi_noclipa(world_, pInfo(peer)->x, pInfo(peer)->y, block_, peer);
											if (impossible) {
												gamepacket_t p(0, pInfo(peer)->netID);
												p.Insert("OnSetPos");
												p.Insert(pInfo(peer)->x, pInfo(peer)->y);
												p.CreatePacket(peer);
												pInfo(peer)->hack_++;
												if (pInfo(peer)->hack_ >= 3) {
													//add_ban(peer, 604800, "Hacking", "System");
												}
												break;
											}
										}
									}
									catch (out_of_range) { // nuskrido uz worldo
										cout << "failed to perform anticheat check for player " << pInfo(peer)->tankIDName + " invalid world??" << endl;
									}
								}
								if (pInfo(peer)->hand == 2286) {
									if (rand() % 100 < 6) {
										pInfo(peer)->geiger_++;
										if (pInfo(peer)->geiger_ >= 100) {
											int c_ = -1;
											modify_inventory(peer, 2286, c_);
											int c_2 = 1;
											modify_inventory(peer, 2204, c_2);
											pInfo(peer)->hand = 2204;
											pInfo(peer)->geiger_ = 0;
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You are detecting radiation... (`$Geiger Counting`` mod added)");
											p.CreatePacket(peer);
											packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
											update_clothes(peer);
										}
									}
								}
								if (pInfo(peer)->gems > 0 && pInfo(peer)->back == 240) {
									if (pInfo(peer)->x != (int)p_->x) {
										if (pInfo(peer)->i240 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
											pInfo(peer)->i240 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
											pInfo(peer)->gems -= 1;
											gems_(world_, 1, (int)p_->x, (int)p_->y);
											gamepacket_t p;
											p.Insert("OnSetBux");
											p.Insert(pInfo(peer)->gems);
											p.Insert(1);
											p.CreatePacket(peer);
										}
									}
								}
								move_(peer, p_);
								if (pInfo(peer)->x == -1 and pInfo(peer)->y == -1) { /*Atnaujinti clothes nes uzejo i worlda*/
									update_clothes(peer);
								}

								long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
								map<string, vector<WorldNPC>>::iterator it;
								for (it = active_npc.begin(); it != active_npc.end(); it++) {
									if (it->first == world_->name) {
										for (int i_ = 0; i_ < it->second.size(); i_++) {
											try {
												WorldNPC npc_ = it->second.at(i_);
												if (npc_.uid == -1) continue;
												cout << npc_.id << " " << npc_.enabled << " " << npc_.projectile_speed << endl;
												double per_sekunde_praeina_bloku = (double)npc_.projectile_speed / 32;
												double praejo_laiko = (double)(ms_time - npc_.started_moving) / 1000;
												double praejo_distancija = (double)per_sekunde_praeina_bloku * (double)praejo_laiko;
												double current_x = ((int)npc_.kryptis == 180 ? (((double)npc_.x - (double)praejo_distancija) * 32) + 16 : (((double)npc_.x + (double)praejo_distancija) * 32) + 16);
												double current_y = (double)npc_.y * 32;
												//WorldBlock* block_ = &world_->blocks.at((int)(current_x / 32) + ((int)(current_y / 32) * 100));
												PlayerMoving data_{};
												data_.packetType = 34;
												data_.x = (current_x + 16); //nuo x
												data_.y = (current_y + (npc_.id == 8020 ? 6 : 16)); //nuo y
												data_.XSpeed = (current_x + 16); // iki x
												data_.YSpeed = (current_y + (npc_.id == 8020 ? 6 : 16)); // iki y
												data_.punchY = npc_.projectile_speed;
												BYTE* raw = packPlayerMoving(&data_);
												raw[1] = (npc_.id == 8020 ? 15 : 8), raw[2] = npc_.uid, raw[3] = 2;
												memcpy(raw + 40, &npc_.kryptis, 4);
												send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												delete[] raw;
											}
											catch (out_of_range) {
												cout << "npc bot error" << endl;
												continue;
											}
										}
										break;
									}
								}

								pInfo(peer)->x = (int)p_->x, pInfo(peer)->y = (int)p_->y, pInfo(peer)->state = p_->characterState & 0x10;
							}
							break;
						}
						case 3: /*Kai zaidejas papunchina/wrenchina bloka*/
						{
							if (p_->plantingTree != 18 and p_->plantingTree != 32) {
								int c_ = 0;
								modify_inventory(peer, p_->plantingTree, c_);
								if (c_ == 0) break;
							} if (p_->plantingTree == 18) {
								if (pInfo(peer)->punch_time + 100 > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) break;
								pInfo(peer)->punch_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							}
							if (p_->plantingTree == 18 and has_playmod(pInfo(peer), "rayman's fist")) { // tingejau galvoti kaip kitaip daryt
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds.at(p - worlds.begin());
									try {
										WorldBlock* block_ = &world_->blocks.at(p_->punchX + (p_->punchY * 100));
										if (block_->fg == 0 and block_->bg == 0) break;
									}
									catch (out_of_range) {
										break;
									}
								}
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									}
								}
							}
							else {
								edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
							}
							break;
						}
						case 7: /*Kai zaidejas ieina pro duris arba portal*/
						{
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds.at(p - worlds.begin());
								try {
									WorldBlock* block_ = &world_->blocks.at(p_->punchX + (p_->punchY * 100));
									if (items.at(items.at(block_->fg ? block_->fg : block_->bg).id).blockType == BlockTypes::CHECKPOINT) {
										pInfo(peer)->c_x = p_->punchX;
										pInfo(peer)->c_y = p_->punchY;
										{
											gamepacket_t p;
											p.Insert("OnPlanterActivated");
											p.Insert(0);
											p.CreatePacket(peer);
										}
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("SetRespawnPos");
										p.Insert(pInfo(peer)->c_x + (pInfo(peer)->c_y * 100));
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnPlanterActivated");
											p.Insert(1);
											p.CreatePacket(peer);
										}
									}
									else if (items.at(block_->fg ? block_->fg : block_->bg).id == 6) exit_(peer);
									else if (items.at(block_->fg).blockType == BlockTypes::DOOR or items.at(block_->fg).blockType == BlockTypes::PORTAL) {
										string door_target = block_->door_destination, door_id = "";
										World target_world = worlds.at(p - worlds.begin());
										bool locked = (block_->open ? false : (target_world.owner_name == pInfo(peer)->tankIDName or pInfo(peer)->dev or target_world.open_to_public or target_world.owner_name.empty() or (find(target_world.admins.begin(), target_world.admins.end(), pInfo(peer)->tankIDName) != target_world.admins.end()) ? false : true));
										int spawn_x = 0, spawn_y = 0;
										if (not locked) {
											if (door_target.find(":") != string::npos) {
												vector<string> detales = explode(":", door_target);
												door_target = detales.at(0), door_id = detales.at(1);
											} if (not door_target.empty() and door_target != world_->name) {
												if (not check_name(door_target)) {
													gamepacket_t p(250, pInfo(peer)->netID);
													p.Insert("OnSetFreezeState");
													p.Insert(1);
													p.CreatePacket(peer);
													{
														gamepacket_t p(250);
														p.Insert("OnConsoleMessage");
														p.Insert(door_target);
														p.CreatePacket(peer);
													}
													{
														gamepacket_t p(250);
														p.Insert("OnZoomCamera");
														p.Insert((float)10000.000000);
														p.Insert(1000);
														p.CreatePacket(peer);
													}
													{
														gamepacket_t p(250, pInfo(peer)->netID);
														p.Insert("OnSetFreezeState");
														p.Insert(0);
														p.CreatePacket(peer);
													}
													break;
												}
												target_world = get_world(door_target);
											}
											int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize, square = (int)target_world.blocks.size();
											if (not door_id.empty()) {
												for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
													WorldBlock block_data = target_world.blocks.at(i_);
													if (block_data.fg == 1684 or items.at(block_data.fg).blockType == BlockTypes::DOOR or items.at(block_data.fg).blockType == BlockTypes::PORTAL) {
														if (block_data.door_id == door_id) {
															spawn_x = i_ % xSize, spawn_y = i_ / xSize;
															break;
														}
													}
												}
											}
										}
										join_world(peer, target_world.name, spawn_x, spawn_y, 250, locked, true);
									}
								}
								catch (out_of_range& klaida) {
									cout << "case 7 klaida -> " << klaida.what() << endl;
								}
							}
							break;
						}
						case 10: /*Kai zaidejas paspaudzia du kartus ant inventory itemo*/
						{
							if (p_->plantingTree <= 0 or p_->plantingTree >= items.size()) break;
							int c_ = 0;
							modify_inventory(peer, p_->plantingTree, c_);
							if (c_ == 0) break;
							if (items.at(p_->plantingTree).blockType != BlockTypes::CLOTHING) {
								int free = get_free_slots(pInfo(peer)), slot = 1;
								int c242 = 242, c1796 = 1796, c6802 = 6802, c1486 = 1486, countofused = 0, getdl = 1, getwl = 100, removewl = -100, removedl = -1, countwl = 0;
								int c7188 = 7188;
								modify_inventory(peer, p_->plantingTree, countofused);
								if (free >= slot) {
									if (p_->plantingTree == 242 || p_->plantingTree == 1796) {
										modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, countwl);
										if (p_->plantingTree == 242 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 242 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 242 ? c242 : c1796, p_->plantingTree == 242 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, p_->plantingTree == 242 ? getdl : getwl);
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!");
												p.Insert(0);
												p.Insert(1);
												p.CreatePacket(peer);
												gamepacket_t p2;
												p2.Insert("OnConsoleMessage");
												p2.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!");
												p2.CreatePacket(peer);
											}
										}
									}
									else if (p_->plantingTree == 7188) {
										modify_inventory(peer, c1796, countwl);
										if (countwl <= 100) {
											if (countofused >= 1) {
												modify_inventory(peer, c7188, removedl);
												modify_inventory(peer, c1796, getwl);
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!");
												p.Insert(0);
												p.Insert(1);
												p.CreatePacket(peer);
												gamepacket_t p2;
												p2.Insert("OnConsoleMessage");
												p2.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!");
												p2.CreatePacket(peer);
											}
										}
									}
									if (p_->plantingTree == 1486 || p_->plantingTree == 6802) {
										modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, countwl);
										if (p_->plantingTree == 1486 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 1486 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 1486 ? c1486 : c6802, p_->plantingTree == 1486 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, p_->plantingTree == 1486 ? getdl : getwl);
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!");
												p.Insert(0);
												p.Insert(1);
												p.CreatePacket(peer);
												gamepacket_t p2;
												p2.Insert("OnConsoleMessage");
												p2.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!");
												p2.CreatePacket(peer);
											}
										}
									}
								}
								/*compress ir t.t*/
								break;
							}
							/*equip*/
							if (pInfo(peer)->ances == p_->plantingTree or pInfo(peer)->back == p_->plantingTree
								or pInfo(peer)->feet == p_->plantingTree or pInfo(peer)->face == p_->plantingTree
								or pInfo(peer)->hair == p_->plantingTree or pInfo(peer)->hand == p_->plantingTree
								or pInfo(peer)->mask == p_->plantingTree or pInfo(peer)->necklace == p_->plantingTree
								or pInfo(peer)->pants == p_->plantingTree or pInfo(peer)->shirt == p_->plantingTree) {
								unequip_(peer, p_->plantingTree);
							}
							else {
								ClothTypes type_ = items.at(p_->plantingTree).clothType;
								if (type_ == ClothTypes::ANCES)
									pInfo(peer)->ances = p_->plantingTree;
								else if (type_ == ClothTypes::BACK)
									pInfo(peer)->back = p_->plantingTree;
								else if (type_ == ClothTypes::FEET)
									pInfo(peer)->feet = p_->plantingTree;
								else if (type_ == ClothTypes::FACE)
									pInfo(peer)->face = p_->plantingTree;
								else if (type_ == ClothTypes::HAIR)
									pInfo(peer)->hair = p_->plantingTree;
								else if (type_ == ClothTypes::HAND)
									pInfo(peer)->hand = p_->plantingTree;
								else if (type_ == ClothTypes::MASK)
									pInfo(peer)->mask = p_->plantingTree;
								else if (type_ == ClothTypes::NECKLACE)
									pInfo(peer)->necklace = p_->plantingTree;
								else if (type_ == ClothTypes::PANTS)
									pInfo(peer)->pants = p_->plantingTree;
								else if (type_ == ClothTypes::SHIRT)
									pInfo(peer)->shirt = p_->plantingTree;
								if (items.at(p_->plantingTree).on_equip != "" or p_->plantingTree == 2286) {
									cout << "yra " << items.at(p_->plantingTree).playmod << endl;
									if (p_->plantingTree == 2204) {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You are detecting radiation... (`$Geiger Counting`` mod added)");
										p.CreatePacket(peer);
									}
									else if (p_->plantingTree == 2286 and pInfo(peer)->geiger_ < 100) {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("Your Geiger Counter is charging... (`$Charging Geiger Counter`` mod added)");
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert(items.at(p_->plantingTree).on_equip + (items.at(p_->plantingTree).playmod != "" ? " (`$" + items.at(p_->plantingTree).playmod + "`` mod added)" : ""));
										p.CreatePacket(peer);
									}
								}
								packet_(peer, "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0");
								update_clothes(peer);
							}
							break;
						}
						case 11: /*Kai zaidejas paema isdropinta itema*/
						{
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds.at(p - worlds.begin());
								for (int i_ = 0; i_ < world_->drop.size(); i_++) {
									if (world_->drop.at(i_).id == 0) continue;
									WorldBlock* block_ = &world_->blocks.at((pInfo(peer)->state == 16 ? world_->drop.at(i_).x / 32 : round((double)world_->drop.at(i_).x / 32)) + (world_->drop.at(i_).y / 32 * 100));
									if (abs((int)p_->x - world_->drop.at(i_).x) >= 32 or abs((int)p_->y - world_->drop.at(i_).y) >= 32) continue;
									int passed = 0;
									if (block_->fg == 1422 || block_->fg == 2488) {
										passed = 1;
										if (world_->owner_name == "") passed = 0;
										else if (world_->owner_name == pInfo(peer)->tankIDName) passed = 0;
										else if (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) passed = 0;
									}
									if (passed == 1) continue;
									if (world_->drop.at(i_).uid == p_->plantingTree) {
										bool impossible = ar_turi_noclipa(world_, pInfo(peer)->x, pInfo(peer)->y, block_, peer);
										if (impossible) {
											break;
										}
										int c_ = world_->drop.at(i_).count;
										if (world_->drop.at(i_).id == 112) {
											pInfo(peer)->gems += c_;
											PlayerMoving data_{};
											data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = pInfo(peer)->netID, data_.plantingTree = world_->drop.at(i_).uid;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[]raw;
											world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
										}
										else if (modify_inventory(peer, world_->drop.at(i_).id, c_, false, true) == 0) {
											PlayerMoving data_{};
											data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = pInfo(peer)->netID, data_.plantingTree = world_->drop.at(i_).uid;
											BYTE* raw = packPlayerMoving(&data_);
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Collected `w" + to_string(world_->drop.at(i_).count) + " " + items.at(world_->drop.at(i_).id).name + "``." + (items.at(world_->drop.at(i_).id).rarity > 363 ? "" : " Rarity: `w" + to_string(items.at(world_->drop.at(i_).id).rarity) + "``") + "");
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													if (pInfo(currentPeer)->netID == pInfo(peer)->netID)
														p.CreatePacket(currentPeer);
												}
											}
											delete[]raw;
											world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
										}
										else {
											if (c_ < 200 and world_->drop.at(i_).count >(200 - c_)) {
												int b_ = 200 - c_;
												world_->drop.at(i_).count -= b_;
												if (modify_inventory(peer, world_->drop.at(i_).id, b_, false) == 0) {
													WorldDrop drop_{};
													drop_.id = world_->drop.at(i_).id;
													drop_.count = world_->drop.at(i_).count;
													drop_.uid = uint16_t(world_->drop.size()) + 1;
													drop_.x = world_->drop.at(i_).x;
													drop_.y = world_->drop.at(i_).y;
													world_->drop.push_back(drop_);
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("Collected `w" + to_string(200 - c_) + " " + items.at(world_->drop.at(i_).id).name + "``." + (items.at(world_->drop.at(i_).id).rarity > 363 ? "" : " Rarity: `w" + to_string(items.at(world_->drop.at(i_).id).rarity) + "``") + "");
													PlayerMoving data_{};
													data_.packetType = 14, data_.netID = -1, data_.plantingTree = world_->drop.at(i_).id;
													data_.x = world_->drop.at(i_).x, data_.y = world_->drop.at(i_).y;
													int32_t item = -1;
													float val = world_->drop.at(i_).count;
													BYTE* raw = packPlayerMoving(&data_);
													data_.plantingTree = world_->drop.at(i_).id;
													memcpy(raw + 8, &item, 4);
													memcpy(raw + 16, &val, 4);
													val = 0;
													data_.netID = pInfo(peer)->netID;
													data_.plantingTree = world_->drop.at(i_).uid;
													data_.x = 0, data_.y = 0;
													BYTE* raw2 = packPlayerMoving(&data_);
													BYTE val2 = 0;
													memcpy(raw2 + 8, &item, 4);
													memcpy(raw2 + 16, &val, 4);
													memcpy(raw2 + 1, &val2, 1);
													world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
														if (pInfo(currentPeer)->world == name_) {
															send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															if (pInfo(currentPeer)->netID == pInfo(peer)->netID)
																p.CreatePacket(currentPeer);
															send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
														}
													}
													delete[]raw, raw2;
												}
											}
										}
										break;
									}
								}
							}
							break;
						}
						case 18: { //chat bubble kai raso
							move_(peer, p_);
							break;
						}
						case 23: /*Kai zaidejas papunchina kita*/
						{
							break;
						}
						default:
						{
							break;
						}
						}
						break;
					}
					default:
						break;
					}
					enet_packet_destroy(event.packet);
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT:
				{
					if (saving_) break;
					if (peer->data != NULL) {
						if (pInfo(peer)->trading_with != -1) {
							cancel_trade(peer, false);
						}
						if (not pInfo(peer)->world.empty()) {
							gamepacket_t p;
							p.Insert("OnRemove");
							p.Insert("netID|" + to_string(pInfo(peer)->netID) + "\n");
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == pInfo(peer)->world) {
									packet_(currentPeer, "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0");
									p.CreatePacket(currentPeer);
								}
							}
						}
						if (not pInfo(peer)->invalid_data) save_player(pInfo(peer), (f_saving_ ? false : true));
						if (f_saving_) pInfo(peer)->saved_on_close = true;
						if (not f_saving_) {
							enet_host_flush(server);
							delete peer->data;
							peer->data = NULL;
						}
					}
					break;
				}
				default:
					break;
				}
			}
			catch (std::exception& e) {
				std::cout << "exception: " << e.what() << std::endl;
			}
			catch (out_of_range& e) {
				std::cout << "exception: " << e.what() << std::endl;
			}

		}
	}
	return 0;
}