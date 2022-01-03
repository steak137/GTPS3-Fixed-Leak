#pragma once
/*
#include <stdio.h>
#include <chrono>
auto begin = chrono::high_resolution_clock::now();
//kodas
auto end = chrono::high_resolution_clock::now();
auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);
*/
// worldo struktura
#include <chrono>
#include <sstream>
#define HOME_TIME (15 * 1000)
#define WORLDBAN_TIME (3600 * 1000)
#define WARP_TIME (15 * 1000)
using namespace chrono;
bool saving_ = false;
bool f_saving_ = false;
int item1 = 0;
int item2 = 0;
int item1c = 0;
int item2c = 0;
int day = 0;
vector<pair<string, long long int>> home_timed;
string lastsbworld = "";
struct WorldBlock
{
	uint16_t fg, bg, fruit;
	uint32_t id = 0, wl = 0, c_ = 0;
	int pr = 0;
	long long lp, planted;
	int hp = -1, sp;
	uint8_t roll;
	string txt;
	string door_destination, door_id;
	bool open = false;
	int flags = 0x00000000;
	long long last_punch_weather;
	bool scanned = false;
	int rate_of_fire = 10, projectile_speed = 100;
	// magplants
	bool enabled = false;
	int gravity = 50;
	bool spin = false, invert = false;
	bool magnetron = false;
	bool locked = false;
	int lock_origin = -1;
	bool open_to_public = false;
	bool empty_air = false;
	vector<string> admins{};
	string owner_name = "";
	string owner_named = "";
	bool build_only = false;
	bool limit_admins = false;
};
struct WorldMachines
{
	uint16_t id, x, y, target_item;
	bool enabled = false;
	long long last_ = 0;
};
struct WorldNPC
{
	uint16_t id, x, y, rate_of_fire = 10, projectile_speed = 100;
	float kryptis = 0;
	int uid = 0;
	bool enabled = false;
	long long last_ = 0, started_moving = 0;
};
struct WorldDrop
{
	int id, count, uid, x, y;
};
struct World
{
	string name, owner_name, owner_named;
	bool nuked = false;
	string n_t = "";
	string n_b = "";
	vector<string> admins;
	vector<WorldBlock> blocks{};
	vector<WorldDrop> drop{};
	uint16_t weather = 0;
	bool open_to_public = false, disable_music_blocks = false, make_music_blocks_invisible = false;
	vector<pair<string, long long int>> bannedPlayers;
	uint32_t music_bpm = 100;
	int entry_level = 1;
	vector<int> active_jammers;
	vector<WorldNPC> npc;
	vector<WorldMachines> machines;
};
vector<World> worlds;
map<string, vector<WorldNPC>> active_npc;
map<string, vector<WorldMachines>> active_machines;
int get_free_slots(Player* p_) {
	int free = 0; // -1
	for (int i_ = 0; i_ < p_->inv.size(); i_++) {
		if (p_->inv.at(i_).id == 0 and p_->inv.at(i_).count == 0)
			free++;
	}
	return free;
}
int inventory_price(int inventory_size) {
	int price = 100; // -1
	inventory_size -= 1;
	if (inventory_size == 16) price = 100;
	else if (inventory_size == 26) price = 200;
	else if (inventory_size == 36) price = 500;
	else if (inventory_size == 46) price = 1000;
	else if (inventory_size == 446) price = 1000;
	else if (inventory_size == 56) price = 1700;
	else if (inventory_size == 66) price = 2600;
	else if (inventory_size == 76) price = 3700;
	else if (inventory_size == 836) price = 5000;
	else if (inventory_size == 96) price = 6500;
	else if (inventory_size == 1061) price = 8200;
	else if (inventory_size == 1161) price = 10100;
	else if (inventory_size == 126) price = 12200;
	else if (inventory_size == 136) price = 100;
	else if (inventory_size == 146) price = 100;
	else if (inventory_size == 156) price = 100;
	else if (inventory_size == 166) price = 100;
	else if (inventory_size == 176) price = 100;
	else if (inventory_size == 186) price = 100;
	/*
	else if (inventory_size == 196) price = 32500;
	else if (inventory_size == 206) price = 36200;
	else if (inventory_size == 216) price = 40100;
	else if (inventory_size == 226) price = 44200;
	else if (inventory_size == 236) price = 48500;
	else if (inventory_size == 246) price = 53000;
	else if (inventory_size == 256) price = 57700;
	else if (inventory_size == 266) price = 62600;
	else if (inventory_size == 276) price = 67700;
	else if (inventory_size == 286) price = 73000;
	else if (inventory_size == 296) price = 78500;
	else if (inventory_size == 306) price = 84200;
	else if (inventory_size == 316) price = 90100;
	else if (inventory_size == 326) price = 96200;
	else if (inventory_size == 336) price = 102500;
	else if (inventory_size == 346) price = 109000;
	else if (inventory_size == 356) price = 115700;
	else if (inventory_size == 366) price = 122600;
	else if (inventory_size == 376) price = 129700;
	else if (inventory_size == 386) price = 137000;
	else if (inventory_size == 396) price = 145000;*/
	return price;
}
World create_world(const string& name_, int s_) {
	World world_;
	world_.name = name_;
	int d_ = rand() % (s_ / (s_ / 100) - 4) + 2;
	for (int i_ = 0; i_ < s_; i_++) {
		WorldBlock block_{ 0, 0, uint16_t(-1) }; // buvo WorldBlock block_{0, 0, -1}; 
		if (i_ >= 3800 && i_ < 5400 && !(rand() % 50))
			block_.fg = 10;
		else if (i_ >= 3700 && i_ < 5400) {
			if (i_ > 5000) {
				if (rand() % 8 < 3)
					block_.fg = 4;
				else
					block_.fg = 2;
			}
			else
				block_.fg = 2;
		}
		else if (i_ >= 5400)
			block_.fg = 8;
		if (i_ == 3600 + d_)
			block_.fg = 6;
		if (i_ == 3700 + d_)
			block_.fg = 8;
		if (i_ >= 3700)
			block_.bg = 14;
		world_.blocks.push_back(block_);
	}
	worlds.push_back(world_);
	return world_;
}
void WriteTxt(string folder, string text) {
	replace_str(folder, ":", ".");
	if (folder == "db/accounts/mac/02.00.00.00.00.00") return;
	ofstream m;
	m.open(folder + ".txt", ios::out | ios::app | ios::binary);
	m << text;
	m.close();
}
void AddLogs(ENetPeer* p_, string logs) {
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	pInfo(p_)->logs.push_back("" + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/2021 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + " Console - " + logs + "");
}
World get_world(const string& name_) {
	/*galima buvo daryti pagal worldid o ne name bet jeigu worldus trinti is memory tai nk gero nebus*/
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	if (p != worlds.end()) {
		return worlds.at(p - worlds.begin()); // return worldo struktura   
	}
	// Worldo Nera bet jis gali buti issaugotas  
	string path_ = "worlds/" + name_ + "_.json";
	if (_access_s(path_.c_str(), 0) == 0) {
		World world_;
		try {
			// Pakrauti worlda is json      
			json world_read;
			ifstream world_file(path_, ifstream::binary);
			world_file >> world_read;
			world_file.close();
			world_.name = name_;
			world_.entry_level = world_read["entry_level"].get<int>();
			world_.open_to_public = world_read["public"].get<bool>();
			world_.nuked = world_read["nuked"].get<bool>();
			world_.n_t = world_read["n_t"].get<string>();
			world_.n_b = world_read["n_b"].get<string>();
			world_.music_bpm = world_read["music_bpm"].get<uint32_t>();
			world_.weather = world_read["weather"].get<uint16_t>();
			world_.make_music_blocks_invisible = world_read["invisible_music_blocks"].get<bool>();
			world_.disable_music_blocks = world_read["disable_music_blocks"].get<bool>();
			world_.owner_name = world_read["owner"].get<string>();
			json p_ = world_read["blocks"].get<json>(), a_ = world_read["drop"].get<json>(), adm_ = world_read["admins"].get<json>(), npc_vector_ = world_read["npc"].get<json>(), machine_vector_ = world_read["machine"].get<json>();
			for (int i_ = 0; i_ < adm_.size(); i_++) {
				string name_ = adm_.at(i_)["name"].get<string>();
				world_.admins.push_back(name_);
			}
			for (int i_ = 0; i_ < p_.size(); i_++) {
				WorldBlock b_{};
				b_.fg = p_.at(i_)["f"].get<int>();
				b_.bg = p_.at(i_)["b"].get<int>();
				b_.planted = p_.at(i_)["p"].get<long long>();
				b_.fruit = p_.at(i_)["fc"].get<int>();
				b_.sp = p_.at(i_)["sp"].get<int>();
				b_.txt = p_.at(i_)["t"].get<string>();
				b_.roll = p_.at(i_)["n"].get<uint8_t>();
				b_.id = p_.at(i_)["id"].get<uint32_t>();
				b_.c_ = p_.at(i_)["c"].get<uint32_t>();
				b_.wl = p_.at(i_)["wl"].get<uint32_t>();
				b_.pr = p_.at(i_)["pr"].get<int>();
				b_.open = p_.at(i_)["o"].get<bool>();
				b_.door_destination = p_.at(i_)["dd"].get<string>();
				b_.door_id = p_.at(i_)["di"].get<string>();
				b_.flags = p_.at(i_)["fl"].get<int>();
				b_.projectile_speed = p_.at(i_)["ps"].get<int>();
				b_.rate_of_fire = p_.at(i_)["rf"].get<int>();
				b_.enabled = p_.at(i_)["en"].get<bool>();
				b_.invert = p_.at(i_)["in"].get<bool>();
				b_.spin = p_.at(i_)["sn"].get<bool>();
				b_.gravity = p_.at(i_)["g"].get<int>();
				if (p_.at(i_).find("m") != p_.at(i_).end()) {
					b_.magnetron = p_.at(i_)["m"].get<bool>();
				}
				if (p_.at(i_).find("l") != p_.at(i_).end()) {
					b_.locked = p_.at(i_)["l"].get<bool>();
				}
				if (p_.at(i_).find("lq") != p_.at(i_).end()) {
					b_.lock_origin = p_.at(i_)["lq"].get<int>();
				}
				if (p_.at(i_).find("lo") != p_.at(i_).end()) {
					b_.owner_name = p_.at(i_)["lo"].get<string>();
				}
				if (p_.at(i_).find("ea") != p_.at(i_).end()) {
					b_.empty_air = p_.at(i_)["ea"].get<bool>();
				}
				if (p_.at(i_).find("otp") != p_.at(i_).end()) {
					b_.open_to_public = p_.at(i_)["otp"].get<bool>();
				}
				if (p_.at(i_).find("ad") != p_.at(i_).end()) {
					json read_block_admins_ = p_.at(i_)["ad"].get<json>();
					for (int i_2 = 0; i_2 < read_block_admins_.size(); i_2++) {
						string name_ = read_block_admins_.at(i_2)["name"].get<string>();
						b_.admins.push_back(name_);
					}
				}
				if (p_.at(i_).find("bo") != p_.at(i_).end()) {
					b_.build_only = p_.at(i_)["bo"].get<bool>();
				}
				if (p_.at(i_).find("la") != p_.at(i_).end()) {
					b_.limit_admins = p_.at(i_)["la"].get<bool>();
				}
				world_.blocks.push_back(b_);
			}
			for (int i_ = 0; i_ < a_.size(); i_++) {
				WorldDrop b_{};
				b_.id = a_.at(i_)["i"].get<int>();
				b_.count = a_.at(i_)["c"].get<int>();
				b_.uid = a_.at(i_)["u"].get<int>();
				b_.x = a_.at(i_)["x"].get<int>();
				b_.y = a_.at(i_)["y"].get<int>();
				world_.drop.push_back(b_);
			}
			for (int i_ = 0; i_ < npc_vector_.size(); i_++) {
				WorldNPC npc_{};
				npc_.id = npc_vector_.at(i_)["i"].get<uint16_t>();
				npc_.x = npc_vector_.at(i_)["x"].get<uint16_t>();
				npc_.y = npc_vector_.at(i_)["y"].get<uint16_t>();
				npc_.projectile_speed = npc_vector_.at(i_)["ps"].get<uint16_t>();
				npc_.rate_of_fire = npc_vector_.at(i_)["rf"].get<uint16_t>();
				npc_.kryptis = npc_vector_.at(i_)["kr"].get<float>();
				npc_.enabled = npc_vector_.at(i_)["en"].get<bool>();
				npc_.last_ = npc_vector_.at(i_)["l"].get<long long>();
				npc_.started_moving = npc_vector_.at(i_)["sm"].get<long long>();
				world_.npc.push_back(npc_);
			}
			for (int i_ = 0; i_ < machine_vector_.size(); i_++) {
				WorldMachines machine_{};
				machine_.id = machine_vector_.at(i_)["i"].get<uint16_t>();
				machine_.x = machine_vector_.at(i_)["x"].get<uint16_t>();
				machine_.y = machine_vector_.at(i_)["y"].get<uint16_t>();
				machine_.target_item = machine_vector_.at(i_)["ti"].get<uint16_t>();
				machine_.enabled = machine_vector_.at(i_)["en"].get<bool>();
				machine_.last_ = machine_vector_.at(i_)["l"].get<long long>();
				world_.machines.push_back(machine_);
			}
		}
		catch (exception err) {
			remove(path_.c_str());
			world_ = create_world(name_, 6000);
		}
		worlds.push_back(world_);
		return world_;
	}
	return create_world(name_, 6000);
}
void save_world(const string& name_, bool erase = true) {
	try {
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			__int64 id_ = p - worlds.begin();
			World* world_ = &worlds.at(id_);
			json save_, blocks_ = json::array(), drops_ = json::array(), admins_ = json::array(), npcs = json::array(), machines = json::array();
			save_["entry_level"] = world_->entry_level;
			save_["nuked"] = world_->nuked;
			save_["n_t"] = world_->n_t;
			save_["n_b"] = world_->n_b;
			save_["music_bpm"] = world_->music_bpm;
			save_["public"] = world_->open_to_public;
			save_["weather"] = world_->weather;
			save_["invisible_music_blocks"] = world_->make_music_blocks_invisible;
			save_["disable_music_blocks"] = world_->disable_music_blocks;
			save_["owner"] = world_->owner_name;
			for (int i_ = 0; i_ < world_->admins.size(); i_++) {
				json admin_;
				admin_["name"] = world_->admins.at(i_);
				admins_.push_back(admin_);
			}
			for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
				json block_;
				block_["f"] = world_->blocks.at(i_).fg;
				block_["b"] = world_->blocks.at(i_).bg;
				block_["p"] = world_->blocks.at(i_).planted;
				block_["fc"] = world_->blocks.at(i_).fruit;
				block_["sp"] = world_->blocks.at(i_).sp;
				block_["t"] = world_->blocks.at(i_).txt;
				block_["n"] = world_->blocks.at(i_).roll;
				block_["id"] = world_->blocks.at(i_).id;
				block_["c"] = world_->blocks.at(i_).c_;
				block_["wl"] = world_->blocks.at(i_).wl;
				block_["pr"] = world_->blocks.at(i_).pr;
				block_["o"] = world_->blocks.at(i_).open;
				block_["dd"] = world_->blocks.at(i_).door_destination;
				block_["di"] = world_->blocks.at(i_).door_id;
				block_["fl"] = world_->blocks.at(i_).flags;
				block_["rf"] = world_->blocks.at(i_).rate_of_fire;
				block_["ps"] = world_->blocks.at(i_).projectile_speed;
				block_["en"] = world_->blocks.at(i_).enabled;
				block_["in"] = world_->blocks.at(i_).invert;
				block_["sn"] = world_->blocks.at(i_).spin;
				block_["g"] = world_->blocks.at(i_).gravity;
				block_["m"] = world_->blocks.at(i_).magnetron;
				block_["l"] = world_->blocks.at(i_).locked;
				block_["lq"] = world_->blocks.at(i_).lock_origin;
				block_["lo"] = world_->blocks.at(i_).owner_name;
				block_["ea"] = world_->blocks.at(i_).empty_air;
				block_["otp"] = world_->blocks.at(i_).open_to_public;
				json block_admins_ = json::array();
				for (int i_2 = 0; i_2 < world_->blocks.at(i_).admins.size(); i_2++) {
					json admin_;
					admin_["name"] = world_->blocks.at(i_).admins.at(i_2);
					block_admins_.push_back(admin_);
				}
				block_["ad"] = block_admins_;
				block_["bo"] = world_->blocks.at(i_).build_only;
				block_["la"] = world_->blocks.at(i_).limit_admins;
				blocks_.push_back(block_);
			}
			for (int i_ = 0; i_ < world_->drop.size(); i_++) {
				if (world_->drop.at(i_).id == 0) {
					world_->drop.erase(world_->drop.begin() + i_);
					i_--;
					for (int a_ = 0; a_ < world_->drop.size(); a_++)
						if (a_ > i_) world_->drop[a_].uid--;
					continue;
				}
				json drop_;
				drop_["i"] = world_->drop.at(i_).id;
				drop_["c"] = world_->drop.at(i_).count;
				drop_["u"] = world_->drop.at(i_).uid;
				drop_["x"] = world_->drop.at(i_).x;
				drop_["y"] = world_->drop.at(i_).y;
				drops_.push_back(drop_);
			}
			for (int i_ = 0; i_ < world_->npc.size(); i_++) {
				json npc_;
				npc_["i"] = world_->npc.at(i_).id;
				npc_["x"] = world_->npc.at(i_).x;
				npc_["y"] = world_->npc.at(i_).y;
				npc_["ps"] = world_->npc.at(i_).projectile_speed;
				npc_["rf"] = world_->npc.at(i_).rate_of_fire;
				npc_["en"] = world_->npc.at(i_).enabled;
				npc_["kr"] = world_->npc.at(i_).kryptis;
				npc_["l"] = world_->npc.at(i_).last_;
				npc_["sm"] = world_->npc.at(i_).started_moving;
				npcs.push_back(npc_);
			}
			for (int i_ = 0; i_ < world_->machines.size(); i_++) {
				json machine_;
				machine_["i"] = world_->machines.at(i_).id;
				machine_["x"] = world_->machines.at(i_).x;
				machine_["y"] = world_->machines.at(i_).y;
				machine_["en"] = world_->machines.at(i_).enabled;
				machine_["ti"] = world_->machines.at(i_).target_item;
				machine_["l"] = world_->machines.at(i_).last_;
				machines.push_back(machine_);
			}
			save_["blocks"] = blocks_, save_["drop"] = drops_, save_["admins"] = admins_, save_["npc"] = npcs, save_["machine"] = machines;
			cout << "saved world " << name_ << endl;
			ofstream w_("worlds/" + name_ + "_.json");
			if (w_.fail()) {
				cout << "world saving failed for " << name_ << endl;
				return;
			}
			w_ << save_ << endl;
			w_.close();
			if (erase) {
				bool dont_del = false;
				for (int i_ = 0; i_ < world_->machines.size(); i_++) {
					WorldMachines machine = world_->machines.at(i_);
					if (machine.enabled) {
						WorldBlock* itemas = &world_->blocks.at(machine.x + (machine.y * 100));
						if (itemas->pr != 0 and machine.target_item != 0) {
							dont_del = true;
							break;
						}
					}
				}
				if (not dont_del) {
					map<string, vector<WorldNPC>>::iterator it;
					for (it = active_npc.begin(); it != active_npc.end(); it++) {
						if (it->first == world_->name) {
							it->second.clear();
							break;
						}
					}
					//cout << "deleted world from memory" << endl;
					worlds.erase(worlds.begin() + id_);
					world_ = NULL;
				}
			}
		}
	}
	catch (exception e) {
		cout << "something failed" << e.what() << endl;
	}
	catch (out_of_range e) {
		cout << "error saving world " << e.what() << endl;
	}
}
void get_players(const string& name_, int& c_, int& t_, int& net_) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (not name_.empty() && pInfo(currentPeer)->world == name_) {
			c_++;
			if (pInfo(currentPeer)->netID >= net_)
				net_ = pInfo(currentPeer)->netID + 1;
		}
		t_++;
	}
}
string setGems(int gems) {
	stringstream ss;
	dotted::imbue(ss);
	ss << gems;
	return ss.str();
}

void packet_(ENetPeer* p_, string t_, string l_ = "") {
	if (l_ != "")
		t_ = "action|log\nmsg|" + t_;
	int y_ = 3;
	BYTE z_ = 0;
	BYTE* const d_ = new BYTE[5 + t_.length()];
	memcpy(d_, &y_, 4);
	memcpy(d_ + 4, t_.c_str(), t_.length());
	memcpy(d_ + 4 + t_.length(), &z_, 1);
	ENetPacket* const p = enet_packet_create(d_, 5 + t_.length(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(p_, 0, p);
	delete[]d_;
	if (l_ != "") {
		const string w_ = "https://privategt.com/";
		l_ = "action|set_url\nurl|" + w_ + "\nlabel|" + l_ + "\n";
		BYTE* const u_ = new BYTE[5 + l_.length()];
		memcpy(u_, &y_, 4);
		memcpy(u_ + 4, l_.c_str(), l_.length());
		memcpy(u_ + 4 + l_.length(), &z_, 1);
		ENetPacket* const p3 = enet_packet_create(u_, 5 + l_.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(p_, 0, p3);
		delete[]u_;
	}
}
bool check_name(string& name_) {
	if (name_ == "EXIT") {
		name_ = "Exit from what? Press back if you're done playing.";
		return false;
	}
	for (char c : name_) if ((c < 'A' || c>'Z') && (c < '0' || c>'9')) {
		name_ = "Sorry, spaces and special characters are not allowed in world or door names.  Try again.";
		return false;
	}
	for (int i = 0; i < swear_words.size(); i++) {
		if (name_.find(swear_words[i]) != string::npos) {
			name_ = "DISNEYLAND";
		}
	}
	if (name_.size() < 1 || name_.size() >= 24) {
		name_ = "`4To reduce confusion, that is not a valid world name.``  Try another?";
		return false;
	} if (name_ == "") {
		name_ = "START";
	}
	return true;
}
long long last_active_update = 0;
vector<string> active_worlds;
void news(ENetPeer* peer) {
	const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	string month = months[newtime.tm_mon];
	string translated = "", str = to_string(newtime.tm_mday);
	if (str == "01" || str == "21") translated = "st";
	else if (str == "02" || str == "22") translated = "nd";
	else if (str == "03") translated = "rd";
	else translated = "th";
	gamepacket_t p;
	p.Insert("OnDialogRequest");
	p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wThe Growtopia Gazette``|left|5016|\nadd_spacer|small|\n#add_image_button|banner|interface/large/news_banner.rttex|bannerlayout|OPENSURVEY||\n#add_spacer|small|\nadd_textbox|`w" + month + " " + to_string(newtime.tm_mday) + "" + translated + ": `5Sale Season Ends!``|left|\nadd_spacer|small|\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn05.rttex|3imageslayout|OPENSTORE|main/gems_bundle06|\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn02.rttex|3imageslayout|OPENSTORE|main/gems_bundle05|\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn03.rttex|3imageslayout|OPENSTORE|main/gems_glory|\nadd_spacer|small|\nadd_textbox|Sale Season has now officially ended! We hope you have enjoyed all the astounding offers we had in store for you! However, that doesn't mean the fun is over. Stay tuned for more exciting stuff very soon!|left|\nadd_spacer|small|\nadd_textbox|The aliens are still roaming around `2Growtopia``! Equip yourself with the `2Alien Scanner`` when harvesting trees and maybe you will find yourself an `2Alien Landing Pod`` hidden in the lush forests of Growtopia!|left|\nadd_spacer|small\nadd_textbox|The Growtopia survey for the November Update is now open! By completing the survey, you will receive `22 Growtokens`` if you have Advanced Account Protection enabled. Complete the survey and claim your reward on your mobile device to let us know what you think!|left|\nadd_spacer|small|\nadd_url_button|survey|`wGive us your opinion!``|noflags|OPENSURVEY||\nadd_spacer|small|\nadd_textbox|Don't forget to join our `2Official Growtopia Private Server Discord`` on `2privategt.com/discord`` or click the link below!|left|\nadd_spacer|small|\n\nadd_quick_exit|add_spacer|small|\nadd_url_button|comment|`2Update Available!``|noflags|https://ubistatic-a.akamaihd.net/0098/23683/GrowtopiaInstaller.exe|Download the new windows client now?|0|0|\nadd_spacer|small|\nadd_url_button|comment|`wVisit Growtopia Private Server Discord``|noflags|http://privategt.com|Visit the Growtopia Private Server Discord?|0|0|\nadd_spacer|small|\nadd_url_button||`wWOTD: `1LAPSEOFMEMORY`` by `#Solerist````|NOFLAGS|OPENWORLD|LAPSEOFMEMORY|0|0|\nadd_spacer|small|\nadd_url_button||`wVOTW: `1MutantBot Battle Growtopia Animation``|NOFLAGS|https://www.youtube.com/watch?v=SJ1hBpJ4oKI|Watch 'MutantBot Battle Growtopia Animation' by NekoGameSS on YouTube?|0|0|\nset_survey_enabled|1\nend_dialog|gazette||OK|\n");
	p.CreatePacket(peer);
}
void world_menu(ENetPeer* peer) {
	long long time_now = time(nullptr);
	if (last_active_update - time_now <= 0 or active_worlds.size() == 0) {
		if (worlds.size() > 0) {
			last_active_update = time_now + 60; // 60 tai 1min
			active_worlds.clear();
			for (int i_ = 0; i_ < 20; i_++) {
				World world_ = worlds[rand() % worlds.size()];
				if (world_.nuked or not check_name(world_.name)) continue;
				if (find(active_worlds.begin(), active_worlds.end(), world_.name) == active_worlds.end()) active_worlds.push_back(world_.name);
			}
		}
	}
	string recently_visited = "", c_active_worlds = "";
	for (auto it = pInfo(peer)->last_visited_worlds.rbegin(); it != pInfo(peer)->last_visited_worlds.rend(); ++it) {
		int w_c = 0, s_c = 0, net_ = 0;
		get_players(*it, w_c, s_c, net_);
		recently_visited += "\nadd_floater|" + *it + "|" + to_string(w_c) + "|0.5|3417414143";
	} for (int i_ = 0; i_ < active_worlds.size(); i_++) {
		string name_ = active_worlds.at(i_);
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) == world_->active_jammers.end()) {
				int w_c = 0, s_c = 0, net_ = 0;
				get_players(active_worlds.at(i_), w_c, s_c, net_);
				c_active_worlds += "\nadd_floater|" + active_worlds.at(i_) + "|0|0.5|3529161471";
			}
		}
	}
	if (c_active_worlds.empty()) c_active_worlds = "\nadd_floater|START|0|0.5|3529161471";
	gamepacket_t p;
	p.Insert("OnRequestWorldSelectMenu");
	p.Insert("add_filter|\nadd_heading|Top Worlds|" + c_active_worlds + "\nadd_heading|Recently Visited Worlds<CR>|" + recently_visited + "\n");
	p.CreatePacket(peer);
}
void exit_(ENetPeer* peer, bool reset_ = false) {
	int w_cc = 0, s_cc = 0, net = 1;
	get_players(pInfo(peer)->last_world, w_cc, s_cc, net);
	if (pInfo(peer)->invis == false) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->tankIDName == pInfo(peer)->tankIDName) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->last_world and not pInfo(peer)->last_world.empty()) {
				if (w_cc <= 14) {
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("`5<" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` left, `w" + to_string(w_cc - 1) + "`` others here>``");
					p.CreatePacket(currentPeer);
				}
			}
		}
	}
	if (pInfo(peer)->invis == false) packet_(peer, "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0");
	int w_c = 0, s_c = 0, net_ = 0;
	string w_ = pInfo(peer)->world;
	pInfo(peer)->x = -1, pInfo(peer)->y = -1, pInfo(peer)->world = "";
	pInfo(peer)->geiger_x = -1, pInfo(peer)->geiger_y = -1;
	pInfo(peer)->ac_.clear();
	get_players(w_, w_c, s_c, net_);
	if (w_c == 0) { /*issaugoti worlda is istrinti is atminties*/
		save_world(w_);
	}
	else {
		gamepacket_t p;
		p.Insert("OnRemove");
		p.Insert("netID|" + to_string(pInfo(peer)->netID) + "\n");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == w_) {
				packet_(currentPeer, "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0");
				p.CreatePacket(currentPeer);
			}
		}
	} if (not reset_) {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Where would you like to go? (`w" + to_string(s_c) + "`` online)");
		p.CreatePacket(peer);
		world_menu(peer);
	}
}
string cleanup_(string strText) {
	string temp = "";
	for (int i = 0; i < strText.size(); ++i) {
		if ((strText[i] >= 'a' && strText[i] <= 'z') || (strText[i] >= 'A' && strText[i] <= 'Z')) {
			temp = temp + strText[i];
		}
		else {
			temp = temp + " ";
		}
	}
	return temp;
}
bool has_playmod(Player* p_, string name_) {
	name_ = replace_str2(cleanup_(to_lower(name_)), " ", "_");
	vector<string> player_playmods;
	player_playmods.push_back(items.at(p_->hair).playmod);
	player_playmods.push_back(items.at(p_->shirt).playmod);
	player_playmods.push_back(items.at(p_->pants).playmod);
	player_playmods.push_back(items.at(p_->feet).playmod);
	player_playmods.push_back(items.at(p_->face).playmod);
	player_playmods.push_back(items.at(p_->hand).playmod);
	player_playmods.push_back(items.at(p_->back).playmod);
	player_playmods.push_back(items.at(p_->mask).playmod);
	player_playmods.push_back(items.at(p_->necklace).playmod);
	player_playmods.push_back(items.at(p_->ances).playmod);
	if (p_->ghost) player_playmods.push_back("Ghost in the Shell");
	if (p_->b_s != 0) player_playmods.push_back("Duct Tape");
	for (int i_ = 0; i_ < player_playmods.size(); i_++) {
		if (player_playmods.at(i_).empty()) continue;
		string playmod = replace_str2(cleanup_(to_lower(player_playmods.at(i_))), " ", "_");
		if (playmod.find(name_) != string::npos)
			return true;
	}
	return false;
}
int form_state(Player* p_) {
	int state_ = 0;
	state_ |= has_playmod(p_, "Ghost in the Shell") << 0;
	state_ |= has_playmod(p_, "double jump") << 1;
	state_ |= p_->hs << 24;
	return state_;
}
string process_till(std::string const& s)
{
	std::string::size_type pos = s.find('/');
	if (pos != std::string::npos)
	{
		return s.substr(0, pos);
	}
	else
	{
		return s;
	}
}
void update_clothes(ENetPeer* peer) {
	gamepacket_t p(0, pInfo(peer)->netID);
	p.Insert("OnSetClothing");
	p.Insert((float)pInfo(peer)->hair, (float)pInfo(peer)->shirt, (float)pInfo(peer)->pants); // hair shirt pants
	p.Insert((float)pInfo(peer)->feet, (float)pInfo(peer)->face, (float)pInfo(peer)->hand); // feet face hand 
	p.Insert((float)pInfo(peer)->back, (float)pInfo(peer)->mask, (float)pInfo(peer)->necklace); // back mask neck
	p.Insert((has_playmod(pInfo(peer), "ninja stealth") ? 1684300950 : pInfo(peer)->skin)); // 1684300950
	p.Insert((float)pInfo(peer)->ances, 0, 0); // tie kiti 2 tai nzn  
	PlayerMoving data{ pInfo(peer)->netID, 0, 0x14, 0, form_state(pInfo(peer)), 0, 0, 0, 1200, (has_playmod(pInfo(peer), "cupid's firepower") ? float(-300) : (has_playmod(pInfo(peer), "fists o' fury") ? 500 : (has_playmod(pInfo(peer), "Dragonborn") ? 500 : (has_playmod(pInfo(peer), "devouring souls") ? -300 : 200)))), (has_playmod(pInfo(peer), "speedy") ? float(310) : (has_playmod(pInfo(peer), "putt putt putt") ? 150 : (has_playmod(pInfo(peer), "fleet of foot") ? float(310) : 250))), (has_playmod(pInfo(peer), "high jump") ? float(700) : 1000) };
	BYTE* raw = packPlayerMoving(&data);
	int e_ = 8421376 + (items.at(pInfo(peer)->hand).effect != 0 ? items.at(pInfo(peer)->hand).effect : items.at(pInfo(peer)->necklace).effect != 0 ? items.at(pInfo(peer)->necklace).effect : items.at(pInfo(peer)->back).effect != 0 ? items.at(pInfo(peer)->back).effect : items.at(pInfo(peer)->face).effect != 0 ? items.at(pInfo(peer)->face).effect : items.at(pInfo(peer)->mask).effect != 0 ? items.at(pInfo(peer)->mask).effect : items.at(pInfo(peer)->hair).effect != 0 ? items.at(pInfo(peer)->hair).effect : items.at(pInfo(peer)->feet).effect != 0 ? items.at(pInfo(peer)->feet).effect : items.at(pInfo(peer)->shirt).effect != 0 ? items.at(pInfo(peer)->shirt).effect : items.at(pInfo(peer)->pants).effect != 0 ? items.at(pInfo(peer)->pants).effect : items.at(pInfo(peer)->ances).effect != 0 ? items.at(pInfo(peer)->ances).effect : 0);
	memcpy(raw + 1, &e_, 3); //16777218
	uint8_t e2 = 128, e3 = 128;
	memcpy(raw + 2, &e2, 1);
	memcpy(raw + 3, &e3, 1);
	float waterspeed = 125.0f;
	memcpy(raw + 16, &waterspeed, 4);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == pInfo(peer)->world) {
			p.CreatePacket(currentPeer);
			send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			if (pInfo(peer)->netID != pInfo(currentPeer)->netID) {
				gamepacket_t p(0, pInfo(currentPeer)->netID);
				p.Insert("OnSetClothing");
				p.Insert((float)pInfo(currentPeer)->hair, (float)pInfo(currentPeer)->shirt, (float)pInfo(currentPeer)->pants); // hair shirt pants
				p.Insert((float)pInfo(currentPeer)->feet, (float)pInfo(currentPeer)->face, (float)pInfo(currentPeer)->hand); // feet face hand 
				p.Insert((float)pInfo(currentPeer)->back, (float)pInfo(currentPeer)->mask, (float)pInfo(currentPeer)->necklace); // back mask neck
				p.Insert((has_playmod(pInfo(currentPeer), "ninja stealth") ? 1684300950 : pInfo(currentPeer)->skin));
				p.Insert((float)pInfo(currentPeer)->ances, 0, 0); // tie kiti 2 tai nzn   
				p.CreatePacket(peer); // kiti tau
				PlayerMoving data{ pInfo(currentPeer)->netID, 0, 0x14, 0, form_state(pInfo(currentPeer)), 0, 0, 0, 1200, (has_playmod(pInfo(currentPeer), "cupid's firepower") ? float(-300) : (has_playmod(pInfo(currentPeer), "fists o' fury") ? 500 : (has_playmod(pInfo(currentPeer), "Dragonborn") ? 500 : (has_playmod(pInfo(currentPeer), "devouring souls") ? -300 : 200)))), (has_playmod(pInfo(currentPeer), "speedy") ? float(310) : (has_playmod(pInfo(currentPeer), "putt putt putt") ? 150 : 250)), (has_playmod(pInfo(currentPeer), "high jump") ? float(700) : 1000) };
				BYTE* raw_ = packPlayerMoving(&data);
				int e_ = 8421376 + (items.at(pInfo(currentPeer)->hand).effect != 0 ? items.at(pInfo(currentPeer)->hand).effect : items.at(pInfo(currentPeer)->necklace).effect != 0 ? items.at(pInfo(currentPeer)->necklace).effect : items.at(pInfo(currentPeer)->back).effect != 0 ? items.at(pInfo(currentPeer)->back).effect : items.at(pInfo(currentPeer)->face).effect != 0 ? items.at(pInfo(currentPeer)->face).effect : items.at(pInfo(currentPeer)->mask).effect != 0 ? items.at(pInfo(currentPeer)->mask).effect : items.at(pInfo(currentPeer)->hair).effect != 0 ? items.at(pInfo(currentPeer)->hair).effect : items.at(pInfo(currentPeer)->feet).effect != 0 ? items.at(pInfo(currentPeer)->feet).effect : items.at(pInfo(currentPeer)->shirt).effect != 0 ? items.at(pInfo(currentPeer)->shirt).effect : items.at(pInfo(currentPeer)->pants).effect != 0 ? items.at(pInfo(currentPeer)->pants).effect : items.at(pInfo(currentPeer)->ances).effect != 0 ? items.at(pInfo(currentPeer)->ances).effect : 0);
				memcpy(raw_ + 1, &e_, 3);
				uint8_t e2 = 128, e3 = 128;
				memcpy(raw + 2, &e2, 1);
				memcpy(raw + 3, &e3, 1);
				float waterspeed = 125.0f;
				memcpy(raw_ + 16, &waterspeed, 4);
				send_raw(peer, 4, raw_, 56, ENET_PACKET_FLAG_RELIABLE);
				delete[]raw_;
			}
		}
	}
	delete[]raw;
}
void unequip_(ENetPeer* p_, const int id_) {
	bool stat_ = 0;
	ItemDB item_ = items.at(id_);
	switch (items.at(id_).clothType) {
	case ClothTypes::ANCES:
		if (pInfo(p_)->ances == id_)
			pInfo(p_)->ances = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::BACK:
		if (pInfo(p_)->back == id_)
			pInfo(p_)->back = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::FACE:
		if (pInfo(p_)->face == id_)
			pInfo(p_)->face = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::FEET:
		if (pInfo(p_)->feet == id_)
			pInfo(p_)->feet = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::HAIR:
		if (pInfo(p_)->hair == id_)
			pInfo(p_)->hair = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::HAND:
		if (pInfo(p_)->hand == id_)
			pInfo(p_)->hand = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::MASK:
		if (pInfo(p_)->mask == id_)
			pInfo(p_)->mask = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::NECKLACE:
		if (pInfo(p_)->necklace == id_)
			pInfo(p_)->necklace = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::PANTS:
		if (pInfo(p_)->pants == id_)
			pInfo(p_)->pants = 0, update_clothes(p_), stat_ = 1;
		break;
	case ClothTypes::SHIRT:
		if (pInfo(p_)->shirt == id_)
			pInfo(p_)->shirt = 0, update_clothes(p_), stat_ = 1;
		break;
	default:
		break;
	}
	if (stat_)
		packet_(p_, "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0");
	if (stat_ and item_.on_remove != "" or id_ == 2286 or id_ == 2204) {
		packet_(p_, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
		if (id_ == 2204) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("Geiger Counter removed. (`$Geiger Counting`` mod removed)");
			p.CreatePacket(p_);
		}
		else if (id_ == 2286 and pInfo(p_)->geiger_ < 100) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("Geiger Counter is no longer charging! (`$Charging Geiger Counter`` mod removed)");
			p.CreatePacket(p_);
			pInfo(p_)->geiger_ = 0;
		}
		else {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert(item_.on_remove + (item_.playmod != "" ? " (`$" + item_.playmod + "`` mod removed)" : ""));
			p.CreatePacket(p_);
		}
	}
}
int modify_inventory(ENetPeer* p_, const int i_, int& c_, bool upd_inv_visuals = true, bool force_return = false) {
	if (c_ > 200 or i_ <= 0) return -1;
	if (c_ == 0) upd_inv_visuals = false;
	int ori_ = c_;
	Player* k_ = pInfo(p_);
	int last_free_ = -1;
	for (int a_ = 0; a_ < k_->inv.size(); a_++) {
		if (k_->inv.at(a_).id == i_) {
			if (k_->inv.at(a_).count + c_ <= 200) {
				if (c_ < 0 and k_->inv.at(a_).count + c_ < 0) return -1;
				if (k_->inv.at(a_).count + c_ == 0) {
					if (items.at(k_->inv.at(a_).id).blockType == BlockTypes::CLOTHING)
						unequip_(p_, k_->inv.at(a_).id);
					k_->inv.at(a_).id = 0, k_->inv.at(a_).count = 0;
					goto s_;
				}
				k_->inv.at(a_).count += c_;
				if (c_ == 0) {
					c_ = k_->inv.at(a_).count;
					return -1;
				}
				c_ = k_->inv.at(a_).count;
			}
			else {
				if (force_return)
					c_ = k_->inv.at(a_).count;
				return -1;
			}
			goto s_;
		}
		else if (k_->inv.at(a_).id == 0 and last_free_ == -1) {
			last_free_ = a_;
		}
		if (a_ + 1 == k_->inv.size()) {
			if (last_free_ != -1 and c_ > 0) {
				k_->inv.at(last_free_).id = i_, k_->inv.at(last_free_).count = c_;
				goto s_;
			}
			return -1;
		}
	}
s_:
	if (upd_inv_visuals and c_ != 0) {
		PlayerMoving data_{};
		data_.packetType = 13, data_.plantingTree = i_;
		BYTE* raw = packPlayerMoving(&data_);
		raw[(ori_ < 0 ? 2 : 3)] = ori_ < 0 ? (ori_ * -1) : ori_;
		send_raw(p_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
		delete[]raw;
	}
	return 0;
}
int form_visual(BYTE*& blc, WorldBlock block_, World world_, ENetPeer* peer, bool case_ = true) {
	uint32_t ySize = world_.blocks.size() / 100, xSize = world_.blocks.size() / ySize, square = world_.blocks.size();
	if (not case_) {
		memcpy(blc, &block_.fg, 2);
		memcpy(blc + 2, &block_.bg, 2);
		memcpy(blc + 4, &block_.flags, 4);
	}
	if (items.at(block_.fg).trickster) {
		BYTE btype = 52;
		memcpy(blc + 8, &btype, 1);
		if (case_) {
			blc += 1;
			return 1;
		}
	}
	if (items.at(block_.fg).trans) {
		BYTE btype = 19;
		memcpy(blc + 8, &btype, 1);
		if (case_) {
			blc += 19;
			return 19;
		}
	}
	if (items.at(block_.fg).charger) {
		BYTE btype = 57;
		memcpy(blc + 8, &btype, 1);
		uint16_t sk = 0;
		memcpy(blc + 9, &sk, 2);
		if (case_) {
			blc += 5;
			return 5;
		}
	}
	if (items.at(block_.fg).magplant or items.at(block_.fg).item_sucker) {
		switch (block_.fg) {
		case 5638: // magplant
		{
			uint8_t magnetronas_ijungtas = block_.magnetron ? 1 : 0;
			uint8_t active_ = block_.enabled ? 1 : 0;
			uint32_t block_id = block_.id;
			uint32_t item_count = block_.pr;
			uint32_t kiek_telpa = 5000;
			BYTE btype = 62;
			memcpy(blc + 8, &btype, 1);
			memcpy(blc + 9, &block_id, 4);
			memcpy(blc + 13, &item_count, 4);
			memcpy(blc + 17, &active_, 1);
			memcpy(blc + 18, &magnetronas_ijungtas, 1);
			memcpy(blc + 20, &kiek_telpa, 2);
			if (case_) {
				blc += 15;
				return 15;
			}
			break;
		}
		case 6948: case 6946:
		{
			int max_telpa = 1500;
			int active_ = block_.enabled ? 1 : 0;
			int block_id = block_.id;
			int item_count = block_.pr;
			BYTE btype = 62;
			memcpy(blc + 8, &btype, 1);
			memcpy(blc + 9, &block_id, 4);
			memcpy(blc + 13, &item_count, 4);
			memcpy(blc + 17, &active_, 4);
			memcpy(blc + 21, &max_telpa, 4);
			if (case_) {
				blc += 15;
				return 15;
			}
			break;
		}
		case 6950: case 6952:
		{
			int actually_active = block_.pr > 0 ? 1 : 0;
			int amount_of_gems = block_.pr;
			int block_id = block_.id;
			int is_enabled = block_.enabled ? 1 : 0;
			BYTE btype = (block_.fg == 6950 ? 70 : 69);
			memcpy(blc + 8, &btype, 1);
			memcpy(blc + 9, &actually_active, 4);
			memcpy(blc + 13, &amount_of_gems, 4);
			memcpy(blc + 17, &block_id, 4);
			memcpy(blc + 21, &is_enabled, 4);
			if (case_) {
				blc += 13;
				return 13;
			}
		}
		}
	}
	switch (items[block_.fg].blockType) {
	case BlockTypes::CRYSTAL:
	{
		BYTE btype = 20;
		memcpy(blc + 8, &btype, 1);
		string text = "";
		int l_ = (int)text.size();
		memcpy(blc + 9, &l_, 2);
		memcpy(blc + 11, text.c_str(), l_);
		if (case_) {
			blc += 3 + l_;
			return 3 + l_;
		}
		break;
	}
	case BlockTypes::WEATHER:
	{
		switch (block_.fg) {
		case 5000:
		{
			BYTE btype = 40;
			memcpy(blc + 8, &btype, 1);
			uint32_t item_id = (block_.id != 0 ? block_.id : 14);
			memcpy(blc + 9, &item_id, 4);
			if (case_) {
				blc += 5;
				return 5;
			}
			break;
		}
		case 3832:
		{
			BYTE btype = 49;
			memcpy(blc + 8, &btype, 1);
			uint32_t item_id = (block_.id != 0 ? block_.id : 2);
			uint32_t item_gravity = block_.gravity;
			uint8_t item_status = block_.spin | (block_.invert << 1);
			memcpy(blc + 9, &item_id, 4);
			memcpy(blc + 13, &item_gravity, 4);
			memcpy(blc + 17, &item_status, 4);
			if (case_) {
				blc += 10;
				return 10;
			}
			break;
		}
		}
		break;
	}
	case BlockTypes::VENDING:
	{
		uint32_t item_id = block_.id;
		uint32_t item_price = block_.pr;
		uint32_t item_count = block_.c_;
		uint32_t vend_available_wls = block_.wl;
		int visual = block_.flags | ((int)item_id == 0 ? ((int)vend_available_wls != 0 ? 0x02000000 : 0x00000000) : ((int)vend_available_wls != 0 ? 0x02410000 : 0x00410000));
		if ((int)item_price < 0 and (int)item_id != 0) {
			if ((int)item_count < ((int)item_price * -1))
				item_id = 0, item_price = 0;
			visual = block_.flags | (((int)item_count < ((int)item_price * -1)) ? ((int)vend_available_wls != 0 ? 0x02410000 : 0x00410000) : ((int)vend_available_wls != 0 ? 0x02410000 : 0x00410000));
		}
		memcpy(blc + 4, &visual, 4);
		BYTE btype = 24;
		memcpy(blc + 8, &btype, 1);
		memcpy(blc + 9, &item_id, 4);
		memcpy(blc + 13, &item_price, 4);
		if (case_) {
			blc += 9;
			return 9;
		}
		break;
	}
	case BlockTypes::DISPLAY:
	{
		BYTE btype = 23;
		memcpy(blc + 8, &btype, 1);
		uint32_t id_ = block_.id;
		memcpy(blc + 9, &id_, 4);
		if (case_) {
			blc += 5;
			return 5;
		}
		break;
	}
	case BlockTypes::PROVIDER:
	{
		BYTE btype = 9;
		memcpy(blc + 8, &btype, 1);
		uint32_t laikas = uint32_t((time(nullptr) - block_.planted <= items.at(block_.fg).growTime ? time(nullptr) - block_.planted : items.at(block_.fg).growTime));
		memcpy(blc + 9, &laikas, 4);
		if (case_) {
			blc += 5;
			return 5;
		}
		break;
	}
	case BlockTypes::RANDOM_BLOCK:
	{
		BYTE btype = 8;
		memcpy(blc + 8, &btype, 1);
		memcpy(blc + 9, &block_.roll, 1);
		if (case_) {
			blc += 2;
			return 2;
		}
		break;
	}
	case BlockTypes::LOCK:
	{
		if (block_.open_to_public) {
			int new_ = 0x00800000;
			memcpy(blc + 4, &new_, 4);
		}
		BYTE btype = 3;
		memcpy(blc + 8, &btype, 1);
		uint8_t world_settings = world_.disable_music_blocks ? (world_.make_music_blocks_invisible ? 12345 : 1234) : (world_.make_music_blocks_invisible ? 100 : 0);
		uint32_t world_owner_id = -1;
		{
			if (block_.fg == 202 or block_.fg == 204 or block_.fg == 206 or block_.fg == 4994) {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (block_.owner_name == pInfo(currentPeer)->tankIDName) {
						world_owner_id = pInfo(currentPeer)->id;
					}
				}
			}
			else {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (world_.owner_name == pInfo(currentPeer)->tankIDName) {
						world_owner_id = pInfo(currentPeer)->id;
					}
				}
			}
		}
		uint32_t admin_id = 0;
		uint32_t bpm_ = world_.music_bpm * -1; //world_.music_bpm * -1
		memcpy(blc + 9, &world_settings, 1);
		memcpy(blc + 10, &world_owner_id, 4);
		memcpy(blc + 18, &bpm_, 4);
		uint32_t count_of_admins = 1;
		{
			if (block_.fg == 202 or block_.fg == 204 or block_.fg == 206 or block_.fg == 4994) {
				if (find(block_.admins.begin(), block_.admins.end(), pInfo(peer)->tankIDName) != block_.admins.end()) {
					memcpy(blc + 22, &pInfo(peer)->id, 4);
					count_of_admins++;
				} for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_.name) {
						if (find(block_.admins.begin(), block_.admins.end(), pInfo(currentPeer)->tankIDName) != block_.admins.end()) {
							memcpy(blc + 22 + (count_of_admins * 4), &pInfo(currentPeer)->id, 4);
							count_of_admins++;
							if (count_of_admins > 7) break;
						}
					}
				}
			}
			else {
				if (find(world_.admins.begin(), world_.admins.end(), pInfo(peer)->tankIDName) != world_.admins.end()) {
					memcpy(blc + 22, &pInfo(peer)->id, 4);
					count_of_admins++;
				} for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_.name) {
						if (find(world_.admins.begin(), world_.admins.end(), pInfo(currentPeer)->tankIDName) != world_.admins.end()) {
							memcpy(blc + 22 + (count_of_admins * 4), &pInfo(currentPeer)->id, 4);
							count_of_admins++;
							if (count_of_admins > 7) break;
						}
					}
				}
			}
			memcpy(blc + 14, &count_of_admins, 1);
		}
		if (case_) {
			blc += 10 + (count_of_admins * 4);
			return 10 + (count_of_admins * 4);
		}
		break;
	}
	case BlockTypes::MAIN_DOOR:
	{
		BYTE btype = 1;
		memcpy(blc + 8, &btype, 1);
		string text = "EXIT";
		int l_ = (int)text.size();
		memcpy(blc + 9, &l_, 2);
		memcpy(blc + 11, text.c_str(), l_);
		if (case_) {
			blc += 4 + l_;
			return 4 + l_;
		}
		break;
	}
	case BlockTypes::SEED:
	{
		int visual = block_.flags | 0x100000;
		memcpy(blc + 4, &visual, 4);
		BYTE data_type = 4;
		memcpy(blc + 8, &data_type, 1);
		uint32_t laikas = uint32_t((time(nullptr) - block_.planted <= items.at(block_.fg).growTime ? time(nullptr) - block_.planted : items.at(block_.fg).growTime));
		uint8_t count = uint8_t(block_.fruit);
		memcpy(blc + 9, &laikas, 4);
		memcpy(blc + 13, &count, 1);
		if (case_) {
			blc += 6;
			return 6;
		}
		break;
	}
	case BlockTypes::DOOR: case BlockTypes::PORTAL:
	{
		BYTE data_type = 1;
		memcpy(blc + 8, &data_type, 1);
		string duru_tekstas = (block_.txt.empty() ? (block_.door_destination.empty() ? "" : (block_.door_destination.find(":") != string::npos ? explode(":", block_.door_destination)[0] + "..." : block_.door_destination)) : block_.txt);
		uint32_t dydis = uint32_t(duru_tekstas.size());
		memcpy(blc + 9, &dydis, 2);
		memcpy(blc + 11, duru_tekstas.c_str(), dydis);
		uint8_t locked_ = (block_.open ? 0 : 0x08);
		memcpy(blc + 11 + dydis, &locked_, 1);
		if (case_) {
			blc += 4 + dydis;
			return 4 + dydis;
		}
		break;
	}
	case BlockTypes::SIGN:
	{
		BYTE data_type = 2;
		memcpy(blc + 8, &data_type, 1);
		string sign_tekstas = block_.txt;
		uint32_t dydis = uint32_t(sign_tekstas.size());
		memcpy(blc + 9, &dydis, 2);
		memcpy(blc + 11, sign_tekstas.c_str(), dydis);
		uint32_t nzn_kas = 0;
		memcpy(blc + 11 + dydis, &nzn_kas, 1);
		if (case_) {
			blc += 7 + dydis;
			return 7 + dydis;
		}
		break;
	}
	}
}
void upd_lock(WorldBlock block_2, World world_, ENetPeer* peer) {
	int l_x = block_2.lock_origin % 100;
	int l_y = block_2.lock_origin / 100;
	WorldBlock block_ = world_.blocks.at(l_x + (l_y * 100));
	vector<WorldBlock> shadow_copy_2 = world_.blocks;
	vector<vector<int>> locked_tiles_around_lock{};
	vector<int> new_tiles{};
	new_tiles.push_back(l_x + (l_y * 100));
	try {
		for (int i2 = 0; i2 < new_tiles.size(); i2++) {
			int s_x_ = new_tiles.at(i2) % 100, s_y_ = new_tiles.at(i2) / 100;
			if (s_x_ < 99 and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).lock_origin == (l_x + (l_y * 100))) {
				if (not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned) {
					shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned = true;
					new_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
					locked_tiles_around_lock.push_back({ s_x_ + 1, s_y_ });
				}
			} if (s_x_ > 0 and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).lock_origin == (l_x + (l_y * 100))) {
				if (not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned) {
					shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned = true;
					new_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
					locked_tiles_around_lock.push_back({ s_x_ - 1, s_y_ });
				}
			} if (s_y_ < 59 and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin == (l_x + (l_y * 100))) {
				if (not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned) {
					shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned = true;
					new_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
					locked_tiles_around_lock.push_back({ s_x_, s_y_ + 1 });
				}
			} if (s_y_ > 0 and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin == (l_x + (l_y * 100))) {
				if (not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned) {
					shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned = true;
					new_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
					locked_tiles_around_lock.push_back({ s_x_, s_y_ - 1 });
				}
			}
		}
	}
	catch (out_of_range) {

	}
	int lock_size = locked_tiles_around_lock.size();
	if (locked_tiles_around_lock.size() != 0) {
		PlayerMoving data_{};
		data_.packetType = 15, data_.punchX = l_x, data_.punchY = l_y, data_.characterState = 0x8;
		data_.netID = peer == NULL ? -1 : (block_.owner_name == pInfo(peer)->tankIDName ? pInfo(peer)->id : -1);
		data_.plantingTree = block_.fg;
		BYTE* raw;
		raw = packPlayerMoving(&data_, 112 + locked_tiles_around_lock.size() * 2);
		int lalala = 8;
		memcpy(raw + 8, &lock_size, 2);
		memcpy(raw + 12, &lalala, 2);
		BYTE* blc = raw + 56;
		for (int i_ = 0; i_ < locked_tiles_around_lock.size(); i_++) {
			vector<int> update_tiles = locked_tiles_around_lock.at(i_);
			int x = update_tiles.at(0);
			int y = update_tiles.at(1);
			int sq_ = x + (y * 100);
			memcpy(blc + (i_ * 2), &sq_, 2);
			shadow_copy_2.at(x + (y * 100)).scanned = false;
		}
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (world_.name == pInfo(currentPeer)->world) {
				send_raw(currentPeer, 4, raw, 112 + locked_tiles_around_lock.size() * 2, ENET_PACKET_FLAG_RELIABLE);
				PlayerMoving data_2{};
				data_2.packetType = 5, data_2.punchX = l_x, data_2.punchY = l_y, data_2.characterState = 0x8;
				BYTE* raw2 = packPlayerMoving(&data_2, 112);
				BYTE* blc2 = raw2 + 56;
				form_visual(blc2, block_, world_, currentPeer, false);
				send_raw(currentPeer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
				delete[] raw2, blc2;
			}
		}
		delete[] raw, blc;
	}
	else {
		PlayerMoving data_{};
		data_.packetType = 15, data_.punchX = l_x, data_.punchY = l_y, data_.characterState = 0x8;
		data_.netID = block_.owner_name == pInfo(peer)->tankIDName ? pInfo(peer)->id : -1;
		data_.plantingTree = block_.fg;
		BYTE* raw = packPlayerMoving(&data_, 56);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (world_.name == pInfo(currentPeer)->world) {
				send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
				PlayerMoving data_2{};
				data_2.packetType = 5, data_2.punchX = l_x, data_2.punchY = l_y, data_2.characterState = 0x8;
				BYTE* raw2 = packPlayerMoving(&data_2, 112);
				BYTE* blc2 = raw2 + 56;
				form_visual(blc2, block_, world_, currentPeer, false);
				send_raw(currentPeer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
				delete[] raw2, blc2;
			}
		}
		delete[] raw;
	}
}
void add_ban(ENetPeer* peer, int seconds, string reason, string bannedby) {
	if (pInfo(peer)->b_t + (seconds * 1000) < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		pInfo(peer)->logs.push_back("" + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/2021 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + " " + bannedby + " - >> Ban for " + to_string(seconds) + " seconds(" + reason + ")");
		pInfo(peer)->bans.push_back("`6ON:`` `#" + pInfo(peer)->tankIDName + "`` `0(" + pInfo(peer)->requestedName + ") #" + to_string(pInfo(peer)->netID) + "`` Secs: " + to_string(seconds) + " IP: " + pInfo(peer)->ip + " ");
		pInfo(peer)->b_s = (seconds * 1000);
		pInfo(peer)->b_r = reason;
		pInfo(peer)->b_b = bannedby;
		pInfo(peer)->b_t = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		update_clothes(peer);
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oReality flickers as you begin to wake up. (`$Ban`` mod added, " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds") + " left)");
			p.CreatePacket(peer);
		}
		gamepacket_t p, p2;
		p.Insert("OnConsoleMessage");
		p.Insert((bannedby == "System" ? "`4**`` " + pInfo(peer)->tankIDName + " `4AUTO-BANNED BY SYSTEM **`` (/rules to view rules)" : "`#**`` `$The Ancients`` have used `#Ban`` on ``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `#**``"));
		p2.Insert("OnConsoleMessage");
		p2.Insert("`#**`` `$The Ancient Ones`` have `4banned`` " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `#**`` (`4/rules`` to see the rules!)");
		gamepacket_t p3(0, pInfo(peer)->netID);
		p3.Insert("OnPlayPositioned");
		p3.Insert("audio/keypad_hit.wav");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->world) {
				p.CreatePacket(currentPeer), p3.CreatePacket(currentPeer);
			}
			else {
				p2.CreatePacket(currentPeer);
			}
		}
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oWarning from `4System``: You've been `4BANNED`` from `wGrowtopia`` for " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
			p.CreatePacket(peer);
			{
				gamepacket_t p;
				p.Insert("OnAddNotification");
				p.Insert("interface/atomic_button.rttex");
				p.Insert("`wWarning from `4System``: You've been `4BANNED`` from Growtopia for " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
				p.Insert("audio/hub_open.wav");
				p.Insert(0);
				p.CreatePacket(peer);
			}
		}
		enet_peer_disconnect_later(peer, 0);
	}
}

void add_mute(ENetPeer* peer, int seconds, string reason, string muttedby) {
	if (not has_playmod(pInfo(peer), "duct tape")) {
		PlayMods give_playmod{};
		give_playmod.id = 11;
		give_playmod.time = time(nullptr) + seconds;
		pInfo(peer)->playmods.push_back(give_playmod);
		update_clothes(peer);
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oDuct tape has covered your mouth! (`$Duct Tape`` mod added, " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds") + " left)");
			p.CreatePacket(peer);
		}
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`#**`` `$The Gods`` have duct-taped " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`o's mouth `#**`` (`4/rules`` to see the rules!)");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			p.CreatePacket(currentPeer);
		}
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oWarning from `4Admin``: You've been `4duct-taped`` for " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
			p.CreatePacket(peer);
			{
				gamepacket_t p;
				p.Insert("OnAddNotification");
				p.Insert("interface/atomic_button.rttex");
				p.Insert("`wWarning from `4Admin``: You've been `4duct-taped`` for " + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
				p.Insert("audio/hub_open.wav");
				p.Insert(0);
				p.CreatePacket(peer);
			}
		}
	}
}

void join_world(ENetPeer* peer, string& name_, int spawnas_x = 0, int spawnas_y = 0, int delay = 0, bool locked = false, bool door = false) {
	if (pInfo(peer)->tankIDName.empty()) return;
	if (not door) {
		if (pInfo(peer)->world_time + 1500 > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
			gamepacket_t p;
			p.Insert("OnFailedToEnterWorld");
			p.CreatePacket(peer);
			return;
		}
		pInfo(peer)->world_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	}
	if (not check_name(name_)) {
		if (door) {
			gamepacket_t p(delay, pInfo(peer)->netID);
			p.Insert("OnSetFreezeState");
			p.Insert(1);
			p.CreatePacket(peer);
			{
				gamepacket_t p(delay);
				p.Insert("OnConsoleMessage");
				p.Insert(name_);
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p(delay);
				p.Insert("OnZoomCamera");
				p.Insert((float)10000.000000);
				p.Insert(1000);
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnSetFreezeState");
				p.Insert(0);
				p.CreatePacket(peer);
			}
		}
		else {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert(name_);
			p.CreatePacket(peer);
			{
				gamepacket_t p;
				p.Insert("OnFailedToEnterWorld");
				p.CreatePacket(peer);
			}
		}
		return;
	}
	if (pInfo(peer)->n == 0) name_ = "START";
	World world_ = get_world(name_);
	string owner_name = world_.owner_name, user_name = pInfo(peer)->tankIDName;
	if (world_.nuked == true && pInfo(peer)->mod + pInfo(peer)->dev < 1) {
		if (door) {
			gamepacket_t p(delay, pInfo(peer)->netID);
			p.Insert("OnSetFreezeState");
			p.Insert(1);
			p.CreatePacket(peer);
			{
				gamepacket_t p(delay);
				p.Insert("OnConsoleMessage");
				p.Insert("That world is inaccessible.");
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p(delay);
				p.Insert("OnZoomCamera");
				p.Insert((float)10000.000000);
				p.Insert(1000);
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnSetFreezeState");
				p.Insert(0);
				p.CreatePacket(peer);
			}
		}
		else {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("That world is inaccessible.");
			p.CreatePacket(peer);
			{
				gamepacket_t p;
				p.Insert("OnFailedToEnterWorld");
				p.CreatePacket(peer);
			}
		}
		return;
	}
	for (pair<string, long long int> p : world_.bannedPlayers) {
		if (p.first == pInfo(peer)->tankIDName) {
			long long int time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			if (p.second + WORLDBAN_TIME > time) {
				if (door) {
					gamepacket_t p(delay, pInfo(peer)->netID);
					p.Insert("OnSetFreezeState");
					p.Insert(1);
					p.CreatePacket(peer);
					{
						gamepacket_t p(delay);
						p.Insert("OnConsoleMessage");
						p.Insert("`4Oh no!`` You've been banned from that world by its owner! Try again later after the world ban wears off.");
						p.CreatePacket(peer);
					}
					{
						gamepacket_t p(delay);
						p.Insert("OnZoomCamera");
						p.Insert((float)10000.000000);
						p.Insert(1000);
						p.CreatePacket(peer);
					}
					{
						gamepacket_t p(delay, pInfo(peer)->netID);
						p.Insert("OnSetFreezeState");
						p.Insert(0);
						p.CreatePacket(peer);
					}
				}
				else {
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("`4Oh no!`` You've been banned from that world by its owner! Try again later after the world ban wears off.");
					p.CreatePacket(peer);
					{
						gamepacket_t p;
						p.Insert("OnFailedToEnterWorld");
						p.CreatePacket(peer);
					}
				}
				return;
			}
		}
	}
	{
		int w_c = 0, s_c = 0, net_ = 1;
		get_players(world_.name, w_c, s_c, net_);
		if (w_c >= 30 and not pInfo(peer)->dev and not pInfo(peer)->mod) {
			if (door) {
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnSetFreezeState");
				p.Insert(1);
				p.CreatePacket(peer);
				{
					gamepacket_t p(delay);
					p.Insert("OnConsoleMessage");
					p.Insert("Oops, `5" + world_.name + "`` already has `430`` people in it. Try again later.");
					p.CreatePacket(peer);
				}
				{
					gamepacket_t p(delay);
					p.Insert("OnZoomCamera");
					p.Insert((float)10000.000000);
					p.Insert(1000);
					p.CreatePacket(peer);
				}
				{
					gamepacket_t p(delay, pInfo(peer)->netID);
					p.Insert("OnSetFreezeState");
					p.Insert(0);
					p.CreatePacket(peer);
				}
			}
			else {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Oops, `5" + world_.name + "`` already has `430`` people in it. Try again later.");
				p.CreatePacket(peer);
				{
					gamepacket_t p;
					p.Insert("OnFailedToEnterWorld");
					p.CreatePacket(peer);
				}
			}
			return;
		}
	}
	if (pInfo(peer)->level < world_.entry_level and world_.owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev) {
		if (find(world_.admins.begin(), world_.admins.end(), user_name) == world_.admins.end()) {
			if (door) {
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnSetFreezeState");
				p.Insert(1);
				p.CreatePacket(peer);
				{
					gamepacket_t p(delay);
					p.Insert("OnConsoleMessage");
					p.Insert("Players lower than level " + to_string(world_.entry_level) + " can't enter " + world_.name + ".");
					p.CreatePacket(peer);
				}
				{
					gamepacket_t p(delay);
					p.Insert("OnZoomCamera");
					p.Insert((float)10000.000000);
					p.Insert(1000);
					p.CreatePacket(peer);
				}
				{
					gamepacket_t p(delay, pInfo(peer)->netID);
					p.Insert("OnSetFreezeState");
					p.Insert(0);
					p.CreatePacket(peer);
				}
			}
			else {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Players lower than level " + to_string(world_.entry_level) + " can't enter " + world_.name + ".");
				p.CreatePacket(peer);
				{
					gamepacket_t p;
					p.Insert("OnFailedToEnterWorld");
					p.CreatePacket(peer);
				}
			}
			return;
		}
	}
	uint32_t ySize = world_.blocks.size() / 100, xSize = world_.blocks.size() / ySize, square = world_.blocks.size();
	pInfo(peer)->name_color = (pInfo(peer)->dev == 1 ? "`6@" : (pInfo(peer)->mod == 1) ? "`#@" : pInfo(peer)->tankIDName == world_.owner_name ? "`2" : (find(world_.admins.begin(), world_.admins.end(), pInfo(peer)->tankIDName) != world_.admins.end()) ? "`^" : "`0");
	if (world_.name == pInfo(peer)->world) {
		gamepacket_t p(delay, pInfo(peer)->netID);
		p.Insert("OnSetFreezeState");
		p.Insert(1);
		p.CreatePacket(peer);
		int door_x_ = 0; int door_y_ = 0;
		if (spawnas_x != 0) {
			door_x_ = spawnas_x, door_y_ = spawnas_y;
		}
		else if (not locked) {
			for (int i_ = 0; i_ < square; i_++) {
				if (items.at(world_.blocks.at(i_).fg).blockType == BlockTypes::MAIN_DOOR) {
					door_x_ = i_ % xSize, door_y_ = i_ / xSize;
					pInfo(peer)->c_x = door_x_;
					pInfo(peer)->c_y = door_y_;
					gamepacket_t p(delay, pInfo(peer)->netID);
					p.Insert("SetRespawnPos");
					p.Insert(i_);
					p.CreatePacket(peer);
					break;
				}
			}
		}
		else {
			gamepacket_t p(delay);
			p.Insert("OnTalkBubble");
			p.Insert(pInfo(peer)->netID);
			p.Insert("The door is locked.");
			p.Insert(0), p.Insert(0);
			p.CreatePacket(peer);
		}
		{
			if (not locked) {
				pInfo(peer)->x = door_x_ * 32, pInfo(peer)->y = door_y_ * 32;
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnSetPos");
				p.Insert(float(door_x_) * 32, float(door_y_) * 32);
				p.CreatePacket(peer);
			}
		}
		{
			gamepacket_t p(delay);
			p.Insert("OnZoomCamera");
			p.Insert((float)10000.000000);
			p.Insert(1000);
			p.CreatePacket(peer);
		}
		{
			gamepacket_t p(delay, pInfo(peer)->netID);
			p.Insert("OnSetFreezeState");
			p.Insert(0);
			p.CreatePacket(peer);
		}
		{
			if (not locked and not pInfo(peer)->invis) {
				gamepacket_t p(delay, pInfo(peer)->netID);
				p.Insert("OnPlayPositioned");
				p.Insert("audio/door_open.wav");
				p.CreatePacket(peer);
			}
		}
		return;
	}
	else if (not pInfo(peer)->world.empty()) {
		exit_(peer, true);
	}
	size_t namelen = world_.name.length();
	int alloc = (8 * square) + (world_.drop.size() * 20), s1 = 4, s3 = 8, zero = 0;
	//world_.drop.size() * 16
	int total = 78 + namelen + square + 24 + alloc;
	BYTE* data = (byte*)malloc(999999);
	memset(data, 0, total);
	memcpy(data, &s1, 1);
	memcpy(data + 4, &s1, 1);
	memcpy(data + 16, &s3, 1);
	memcpy(data + 66, &namelen, 1);
	memcpy(data + 68, world_.name.c_str(), namelen);
	memcpy(data + 68 + namelen, &xSize, 1);
	memcpy(data + 72 + namelen, &ySize, 1);
	memcpy(data + 76 + namelen, &square, 2);
	BYTE* blc = data + 80 + namelen;
	int spawn_x = 0, spawn_y = 0;
	world_.active_jammers.clear();
	vector<string> world_mods;
	vector<vector<unsigned int>> world_locks;
	for (int i_ = 0; i_ < square; i_++) {
		memcpy(blc, &world_.blocks.at(i_).fg, 2);
		memcpy(blc + 2, &world_.blocks.at(i_).bg, 2);
		memcpy(blc + 4, &world_.blocks.at(i_).flags, 4);
		if (world_.blocks.at(i_).flags & 0x00400000) {
			if (find(world_.active_jammers.begin(), world_.active_jammers.end(), world_.blocks.at(i_).fg) == world_.active_jammers.end()) world_.active_jammers.push_back(world_.blocks.at(i_).fg);
		} if (items.at(world_.blocks.at(i_).fg).blockType == BlockTypes::WEATHER or items.at(world_.blocks.at(i_).fg).infinitymachine or items.at(world_.blocks.at(i_).fg).trans or items.at(world_.blocks.at(i_).fg).spirit or items.at(world_.blocks.at(i_).fg).charger or items.at(world_.blocks.at(i_).fg).trickster or items.at(world_.blocks.at(i_).fg).timer or items.at(world_.blocks.at(i_).fg).magplant or items.at(world_.blocks.at(i_).fg).item_sucker) {
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
		} switch (items[world_.blocks.at(i_).fg].blockType) {
		case BlockTypes::CRYSTAL:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::VENDING:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::DISPLAY:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::PROVIDER:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::RANDOM_BLOCK:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::LOCK:
		{
			if (world_.blocks.at(i_).fg == 202 or world_.blocks.at(i_).fg == 204 or world_.blocks.at(i_).fg == 206 or world_.blocks.at(i_).fg == 4994) {
				world_locks.push_back({ i_ % xSize, i_ / xSize });
			}
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::MAIN_DOOR:
		{
			spawn_x = (i_ % xSize) * 32, spawn_y = (i_ / xSize) * 32;
			pInfo(peer)->c_x = spawn_x / 32;
			pInfo(peer)->c_y = spawn_y / 32;
			BYTE btype = 1;
			memcpy(blc + 8, &btype, 1);
			string text = "EXIT";
			int l_ = (int)text.size();
			memcpy(blc + 9, &l_, 2);
			memcpy(blc + 11, text.c_str(), l_);
			blc += 4 + l_;
			total += 4 + l_;
			break;
		}
		case BlockTypes::SEED:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::DOOR: case BlockTypes::PORTAL:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		case BlockTypes::SIGN:
		{
			total += form_visual(blc, world_.blocks.at(i_), world_, peer);
			break;
		}
		}
		blc += 8;
	}
	int count = int(world_.drop.size()), last_uid = int(world_.drop.size());
	memcpy(blc, &count, 4);
	memcpy(blc + 4, &last_uid, 4);
	blc += 8;
	for (int i_ = 0; i_ < world_.drop.size(); i_++) {
		int item = world_.drop.at(i_).id, count = world_.drop.at(i_).count, uid = world_.drop.at(i_).uid;
		float x = world_.drop.at(i_).x, y = world_.drop.at(i_).y;
		memcpy(blc, &item, 2);
		memcpy(blc + 2, &x, 4);
		memcpy(blc + 6, &y, 4);
		memcpy(blc + 10, &count, 2);
		memcpy(blc + 12, &uid, 4);
		blc += 16;
	}
	ENetPacket* p_ = enet_packet_create(data, total, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p_);
	delete[] data;
	for (int i_ = 0; i_ < world_.machines.size(); i_++) {
		WorldMachines machine_ = world_.machines.at(i_);
		WorldBlock block_ = world_.blocks.at(machine_.x + (machine_.y * 100));
		PlayerMoving data_{};
		data_.packetType = 5, data_.punchX = machine_.x, data_.punchY = machine_.y, data_.characterState = 0x8;
		BYTE* raw = packPlayerMoving(&data_, 112);
		BYTE* blc = raw + 56;
		form_visual(blc, block_, world_, peer, false);
		send_raw(peer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
		delete[] raw, blc;
	}
	if (world_locks.size() > 0) {
		vector<WorldBlock> shadow_copy_2 = world_.blocks;
		for (vector<unsigned int> sk_ : world_locks) {
			int l_x = sk_[0];
			int l_y = sk_[1];
			WorldBlock block_ = world_.blocks.at(l_x + (l_y * 100));
			if (block_.owner_named == "") {
				block_.owner_named = "`o" + block_.owner_name;
				try {
					ifstream ifs("players/" + block_.owner_name + "_.json");
					if (ifs.is_open()) {
						json j;
						ifs >> j;
						if (j["mod"] == 1) block_.owner_named = "`#@" + block_.owner_name;
						if (j["dev"] == 1) block_.owner_named = "`6@" + block_.owner_name;
					} vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (p != worlds.end()) {
						World* world_pointer_ = &worlds.at(p - worlds.begin());
						world_pointer_->blocks.at(l_x + (l_y * 100)).owner_named = block_.owner_named;
					}
				}
				catch (exception) {
					cout << "something failed" << endl;
				}
			}
			vector<vector<int>> locked_tiles_around_lock{};
			vector<int> new_tiles{};
			new_tiles.push_back(l_x + (l_y * 100));
			for (int i2 = 0; i2 < new_tiles.size(); i2++) {
				int s_x_ = new_tiles.at(i2) % 100, s_y_ = new_tiles.at(i2) / 100;
				if (s_x_ < 99 and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).lock_origin == (l_x + (l_y * 100))) {
					if (not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned) {
						shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned = true;
						new_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
						locked_tiles_around_lock.push_back({ s_x_ + 1, s_y_ });
					}
				} if (s_x_ > 0 and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).lock_origin == (l_x + (l_y * 100))) {
					if (not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned) {
						shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned = true;
						new_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
						locked_tiles_around_lock.push_back({ s_x_ - 1, s_y_ });
					}
				} if (s_y_ < 59 and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin == (l_x + (l_y * 100))) {
					if (not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned) {
						shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned = true;
						new_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
						locked_tiles_around_lock.push_back({ s_x_, s_y_ + 1 });
					}
				} if (s_y_ > 0 and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin == (l_x + (l_y * 100))) {
					if (not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned) {
						shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned = true;
						new_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
						locked_tiles_around_lock.push_back({ s_x_, s_y_ - 1 });
					}
				}
			}
			int lock_size = locked_tiles_around_lock.size();
			if (locked_tiles_around_lock.size() != 0) {
				PlayerMoving data_{};
				data_.packetType = 15, data_.punchX = l_x, data_.punchY = l_y, data_.characterState = 0x8;
				data_.netID = block_.owner_name == pInfo(peer)->tankIDName ? pInfo(peer)->id : -1;
				data_.plantingTree = block_.fg;
				BYTE* raw;
				raw = packPlayerMoving(&data_, 112 + locked_tiles_around_lock.size() * 2);
				int lalala = 8;
				memcpy(raw + 8, &lock_size, 2);
				memcpy(raw + 12, &lalala, 2);
				BYTE* blc = raw + 56;
				for (int i_ = 0; i_ < locked_tiles_around_lock.size(); i_++) {
					vector<int> update_tiles = locked_tiles_around_lock.at(i_);
					int x = update_tiles.at(0);
					int y = update_tiles.at(1);
					int sq_ = x + (y * 100);
					memcpy(blc + (i_ * 2), &sq_, 2);
					shadow_copy_2.at(x + (y * 100)).scanned = false;
				}
				send_raw(peer, 4, raw, 112 + locked_tiles_around_lock.size() * 2, ENET_PACKET_FLAG_RELIABLE);
				PlayerMoving data_2{};
				data_2.packetType = 5, data_2.punchX = l_x, data_2.punchY = l_y, data_2.characterState = 0x8;
				BYTE* raw2 = packPlayerMoving(&data_2, 112);
				BYTE* blc2 = raw2 + 56;
				form_visual(blc2, block_, world_, peer, false);
				send_raw(peer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
				delete[] raw, blc, raw2, blc2;
			}
		}
	}
	int w_c = 0, s_c = 0, net_ = 1;
	get_players(world_.name, w_c, s_c, net_);
	pInfo(peer)->netID = net_;
	if (spawnas_x != 0 or spawnas_y != 0) {
		spawn_x = spawnas_x * 32, spawn_y = spawnas_y * 32;
	}
	gamepacket_t p;
	p.Insert("OnSetBux");
	p.Insert(pInfo(peer)->gems);
	p.Insert(1);
	p.CreatePacket(peer);
	{
		//World `wWORLDSHOPFSDFG2 `0[```4JAMMED```0]`` `` entered.  There are `w0`` other people here, `w70,839`` online.
		//1: World `wSELL `0[```2NOPUNCH``, `2IMMUNE```0]`` `` (`3Honors:`` `8#171 today``, `5#232 yesterday``, `w#36 overall``) entered.  There are `w48`` other people here, `w70,716`` online.
		//World `wBUYSHIRT `0[```2NOPUNCH``, `2IMMUNE``, `2ANTIGRAVITY```0]`` `` (`3Honors:`` `8#523 today``) entered.  There are `w1`` other people here, `w70,729`` online.
		//1: World `wTOKODICA `0[```9Shop``, `2NOPUNCH``, `2IMMUNE``, `2NOWAR``, `2ANTIGRAVITY```0]`` `` (`3Honors:`` `8#117 today``, `5#175 yesterday``) entered.  There are `w26`` other people here, `w70,836`` online.
		string nuked = "";
		if (world_.nuked == true) nuked = "`0[NUKED: " + world_.n_b + "," + world_.n_t + "]`` ";
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("" + (pInfo(peer)->mod + pInfo(peer)->dev > 0 ? nuked : "") + "World `w" + world_.name + "`` " + (world_mods.size() != 0 ? "`0[``" + join(world_mods, ", ") + "`0]`` " : "") + "entered.  There are `w" + to_string(w_c) + "`` other people here, `w" + to_string(s_c) + "`` online.");
		p.CreatePacket(peer);
	}
	{
		if (world_.weather != 0) {
			gamepacket_t p;
			p.Insert("OnSetCurrentWeather");
			p.Insert(world_.weather);
			p.CreatePacket(peer);
		}
	}
	{
		gamepacket_t p;
		p.Insert("OnEmoticonDataChanged");
		p.Insert(151749376);
		p.Insert("(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ġ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&(eyes)|ķ|1&(weary)|ĸ|1&");
		p.CreatePacket(peer);
	}
	{
		string s_ = "spawn|avatar\nnetID|" + to_string(net_) + "\nuserID|" + to_string(pInfo(peer)->id) + "\ncolrect|0|0|20|30\nposXY|" + to_string(spawn_x) + "|" + to_string(spawn_y) + "\nname|" + pInfo(peer)->name_color + (pInfo(peer)->tankIDName.empty() ? pInfo(peer)->requestedName : pInfo(peer)->tankIDName) + "``\ncountry|" + pInfo(peer)->country + "\ninvis|" + (pInfo(peer)->invis ? "1" : "0") + "\nmstate|" + (pInfo(peer)->mod or pInfo(peer)->dev ? "1" : "0") + "\nsmstate|" + (pInfo(peer)->dev ? "1" : "0") + "\nonlineID|";
		gamepacket_t p;
		p.Insert("OnSpawn");
		p.Insert(s_);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == name_) {
				p.CreatePacket(currentPeer);
				user_name = pInfo(currentPeer)->tankIDName;
				gamepacket_t p;
				p.Insert("OnSpawn");
				p.Insert("spawn|avatar\nnetID|" + to_string(pInfo(currentPeer)->netID) + "\nuserID|" + to_string(pInfo(currentPeer)->id) + "\ncolrect|0|0|20|30\nposXY|" + to_string(pInfo(currentPeer)->x) + "|" + to_string(pInfo(currentPeer)->y) + "\nname|" + pInfo(currentPeer)->name_color + (pInfo(currentPeer)->tankIDName.empty() ? pInfo(currentPeer)->requestedName : pInfo(currentPeer)->tankIDName) + "``\ncountry|" + pInfo(currentPeer)->country + "\ninvis|" + (pInfo(currentPeer)->invis ? "1" : "0") + "\nmstate|" + (pInfo(currentPeer)->mod or pInfo(currentPeer)->dev ? "1" : "0") + "\nsmstate|" + (pInfo(currentPeer)->dev ? "1" : "0") + "\nonlineID|");
				p.CreatePacket(peer);
				if (w_c <= 14 && w_c >= 1 && pInfo(peer)->invis == false) {
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(peer)->netID);
					p.Insert("`5<" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` entered, `w" + to_string(w_c) + "`` others here>``");
					p.Insert(1);
					p.CreatePacket(currentPeer);
					{
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`5<" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` entered, `w" + to_string(w_c) + "`` others here>``");
						p.CreatePacket(currentPeer);
					}
				}
			}
		}
		{
			gamepacket_t p;
			p.Insert("OnSpawn");
			p.Insert(s_ + "\ntype|local");
			p.CreatePacket(peer);
		}
	}
	/*send world info if any*/
	if (not world_.owner_name.empty()) {
		if (world_.owner_named == "") {
			world_.owner_named = "`o" + world_.owner_name;
			try {
				ifstream ifs("players/" + world_.owner_name + "_.json");
				if (ifs.is_open()) {
					json j;
					ifs >> j;
					if (j["mod"] == 1) world_.owner_named = "`#@" + world_.owner_name;
					if (j["dev"] == 1) world_.owner_named = "`6@" + world_.owner_name;
				}
			}
			catch (exception) {
				cout << "something failed" << endl;
			}
		}
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`5[```w" + world_.name + "`` `$World Locked`` by " + world_.owner_named + "``" + (world_.owner_name == pInfo(peer)->tankIDName or (find(world_.admins.begin(), world_.admins.end(), pInfo(peer)->tankIDName) != world_.admins.end()) ? " (`2ACCESS GRANTED``)" : (world_.open_to_public ? " (`$PUBLIC``)" : "")) + "`5]``");
		p.CreatePacket(peer);
	}
	{
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_pointer_ = &worlds.at(p - worlds.begin());
			world_pointer_->owner_named = world_.owner_named;
			world_pointer_->active_jammers = world_.active_jammers;
		}
	}
	pInfo(peer)->world = world_.name;
	for (int i_ = 0; i_ < pInfo(peer)->last_visited_worlds.size(); i_++) {
		if (pInfo(peer)->last_visited_worlds.at(i_) == world_.name) {
			pInfo(peer)->last_visited_worlds.erase(pInfo(peer)->last_visited_worlds.begin() + i_);
			pInfo(peer)->last_visited_worlds.push_back(world_.name);
		}
		else if (i_ + 1 == pInfo(peer)->last_visited_worlds.size()) {
			if (pInfo(peer)->last_visited_worlds.size() + 1 > 11) {
				pInfo(peer)->last_visited_worlds.erase(pInfo(peer)->last_visited_worlds.begin());
			}
			pInfo(peer)->last_visited_worlds.push_back(world_.name);
		}
	}
	if (pInfo(peer)->last_visited_worlds.size() == 0)
		pInfo(peer)->last_visited_worlds.push_back(world_.name);
	int c_ = 0;
	modify_inventory(peer, 1424, c_);
	if (c_ != 0) {
		c_ *= -1;
		modify_inventory(peer, 1424, c_, false);
	}
	{
		int c_ = 0;
		modify_inventory(peer, 5640, c_);
		if (c_ != 0) {
			c_ *= -1;
			modify_inventory(peer, 5640, c_, false);
			pInfo(peer)->magnetron_id = 0;
			pInfo(peer)->magnetron_x = 0;
			pInfo(peer)->magnetron_y = 0;
		}
	}
	send_inventory(peer);
	if (not pInfo(peer)->invis) packet_(peer, "action|play_sfx\nfile|audio/door_open.wav\ndelayMS|0");
	if (name_ == "START" && pInfo(peer)->n == 0) {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Welcome``|left|6336|\n\nadd_spacer|small|\n\nadd_textbox|`5Welcome to our Growtopia Private Server!``|\nadd_textbox|`0This is where everything begins, at ```1START```0, find and make friends here!``|\nadd_spacer|small|\n\nadd_textbox|`6Newbie player reward:``|left|\nadd_button_with_icon|||staticBlueFrame|9640|1|\nadd_button_with_icon|||staticBlueFrame|954|20|\nadd_button_with_icon|||staticBlueFrame|7164|4|\nadd_button_with_icon|||staticBlueFrame|3898|1|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_smalltext|`e1 My First World, 20 Sugar Cane, 4 Red House Entrance and 1 Telephone.``|left|\n\nadd_spacer|small|\nadd_button|newbie|`2Continue``|NOFLAGS|0|0|\n\nadd_spacer|");
		p.CreatePacket(peer);
		/*
		{
			gamepacket_t p;
			p.Insert("OnTutorialArrow");
			p.Insert("arrow_ui");
			p.Insert(180);
			p.Insert(1);
			p.Insert(2);
			p.Insert(6336);
			p.CreatePacket(peer);
		}*/
	}
	pInfo(peer)->last_world = name_;
}
ENetPeer* get_clicked_on(World* world_, int x_, int y_) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == world_->name and not pInfo(currentPeer)->ghost) {
			if (y_ == pInfo(currentPeer)->y / 32) {
				if (pInfo(currentPeer)->state == 0 and x_ * 32 < pInfo(currentPeer)->x and abs(x_ * 32 - pInfo(currentPeer)->x) < 32 or pInfo(currentPeer)->state == 16 and abs(x_ * 32 - pInfo(currentPeer)->x) < 32 or pInfo(currentPeer)->state != 16 and abs(x_ * 32 - pInfo(currentPeer)->x) < 20) {
					return currentPeer;
				}
			}
		}
	}
	return NULL;
}
void save_player(Player* p_, bool on_exit = true) {
	if (p_->tankIDName.empty() or p_->email.empty()) return;
	if (saving_ and p_->saved_on_close) {
		cout << "already saved" << endl;
		return;
	}
	try {
		//saveall
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		p_->lo = "" + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/2021 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
		json save_, achievements_ = json::array(), friends_ = json::array(), inv_ = json::array(), visited_worlds_ = json::array(), worlds_owned_ = json::array(), playmods_ = json::array();
		save_["name"] = p_->tankIDName;
		save_["n"] = p_->n;
		save_["mod"] = p_->mod;
		save_["dev"] = p_->dev;
		save_["m_h"] = p_->m_h;
		save_["bans"] = p_->bans;
		save_["logs"] = p_->logs;
		save_["b_t"] = p_->b_t;
		save_["b_b"] = p_->b_b;
		save_["dd"] = p_->dd;
		save_["lo"] = p_->lo;
		save_["ip"] = p_->ip;
		save_["b_s"] = p_->b_s;
		save_["b_r"] = p_->b_r;
		save_["m_r"] = p_->m_r;
		save_["m_b"] = p_->m_b;
		save_["note"] = p_->note;
		save_["supp"] = p_->supp;
		save_["hs"] = p_->hs;
		save_["pass"] = p_->tankIDPass, save_["email"] = p_->email;
		save_["aap"] = p_->aap;
		save_["aap2"] = p_->aap2;
		save_["gems"] = p_->gems;
		save_["punch"] = p_->punch_count;
		save_["home_world"] = p_->home_world;
		save_["show_location"] = p_->show_location_;
		save_["show_notifications"] = p_->show_friend_notifications_;
		save_["xp"] = p_->xp;
		save_["level"] = p_->level;
		save_["skin"] = p_->skin;
		save_["geiger"] = p_->geiger_;
		save_["ghost"] = p_->ghost;
		save_["invis"] = p_->invis;
		save_["date"] = p_->account_created;
		save_["booty_broken"] = p_->booty_broken;
		save_["playtime"] = p_->seconds + (time(NULL) - p_->playtime);
		for (int i_ = 0; i_ < p_->inv.size(); i_++) {
			json item_;
			item_["i"] = p_->inv.at(i_).id;
			item_["c"] = p_->inv.at(i_).count;
			inv_.push_back(item_);
		}
		map<string, int>::iterator it;
		for (it = p_->achievements.begin(); it != p_->achievements.end(); it++) {
			json achievement_;
			achievement_["title"] = it->first;
			achievement_["progress"] = it->second;
			achievements_.push_back(achievement_);
		} for (int i_ = 0; i_ < p_->friends.size(); i_++) {
			json friend_;
			friend_["name"] = p_->friends.at(i_).name;
			friend_["mute"] = p_->friends.at(i_).mute;
			friend_["block_trade"] = p_->friends.at(i_).block_trade;
			friend_["last_seen"] = p_->friends.at(i_).last_seen;
			friends_.push_back(friend_);
		} for (int i_ = 0; i_ < p_->last_visited_worlds.size(); i_++) {
			json world_;
			world_["name"] = p_->last_visited_worlds.at(i_);
			visited_worlds_.push_back(world_);
		} for (int i_ = 0; i_ < p_->worlds_owned.size(); i_++) {
			json world_;
			world_["name"] = p_->worlds_owned.at(i_);
			worlds_owned_.push_back(world_);
		} for (int i_ = 0; i_ < p_->playmods.size(); i_++) {
			json playmod_;
			playmod_["id"] = p_->playmods.at(i_).id;
			playmod_["time"] = p_->playmods.at(i_).time;
			playmod_["user"] = p_->playmods.at(i_).user;
			playmods_.push_back(playmod_);
		} 
		json blarneys_ = json::array();
		for (int i_ = 0; i_ < p_->completed_blarneys.size(); i_++) {
			json blarney_;
			blarney_["world"] = p_->completed_blarneys.at(i_).at(0);
			blarney_["time"] = p_->completed_blarneys.at(i_).at(1);
			blarneys_.push_back(blarney_);
		}
		save_["blarney"] = blarneys_;
		save_["playmods"] = playmods_;
		save_["worlds_owned"] = worlds_owned_;
		save_["last_worlds"] = visited_worlds_;
		save_["inv"] = inv_;
		save_["achievements"] = achievements_;
		save_["friends"] = friends_;
		save_["hair"] = p_->hair, save_["shirt"] = p_->shirt, save_["pants"] = p_->pants, save_["feet"] = p_->feet, save_["face"] = p_->face, save_["hand"] = p_->hand, save_["back"] = p_->back, save_["mask"] = p_->mask, save_["necklace"] = p_->necklace, save_["ances"] = p_->ances;
		ofstream w_("players/" + p_->tankIDName + "_.json");
		if (w_.fail()) {
			cout << "failed to save player " << p_->tankIDName << endl;
			return;
		}
		w_ << save_ << endl;
		w_.close();
		cout << "Saved: " << p_->tankIDName << endl;
	}
	catch (exception) {
		cout << "something failed" << endl;
		return;
	}
	catch (out_of_range e) {
		cout << "error saving player " << p_->tankIDName << " reason " << e.what() << endl;
		return;
	}
}
int auth_(ENetPeer* peer) {
	Player* p_ = pInfo(peer);
	string path_ = "players/" + p_->tankIDName + "_.json";
	if (_access_s(path_.c_str(), 0) == 0) {
		try {
			//saveall
			json r_;
			ifstream f_(path_, ifstream::binary);
			if (f_.fail()) {
				cout << "failed reading data for " << p_->tankIDName << endl;
				return -1;
			}
			f_ >> r_;
			f_.close();
			if (p_->tankIDPass != r_["pass"] and p_->tankIDPass!="//") //fix server error
				return -1;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->tankIDName == p_->tankIDName and pInfo(currentPeer)->id != p_->id) {
					save_player(pInfo(currentPeer));
					if (p_->tankIDPass != r_["pass"] and p_->tankIDPass != "//")
						return -1;
					pInfo(currentPeer)->invalid_data = true;
					exit_(currentPeer, true);
					enet_peer_disconnect_later(currentPeer, 0);
					ifstream f_(path_, ifstream::binary);
					f_ >> r_;
					f_.close();
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("`4ALREADY ON?! `o: This account was already online, kicking it off so you can log on. (if you were just playing before, this is nothing to worry about)");
					p.CreatePacket(peer);
					break;
				}
			}
			json a_ = r_["inv"].get<json>(), b_ = r_["achievements"].get<json>(), c_ = r_["friends"].get<json>(), d_ = r_["last_worlds"].get<json>(), e_ = r_["worlds_owned"].get<json>();
			for (int i_ = 0; i_ < a_.size(); i_++) {
				Items item_{};
				item_.id = a_.at(i_)["i"].get<int>();
				item_.count = a_.at(i_)["c"].get<int>();
				p_->inv.push_back(item_);
			} for (int i_ = 0; i_ < b_.size(); i_++) {
				p_->achievements.insert({ b_.at(i_)["title"].get<string>(), b_.at(i_)["progress"].get<int>() });
			} for (int i_ = 0; i_ < c_.size(); i_++) {
				Friends new_friend_;
				new_friend_.name = c_.at(i_)["name"].get<string>();
				new_friend_.mute = c_.at(i_)["mute"].get<bool>();
				new_friend_.block_trade = c_.at(i_)["block_trade"].get<bool>();
				new_friend_.last_seen = c_.at(i_)["last_seen"].get<long long>();
				p_->friends.push_back(new_friend_);
			} for (int i_ = 0; i_ < d_.size(); i_++) {
				p_->last_visited_worlds.push_back(d_.at(i_)["name"].get<string>());
			} for (int i_ = 0; i_ < e_.size(); i_++) {
				p_->worlds_owned.push_back(e_.at(i_)["name"].get<string>());
			}
			p_->dd = (!(r_.find("dd") != r_.end()) ? 0 : r_["dd"].get<int>());
			p_->supp = (!(r_.find("supp") != r_.end()) ? 0 : r_["supp"].get<int>());
			p_->hs = (!(r_.find("hs") != r_.end()) ? 0 : r_["hs"].get<int>());
			p_->note = (!(r_.find("note") != r_.end()) ? "" : r_["note"].get<string>());
			p_->tankIDName = r_["name"].get<string>();
			p_->email = r_["email"].get<string>();
			p_->b_r = r_["b_r"].get<string>();
			p_->b_b = r_["b_b"].get<string>();
			p_->b_s = r_["b_s"].get<long long int>();
			p_->b_t = r_["b_t"].get<long long int>();
			p_->m_r = r_["m_r"].get<string>();
			p_->m_b = r_["m_b"].get<string>();
			p_->punch_count = r_["punch"].get<long long int>();
			p_->aap = r_["aap"].get<string>();
			p_->aap2 = r_["aap2"].get<string>();
			p_->n = r_["n"].get<int>();
			p_->lo = r_["lo"].get<string>();
			p_->ghost = r_["ghost"].get<bool>();
			p_->invis = r_["invis"].get<bool>();
			p_->bans = r_["bans"].get<vector<string>>();
			p_->logs = r_["logs"].get<vector<string>>();
			p_->mod = r_["mod"].get<int>();
			p_->dev = r_["dev"].get<int>();
			p_->m_h = r_["m_h"].get<int>();
			p_->gems = r_["gems"].get<int>();
			p_->xp = r_["xp"].get<long long int>();
			p_->level = r_["level"].get<int>();
			p_->skin = r_["skin"].get<int>();
			p_->show_location_ = r_["show_location"].get<bool>();
			p_->show_friend_notifications_ = r_["show_notifications"].get<bool>();
			p_->playtime = time(NULL), p_->seconds = r_["playtime"].get<long long int>();
			p_->account_created = r_["date"].get<long long int>();
			if (p_->account_created == 0) p_->account_created = time(NULL) / 86400;
			p_->home_world = r_["home_world"].get<string>();
			p_->hair = r_["hair"].get<int>();
			p_->shirt = r_["shirt"].get<int>();
			p_->pants = r_["pants"].get<int>();
			p_->feet = r_["feet"].get<int>();
			p_->face = r_["face"].get<int>();
			p_->ip = r_["ip"].get<string>();
			p_->hand = r_["hand"].get<int>();
			p_->back = r_["back"].get<int>();
			p_->mask = r_["mask"].get<int>();
			p_->necklace = r_["necklace"].get<int>();
			p_->ances = r_["ances"].get<int>();
			if (r_.find("geiger") != r_.end()) {
				p_->geiger_ = r_["geiger"].get<int>();
			}
			if (r_.find("booty_broken") != r_.end()) {
				p_->booty_broken = r_["booty_broken"].get<int>();
			}
			if (r_.find("playmods") != r_.end()) {
				json list_playmod = r_["playmods"].get<json>();
				for (int i_ = 0; i_ < list_playmod.size(); i_++) {
					PlayMods give_playmod{};
					give_playmod.id = list_playmod.at(i_)["id"].get<int>();
					give_playmod.time = list_playmod.at(i_)["time"].get<long long>();
					if (list_playmod.at(i_).find("user") != list_playmod.at(i_).end()) {
						give_playmod.user = list_playmod.at(i_)["user"].get<string>();
					}
					p_->playmods.push_back(give_playmod);
				}
			}
			if (r_.find("blarney") != r_.end()) {
				json list_blarney = r_["blarney"].get<json>();
				for (int i_ = 0; i_ < list_blarney.size(); i_++) {
					int w_ = list_blarney.at(i_)["world"].get<int>();
					long long tim_ = list_blarney.at(i_)["time"].get<long long>();
					for (int c_ = 0; c_ < p_->completed_blarneys.size(); c_++) {
						if ((int)p_->completed_blarneys.at(c_).at(0) == w_) {
							p_->completed_blarneys.at(c_).at(1) = tim_;
							break;
						}
					}
				}
			}
			if (p_->ghost or p_->invis) {
				if (not p_->mod and not p_->dev) {
					p_->invis = false;
				}
				if (not p_->dev) {
					p_->ghost = false;
					if (p_->skin == -2450) p_->skin = 0x8295C3FF;
				}
			}
		}
		catch (exception exx) {
			cout << exx.what() << endl;
			return -1;
		}
		gamepacket_t p;
		p.Insert("SetHasGrowID");
		p.Insert(1);
		p.Insert(p_->tankIDName);
		p.Insert(p_->tankIDPass);
		p.CreatePacket(peer);
		return 0;
	}
	return -1;
}
string r_dialog(const string& r_, const string& a_ = "", const string& b_ = "", const string& c_ = "", const string& d_ = "") {
	return "text_scaling_string|Dirttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt|\nset_default_color|`o\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\nadd_spacer|small|\nadd_textbox|" + (r_.empty() ? "By choosing a `wGrowID``, you can use a name and password to logon from any device.Your `wname`` will be shown to other players!" : r_) + "|left|\nadd_spacer|small|\nadd_text_input|logon|Name|" + a_ + "|18|\nadd_textbox|Your `wpassword`` must contain `w8 to 18 characters, 1 letter, 1 number`` and `w1 special character: @#!$^&*.,``|left|\nadd_text_input_password|password|Password|" + b_ + "|18|\nadd_text_input_password|password_verify|Password Verify|" + c_ + "|18|\nadd_textbox|Your `wemail`` will only be used for account verification and support. If you enter a fake email, you can't verify your account, recover or change your password.|left|\nadd_text_input|email|Email|" + d_ + "|64|\nadd_textbox|We will never ask you for your password or email, never share it with anyone!|left|\nend_dialog|growid_apply|Cancel|Get My GrowID!|\n";
}
string to_playmod_time(int seconds) {
	int hour = seconds / 3600;
	int minute = (seconds % 3600) / 60;
	int second = seconds % 60;
	if (hour == 0 and minute == 0 and second == 0) return "Removing now ";
	return (hour > 0 ? to_string(hour) + " hours" : "") + (minute > 0 ? (hour > 0 ? ", " : "") + to_string(minute) + " mins" : "") + (second > 0 ? (minute > 0 ? ", " : "") + to_string(second) + " secs " : " ");
}
string form_mods(Player* p_, int text) {
	vector<string> player_playmods;
	long long time_ = time(nullptr);
	vector<string> added_{};
	player_playmods.push_back(items.at(p_->hair).playmod), player_playmods.push_back(to_string(p_->hair));
	player_playmods.push_back(items.at(p_->shirt).playmod), player_playmods.push_back(to_string(p_->shirt));
	player_playmods.push_back(items.at(p_->pants).playmod), player_playmods.push_back(to_string(p_->pants));
	player_playmods.push_back(items.at(p_->feet).playmod), player_playmods.push_back(to_string(p_->feet));
	player_playmods.push_back(items.at(p_->face).playmod), player_playmods.push_back(to_string(p_->face));
	player_playmods.push_back(items.at(p_->hand).playmod), player_playmods.push_back(to_string(p_->hand));
	player_playmods.push_back(items.at(p_->back).playmod), player_playmods.push_back(to_string(p_->back));
	player_playmods.push_back(items.at(p_->mask).playmod), player_playmods.push_back(to_string(p_->mask));
	player_playmods.push_back(items.at(p_->necklace).playmod), player_playmods.push_back(to_string(p_->necklace));
	player_playmods.push_back(items.at(p_->ances).playmod), player_playmods.push_back(to_string(p_->ances));
	if (p_->ghost) player_playmods.push_back("Ghost in the Shell"), player_playmods.push_back("290");
	if (p_->b_s != 0) player_playmods.push_back("Duct Tape"), player_playmods.push_back("408");
	if (p_->hand == 2286) player_playmods.push_back("Charging Geiger Counter`` (" + to_string(p_->geiger_) + "%)"), player_playmods.push_back("2204");
	if (find(added_.begin(), added_.end(), "Irradiated") == added_.end()) {
		if (p_->hand == 2204) player_playmods.push_back("Geiger Counting"), player_playmods.push_back("2204");
	}
	string t_ = "";
	int active = 0;
	try {
		for (int i_ = 0; i_ < player_playmods.size(); i_++) {
			if (player_playmods.at(i_).empty() or isdigit(player_playmods.at(i_)[0])) continue;
			t_ += (text == 0 ? "\nadd_label_with_icon|small|`w" + player_playmods.at(i_) + "``|left|" + player_playmods[i_ + 1] + "|" : "\n`w" + player_playmods.at(i_) + "``");
			active++;
		}
	}
	catch (out_of_range) {
		return t_;
	}
	if (t_.empty())
		t_ = "";
	else
		if (text == 0) t_ = "\nadd_textbox|`wActive effects:``|left|\nadd_label_with_icon|small|" + t_;
		else t_ = "\n" + to_string(active) + " mods active:" + t_;
	return t_;
}
void update_gem_item_(World* world_, WorldDrop drop_, int target_) {
	for (int i_ = 0; i_ < world_->drop.size(); i_++) {
		if (abs(world_->drop.at(i_).y - drop_.y) <= 16 and abs(world_->drop.at(i_).x - drop_.x) <= 16 and world_->drop.at(i_).id == 112) {
			if (world_->drop.at(i_).count == target_) {
				PlayerMoving data_{};
				data_.packetType = 14, data_.netID = -2, data_.plantingTree = world_->drop.at(i_).uid;
				BYTE* raw = packPlayerMoving(&data_);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_->name) {
						send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
					}
				}
				delete[]raw;
				world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
			}
		}
	}
}
void dropas_(World* world_, WorldDrop drop_, int net_id = -1) {
	if (drop_.id == 112) {
		// gemu merging   
		int c_ = 0;
		for (int i_ = 0; i_ < world_->drop.size(); i_++) {
			if (abs(world_->drop.at(i_).y - drop_.y) <= 16 and abs(world_->drop.at(i_).x - drop_.x) <= 16 and world_->drop.at(i_).id == 112) {
				c_ += world_->drop.at(i_).count;
			}
		}
		if (c_ != 0) {
			int b_purple_ = c_ >= 100 ? c_ / 100 : 0, b_green_ = c_ - (b_purple_ * 100) >= 50 ? (c_ - (b_purple_ * 100)) / 50 : 0, b_red_ = c_ - (b_purple_ * 100) - (b_green_ * 50) >= 10 ? (c_ - (b_purple_ * 100) - (b_green_ * 50)) / 10 : 0, b_blue_ = c_ - (b_green_ * 50) - (b_purple_ * 100) - (b_red_ * 10) >= 5 ? (c_ - (b_green_ * 50) - (b_purple_ * 100) - (b_red_ * 10)) / 5 : 0, b_yellow_ = c_ - (b_red_ * 10) - (b_green_ * 50) - (b_purple_ * 100) - (b_blue_ * 5) > 0 ? (c_ - (b_red_ * 10) - (b_green_ * 50) - (b_purple_ * 100) - (b_blue_ * 5)) / 1 : 0;
			c_ += drop_.count;
			int purple_ = c_ >= 100 ? c_ / 100 : 0, green_ = c_ - (purple_ * 100) >= 50 ? (c_ - (purple_ * 100)) / 50 : 0, red_ = c_ - (purple_ * 100) - (green_ * 50) >= 10 ? (c_ - (purple_ * 100) - (green_ * 50)) / 10 : 0, blue_ = c_ - (green_ * 50) - (purple_ * 100) - (red_ * 10) >= 5 ? (c_ - (green_ * 50) - (purple_ * 100) - (red_ * 10)) / 5 : 0, yellow_ = c_ - (red_ * 10) - (green_ * 50) - (purple_ * 100) - (blue_ * 5) > 0 ? (c_ - (red_ * 10) - (green_ * 50) - (purple_ * 100) - (blue_ * 5)) / 1 : 0;
			if (blue_ > b_blue_ or blue_ == 0 and b_blue_ != 0) {
				drop_.count = 5;
				update_gem_item_(world_, drop_, 1);
			} if (red_ > b_red_ or red_ == 0 and b_red_ != 0) {
				drop_.count = 10;
				update_gem_item_(world_, drop_, 5);
			} if (green_ > b_green_ or green_ == 0 and b_green_ != 0) {
				drop_.count = 50;
				update_gem_item_(world_, drop_, 10);
			} if (purple_ > b_purple_) {
				drop_.count = 100;
				update_gem_item_(world_, drop_, 50);
			}
		}
	}
	else {
		for (int i_ = 0; i_ < world_->drop.size(); i_++) {
			if (world_->drop.at(i_).id == 0) continue;
			if (abs(world_->drop.at(i_).y - drop_.y) <= 16 and abs(world_->drop.at(i_).x - drop_.x) <= 16 and world_->drop.at(i_).id == drop_.id and world_->drop.at(i_).count < 200) {
				int truksta_iki_200 = 200 - world_->drop.at(i_).count;
				if (drop_.count > truksta_iki_200 or world_->drop.at(i_).count + drop_.count <= 200) {
					int drop_atskirai = drop_.count - truksta_iki_200;
					if (world_->drop.at(i_).count + drop_.count <= 200) {
						world_->drop.at(i_).count += drop_.count;
						drop_.count = 0;
						goto update;
					}
					drop_.count = drop_atskirai;
					world_->drop.at(i_).count = 200;
				update:
					PlayerMoving data_{};
					data_.packetType = 14, data_.netID = -3, data_.plantingTree = world_->drop.at(i_).id;
					data_.x = world_->drop.at(i_).x, data_.y = world_->drop.at(i_).y;
					int32_t item = world_->drop.at(i_).uid;
					float val = world_->drop.at(i_).count;
					BYTE* raw = packPlayerMoving(&data_);
					memcpy(raw + 8, &item, 4);
					memcpy(raw + 16, &val, 4);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[]raw;
					break;
				}
			}
		}
	}
	if (drop_.count != 0) {
		world_->drop.push_back(drop_);
		PlayerMoving data_{};
		data_.packetType = 14, data_.x = drop_.x, data_.y = drop_.y, data_.netID = -1, data_.plantingTree = drop_.id;
		float val = drop_.count;
		int32_t item = net_id;
		BYTE val2 = 0;
		BYTE* raw = packPlayerMoving(&data_);
		memcpy(raw + 8, &item, 4);
		memcpy(raw + 16, &val, 4);
		memcpy(raw + 1, &val2, 1);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == world_->name) {
				send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			}
		}
		delete[]raw;
	}
}
void gems_(World* world_, int c_, int x_, int y_) {
	//c_ *= 2;
	// gem konvertavimas
	int a_ = c_;
	int purple_ = c_ >= 100 ? c_ / 100 : 0, green_ = c_ - (purple_ * 100) >= 50 ? (c_ - (purple_ * 100)) / 50 : 0, red_ = c_ - (purple_ * 100) - (green_ * 50) >= 10 ? (c_ - (purple_ * 100) - (green_ * 50)) / 10 : 0, blue_ = c_ - (green_ * 50) - (purple_ * 100) - (red_ * 10) >= 5 ? (c_ - (green_ * 50) - (purple_ * 100) - (red_ * 10)) / 5 : 0, yellow_ = c_ - (red_ * 10) - (green_ * 50) - (purple_ * 100) - (blue_ * 5) > 0 ? (c_ - (red_ * 10) - (green_ * 50) - (purple_ * 100) - (blue_ * 5)) / 1 : 0;
	// dabar drop   
	WorldDrop item_{};
	item_.id = 112;
	item_.count = 100;
	for (int i_ = 0; i_ < purple_; i_++) {
		item_.x = x_ + rand() % 17, item_.y = y_ + rand() % 17;
		item_.uid = uint16_t(world_->drop.size()) + 1;
		dropas_(world_, item_);
	}
	item_.count = 50;
	for (int i_ = 0; i_ < green_; i_++) {
		item_.x = x_ + rand() % 17, item_.y = y_ + rand() % 17;
		item_.uid = uint16_t(world_->drop.size()) + 1;
		dropas_(world_, item_);
	}
	item_.count = 10;
	for (int i_ = 0; i_ < red_; i_++) {
		item_.x = x_ + rand() % 17, item_.y = y_ + rand() % 17;
		item_.uid = uint16_t(world_->drop.size()) + 1;
		dropas_(world_, item_);
	}
	item_.count = 5;
	for (int i_ = 0; i_ < blue_; i_++) {
		item_.x = x_ + rand() % 17, item_.y = y_ + rand() % 17;
		item_.uid = uint16_t(world_->drop.size()) + 1;
		dropas_(world_, item_);
	}
	item_.count = 1;
	for (int i_ = 0; i_ < yellow_; i_++) {
		item_.x = x_ + rand() % 17, item_.y = y_ + rand() % 17;
		item_.uid = uint16_t(world_->drop.size()) + 1;
		dropas_(world_, item_);
	}
}
bool static_(BlockTypes& c_, ItemDB item_) {
	// sugalvoti kaip nuspresti ar blockas yra solid arba background
	c_ = item_.blockType;
	if (item_.id == 0) return false;
	if (c_ == LOCK or c_ == BEDROCK or c_ == MAIN_DOOR or c_ == FOREGROUND or c_ == DEADLY or c_ == PAIN_BLOCK or item_.name.find(" Block") != string::npos and item_.name.find(" Seed") == string::npos or item_.name.find(" Bricks") != string::npos and item_.name.find(" Seed") == string::npos)
		return true;
	return false;
}
void send_friends(ENetPeer* p_, bool all = false) {
	// labai cia sudinai gavosi   
	int on_ = 0;
	string info_ = "";
	vector<string> friends_, online_friends_;
	for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
		friends_.push_back(pInfo(p_)->friends.at(c_).name);
	} for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
			online_friends_.push_back(pInfo(currentPeer)->tankIDName);
			on_++;
		}
	} if (all and pInfo(p_)->friends.size() != 0) {
		long long time_t = time(NULL);
		for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
			if (find(online_friends_.begin(), online_friends_.end(), pInfo(p_)->friends.at(c_).name) == online_friends_.end()) {
				long long friend_last_online_ = time_t - pInfo(p_)->friends.at(c_).last_seen;
				info_ += "\nadd_friend_image_label_button|" + pInfo(p_)->friends.at(c_).name + "|`4(" + (friend_last_online_ < 60 ? to_string(friend_last_online_) + "s" : (friend_last_online_ < 3600 ? to_string(friend_last_online_ / 60) + "m" : (friend_last_online_ < 86400 ? to_string(friend_last_online_ / 3600) + "h" : to_string(friend_last_online_ / 86400) + "d"))) + ") ``" + pInfo(p_)->friends.at(c_).name + "|game/tiles_page14.rttex|1.6|31|23|32|" + (pInfo(p_)->friends.at(c_).mute ? "true" : "false") + "|" + (pInfo(p_)->friends.at(c_).block_trade ? "true" : "false") + "|";
			}
		}
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|big|" + to_string(on_) + " of " + to_string(pInfo(p_)->friends.size()) + " `wFriends Online``|left|1366|\nadd_spacer|small|" + info_ + "\nadd_spacer|small|\nadd_textbox|`oYou aren't currently ignoring anyone.``|left|\nadd_spacer|small|\nadd_button|all_friends|Edit Friends|noflags|0|0|\nadd_button|friends_options|Friend Options|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nadd_button||Close|noflags|0|0|\nend_dialog|friends|||\nadd_quick_exit|");
		p.CreatePacket(p_);
	}
	else {
		for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
			if (find(online_friends_.begin(), online_friends_.end(), pInfo(p_)->friends.at(c_).name) != online_friends_.end()) {
				info_ += "\nadd_friend_image_label_button|" + pInfo(p_)->friends.at(c_).name + "|" + pInfo(p_)->friends.at(c_).name + "|game/tiles_page14.rttex|1.6|28|23|32|" + (pInfo(p_)->friends.at(c_).mute ? "true" : "false") + "|" + (pInfo(p_)->friends.at(c_).block_trade ? "true" : "false") + "|";
			}
		}
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|big|" + to_string(on_) + " of " + to_string(pInfo(p_)->friends.size()) + " `wFriends Online``|left|1366|\nadd_spacer|small|" + (on_ == 0 and pInfo(p_)->friends.size() != 0 ? "\nadd_textbox|`oNone of your friends are currently online.``|left|\nadd_spacer|small|" : (pInfo(p_)->friends.size() == 0 ? "\nadd_textbox|`oYou currently have no friends.  That's just sad.  To make some, press a person's wrench icon, then choose `5Add as friend``.``|left|\nadd_spacer|small|" : (on_ != 0 ? info_ : "\nadd_textbox|`oNone of your friends are currently online.``|left|\nadd_spacer|small|"))) + "\nadd_spacer|small|" + (pInfo(p_)->friends.size() == 0 ? "" : (on_ == pInfo(p_)->friends.size() ? "\nadd_spacer|small|\nadd_button|all_friends|Edit Friends|noflags|0|0|" : "\nadd_button|friend_all|Show offline and ignored too|noflags|0|0|\nadd_button|all_friends|Edit Friends|noflags|0|0|")) + "\nadd_button|friends_options|Friend Options|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nadd_button||Close|noflags|0|0|\nend_dialog|friends|||\nadd_quick_exit|");
		p.CreatePacket(p_);
	}
}
void send_social(ENetPeer* p_) {
	gamepacket_t p;
	p.Insert("OnDialogRequest");
	p.Insert("set_default_color|`o\nadd_label_with_icon|big| `wSocial Portal`` |left|1366|\nadd_spacer|small|\nadd_button|showfriend|`wShow Friends``|noflags|0|0|\nadd_button|communityhub|`wCommunity Hub``|noflags|0|0|\nadd_button|show_apprentices|`wShow Apprentices``|noflags|0|0|\nadd_button|showguild|`wCreate Guild``|noflags|0|0|\nadd_button|trade_history|`wTrade History``|noflags|0|0|\nadd_quick_exit|\nend_dialog|socialportal||Back|\n");
	p.CreatePacket(p_);
}
void edit_friend(ENetPeer* p_, string name_, bool back_ = false) {
	for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
		if (pInfo(p_)->friends.at(c_).name == name_) {
			if (back_) {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->tankIDName == pInfo(p_)->friends.at(c_).name) {
						send_friends(p_);
						return;
					}
				}
				send_friends(p_, true);
				break;
			}
			gamepacket_t p;
			p.Insert("OnDialogRequest");
			p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Remove Friend``|left|1366|\nadd_spacer|small|\nadd_textbox|`oAre you sure you wish to `4remove`` " + pInfo(p_)->friends.at(c_).name + " as a friend?|left|\nadd_spacer|small|\nadd_button|remove|`4Remove Friend``|noflags|0|0|\nembed_data|friendID|" + pInfo(p_)->friends.at(c_).name + "\nadd_button|back|Back|noflags|0|0|\nend_dialog|friends_remove|||\nadd_quick_exit|");
			p.CreatePacket(p_);
			break;
		}
	}
}
void send_info_friend(ENetPeer* p_, string name_) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->tankIDName == name_) {
			for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
				if (pInfo(p_)->friends.at(c_).name == pInfo(currentPeer)->tankIDName) {
					pInfo(p_)->last_edit = pInfo(currentPeer)->tankIDName;
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					if (not pInfo(currentPeer)->show_location_) {
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + pInfo(currentPeer)->tankIDName + "``|left|1366|\nadd_spacer|small|\nembed_data|friendID|" + pInfo(currentPeer)->tankIDName + "\nadd_textbox|`o" + pInfo(currentPeer)->tankIDName + " is `2online`` now, but has not made their location public to friends.|left|\nadd_spacer|small|\nadd_button|remove|Remove as friend|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|friends_edit|||\nadd_quick_exit|");
					}
					else {
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + pInfo(currentPeer)->tankIDName + "``|left|1366|\nadd_spacer|small|\nembed_data|friendID|" + pInfo(currentPeer)->tankIDName + "\nadd_textbox|`o" + pInfo(currentPeer)->tankIDName + " is `2online`` now in the world `5" + (pInfo(currentPeer)->world.empty() ? "EXIT" : pInfo(currentPeer)->world) + "``.|left|\nadd_spacer|small|\nadd_button|goto|Warp to `5" + (pInfo(currentPeer)->world.empty() ? "EXIT" : pInfo(currentPeer)->world) + "``|noflags|0|0|" + (pInfo(p_)->friends.at(c_).mute ? "\nadd_button||`4Can't Send message``|disabled|0|0|\nadd_button|mute|Un Mute Friend|noflags|0|0|" : "\nadd_button|msg|`5Send message``|noflags|0|0|\nadd_button|mute|Mute Friend|noflags|0|0|") + (pInfo(p_)->friends.at(c_).block_trade ? "\nadd_button|trade_block|Enable Trade|noflags|0|0|" : "\nadd_button|trade_block|Disable Trade|noflags|0|0|") + "\nadd_spacer|small|\nadd_button|remove|Remove as friend|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|friends_edit|||\nadd_quick_exit|");
					}
					p.CreatePacket(p_);
					return;
				}
			}
			return;
		}
	}
	for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
		if (pInfo(p_)->friends.at(c_).name == name_) {
			gamepacket_t p;
			p.Insert("OnDialogRequest");
			p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + name_ + "``|left|1366|\nadd_spacer|small|\nembed_data|friendID|" + name_ + "\nadd_textbox|`o" + name_ + " is `4offline``.|left|\nadd_spacer|small|\nadd_button|remove|Remove as friend|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|friends_edit|||\nadd_quick_exit|");
			p.CreatePacket(p_);
			break;
		}
	}
}
void transfer_world(World* world_, ENetPeer* from_, ENetPeer* to_) {
	if (world_->owner_name.empty()) return;
	int lock_id = 0, lock_x = 0, lock_y = 0;
	int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
	for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
		if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
			uint16_t id_ = world_->blocks.at(i_).fg;
			if (id_ != 202 and id_ != 204 and id_ != 206 and id_ != 4994) {
				lock_id = id_, lock_x = i_ % xSize, lock_y = i_ / xSize;
				break;
			}
		}
	}
	if (lock_id == 0 or lock_x == 0 or lock_y == 0) return;
	if (pInfo(from_)->tankIDName == world_->owner_name) {
		pInfo(from_)->worlds_owned.erase(remove(pInfo(from_)->worlds_owned.begin(), pInfo(from_)->worlds_owned.end(), world_->name), pInfo(from_)->worlds_owned.end());
	}
	else {
		bool on_ = false;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->tankIDName == world_->owner_name) {
				pInfo(currentPeer)->worlds_owned.erase(remove(pInfo(currentPeer)->worlds_owned.begin(), pInfo(currentPeer)->worlds_owned.end(), world_->name), pInfo(currentPeer)->worlds_owned.end());
				on_ = true;
				break;
			}
		} if (not on_) {
			try {
				string path_ = "players/" + world_->owner_name + "_.json";
				if (_access_s(path_.c_str(), 0) == 0) {
					json r_;
					ifstream f_(path_, ifstream::binary);
					if (f_.fail()) {
						cout << "failed reading data for " << world_->owner_name << endl;
						return;
					}
					f_ >> r_;
					f_.close();
					try {
						json f_ = r_["worlds_owned"].get<json>();
						for (int i_ = 0; i_ < f_.size(); i_++) {
							if (f_.at(i_)["name"] == world_->name) {
								f_.erase(f_.begin() + i_);
								break;
							}
						}
						r_["worlds_owned"] = f_;
					}
					catch (exception) {
						return;
					}
					{
						ofstream f_(path_, ifstream::binary);
						f_ << r_;
						f_.close();
					}
				}
			}
			catch (exception) {
				cout << "something failed" << endl;
			}
		}
	}
	world_->owner_name = pInfo(to_)->tankIDName;
	if (pInfo(to_)->name_color != "`0") world_->owner_named = pInfo(to_)->name_color + pInfo(to_)->tankIDName + "``";
	pInfo(to_)->worlds_owned.push_back(world_->name);
	PlayerMoving data_{};
	data_.packetType = 15, data_.punchX = lock_x, data_.punchY = lock_y, data_.characterState = 0x8;
	data_.netID = pInfo(to_)->id;
	data_.plantingTree = lock_id;
	BYTE* raw = packPlayerMoving(&data_, 56);
	gamepacket_t p;
	p.Insert("OnTalkBubble");
	p.Insert(pInfo(to_)->netID);
	p.Insert("`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(to_)->name_color + world_->owner_name + "```5]``");
	p.Insert(0);
	gamepacket_t p2;
	{
		p2.Insert("OnConsoleMessage");
		p2.Insert("`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(to_)->name_color + world_->owner_name + "```5]``");
	}
	gamepacket_t p3(0, pInfo(to_)->netID);
	{
		p3.Insert("OnNameChanged");
		if (pInfo(to_)->mod == 0 && pInfo(to_)->dev == 0) pInfo(to_)->name_color = "`2";
		p3.Insert(pInfo(to_)->name_color + pInfo(to_)->tankIDName + "``");
	}
	gamepacket_t p4(0, pInfo(from_)->netID);
	{
		p4.Insert("OnNameChanged");
		if (pInfo(from_)->mod == 0 && pInfo(from_)->dev == 0) pInfo(from_)->name_color = "`0";
		p4.Insert(pInfo(from_)->name_color + pInfo(from_)->tankIDName + "``");
	}
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == world_->name) {
			packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
			send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer), p3.CreatePacket(currentPeer), p4.CreatePacket(currentPeer);
		}
	}
	delete[] raw;
}
void remove_friend(ENetPeer* p_, World* world_, string name_, bool show_Dialog = true) {
	for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
		if (pInfo(p_)->friends.at(c_).name == name_) {
			if (show_Dialog) {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Friend removed``|left|1366|\nadd_spacer|small|\nadd_textbox|`oOk, you are no longer friends with " + pInfo(p_)->friends.at(c_).name + ".|left|\nadd_spacer|small|\nadd_button|back|OK|noflags|0|0|\nend_dialog|friends_remove_finish|||\nadd_quick_exit|");
				p.CreatePacket(p_);
			}
			bool on_ = false;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->tankIDName == name_) {
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("`3FRIEND ALERT:`` " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has removed you as a friend.");
					p.CreatePacket(currentPeer);
					for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
						if (pInfo(currentPeer)->friends.at(c_).name == pInfo(p_)->tankIDName) {
							pInfo(currentPeer)->friends.erase(pInfo(currentPeer)->friends.begin() + c_);
							break;
						}
					}
					on_ = true;
					break;
				}
			} if (not on_) {
				try {
					string path_ = "players/" + name_ + "_.json";
					if (_access_s(path_.c_str(), 0) == 0) {
						json r_;
						ifstream f_(path_, ifstream::binary);
						if (f_.fail()) {
							cout << "failed reading data for " << name_ << endl;
							return;
						}
						f_ >> r_;
						f_.close();
						try {
							json f_ = r_["friends"].get<json>();
							for (int i_ = 0; i_ < f_.size(); i_++) {
								if (f_.at(i_)["name"] == pInfo(p_)->tankIDName) {
									f_.erase(f_.begin() + i_);
									break;
								}
							}
							r_["friends"] = f_;
						}
						catch (exception) {
							return;
						}
						{
							ofstream f_(path_, ifstream::binary);
							f_ << r_;
							f_.close();
						}
					}
				}
				catch (exception) {
					cout << "something failed" << endl;
				}
			}
			pInfo(p_)->friends.erase(pInfo(p_)->friends.begin() + c_);
		}
	}
}
int isValidMacAddress(const char* mac) {
	int i = 0;
	int s = 0;
	while (*mac) {
		if (isxdigit(*mac)) {
			i++;
		}
		else if (*mac == ':' || *mac == '-') {
			if (i == 0 || i / 2 - 1 != s) break;
			++s;
		}
		else s = -1;
		++mac;
	}
	return (i == 12 && (s == 5 || s == 0));
}
void send_all_edit_friends(ENetPeer* p_) {
	string info_ = "";
	for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
		info_ += "\nadd_checkbox|cf_" + to_string(c_) + "|" + pInfo(p_)->friends.at(c_).name + (pInfo(p_)->friends.at(c_).mute ? " <Muted>" : "") + (pInfo(p_)->friends.at(c_).block_trade ? " <Trade Block>" : "") + "|0";
	}
	gamepacket_t p;
	p.Insert("OnDialogRequest");
	p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAll Friends``|left|1366|\nadd_spacer|small|\nadd_button|remove_multi_friends|Remove|noflags|0|0|\nadd_button|block_multi_friends|Block / Unblock Trade|noflags|0|0|\nadd_button|mute_multi_friends|Mute / Unmute|noflags|0|0|\nadd_spacer|small|" + info_ + "\nadd_button|back|Back|noflags|0|0|\nend_dialog|all_friends|||\nadd_quick_exit|");
	p.CreatePacket(p_);
}
void cancel_trade(ENetPeer* p_, bool confirm_cancel = false, bool busy_ = false) {
	bool found = false;
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == pInfo(p_)->world) {
			if (pInfo(currentPeer)->netID == pInfo(p_)->trading_with and pInfo(p_)->netID == pInfo(currentPeer)->trading_with) {
				found = true;
				pInfo(currentPeer)->block_trade = false, pInfo(currentPeer)->accept_the_offer = false, pInfo(currentPeer)->trading_with = -1, pInfo(currentPeer)->trade_items.clear();
				string name_ = pInfo(p_)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					if (not confirm_cancel) {
						World* world_ = &worlds.at(p - worlds.begin());
						{
							if (busy_) {
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` is too busy to trade!");
									p.CreatePacket(currentPeer), p.CreatePacket(p_);
								}
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` is too busy to trade!");
								p.CreatePacket(currentPeer), p.CreatePacket(p_);
							}
							else {
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has canceled the trade");
								p.CreatePacket(currentPeer);
							}
						}
					}
					else {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("`6[```4Trade canceled by " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``!```6]``");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(p_);
						{
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(currentPeer)->netID);
							p.Insert("`6[```4Trade canceled by " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``!```6]``");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(currentPeer);
						}
						{
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("`6[```4Trade canceled by " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``!```6]``");
							p.CreatePacket(p_), p.CreatePacket(currentPeer);
						}
						{
							gamepacket_t p;
							p.Insert("OnTextOverlay");
							p.Insert("`6[```4Trade canceled by " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``!```6]``");
							p.CreatePacket(p_), p.CreatePacket(currentPeer);
						}
					}
					gamepacket_t p;
					p.Insert("OnForceTradeEnd");
					p.CreatePacket(currentPeer);
					if (busy_) {
						p.CreatePacket(p_);
					}
				}
				pInfo(p_)->block_trade = false, pInfo(p_)->trading_with = -1, pInfo(p_)->trade_accept = false, pInfo(p_)->accept_the_offer = false, pInfo(p_)->trade_items.clear();
				return;
			}
		}
	}
	if (busy_) {
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert(pInfo(p_)->tankIDName + " is too busy to trade!");
			p.CreatePacket(p_);
		}
		gamepacket_t p;
		p.Insert("OnTextOverlay");
		p.Insert(pInfo(p_)->tankIDName + " is too busy to trade!");
		p.CreatePacket(p_);
	}
	else if (pInfo(p_)->trade_accept) {
		gamepacket_t p;
		p.Insert("OnTextOverlay");
		p.Insert("The other person left the trade!");
		p.CreatePacket(p_);
	}
	if (not found) {
		gamepacket_t p;
		p.Insert("OnForceTradeEnd");
		p.CreatePacket(p_);
	}
	pInfo(p_)->block_trade = false, pInfo(p_)->trading_with = -1, pInfo(p_)->trade_accept = false, pInfo(p_)->accept_the_offer = false, pInfo(p_)->trade_items.clear();
}
string make_trade_offer(Player* p_, bool special_ = false) {
	if (p_->trade_items.size() == 0 and not special_)
		return "\nadd_textbox|`4Nothing!``|left|";
	string list_ = "";
	for (int i_ = 0; i_ < p_->trade_items.size(); i_++) {
		map<string, int>::iterator it;
		for (auto it = p_->trade_items.at(i_).begin(); it != p_->trade_items.at(i_).end(); it++) {
			if (special_)
				list_ += "add_slot|" + to_string(it->first) + "|" + to_string(it->second) + "\n";
			else
				list_ += "\nadd_label_with_icon|small|(`w" + to_string(it->second) + "``) " + items.at(it->first).name + "|left|" + to_string(it->first) + "|";
		}
	}
	return list_;
}
void send_wrench_self(ENetPeer* peer) {
	time_t s__;
	s__ = time(NULL);
	int days_ = int(s__) / (60 * 60 * 24);
	double hours_ = (double)((s__ - pInfo(peer)->playtime) + pInfo(peer)->seconds) / 3600;
	string num_text = to_string(hours_);
	string rounded = num_text.substr(0, num_text.find(".") + 3);
	int w_c = 0, s_c = 0, net_ = 1;
	get_players(pInfo(peer)->world, w_c, s_c, net_);
	string extra = "";
	if (pInfo(peer)->ac_.size() != 0) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->world) {
				if (pInfo(peer)->ac_.find(pInfo(currentPeer)->netID) != pInfo(peer)->ac_.end()) {
					string name_ = pInfo(peer)->world;
					vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (p != worlds.end()) {
						World* world_ = &worlds.at(p - worlds.begin());
						string owner_name = world_->owner_name, user_name = pInfo(currentPeer)->tankIDName;
						WorldBlock block_ = world_->blocks.at(pInfo(peer)->ac_.at(pInfo(currentPeer)->netID));
						if (block_.fg == 202 or block_.fg == 204 or block_.fg == 206 or block_.fg == 4994) {
							if (block_.owner_name != user_name) break;
						}
						else {
							if (owner_name != user_name) break;
						}
						extra = "\nadd_button|acceptlock|`2Accept Access on " + items.at(block_.fg).name + "``|noflags|0|0|";
					}
					break;
				}
			}
		}
		if (extra.empty()) pInfo(peer)->ac_.clear();
	}
	gamepacket_t p;
	p.Insert("OnDialogRequest");
	p.Insert("set_default_color|`o\n\nadd_player_info|`0" + pInfo(peer)->tankIDName + "``|" + (pInfo(peer)->level >= 125 ? "125|5001000|5001000|" : "") + "" + (pInfo(peer)->level <= 125 ? to_string(pInfo(peer)->level) + "|" + to_string(pInfo(peer)->xp) + "|" + to_string(50 * ((pInfo(peer)->level * pInfo(peer)->level) + 2)) : "") + "|\nadd_spacer|small|\nadd_spacer|small|" + extra + ""/*"\nadd_button|renew_pvp_license|Get Card Battle License|noflags|0|0|"*/"\nadd_spacer|small|\nset_custom_spacing|x:5;y:10|\nadd_custom_button|title_edit|image:interface/large/gui_wrench_title.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|set_online_status|image:interface/large/gui_wrench_online_status_1green.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|notebook_edit|image:interface/large/gui_wrench_notebook.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|goals|image:interface/large/gui_wrench_goals_quests.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|bonus|image:interface/large/gui_wrench_daily_bonus_active.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|my_worlds|image:interface/large/gui_wrench_my_worlds.rttex;image_size:400,260;width:0.19;|\nadd_custom_button|alist|image:interface/large/gui_wrench_achievements.rttex;image_size:400,260;width:0.19;|\nadd_custom_label|(" + to_string(pInfo(peer)->achievements.size()) + "/169)|target:alist;top:0.72;left:0.5;size:small|\nadd_custom_button|emojis|image:interface/large/gui_wrench_growmojis.rttex;image_size:400,260;width:0.19;|"/*"\nadd_custom_button|marvelous_missions|image:interface/large/gui_wrench_marvelous_missions.rttex;image_size:400,260;width:0.19;|"*/"\nadd_custom_break|\nadd_spacer|small|\nset_custom_spacing|x:0;y:0|" + form_mods(pInfo(peer), 0) + (pInfo(peer)->firesputout != 0 ? "\nadd_spacer|small|\nadd_smalltext|Fires Put Out: " + to_string(pInfo(peer)->firesputout) + "|left|" : "") + (pInfo(peer)->carnivalgameswon != 0 ? "\nadd_spacer|small|\nadd_smalltext|Carnival games won: " + to_string(pInfo(peer)->carnivalgameswon) + "|left|" : "") + "\nadd_spacer|small|\nadd_textbox|`oYou have `w" + to_string(pInfo(peer)->inv.size() - 1) + "`` backpack slots.``|left|\nadd_textbox|`oCurrent world: `w" + pInfo(peer)->world + "`` (`w" + to_string(pInfo(peer)->x / 32) + "``, `w" + to_string(pInfo(peer)->y / 32) + "``) (`w" + to_string(w_c) + "`` person)````|left|\nadd_textbox|"+(pInfo(peer)->supp == 0 ? "`oYou are not yet a `2Supporter`` or `5Super Supporter``.``" : pInfo(peer)->supp == 1 ? "`oYou are a `5Supporter`` and have the `wRecycler``.``" : pInfo(peer)->supp == 2 ? "`oYou are a `5super Supporter`` and have the `wRecycler`` and `w/warp``.``" : "") + "|left|\nadd_textbox|`oYou are standing on the note \"A\".``|left|\nadd_spacer|small|\nadd_textbox|`oTotal time played is `w" + rounded + "`` hours.  This account was created `w" + to_string(days_ - pInfo(peer)->account_created) + "`` days ago.``|left|\nadd_spacer|small|\nend_dialog|popup||Continue|\nadd_quick_exit|");
	p.CreatePacket(peer);
}
void send_trade_confirm_dialog(ENetPeer* peer, ENetPeer* currentPeer, bool self_only = false) {
	pInfo(peer)->block_trade = true;
	pInfo(currentPeer)->block_trade = true;
	string name_ = pInfo(peer)->world;
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	if (p != worlds.end()) {
		World* world_ = &worlds.at(p - worlds.begin());
		bool world_key_p = false, world_key_cp = false;
		string lock = "";
		for (int i_ = 0; i_ < pInfo(peer)->trade_items.size(); i_++) {
			if (world_key_p) break;
			map<string, int>::iterator it;
			for (auto it = pInfo(peer)->trade_items.at(i_).begin(); it != pInfo(peer)->trade_items.at(i_).end(); it++) {
				if (it->first == 1424) {
					world_key_p = true;
					for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
						if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
							uint16_t id_ = world_->blocks.at(i_).fg;
							if (id_ != 202 and id_ != 204 and id_ != 206 and id_ != 4994) {
								lock = items.at(id_).name;
								break;
							}
						}
					}
					break;
				}
			}
		} for (int i_ = 0; i_ < pInfo(currentPeer)->trade_items.size(); i_++) {
			if (world_key_cp) break;
			map<string, int>::iterator it;
			for (auto it = pInfo(currentPeer)->trade_items.at(i_).begin(); it != pInfo(currentPeer)->trade_items.at(i_).end(); it++) {
				if (it->first == 1424) {
					world_key_cp = true;
					for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
						if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
							uint16_t id_ = world_->blocks.at(i_).fg;
							if (id_ != 202 and id_ != 204 and id_ != 206 and id_ != 4994) {
								lock = items.at(id_).name;
								break;
							}
						}
					}
					break;
				}
			}
		}
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small|\nadd_textbox|`4You'll give:``|left|\nadd_spacer|small|" + make_trade_offer(pInfo(peer)) + "\nadd_spacer|small|\nadd_textbox|`2You'll get:``|left|\nadd_spacer|small|" + make_trade_offer(pInfo(currentPeer)) + "\nadd_spacer|small|" + (pInfo(currentPeer)->trade_items.size() == 0 ? "\nadd_spacer|small|\nadd_textbox|`4SCAM WARNING: ``You are about to do a trade without receiving anything in return. Once you do the trade you cannot get the items back.|left|\nadd_textbox|`4Do you really want to do this?``|left|\nadd_spacer|small|" : "") + (world_key_cp ? "\nadd_spacer|small|\nadd_textbox|`4SCAM WARNING: ``You are buying this world, `#" + world_->name + "``. Don't buy a world just to get its rare items, because scammers can easily place secret doors allowing someone to jump in and `4steal the items back`` after a trade!|left|\nadd_spacer|small|\nadd_textbox|Also, all ratings will be removed from a world when it is traded. Don't buy a world for its ranking!|left|\nadd_spacer|small|\nadd_textbox|To be safe, only buy a world for its name and placed blocks, not loose items or high ratings. Consider yourself warned!|left|\nadd_spacer|small|\nadd_textbox|This world is locked by " + lock + ".|left|\nadd_spacer|small|" : (world_key_p ? "\nadd_spacer|small|\nadd_textbox|`4WARNING: ``You are about to sell your world `#" + world_->name + "`` - the world lock ownership will be transferred over to " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``.|left|\nadd_spacer|small|" : "")) + "\nadd_button|accept|Do The Trade!|noflags|0|0|\nadd_button|back|Cancel|noflags|0|0|\nend_dialog|trade_confirm|||");
		p.CreatePacket(peer);
		if (not self_only) {
			{
				gamepacket_t p;
				p.Insert("OnForceTradeEnd");
				p.CreatePacket(currentPeer);
			}
			gamepacket_t p;
			p.Insert("OnDialogRequest");
			p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small|\nadd_textbox|`4You'll give:``|left|\nadd_spacer|small|" + make_trade_offer(pInfo(currentPeer)) + "\nadd_spacer|small|\nadd_textbox|`2You'll get:``|left|\nadd_spacer|small|" + make_trade_offer(pInfo(peer)) + "\nadd_spacer|small|" + (pInfo(peer)->trade_items.size() == 0 ? "\nadd_spacer|small|\nadd_textbox|`4SCAM WARNING: ``You are about to do a trade without receiving anything in return. Once you do the trade you cannot get the items back.|left|\nadd_textbox|`4Do you really want to do this?``|left|\nadd_spacer|small|" : "") + (world_key_p ? "\nadd_spacer|small|\nadd_textbox|`4SCAM WARNING: ``You are buying this world, `#" + world_->name + "``. Don't buy a world just to get its rare items, because scammers can easily place secret doors allowing someone to jump in and `4steal the items back`` after a trade!|left|\nadd_spacer|small|\nadd_textbox|Also, all ratings will be removed from a world when it is traded. Don't buy a world for its ranking!|left|\nadd_spacer|small|\nadd_textbox|To be safe, only buy a world for its name and placed blocks, not loose items or high ratings. Consider yourself warned!|left|\nadd_spacer|small|\nadd_textbox|This world is locked by " + lock + ".|left|\nadd_spacer|small|" : (world_key_cp ? "\nadd_spacer|small|\nadd_textbox|`4WARNING: ``You are about to sell your world `#" + world_->name + "`` - the world lock ownership will be transferred over to " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``.|left|\nadd_spacer|small|" : "")) + "\nadd_button|accept|Do The Trade!|noflags|0|0|\nadd_button|back|Cancel|noflags|0|0|\nend_dialog|trade_confirm|||");
			p.CreatePacket(currentPeer);
		}
	}
}
void mod_trade(ENetPeer* p_, int item_id, int count, bool remove = false) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == pInfo(p_)->world) {
			if (pInfo(currentPeer)->netID == pInfo(p_)->trading_with and pInfo(p_)->netID == pInfo(currentPeer)->trading_with) {
				string name_ = pInfo(p_)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds.at(p - worlds.begin());
					if (pInfo(p_)->block_trade or pInfo(currentPeer)->block_trade) {
						cancel_trade(pInfo(p_)->block_trade ? p_ : currentPeer, false);
						return;
					}
					if (item_id == 1424 and pInfo(p_)->tankIDName != world_->owner_name and not pInfo(p_)->dev) {
						packet_(p_, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
						gamepacket_t p;
						p.Insert("OnTextOverlay");
						p.Insert("You can only trade World Keys in a world you own!");
						p.CreatePacket(p_);
						break;
					}
					if (remove) {
						int count_ = 0;
						for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
							auto i = pInfo(p_)->trade_items.at(i_).find(item_id);
							if (i != pInfo(p_)->trade_items.at(i_).end()) {
								map<string, int>::iterator it;
								for (auto it = pInfo(p_)->trade_items.at(i_).begin(); it != pInfo(p_)->trade_items.at(i_).end(); it++) {
									if (it->first == item_id)
										count_ = it->second;
								}
								pInfo(p_)->trade_items.erase(pInfo(p_)->trade_items.begin() + i_);
								break;
							}
						}
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`1TRADE CHANGE: `` " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` removed `w" + to_string(count_) + "`` " + items.at(item_id).name);
						p.CreatePacket(currentPeer);
					}
					else {
						bool f_ = false;
						for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
							map<string, int>::iterator it;
							for (auto it = pInfo(p_)->trade_items.at(i_).begin(); it != pInfo(p_)->trade_items.at(i_).end(); it++) {
								if (it->first == item_id and it->second == count) {
									swap(pInfo(p_)->trade_items.at(i_), pInfo(p_)->trade_items.back());
									f_ = true;
									break;
								}
								else if (it->first == item_id and it->second != count) {
									swap(pInfo(p_)->trade_items.at(i_), pInfo(p_)->trade_items.back());
									f_ = true;
									it->second = count;
									break;
								}
							}
						} if (not f_) {
							if (pInfo(p_)->trade_items.size() > 3) return;
							map<int, int> new_;
							new_.insert({ item_id, count });
							pInfo(p_)->trade_items.push_back(new_);
						}
						else {
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("`1TRADE CHANGE: `` " + pInfo(p_)->tankIDName + " removed `w" + to_string(count) + "`` " + items.at(item_id).name);
							p.CreatePacket(currentPeer);
						}
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`1TRADE CHANGE: `` " + pInfo(p_)->tankIDName + " added `w" + to_string(count) + "`` " + items.at(item_id).name);
						p.CreatePacket(currentPeer);
					}
					if (pInfo(p_)->trade_accept == 1) {
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(p_)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
							p.Insert("locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(p_);
						}
						gamepacket_t p;
						p.Insert("OnTradeStatus");
						p.Insert(pInfo(p_)->netID);
						p.Insert("");
						p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
						p.Insert("locked|0\naccepted|1");
						p.CreatePacket(p_);
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(p_)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
							p.Insert("locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(p_);
						}
					}
					gamepacket_t p;
					p.Insert("OnTradeStatus");
					p.Insert(pInfo(p_)->netID);
					p.Insert("");
					p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
					p.Insert(make_trade_offer(pInfo(p_), true) + "locked|0\naccepted|0");
					p.CreatePacket(p_);
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
							p.Insert(pInfo(p_)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
							p.Insert(make_trade_offer(pInfo(p_), true) + "locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(currentPeer);
						}
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(currentPeer)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
							p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(p_);
						}
					}
					{
						packet_(p_, "action|play_sfx\nfile|audio/tile_removed.wav\ndelayMS|0");
						packet_(currentPeer, "action|play_sfx\nfile|audio/tile_removed.wav\ndelayMS|0");
						gamepacket_t p;
						p.Insert("OnTextOverlay");
						p.Insert("The deal has changed");
						p.CreatePacket(p_), p.CreatePacket(currentPeer);
					}
					pInfo(p_)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
				}
				return;
			}
		}
	}
	if (remove) {
		for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
			auto i = pInfo(p_)->trade_items.at(i_).find(item_id);
			if (i != pInfo(p_)->trade_items.at(i_).end()) {
				pInfo(p_)->trade_items.erase(pInfo(p_)->trade_items.begin() + i_);
				break;
			}
		}
	}
	else {
		bool f_ = false;
		for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
			map<string, int>::iterator it;
			for (auto it = pInfo(p_)->trade_items.at(i_).begin(); it != pInfo(p_)->trade_items.at(i_).end(); it++) {
				if (it->first == item_id and it->second == count) {
					swap(pInfo(p_)->trade_items.at(i_), pInfo(p_)->trade_items.back());
					f_ = true;
					break;
				}
				else if (it->first == item_id and it->second != count) {
					swap(pInfo(p_)->trade_items.at(i_), pInfo(p_)->trade_items.back());
					f_ = true;
					it->second = count;
					break;
				}
			}
		} if (not f_) {
			if (pInfo(p_)->trade_items.size() > 3) return;
			map<int, int> new_;
			new_.insert({ item_id, count });
			pInfo(p_)->trade_items.push_back(new_);
		}
	}
	string name_ = pInfo(p_)->world;
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	if (p != worlds.end()) {
		World* world_ = &worlds.at(p - worlds.begin());
		if (pInfo(p_)->trade_accept == 1) {
			{
				gamepacket_t p;
				p.Insert("OnTradeStatus");
				p.Insert(pInfo(p_)->netID);
				p.Insert("");
				p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
				p.Insert("locked|0\nreset_locks|1\naccepted|0");
				p.CreatePacket(p_);
			}
			gamepacket_t p;
			p.Insert("OnTradeStatus");
			p.Insert(pInfo(p_)->netID);
			p.Insert("");
			p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
			p.Insert("locked|0\naccepted|1");
			p.CreatePacket(p_);
			{
				gamepacket_t p;
				p.Insert("OnTradeStatus");
				p.Insert(pInfo(p_)->netID);
				p.Insert("");
				p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
				p.Insert("locked|0\nreset_locks|1\naccepted|0");
				p.CreatePacket(p_);
			}
		}
		gamepacket_t p;
		p.Insert("OnTradeStatus");
		p.Insert(pInfo(p_)->netID);
		p.Insert("");
		p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
		p.Insert(make_trade_offer(pInfo(p_), true) + "locked|0\naccepted|0");
		p.CreatePacket(p_);
		{
			if (pInfo(p_)->trade_accept == 1) {
				packet_(p_, "action|play_sfx\nfile|audio/tile_removed.wav\ndelayMS|0");
				gamepacket_t p;
				p.Insert("OnTextOverlay");
				p.Insert("The deal has changed");
				p.CreatePacket(p_);
				pInfo(p_)->trade_accept = 0;
			}
		}
	}
}
void SendRespawn(ENetPeer* peer, int instant, bool kill = false) {
	if (pInfo(peer)->trading_with != -1) {
		cancel_trade(peer, false, true);
	}
	if (pInfo(peer)->respawn_time + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
		pInfo(peer)->respawn_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			WorldBlock* block_ = &world_->blocks.at(pInfo(peer)->c_x + (pInfo(peer)->c_y * 100));
			uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
			if (items.at(t_).blockType == BlockTypes::CHECKPOINT or items.at(t_).blockType == BlockTypes::MAIN_DOOR) {
			}
			else {
				int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize, square = (int)world_->blocks.size();
				for (int i_ = 0; i_ < square; i_++) {
					if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::MAIN_DOOR) {
						pInfo(peer)->c_x = (i_ % xSize);
						pInfo(peer)->c_y = (i_ / xSize);
						gamepacket_t p(0, pInfo(peer)->netID);
						p.Insert("SetRespawnPos");
						p.Insert(i_);
						p.CreatePacket(peer);
						break;
					}
				}
			}
		}
		{
			gamepacket_t p(0, pInfo(peer)->netID);
			p.Insert("OnSetFreezeState");
			p.Insert(2);
			p.CreatePacket(peer);
		}

		{
			gamepacket_t p(0, pInfo(peer)->netID);
			p.Insert("SetRespawnPos");
			p.Insert(pInfo(peer)->c_x + (pInfo(peer)->c_y * 100));
			p.CreatePacket(peer);
		}
		{
			if (kill) {
				gamepacket_t p(0, pInfo(peer)->netID);
				p.Insert("OnKilled");
				p.CreatePacket(peer);
			}
		}
		{

			gamepacket_t p((instant == 0 ? 2000 : 100), pInfo(peer)->netID);
			p.Insert("OnSetPos");
			p.Insert(float(pInfo(peer)->c_x) * 32, float(pInfo(peer)->c_y) * 32);
			p.CreatePacket(peer);
		}
		{
			gamepacket_t p((instant == 0 ? 2020 : 100), pInfo(peer)->netID);
			p.Insert("OnPlayPositioned");
			p.Insert("audio/teleport.wav");
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == pInfo(peer)->world) {
					p.CreatePacket(currentPeer);
				}
			}
		}
		{
			gamepacket_t p((instant == 0 ? 2000 : 100), pInfo(peer)->netID);
			p.Insert("OnSetFreezeState");
			p.Insert(0);
			p.CreatePacket(peer);
		}
	}
}
void SendCmd(ENetPeer* peer, string cmd, bool c_ = false) {
	string actual_command = cmd;
	transform(actual_command.begin(), actual_command.end(), actual_command.begin(), ::tolower);
	if (actual_command.find("player_chat=") != string::npos) return;
	if (actual_command.substr(0, 5) == "/msg " || actual_command.substr(0, 3) == "/r " || actual_command == "/msg" || actual_command == "/r") packet_(peer, "action|log\nmsg|CT:[MSG]_ `6" + cmd + "``", "");
	else if (actual_command.substr(0, 4) == "/sb " || actual_command == "/sb") packet_(peer, "action|log\nmsg|CT:[SB]_ `6" + cmd + "``", "");
	else if (actual_command.substr(0, 4) == "/bc " || actual_command == "/bc") packet_(peer, "action|log\nmsg|CT:[BC]_ `6" + cmd + "``", "");
	else if (not c_) packet_(peer, "action|log\nmsg| `6" + cmd + "``", "");
	if (actual_command == "/help" || actual_command == "/?") {
		string a = "";
		packet_(peer, a + "action|log\nmsg|>> Commands: /buy /receive /refund /msg /status /broadcast /sb /cb /sdb /stats /top /ignore /time /who /me /radio /mods /uba /r /go /rgo /pull /kick /ban /wave /dance /love /sleep /facepalm /fp /smh /yes /no /renderworld /omg  /idk /shrug /trade /pb /furious /rolleyes /unaccess /report /rate /foldarms /fa /stubborn /fold /fc " + (pInfo(peer)->aap == "notenabled" ? "/secureaccount " : "") + "/gc /gwarp /guild /roles "+ (pInfo(peer)->mod + pInfo(peer)->dev >= 1 || pInfo(peer)->supp == 2 ? "/warp /hidestatus " : "") +"/fav /home /sethome /gethome /dab /sassy /dance2 /favrm /grumpy /shy " + (pInfo(peer)->dev == 1 ? "/ghost /give <item id> <count> /drop <item id> <count> /hide /pullall" : (pInfo(peer)->mod == 1 ? "/hide /invis /ipcheck /ridcheck /info <name> /banworld /warpto /summon /ban /unmute" : "")) + "");
	}
	else if (actual_command == "/news") news(peer);
	else if (actual_command == "/stop" and pInfo(peer)->dev) {
		cout << "saving everything" << endl;
		saving_ = true;
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`9Server is restarting! (heart)");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			packet_(currentPeer, "action|play_sfx\nfile|audio/ogg/suspended.ogg\ndelayMS|0");
			p.CreatePacket(currentPeer);
		}
		enet_host_flush(server);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			save_player(pInfo(currentPeer), false);
		}
		cout << "saving worlds now" << endl;
		Sleep(2000);
		for (int i = 0; i < worlds.size(); i++) {
			string world_name = worlds.at(i).name;
			save_world(world_name, false);
			Sleep(50);
		}
		cout << "worlds saved now closing" << endl;
		Sleep(2000);
		system("PAUSE");
		exit(0);
	}
	else if (actual_command == "/invis" && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
		if (pInfo(peer)->invis) {
			pInfo(peer)->invis = false;
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oYou are once again visible to mortals.");
			p.CreatePacket(peer);
			{
				gamepacket_t p(0, pInfo(peer)->netID);
				p.Insert("OnInvis");
				p.Insert(0);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(peer)->world) {
						p.CreatePacket(currentPeer);
					}
				}
			}
			update_clothes(peer);
			return;
		}
		else {
			pInfo(peer)->invis = true;
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oYou are now ninja, invisible at all.");
			p.CreatePacket(peer);
			{
				gamepacket_t p(0, pInfo(peer)->netID);
				p.Insert("OnInvis");
				p.Insert(1);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(peer)->world) {
						p.CreatePacket(currentPeer);
					}
				}
			}
			update_clothes(peer);
		}
	}
	else if (actual_command == "/ghost" && pInfo(peer)->dev) {
		packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
		if (pInfo(peer)->ghost) {
			pInfo(peer)->ghost = false;
			pInfo(peer)->skin = 0x8295C3FF;
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
			p.CreatePacket(peer);
			update_clothes(peer);
			return;
		}
		pInfo(peer)->ghost = true;
		pInfo(peer)->skin = -2450;
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
		p.CreatePacket(peer);
		update_clothes(peer);
	}
	else if (actual_command.substr(0, 9) == "/ipcheck " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(9, cmd.length() - 9).c_str();
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert(">> IP CHECK on player " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` (" + pInfo(currentPeer)->requestedName + ") -> " + pInfo(currentPeer)->ip + "");
				p.CreatePacket(peer);
				break;
			}
		}
	}
	else if (actual_command.substr(0, 10) == "/ridcheck " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(10, cmd.length() - 10).c_str();
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert(">> RID CHECK on player " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` (" + pInfo(currentPeer)->requestedName + ") -> " + pInfo(currentPeer)->rid + "");
				p.CreatePacket(peer);
				break;
			}
		}
	}
	else if (actual_command.substr(0, 8) == "/warpto " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(8, cmd.length() - 8).c_str();
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				if (pInfo(currentPeer)->invis and pInfo(currentPeer)->dev and pInfo(peer)->mod) {

				}
				else if (pInfo(currentPeer)->world != "EXIT") {
					{
						if (not pInfo(peer)->invis) {
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnPlayPositioned");
							p.Insert("audio/object_spawn.wav");
							for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
								if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
								if (pInfo(currentPeer2)->world == pInfo(peer)->world) {
									p.CreatePacket(currentPeer2);
								}
							}
						}
					}
					gamepacket_t p;
					p.Insert("OnTextOverlay");
					p.Insert("Moving to location of " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` (`2" + pInfo(currentPeer)->world + "``) ...");
					p.CreatePacket(peer);
					join_world(peer, pInfo(currentPeer)->world, pInfo(currentPeer)->x / 32, pInfo(currentPeer)->y / 32);
				}
				else {
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(peer)->netID);
					p.Insert("Hmm, this person isn't in a world right now.");
					p.Insert(0), p.Insert(0);
					p.CreatePacket(peer);
				}
				break;
			}
		}
	}
	else if (actual_command.substr(0, 8) == "/summon " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(8, cmd.length() - 8).c_str();
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				if (pInfo(currentPeer)->invis and pInfo(currentPeer)->dev and pInfo(peer)->mod) {

				}
				else {
					{
						gamepacket_t p(0, pInfo(currentPeer)->netID);
						p.Insert("OnPlayPositioned");
						p.Insert("audio/object_spawn.wav");
						for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
							if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
							if (pInfo(currentPeer2)->world == pInfo(peer)->world) {
								p.CreatePacket(currentPeer2);
							}
						}
					}
					gamepacket_t p;
					p.Insert("OnTextOverlay");
					p.Insert("You were summoned by a mod");
					p.CreatePacket(currentPeer);
					{
						gamepacket_t p;
						p.Insert("OnTextOverlay");
						p.Insert("Summoning...");
						p.CreatePacket(peer);
					}
					join_world(currentPeer, pInfo(peer)->world, pInfo(peer)->x / 32, pInfo(peer)->y / 32);
				}
				break;
			}
		}
	}
	else if (actual_command == "/pullall" && pInfo(peer)->dev == 1) {
		gamepacket_t p;
		p.Insert("OnTextOverlay");
		p.Insert("Summoning everyone...");
		p.CreatePacket(peer);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->world) {
				gamepacket_t p(0, pInfo(currentPeer)->netID);
				p.Insert("OnPlayPositioned");
				p.Insert("audio/object_spawn.wav");
				p.CreatePacket(currentPeer);
				{
					gamepacket_t p;
					p.Insert("OnTextOverlay");
					p.Insert("You were summoned by a mod");
					p.CreatePacket(currentPeer);
				}
				{
					gamepacket_t p(0, pInfo(currentPeer)->netID);
					p.Insert("OnSetPos");
					p.Insert(pInfo(peer)->x, pInfo(peer)->y);
					p.CreatePacket(currentPeer);
				}
				break;
			}
		}
	}
	else if (actual_command == "/banworld" && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (not world_->nuked) {
				struct tm newtime;
				time_t now = time(0);
				localtime_s(&newtime, &now);
				world_->nuked = true;
				world_->n_t = "" + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/2021 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
				world_->n_b = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("`o>> `4" + world_->name + " `4was nuked from orbit`o. It's the only way to be sure. Play nice, everybody!");
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(peer)->world and not pInfo(currentPeer)->mod and not pInfo(currentPeer)->dev) {
						exit_(currentPeer);
					}
					packet_(peer, "action|play_sfx\nfile|audio/bigboom.wav\ndelayMS|0");
					p.CreatePacket(currentPeer);
				}
			}
			else {
				world_->nuked = false;
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("This world is once again available to everyone!");
				p.CreatePacket(peer);
			}
		}
	}
	else if (actual_command.substr(0, 8) == "/unmute " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(8, cmd.length() - 8).c_str();
		if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
			string bans = "", logs = "", alt = "", alt2 = "", mac = "";
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->tankIDName == pInfo(peer)->last_wrenched) {
					for (int i_ = 0; i_ < pInfo(currentPeer)->playmods.size(); i_++) {
						if (pInfo(currentPeer)->playmods.at(i_).id == 11) {
							pInfo(currentPeer)->playmods.at(i_).time = 0;
							break;
						}
					}
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("`o>> Unmuted person <`2" + pInfo(currentPeer)->tankIDName + "``>``");
					p.CreatePacket(peer);
					break;
				}
			}
		}
	}
	else if (actual_command.substr(0, 6) == "/info " && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		pInfo(peer)->last_wrenched = cmd.substr(6, cmd.length() - 6).c_str();
		if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
			string bans = "", logs = "", alt = "", alt2 = "", mac = "";
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
					if (pInfo(currentPeer)->invis and pInfo(currentPeer)->dev and pInfo(peer)->mod) {

					}
					else {
						mac = pInfo(currentPeer)->mac;
						ifstream m("db/accounts/rid/" + pInfo(currentPeer)->rid + ".txt");
						if (m.is_open()) {
							getline(m, alt);
							m.close();
						}
						replace_str(mac, ":", ".");
						ifstream m2("db/accounts/mac/" + mac + ".txt");
						if (m2.is_open()) {
							getline(m2, alt2);
							m2.close();
						}
						replace_str(alt, "|", " ");
						replace_str(alt2, "|", " ");
						if (alt2 == "") alt2 = "No accounts found. (Because MAC : 02.00.00.00.00.00)";
						for (string a : pInfo(currentPeer)->bans) bans += "\nadd_label_with_icon|small|" + a + "|left|658|";
						for (string a : pInfo(currentPeer)->logs) logs += "\nadd_textbox|" + a + "|";
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|small|`0Editing " + pInfo(currentPeer)->tankIDName + " (" + pInfo(currentPeer)->requestedName + ") - #" + to_string(pInfo(currentPeer)->netID) + "|left|6746|\nadd_spacer|small|" + bans + "\nadd_button|warp_to_" + pInfo(currentPeer)->world + "|Warp To User (in `5" + pInfo(currentPeer)->world + "``)|noflags|0|0|\nadd_spacer|small|\nadd_textbox|Account information:|\nadd_textbox|Email: " + pInfo(currentPeer)->email + "|\nadd_textbox|IP: " + pInfo(currentPeer)->ip + "|\nadd_textbox|RID: " + pInfo(currentPeer)->rid + "|\nadd_textbox|MAC: " + pInfo(currentPeer)->mac + "|\nadd_textbox|AAP: " + pInfo(currentPeer)->aap + "|\nadd_spacer|small|\nadd_textbox|Account notes:|" + logs + "|\nadd_spacer|small|\nadd_textbox|Other accounts (RID):" + alt + "|\nadd_textbox|Other accounts (MAC):" + alt2 + "|\nadd_button|duc_600|`4MUTE for 10 MIN``|noflags|0|0|\nadd_button|duc_1800|`4MUTE for 30 MIN``|noflags|0|0|\nadd_button|ban_600|`4Ban for 10 MIN``|noflags|0|0|\nadd_button|ban_1800|`4Ban for 30 MIN``|noflags|0|0|\nadd_button|ban_3600|`4Ban for 1 HOUR``|noflags|0|0|\nadd_button|ban_21600|`4Ban for 6 HOUR``|noflags|0|0|\nend_dialog|punish_view|Continue||");
						p.CreatePacket(peer);
					}
					break;
				}
			}
		}
	}
	else if (actual_command == "/hide" && pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		if (pInfo(peer)->m_h == 0) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`o>> You hide yourself from everyone (You `4won't`` be visible in /mods, /msg etc.)``");
			p.CreatePacket(peer);
			pInfo(peer)->m_h = 1;
			return;
		}
		pInfo(peer)->m_h = 0;
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`o>> You un-hide yourself from everyone (You `2will`` be visible in /mods, /msg etc.)``");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/unaccess") {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|small|Remove Your Access From World|left|242|\nadd_textbox|Are you sure you want to remove yourself from all locks in this world?|left|\nadd_textbox|Any locks you placed will still be owned by you, but you will be removed from any other locks that you have access on.|left|\nadd_spacer|small|\nend_dialog|unaccess|No|Yes|");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/home") {
		if (pInfo(peer)->home_world.empty()) {
			packet_(peer, "action|log\nmsg|You haven't set a home world yet!");
			return;
		}
		for (pair<string, long long int> p : home_timed) {
			if (p.first == pInfo(peer)->tankIDName) {
				if (p.second + HOME_TIME > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
					packet_(peer, "action|log\nmsg|`4Cooldown active`` - You can use `5/home`` in `5" + to_string(((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) - ((((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) / 60) * 60)) + " ``seconds.");
					return;
				}
			}
		}
		home_timed.push_back(make_pair(pInfo(peer)->tankIDName, (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
		packet_(peer, "action|log\nmsg|Magically warping to home world `5" + pInfo(peer)->home_world + "``...");
		join_world(peer, pInfo(peer)->home_world);
	}
	else if (actual_command == "/status") {
		int w_c = 0, s_c = 0, net_ = 1;
		get_players(pInfo(peer)->world, w_c, s_c, net_);
		string recently_visited = "";
		for (auto it = pInfo(peer)->last_visited_worlds.rbegin(); it != pInfo(peer)->last_visited_worlds.rend(); ++it) {
			string a_ = *it + (next(it) != pInfo(peer)->last_visited_worlds.rend() ? "``, " : "``");
			recently_visited += "`#" + a_;
		}
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s Status:\nCurrent world: `w" + pInfo(peer)->world + "`` (`w" + to_string(pInfo(peer)->x / 32) + "``, `w" + to_string(pInfo(peer)->y / 32) + "``) (`w" + to_string(w_c) + "`` people)\nBackpack slots: `w" + to_string(pInfo(peer)->inv.size() - 1) + "``\nLast visited: " + recently_visited + form_mods(pInfo(peer), 1) + "");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/msg") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Usage: /msg <`$full or first part of a name``> <`$your message``> - This will send a private message to someone anywhere in the universe.  If you don't include a message, you can just see if he/she is online or not.");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/stats") {
		int w_c = 0, s_c = 0, net_ = 1;
		get_players(pInfo(peer)->world, w_c, s_c, net_);
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		string month = months[newtime.tm_mon];
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("S1 Uptime: 1 day, 8 hours, 6 mins, 17 secs - `$" + setGems(s_c) + "`` players on.  Stats for this node: `$" + setGems(s_c) + "`` players. (44 Android, 4 iOS) and `$129`` Worlds active. Server Load: 25.82 27.14 27.14``\n`2Growtopia Time (EDT/UTC-5): " + month + " " + to_string(newtime.tm_mday) + "th, " + to_string(newtime.tm_hour) + ":" + to_string(newtime.tm_min) + "");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/top") {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wWorld Rankings``|left|394|\nadd_spacer|small|\nadd_textbox|`oWorld Rankings are based on unique daily visitors.  Where do your worlds stack up?``|left|\nadd_button|toprated|`8Top Rated Worlds``|noflags|0|0|\nadd_button|today|`8Top worlds today``|noflags|0|0|\nadd_button|yesterday|`5Top worlds yesterday``|noflags|0|0|\nadd_button|total|`wTop worlds overall``|noflags|0|0|\nadd_button|wotd|`$World of the Day winners``|noflags|0|0|\nadd_button|votw|`$Video of the Week winners``|noflags|0|0|\nadd_button||Close|noflags|0|0|\nend_dialog|ranking|||\n");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/ignore") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Type `5/ignore`` <`5name``> to mute them.  (You can unmute people using the `5Friends List``)");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/mods") {
		string mods = "", a = "";
		int count = 0;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->m_h == 1) continue;
			if (pInfo(currentPeer)->invis == true) continue;
			if (pInfo(currentPeer)->mod == 1 || pInfo(currentPeer)->dev == 1) {
				count++;
				mods += "" + a + (count == 1 ? "" : ", ") + "" + (pInfo(currentPeer)->mod ? "`#@" : (pInfo(currentPeer)->dev ? "`6@" : "")) + pInfo(currentPeer)->tankIDName + "``";
			}
		}
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Mods online: " + (mods != "" ? mods : "(All are hidden)") + "`o.``");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/go") {
		gamepacket_t p;
		p.Insert("OnTextOverlay");
		if (lastsbworld == pInfo(peer)->world || lastsbworld == "") p.Insert("Unable to track down the location of the last broadcast!");
		else {
			p.Insert("Moving to location of the last broadcast (`2" + lastsbworld + "``) ...");
			packet_(peer, "action|play_sfx\nfile|audio/object_spawn.wav\ndelayMS|0");
			join_world(peer, lastsbworld);
		}
		p.CreatePacket(peer);
	}
	else if (actual_command == "/rgo") {
		gamepacket_t p;
		if (pInfo(peer)->lastmsgworld == pInfo(peer)->world) {
			p.Insert("OnConsoleMessage");
			p.Insert("You magically appear at the world you were already in.  Great job!");
			p.CreatePacket(peer);
			return;
		}
		if (pInfo(peer)->lastmsgworld == "") {
			p.Insert("OnTextOverlay");
			p.Insert("Unable to track down the location of the last broadcast!");
			p.CreatePacket(peer);
			return;
		}
		p.Insert("OnTextOverlay");
		p.Insert("Moving to where `w/" + pInfo(peer)->lastmsg + "`` sent that last `5/msg`` from... (`2" + pInfo(peer)->lastmsgworld + "``) ...");
		p.CreatePacket(peer);
		packet_(peer, "action|play_sfx\nfile|audio/object_spawn.wav\ndelayMS|0");
		join_world(peer, pInfo(peer)->lastmsgworld);
	}
	else if (actual_command == "/pull" || actual_command == "/kick" || actual_command == "/ban") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("You'll need to enter at least the first three characters of the person's name.");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/trade") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("To trade with a specific person in this world, do `2/trade <``full or partial name`2>``");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/gc") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`6>> Guildcast! Use /gc <message> to send messages to everyone who's online in your guild list. (they must have `5Show Guild Member Notifications`` checked to see them!)``");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/gwarp") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("You are not in a Guild!");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/guild") {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1You need to be a `2Supporter`` or `2Super Supporter`` to create a guild. However you can join other guilds to compete for glory!``|left|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||\n");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/roles") {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert("add_label_with_icon|big|`wRole Quests``|left|982|\nadd_spacer|small|\nadd_textbox|`9What's your specialty? Punch, Build, Grow, and more to earn points and unlock Role Rewards and Powers!``|left|\nadd_spacer|small|\nadd_smalltext|- You have embarked on 0 Role Quests today!|left|\nadd_smalltext|- Your quests will reset in: 8 hours, 56 mins and any progress on the current quest will be lost.|left|\nadd_spacer|small|\nadd_smalltext|- You haven't started any Role Quests today!|left|\nadd_smalltext|- Your first quest for the day is `2FREE`` to start!|left|\nadd_button|questselect|Quest Select|noflags|0|0|\nadd_button|viewrolestats|View Role Stats|noflags|0|0|\nadd_custom_textbox|`5- Earn 20 Grow Pass Points.``|size:small|\nadd_button|grow_pass|View Grow Pass|noflags|0|0|\nend_dialog|rolequestspage||Back|\nadd_quick_exit|\n");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/secureaccount") {
		if (pInfo(peer)->aap == "notenabled") {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("Working...");
			p.CreatePacket(peer);
			{
				gamepacket_t p(500);
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAdvanced Account Protection ``|left|3732|\nadd_textbox|`1You are about to enable the Advanced Account Protection.``|left|\nadd_textbox|`1After that, every time you try to log in from a new device and IP you will receive an email with a login confirmation link.``|left|\nadd_textbox|`1This will significantly increase your account security.``|left|\nend_dialog|secureaccount|Cancel|Ok|");
				p.CreatePacket(peer);
			}
		}
	}
	else if (actual_command == "/broadcast" || actual_command == "/bc") packet_(peer, "action|log\nmsg|>> This lets you send a message to `5100`` random users online.  Costs `$100 Gems`` to use.  Example:`` `w/broadcast Hey guys, come to my world!", "");
	else if (actual_command == "/sb") {
		int w_c = 0, s_c = 0, net_ = 1;
		get_players(pInfo(peer)->world, w_c, s_c, net_);
		packet_(peer, "action|log\nmsg|>> This lets you send a message to " + to_string(s_c) + "`` random users online and make an annoying beep noise.  Costs `$" + to_string(s_c) + " Gems`` to use. Example:`` `w/sb Hey guys, come to my world!", "");
	}
	else if (actual_command == "/cb") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`5/cb`` allows you to broadcast to a specific # of people.  Usage: `5/cb <people to hit> <message>``.  It will max out at the current people online.  `5/cb <person count>`` with no other parms will show the cost to send to that many people.");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/sdb") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`6>> `4Oops: ``The super duper broadcast has been disabled for now, either because it was causing lag or just too dang annoying.  Try again later.");
		p.CreatePacket(peer);
	}
	else if (actual_command == "/me") packet_(peer, "action|log\nmsg|`6>> Type `5/me looks around suspiciously`` or any other text, useful for role playing.", "");
	else if (actual_command == "/hidestatus" && pInfo(peer)->supp >= 2) {
	if (pInfo(peer)->hs == 0) pInfo(peer)->hs = 1;
	else pInfo(peer)->hs = 0;
		string a = "";
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Super Supporter status "+a + (pInfo(peer)->hs == 1 ? "visible" : "hidden") + "!");
		p.CreatePacket(peer);
		update_clothes(peer);
	}
	else if (actual_command.substr(0, 6) == "/warp " && pInfo(peer)->supp + pInfo(peer)->mod + pInfo(peer)->dev >= 1) {
		string world = actual_command.substr(6, cmd.length() - 6).c_str();
		transform(world.begin(), world.end(), world.begin(), ::toupper);
		gamepacket_t p;
		bool passed = true;
		p.Insert("OnConsoleMessage");
		if (pInfo(peer)->mod + pInfo(peer)->dev == 0) {
			if (pInfo(peer)->warp_time + 15000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) pInfo(peer)->warp_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			else {
				p.Insert("`4Cooldown active`` - You can use  `5/warp`` in `5" + to_string((pInfo(peer)->warp_time + WARP_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) + "`` seconds.");
				passed = false;
			}
		}
		if (passed) {
			p.Insert("Magically warping to world `5" + world + "``...");
			p.CreatePacket(peer);
			join_world(peer, world);
		}
		else p.CreatePacket(peer);
	}
	else if (actual_command.substr(0, 4) == "/me ") {
		if (has_playmod(pInfo(peer), "duct tape")) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`6>> That's sort of hard to do while duct-taped.``");
			p.CreatePacket(peer);
			return;
		}
		string text = cmd.substr(4, cmd.length() - 4).c_str();
		if (text.length() <= 0 || text.length() > 120 || text.empty() || std::all_of(text.begin(), text.end(), [](char c) {return std::isspace(c); })) return;
		for (char c : text) if (c < 0x20 || c>0x7A) return;
		gamepacket_t p, p2;
		p.Insert("OnConsoleMessage");
		p.Insert("CP:0_PL:0_OID:__CT:[W]_ `6<``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `#" + text + "```6>``");
		p2.Insert("OnTalkBubble");
		p2.Insert(pInfo(peer)->netID);
		p2.Insert("player_chat= `6<```0" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `#" + text + "```6>``");
		p2.Insert(0);
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->world) {
				p.CreatePacket(currentPeer);
				p2.CreatePacket(currentPeer);
			}
		}
	}
	else if (actual_command == "/who") {
		string who = "`wWho's in `$" + pInfo(peer)->world + "``:`` " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->tankIDName == pInfo(peer)->tankIDName) continue;
			if (pInfo(currentPeer)->invis == true) continue;
			if (pInfo(currentPeer)->world == pInfo(peer)->world) {
				who += ", " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``";
				gamepacket_t p2;
				p2.Insert("OnTalkBubble");
				p2.Insert(pInfo(currentPeer)->netID);
				p2.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName);
				p2.CreatePacket(peer);
			}
		}
		p.Insert(who);
		p.CreatePacket(peer);
	}
	else if (actual_command == "/r") {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("Usage: /r <`$your message``> - This will send a private message to the last person who sent you a message. Use /msg to talk to somebody new!");
		p.CreatePacket(peer);
	}
	else if (actual_command.substr(0, 7) == "/trade ") {
		pInfo(peer)->last_wrenched = cmd.substr(7, cmd.length() - 7).c_str();
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == pInfo(peer)->world and to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched) || to_lower(pInfo(currentPeer)->tankIDName.substr(0, 3)) == to_lower(pInfo(peer)->last_wrenched) and not pInfo(currentPeer)->invis) {
					for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
						if (pInfo(currentPeer)->friends.at(c_).name == pInfo(peer)->tankIDName) {
							if (pInfo(currentPeer)->friends.at(c_).block_trade)
								return;
						}
					}
					if (pInfo(currentPeer)->trading_with != -1 and pInfo(currentPeer)->trading_with != pInfo(peer)->netID) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("That person is busy.");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
						pInfo(peer)->block_trade = false, pInfo(peer)->trading_with = -1;
						{
							gamepacket_t p;
							p.Insert("OnForceTradeEnd");
							p.CreatePacket(peer);
						}
						return;
					}
					pInfo(peer)->trading_with = pInfo(currentPeer)->netID;
					pInfo(peer)->trade_accept = 0;
					pInfo(currentPeer)->trade_accept = 0;
					gamepacket_t p;
					p.Insert("OnStartTrade");
					p.Insert(pInfo(currentPeer)->tankIDName);
					p.Insert(pInfo(currentPeer)->netID);
					p.CreatePacket(peer);
					if (pInfo(currentPeer)->trading_with != -1) {
						// as neisivaizduoju kdl real gt taip daro bet noriu kad butu kaip rgt.
						gamepacket_t p;
						p.Insert("OnTradeStatus");
						p.Insert(pInfo(peer)->netID);
						p.Insert("");
						p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
						p.Insert("locked|0\nreset_locks|1\naccepted|0");
						p.CreatePacket(peer);
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(peer)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
							p.Insert("locked|0\naccepted|1");
							p.CreatePacket(peer);
						}
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(peer)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``'s offer.``");
							p.Insert("locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(peer);
						}
						{
							gamepacket_t p;
							p.Insert("OnTradeStatus");
							p.Insert(pInfo(currentPeer)->netID);
							p.Insert("");
							p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
							p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
							p.CreatePacket(peer);
							{
								gamepacket_t p;
								p.Insert("OnTradeStatus");
								p.Insert(pInfo(currentPeer)->netID);
								p.Insert("");
								p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
								p.Insert("locked|0\nreset_locks|1\naccepted|0");
								p.CreatePacket(currentPeer);
							}
							{
								gamepacket_t p;
								p.Insert("OnTradeStatus");
								p.Insert(pInfo(currentPeer)->netID);
								p.Insert("");
								p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
								p.Insert("locked|0\naccepted|1");
								p.CreatePacket(currentPeer);
							}
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
								p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
								p.CreatePacket(currentPeer);
							}
						}
						break;
					}
					packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
					{
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`#TRADE ALERT:`` `w" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "```` wants to trade with you!  To start, use the `wWrench`` on that person's wrench icon, or type `w/trade " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
						p.CreatePacket(currentPeer);
					}
					break;
				}
			}
		}
	}
	else if (actual_command.substr(0, 6) == "/kick ") {
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) {
				gamepacket_t p;
				p.Insert("OnTextOverlay");
				p.Insert("Can't `4kick``, is not in a locked area you control!");
				p.CreatePacket(peer);
				return;
			}
		}
		string username = cmd.substr(6, cmd.length() - 6).c_str();
		if (to_lower(pInfo(peer)->tankIDName) == to_lower(username)) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oYou give yourself a solid boot to the backside. But what did that really accomplish?");
			p.CreatePacket(peer);
			return;
		}
		bool playerFound = false;
		string color = "`o";
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(peer)->world == pInfo(currentPeer)->world) {
				if (to_lower(pInfo(currentPeer)->tankIDName.substr(0, 3)) == to_lower(username) || to_lower(pInfo(currentPeer)->tankIDName) == to_lower(username)) {
					if (not pInfo(currentPeer)->dev) {
						playerFound = true;
						username = pInfo(currentPeer)->tankIDName;
						if (pInfo(currentPeer)->name_color != "`0") color = pInfo(currentPeer)->name_color;
						SendRespawn(currentPeer, 0, 1);
					}
					break;
				}
			}
		}
		if (playerFound) {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(peer)->world == pInfo(currentPeer)->world) {
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `4kicks`` `o" + color + username + "``!``");
					p.CreatePacket(currentPeer);
				}
			}
		}
		else {
			packet_(peer, "action|log\nmsg| `4Oops: `oThere is nobody currently in this world with a name starting with `w" + username + "`o.", "");
		}
	}
	else if (actual_command == "/uba") {
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("You don't have access to the world lock, so you can't unban all!");
				p.CreatePacket(peer);
				return;
			}
			world_->bannedPlayers.clear();
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("CP:_PL:0_OID:_CT:[S]_ You've unbanned everybody from this world.");
			p.CreatePacket(peer);
		}
	}
	else if (actual_command.substr(0, 5) == "/ban ") {
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) {
				gamepacket_t p;
				p.Insert("OnTextOverlay");
				p.Insert("Can't `4world ban``, is not in a world you control!");
				p.CreatePacket(peer);
				return;
			}
			string name = cmd.substr(5, cmd.length() - 5).c_str();
			if (to_lower(pInfo(peer)->tankIDName) == to_lower(name)) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("`oYou are banned from banning yourself!");
				p.CreatePacket(peer);
				return;
			}
			string color = "`o", named = "";
			bool playerfound = false;
			int found = 0;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
				if (to_lower(pInfo(currentPeer)->tankIDName.substr(0, 3)) == to_lower(name) || to_lower(name) == to_lower(pInfo(currentPeer)->tankIDName)) {
					if (not pInfo(currentPeer)->dev) {
						found++;
						playerfound = true;
						world_->bannedPlayers.push_back(make_pair(pInfo(currentPeer)->tankIDName, (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
						if (pInfo(currentPeer)->name_color != "`0") color = pInfo(currentPeer)->name_color;
						named = pInfo(currentPeer)->tankIDName;
						exit_(currentPeer);
					}
					break;
				}
			}
			if (playerfound) {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(peer)->world == pInfo(currentPeer)->world or to_lower(name) == to_lower(pInfo(currentPeer)->tankIDName)) {
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `4world bans`` " + color + named + "`` from `0" + name_ + "``!");
						p.CreatePacket(currentPeer);
						packet_(currentPeer, "action|play_sfx\nfile|audio/repair.wav\ndelayMS|0");
					}
				}
				gamepacket_t p2;
				p2.Insert("OnConsoleMessage");
				p2.Insert("You've banned " + color + named + "`` from `w" + name_ + "`` for one hour.  You can also type `#/uba`` to unban him/her early.");
				p2.CreatePacket(peer);
			}
			else {
				packet_(peer, "action|log\nmsg| `4Oops: `oThere is nobody currently in this world with a name starting with `w" + name + "`o.", "");
			}
		}
	}
	else if (actual_command.substr(0, 6) == "/pull ") {
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) {
				gamepacket_t p;
				p.Insert("OnTextOverlay");
				p.Insert("Can't `5pull``, that player is not standing in an area you control!");
				p.CreatePacket(peer);
				return;
			}
		}
		string username = cmd.substr(6, cmd.length() - 6).c_str();
		if (to_lower(pInfo(peer)->tankIDName) == to_lower(username)) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`oOuch!");
			p.CreatePacket(peer);
			return;
		}
		bool playerFound = false;
		string color = "`o";
		/*0: OnTextOverlay
1: Can't `4kick``, is not in a locked area you control!
*/
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(peer)->world == pInfo(currentPeer)->world) {
				if (to_lower(pInfo(currentPeer)->tankIDName.substr(0, 3)) == to_lower(username) || to_lower(pInfo(currentPeer)->tankIDName) == to_lower(username)) {
					if (not pInfo(currentPeer)->dev) {
						username = pInfo(currentPeer)->tankIDName;
						playerFound = true;
						if (pInfo(currentPeer)->name_color != "`0") color = pInfo(currentPeer)->name_color;
						pInfo(currentPeer)->x = pInfo(peer)->x, pInfo(currentPeer)->y = pInfo(peer)->y;
						gamepacket_t p(0, pInfo(currentPeer)->netID);
						p.Insert("OnSetPos");
						p.Insert(pInfo(peer)->x, pInfo(peer)->y);
						p.CreatePacket(currentPeer);
					}
					break;
				}
			}
		}
		if (playerFound) {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(peer)->world == pInfo(currentPeer)->world) {
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` `5pulls`` `o" + color + username + "``!``");
					p.CreatePacket(currentPeer);
					packet_(currentPeer, "action|play_sfx\nfile|audio/teleport.wav\ndelayMS|0");
				}
			}
		}
		else {
			packet_(peer, "action|log\nmsg| `4Oops: `oThere is nobody currently in this world with a name starting with `w" + username + "`o.", "");
		}
	}
	else if (actual_command.substr(0, 5) == "/msg " || actual_command.substr(0, 3) == "/r ") {
		if (has_playmod(pInfo(peer), "duct tape")) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`6>> That's sort of hard to do while duct-taped.``");
			p.CreatePacket(peer);
			return;
		}
		string message = "";
		string username = "";
		if (actual_command.substr(0, 5) == "/msg ") {
			if (cmd.substr(5).find(" ") == string::npos) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Usage: /msg <`$full or first part of a name``> <`$your message``> - This will send a private message to someone anywhere in the universe.  If you don't include a message, you can just see if he/she is online or not.");
				p.CreatePacket(peer);
				return;
			}
			string s = cmd.substr(5);
			stringstream ss(s);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> vstrings(begin, end);
			if (vstrings.size() < 1) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Usage: /msg <`$full or first part of a name``> <`$your message``> - This will send a private message to someone anywhere in the universe.  If you don't include a message, you can just see if he/she is online or not.");
				p.CreatePacket(peer);
				return;
			}
			username = vstrings[0];
			if (username == "") {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Usage: /msg <`$full or first part of a name``> <`$your message``> - This will send a private message to someone anywhere in the universe.  If you don't include a message, you can just see if he/she is online or not.");
				p.CreatePacket(peer);
				return;
			}
			message = "";
			for (int i = 1; i < vstrings.size(); i++) message = message + vstrings[i] + " ";
		}
		else {
			message = cmd.substr(3, cmd.length() - 3).c_str();
			username = pInfo(peer)->lastmsg;
			if (username == "") {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Usage: /r <`$your message``> - This will send a private message to the last person who sent you a message. Use /msg to talk to somebody new!");
				p.CreatePacket(peer);
				return;
			}
		}
		//find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) == world_->active_jammers.end()
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			bool playerFound = false;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->m_h == 1 or pInfo(currentPeer)->invis == true) continue;
				if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(username)) {
					playerFound = true;
					if (message.length() < 1) {
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`6>> `$" + pInfo(currentPeer)->tankIDName + "`` is online now.``");
						p.CreatePacket(peer);
					}
					else {
						bool muted_ = false;
						for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
							if (pInfo(peer)->friends.at(c_).name == pInfo(currentPeer)->tankIDName) {
								if (pInfo(peer)->friends.at(c_).mute) {
									muted_ = true;
									break;
								}
							}
						}
						{
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							if (pInfo(currentPeer)->mod == 1 || pInfo(currentPeer)->dev == 1) p.Insert("CT:[MSG]_`6>> (Sent to `$" + pInfo(currentPeer)->tankIDName + "``)`` (`4Note: ``Message a mod `4ONLY ONCE`` about an issue. Mods don't fix scams or replace items, they punish players who break the `5/rules``.  For issues related to account recovery or purchasing, contact support at `5http://privategt.com``)");
							else {
								if (muted_) {
									p.Insert("CT:[MSG]_`6>> (Sent to `$" + pInfo(currentPeer)->tankIDName + "``)`` (`4Note: ``You can't send messages to people you muted)");
								}
								else {
									p.Insert("CT:[MSG]_`6>> (Sent to `$" + pInfo(currentPeer)->tankIDName + "``)``");
								}
							}
							p.CreatePacket(peer);
						}
						{
							for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
								if (pInfo(currentPeer)->friends.at(c_).name == pInfo(peer)->tankIDName) {
									if (pInfo(currentPeer)->friends.at(c_).mute) {
										return;
									}
								}
							}
							pInfo(currentPeer)->lastmsg = pInfo(peer)->tankIDName;
							if (pInfo(peer)->mod == 0 && pInfo(peer)->dev == 0)pInfo(currentPeer)->lastmsgworld = pInfo(peer)->world;
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("CP:0_PL:0_OID:_CT:[MSG]_>> `c>> from (```c" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`````c) in [`$" + (pInfo(peer)->m_h || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4<HIDDEN>``" : pInfo(peer)->world) + "``] > ```$" + message + "``");
							p.CreatePacket(currentPeer);
							packet_(currentPeer, "action|play_sfx\nfile|audio/pay_time.wav\ndelayMS|0");
						}
					}
					break;
				}
			}
			if (!playerFound) {
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				if (username.length() < 5) p.Insert("`6>> `$" + username + "`` is not online right now (you need to enter at least 5 letters if you meant a longer name!).``");
				else p.Insert("`6>> No one online who has a name starting with `$" + username + "``.``");
				p.CreatePacket(peer);
			}
		}
	}
	else if (actual_command.substr(0, 4) == "/gm " && pInfo(peer)->dev == 1) {
		string text = cmd.substr(4, cmd.length() - 4).c_str();
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("CP:_PL:0_OID:_CT:[S]_ `o**`` `$Global System Message:`` `4" + text + "``");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			p.CreatePacket(currentPeer);
		}
	}
	else if (actual_command.substr(0, 4) == "/sb " || actual_command.substr(0, 4) == "/bc ") {
		if (has_playmod(pInfo(peer), "duct tape")) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`6>> That's sort of hard to do while duct-taped.``");
			p.CreatePacket(peer);
			return;
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
			return;
		}
		int w_c = 0, s_c = 100, net_ = 1;
		if (actual_command.substr(0, 4) == "/sb ") {
			s_c = 0;
			get_players(pInfo(peer)->world, w_c, s_c, net_);
		}
		if (pInfo(peer)->gems >= s_c) {
			pInfo(peer)->gems -= s_c;
			PlayMods new_playmod{};
			new_playmod.id = 13;
			new_playmod.time = time(nullptr) + 600;
			pInfo(peer)->playmods.push_back(new_playmod);
			{
				gamepacket_t p;
				p.Insert("OnSetBux");
				p.Insert(pInfo(peer)->gems);
				p.Insert(1);
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("Broadcasting to ALL! (`$Megaphone!`` mod added)");
				p.CreatePacket(peer);
			}
			{
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				if (actual_command.substr(0, 4) == "/sb ") p.Insert("`#Super-Broadcast sent. Used `$" + setGems(s_c) + " Gems``. (`$" + setGems(pInfo(peer)->gems) + "`` left)`` (10 mins before you can broadcast again)");
				else p.Insert(">> `#Broadcast sent. Used `$" + setGems(s_c) + " Gems``. (`$" + setGems(pInfo(peer)->gems) + "`` left)`` (10 mins before you can broadcast again)");
				p.CreatePacket(peer);
			}
		}
		else {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert(">> You don't have `$" + setGems(s_c) + " Gems``, you can't broadcast a message!");
			p.CreatePacket(peer);
			return;
		}
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			string text = cmd.substr(4, cmd.length() - 4).c_str();
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			if (pInfo(peer)->m_h != 1 and find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) == world_->active_jammers.end()) {
				lastsbworld = pInfo(peer)->world;
			}
			int sentto = 0;
			if (actual_command.substr(0, 4) == "/sb ") p.Insert("CP:_PL:0_OID:_CT:[SB]_ `5** from (`0" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`````5) in [```$" + (pInfo(peer)->m_h == 1 || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "```5] ** : ``" + (pInfo(peer)->mod + pInfo(peer)->dev == 0 ? "`$" : "`^") + "" + text + "``");
			else p.Insert("CP:_PL:0_OID:_CT:[BC]_ `p** from (`0" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`````p) in [```$" + (pInfo(peer)->m_h == 1 || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "```p] ** : ``" + (pInfo(peer)->mod + pInfo(peer)->dev == 0 ? "`$" : "`^") + "" + text + "``");
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (actual_command.substr(0, 4) == "/bc " && sentto > 100) continue;
				sentto++;
				p.CreatePacket(currentPeer);
			}
		}
	}
	else if (actual_command == "/time") {
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		string month = months[newtime.tm_mon];
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert("`2Growtopia Time (EDT/UTC-5): " + month + " " + to_string(newtime.tm_mday) + "th, " + (newtime.tm_hour < 10 ? "0" + to_string(newtime.tm_hour) + "" : "" + to_string(newtime.tm_hour) + "") + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min) + "") + ".");
		p.CreatePacket(peer);
	}
	else if (actual_command.substr(0, 6) == "/give " && pInfo(peer)->dev == 1) {
		vector<string> a_ = explode(" ", cmd);
		if (a_.size() != 3) return;
		if (not isdigit(a_[1][0]) or not isdigit(a_[2][0])) return;
		int i_ = atoi(a_[1].c_str()), c_ = atoi(a_[2].c_str());
		if (i_ <= 0 or c_ <= 0 or i_ >= items.size()) return;
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		if (modify_inventory(peer, i_, c_) == -1) p.Insert("Failed to add inventory item");
		else {
			AddLogs(peer, "Used /give to receive " + items.at(i_).name + " (" + a_[2] + ")");
			p.Insert("Collected `w" + a_[2] + " " + items.at(i_).name + "``." + (items.at(i_).rarity > 363 ? "" : " Rarity: `w" + to_string(items.at(i_).rarity) + "``") + "");
		}
		p.CreatePacket(peer);
		return;
	}
	else if (actual_command.substr(0, 6) == "/drop " && pInfo(peer)->dev == 1) {
		vector<string> a_ = explode(" ", cmd);
		if (a_.size() != 3) return;
		if (not isdigit(a_[1][0]) or not isdigit(a_[2][0])) return;
		int i_ = atoi(a_[1].c_str()), c_ = atoi(a_[2].c_str());
		if (i_ <= 0 or c_ <= 0 or i_ >= items.size()) return;
		string name_ = pInfo(peer)->world;
		vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (p != worlds.end()) {
			World* world_ = &worlds.at(p - worlds.begin());
			WorldDrop drop_block_{};
			drop_block_.x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - ((rand() % 12) + 18) : pInfo(peer)->x + ((rand() % 12) + 22));
			drop_block_.y = pInfo(peer)->y + rand() % 16;
			drop_block_.id = i_, drop_block_.count = c_, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
			dropas_(world_, drop_block_);
		}
		return;
	}
	else if (actual_command == "/dance" || actual_command == "/sad" || actual_command == "/wave" || actual_command == "/love" || actual_command == "/sleep" || actual_command == "/wink" || actual_command == "/troll" || actual_command == "/cheer" || actual_command == "/fa" || actual_command == "/furious" || actual_command == "/dab" || actual_command == "/dance2" || actual_command == "/cheer" || actual_command == "/laugh" || actual_command == "/cry" || actual_command == "/mad" || actual_command == "/shower" || actual_command == "/rolleyes" || actual_command == "/omg" || actual_command == "/yes" || actual_command == "/idk" || actual_command == "/fold" || actual_command == "/no" || actual_command == "/sassy" || actual_command == "/fp" || actual_command == "/troll" || actual_command == "/facepalm" || actual_command == "/foldarms" || actual_command == "/stubborn" || actual_command == "/grumpy" || actual_command == "/shy" || actual_command == "/smh") {
		gamepacket_t p(0, pInfo(peer)->netID);
		p.Insert("OnAction");
		p.Insert(cmd);
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
				}
				if (not muted_)
					p.CreatePacket(currentPeer);
			}
		}
	}
	else packet_(peer, "action|log\nmsg|`4Unknown command.``  Enter `$/?`` for a list of valid commands.");
}
bool trade_space_check(ENetPeer* peer, ENetPeer* currentPeer) {
	int slots_needed = int(pInfo(currentPeer)->trade_items.size());
	for (int i_ = 0; i_ < pInfo(currentPeer)->trade_items.size(); i_++) {
		map<string, int>::iterator it;
		for (auto it = pInfo(currentPeer)->trade_items.at(i_).begin(); it != pInfo(currentPeer)->trade_items.at(i_).end(); it++) {
			int c_ = 0;
			modify_inventory(peer, it->first, c_);
			if (c_ != 0) {
				if (c_ + it->second > 200) {
					gamepacket_t p;
					p.Insert("OnTextOverlay");
					p.Insert("`4Oops - " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` is carrying too many " + items.at(it->first).name + " and can't fit that many in their backpack.");
					p.CreatePacket(peer), p.CreatePacket(currentPeer);
					return false;
				}
				slots_needed--;
			}
		}
	}
	int free_slots = get_free_slots(pInfo(peer));
	if (free_slots < slots_needed) {
		gamepacket_t p;
		p.Insert("OnTextOverlay");
		p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` needs more backpack room first!");
		p.CreatePacket(peer), p.CreatePacket(currentPeer);
		return false;
	}
	return true;
}
int get_wls(ENetPeer* peer) {
	int my_wls = 0;
	int c_ = 0;
	modify_inventory(peer, 242, c_);
	my_wls += c_;
	c_ = 0;
	modify_inventory(peer, 1796, c_);
	my_wls += c_ * 100;
	/*c_ = 0;
	modify_inventory(peer, 7188, c_);
	my_wls += c_ * 10000;*/
	return my_wls;
}
string get_sucker(ENetPeer* peer, World* world_, WorldBlock* block_, int x_, int y_) {
	if (block_->id == 0) {
		return "set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_textbox|`6The machine is empty.``|left|\nadd_item_picker|selectitem|`wChoose Item``|Choose an item to put in the " + items.at(block_->fg).name + "!|\nend_dialog|itemsucker_block|Close||";
	}
	bool ar_turi = false;
	int c_ = 0;
	if (block_->id != 0) {
		modify_inventory(peer, block_->id, c_);
		if (c_ != 0) {
			ar_turi = true;
		}
	}
	bool ar_turi_mag = false;
	{
		int c_ = 0;
		if (block_->id != 0) {
			modify_inventory(peer, 5640, c_);
			if (c_ != 0) {
				if (pInfo(peer)->magnetron_x == x_ and pInfo(peer)->magnetron_y == y_ and pInfo(peer)->magnetron_id == block_->id) {
					ar_turi_mag = true;
				}
			}
		}
	}
	bool dont_give = false;
	if (items.at(block_->id).collisionType != 1 and items.at(block_->id).blockType != BACKGROUND and items.at(block_->id).blockType != SEED and not items.at(block_->id).farmable or items.at(block_->id).rarity == 999) {
		dont_give = true;
	}
	string alalala = (block_->magnetron ? "`5ACTIVE" : "`6DISABLED");
	return "set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_label_with_icon|small|`2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|" + (block_->pr == 0 ? "\nadd_textbox|`6The machine is currently empty!``|left|" : "\nadd_textbox|The machine contains " + to_string(block_->pr) + " `2" + items.at(block_->id).name + "``|left|") + (ar_turi ? (block_->pr >= (block_->fg == 5638 ? 5000 : 1500) ? "\nadd_smalltext|`4The machine is at maximum capacity!``|left|" : "\nadd_button|additem|Add Items to the machine|noflags|0|0|") : (block_->pr >= (block_->fg == 5638 ? 5000 : 1500) ? "\nadd_smalltext|`4The machine is at maximum capacity!``|left|" : "")) + (block_->pr != 0 ? (c_ == 200 ? "\nadd_textbox|`6You are already carrying 200 " + items.at(block_->id).name + "!``|left|" : "\nadd_button|retrieveitem|Retrieve Item|noflags|0|0|") : "\nadd_button|clearitem|Change Item|noflags|0|0|") + (block_->fg == 5638 ? "\nadd_textbox|Building mode: " + alalala + "``|left|" : "") + (block_->fg == 5638 ? "\nadd_textbox|Use the " + items.at(5640).name + " to build `2" + items.at(block_->id).name + "`` directly from the " + items.at(block_->fg).name + "'s storage.|left|" : "") + (block_->fg == 5638 and not ar_turi_mag and not dont_give ? "\nadd_button|getplantationdevice|Get Remote|noflags|0|0|" : "") + "\nadd_checkbox|chk_enablesucking|Enable Collection.|" + (block_->enabled ? "1" : "0") + "\nend_dialog|itemsucker_block|Close|Update|";
}
bool not_mod(WorldBlock block_, int x_, int y_) {
	cout << block_.fg << endl;
	if (x_ < 0 or x_ >= 100 or y_ >= 60 or y_ < 0 or block_.locked or items.at(block_.fg).blockType == LOCK) {
		cout << "return false" << endl;
		return false;
	} if (block_.fg == 0) return true;
	if (items.at(block_.fg).properties & Property_Mod) {
		return false;
	}
	return true;
}
string get_vending(ENetPeer* peer, World* world_, WorldBlock* block_, int x_, int y_) {
	int c_ = 0;
	string ex_ = "";
	if (block_->id != 0) {
		modify_inventory(peer, block_->id, c_);
		if (c_ != 0) {
			ex_ = "\nadd_smalltext|You have " + to_string(c_) + " " + items.at(block_->id).name + " in your backpack.|\nadd_button|addstock|Add them to the machine|noflags|0|0|";
		}
	}
	string a_ = (block_->pr < 0 and (block_->pr * -1 > block_->c_) ? "\nadd_smalltext|`4(You need to add more items or people can't purchase at this price!)``|left|" : "");
	return "set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "" + (block_->id == 0 ? "\nadd_textbox|This machine is empty.|left|\nadd_item_picker|stockitem|`wPut an item in``|Choose an item to put in the machine!|" : "\nadd_label_with_icon|sml|The machine contains a total of " + to_string(block_->c_) + " `2" + items.at(block_->id).name + +"``. |left|" + to_string(block_->id) + "|") + (block_->pr == 0 ? (block_->id != 0 ? "\nadd_spacer|small|\nadd_textbox|Not currently for sale!|left|" + ex_ + "\nadd_button|pullstock|Empty the machine|noflags|0|0|" : "") : "\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + (block_->pr < 0 ? "1" : to_string(block_->pr)) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + (block_->pr < 0 ? to_string(block_->pr * -1) : "1") + " x `2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|\nadd_spacer|small|" + ex_ + "\nadd_button|pullstock|Empty the machine|noflags|0|0|") + (block_->id != 0 ? "" + a_ + "\nadd_smalltext|`5(" + items.at(block_->fg).name + " will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + (block_->pr < 0 ? to_string(block_->pr * -1) : to_string(block_->pr)) + "|5|\nadd_checkbox|chk_peritem|World Locks per Item|" + (block_->pr >= 0 ? "1" : "0") + "\nadd_checkbox|chk_perlock|Items per World Lock|" + (block_->pr < 0 ? "1" : "0") + "" : "") + (block_->wl != 0 ? "\nadd_smalltext|You have earned " + to_string(block_->wl) + " World Locks.|left|\nadd_button|withdraw|Withdraw World Locks|noflags|0|0|" : "") + "\nadd_smalltext|Upgrade to a DigiVend Machine for `44,000 Gems``.|left|\nadd_button|upgradedigital|Upgrade to DigiVend|noflags|0|0|\nadd_spacer|small|\nend_dialog|vending|Close|" + (block_->id != 0 ? "Update" : "") + "|";
}
string get_vending_buyer_side(ENetPeer* peer, World* world_, WorldBlock* block_, int x_, int y_) {
	return "set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "" + (block_->id == 0 or block_->pr == 0 ? "\nadd_textbox|This machine is out of order.|left|\nend_dialog|vending|Close||" : "\nadd_label_with_icon|sml|The machine contains a total of " + to_string(block_->c_) + " `2" + items.at(block_->id).name + "``. |left|" + to_string(block_->id) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + (block_->pr < 0 ? "1" : to_string(block_->pr)) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + (block_->pr < 0 ? to_string(block_->pr * -1) : "1") + " x `2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|\nadd_spacer|small|" + (block_->pr < 0 and (block_->pr * -1 > block_->c_) ? "\nadd_textbox|You'll need to wait for the owner to stock up to at least 1 World Lock's worth before you can buy.|left|\nend_dialog|vending|Close||" : "\nadd_textbox|You have " + to_string(get_wls(peer)) + " World Locks.|left|\nadd_text_input|buycount|How many would you like to buy?|0|3|\nembed_data|expectprice|" + to_string(block_->pr) + "\nembed_data|expectitem|" + to_string(block_->id) + "\nend_dialog|vending|Close|Buy|"));
}
uint16_t get_weather_id(uint32_t block_id) {
	switch (block_id) {
	case 3832: {
		return 29;
	}
	case 5000: {
		return 34;
	}
	case 1490: {
		return 10;
	}
	case 934: {
		return 2;
	}
	case 946: {
		return 3;
	}
	case 932: {
		return 4;
	}
	case 984: {
		return 5;
	}
	case 1210: {
		return 8;
	}
	case 1364: {
		return 11;
	}
	case 1750: {
		return 15;
	}
	case 2046: {
		return 17;
	}
	case 2284: {
		return 18;
	}
	case 2744: {
		return 19;
	}
	case 3252: {
		return 20;
	}
	case 3446: {
		return 21;
	}
	case 3534: {
		return 22;
	}
	case 4242: {
		return 30;
	}
	case 4486: {
		return 31;
	}
	case 4776: {
		return 32;
	}
	case 4892: {
		return 33;
	}
	case 5112: {
		return 35;
	}
	case 5654: {
		return 36;
	}
	case 5716: {
		return 37;
	}
	case 5958: {
		return 38;
	}
	case 6854: {
		return 42;
	}
	case 7644: {
		return 44;
	}
	}
	return 0;
}
bool is_false_state(WorldBlock block_, int t_) {
	if (items.at(block_.fg).collisionType == 0) return false;
	if (items.at(block_.fg).collisionType == 1) {
		return true;
	}
	if (block_.flags & t_) {
		return false;
	}
	return true;
}
vector<vector<int>> lock_tiles(World* w_, int st_x, int st_y, int lock_size) {
	try {
		int layer_ = 0;
		int og_lock_size = lock_size;
		vector<vector<int>> new_tiles{};
		vector<vector<int>> new_lock{};
		if (w_->blocks.at(st_x + (st_y * 100)).locked) {
			return new_lock;
		}
		if (st_x - 1 > 0) {
			new_tiles.push_back({ st_x - 1 + (st_y * 100), 1 });
			if (not_mod(w_->blocks.at(st_x - 1 + (st_y * 100)), st_x - 1, st_y)) new_lock.push_back({ st_x - 1, st_y });
		}
		if (st_y - 1 > 0) {
			new_tiles.push_back({ st_x + ((st_y - 1) * 100), 2 });
			if (not_mod(w_->blocks.at(st_x + ((st_y - 1) * 100)), st_x, st_y - 1)) new_lock.push_back({ st_x, st_y - 1 });
		}
		if (st_x + 1 < 100) {
			new_tiles.push_back({ st_x + 1 + (st_y * 100), 3 });
			if (not_mod(w_->blocks.at(st_x + 1 + (st_y * 100)), st_x + 1, st_y)) new_lock.push_back({ st_x + 1, st_y });
		}
		if (st_y + 1 < 60) {
			new_tiles.push_back({ st_x + ((st_y + 1) * 100), 4 });
			if (not_mod(w_->blocks.at(st_x + ((st_y + 1) * 100)), st_x, st_y + 1)) new_lock.push_back({ st_x, st_y + 1 });
		}
		int ySize = w_->blocks.size() / 100, xSize = w_->blocks.size() / ySize;
		int max_up = 0;
		int max_down = 0;
		int max_right = 0;
		int max_left = 0;
		vector<WorldBlock> shadow_copy = w_->blocks;
		for (int i_ = 0; i_ < new_tiles.size(); i_++) {
			if (new_lock.size() >= og_lock_size) {
				break;
			}
			vector<int> test__ = new_tiles.at(i_);
			int x_ = test__.at(0) % 100, y_ = test__.at(0) / 100;
			int where_ = test__.at(1);
			if (where_ == 1) {
				if (y_ - 1 < 0) {
				}
				else {
					if (not shadow_copy.at(x_ + ((y_ - 1) * 100)).scanned) {
						if (not_mod(shadow_copy.at(x_ + ((y_ - 1) * 100)), x_, y_ - 1)) {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_up != 0 and y_ > max_up + 1 and y_ - 1 > 0) {
								new_tiles.push_back({ x_ + ((y_ - 1) * 100), 1 });
							}
							new_lock.push_back({ x_, y_ - 1 });
							if (new_lock.size() >= og_lock_size) {
								break;
							}
						}
						else {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_up != 0 and y_ > max_up + 1 and y_ - 1 > 0) {
								new_tiles.push_back({ x_ + ((y_ - 1) * 100), 1 });
								if (new_lock.size() >= og_lock_size) {
									break;
								}
							}
							lock_size++;
						}
					}
				}
			}
			if (where_ == 2) {
				if (x_ + 1 > 100) {

				}
				else {
					if (not shadow_copy.at(x_ + 1 + (y_ * 100)).scanned) {
						if (not_mod(shadow_copy.at(x_ + 1 + (y_ * 100)), x_ + 1, y_)) {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_left != 0 and x_ < max_left - 1 and x_ + 1 < 100) {
								new_tiles.push_back({ x_ + 1 + (y_ * 100), 2 });
							}
							new_lock.push_back({ x_ + 1, y_ });
							if (new_lock.size() >= og_lock_size) {
								break;
							}
						}
						else {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_left != 0 and x_ < max_left - 1 and x_ + 1 < 100) {
								new_tiles.push_back({ x_ + 1 + (y_ * 100), 2 });
								if (new_lock.size() >= og_lock_size) {
									break;
								}
							}
							lock_size++;
						}
					}
				}

			}
			if (where_ == 3) {
				if (y_ + 1 > 60) {

				}
				else {
					if (not shadow_copy.at(x_ + ((y_ + 1) * 100)).scanned) {
						if (not_mod(shadow_copy.at(x_ + ((y_ + 1) * 100)), x_, y_ + 1)) {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_down != 0 and y_ < max_down - 1 and y_ + 1 < 60) {
								new_tiles.push_back({ x_ + ((y_ + 1) * 100), 3 });
							}
							new_lock.push_back({ x_, y_ + 1 });
							if (new_lock.size() >= og_lock_size) {
								break;
							}
						}
						else {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_down != 0 and y_ < max_down - 1 and y_ + 1 < 60) {
								new_tiles.push_back({ x_ + ((y_ + 1) * 100), 3 });
								if (new_lock.size() >= og_lock_size) {
									break;
								}
							}
							lock_size++;
						}
					}
				}

			}
			if (where_ == 4) {
				if (x_ - 1 < 0) {
				}
				else {
					if (not shadow_copy.at(x_ - 1 + (y_ * 100)).scanned) {
						if (not_mod(shadow_copy.at(x_ - 1 + (y_ * 100)), x_ - 1, y_)) {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_right != 0 and x_ > max_right + 1 and x_ - 1 > 0) {
								new_tiles.push_back({ x_ - 1 + (y_ * 100), 4 });
							}
							new_lock.push_back({ x_ - 1, y_ });
							if (new_lock.size() >= og_lock_size) {
								break;
							}
						}
						else {
							shadow_copy.at(x_ + (y_ * 100)).scanned = true;
							if (max_right != 0 and x_ > max_right + 1 and x_ - 1 > 0) {
								new_tiles.push_back({ x_ - 1 + (y_ * 100), 4 });
								if (new_lock.size() >= og_lock_size) {
									break;
								}
							}
							lock_size++;
						}
					}
				}

			}
			if (i_ == new_tiles.size() - 1) {
				layer_++;
				if (og_lock_size <= 10 or lock_size - new_lock.size() <= 5) layer_ = 0;
				int t_ = 1;
				if (st_x - t_ < 0) {
					//lock_size++;

				}
				else {
					while (shadow_copy.at(st_x - t_ + (st_y * 100)).scanned) {
						t_++;
						if (st_x - t_ < 0) {
							break;
						}
						else {
							if (not shadow_copy.at(st_x - t_ + (st_y * 100)).scanned) {
								if (not_mod(shadow_copy.at(st_x - t_ + ((st_y + layer_) * 100)), st_x - t_, st_y + layer_)) {
									max_right = st_x - t_;
									new_tiles.push_back({ st_x - t_ + ((st_y + layer_) * 100), 1 });
									new_lock.push_back({ st_x - t_, (st_y + layer_) });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
								}
								else {
									max_right = st_x - t_;
									new_tiles.push_back({ st_x - t_ + ((st_y + layer_) * 100), 1 });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
									lock_size++;
								}
								break;
							}
						}
					}
				}
				t_ = 1;
				if (st_y - t_ < 0) {
					//lock_size++;

				}
				else {
					while (shadow_copy.at(st_x + ((st_y - t_) * 100)).scanned) {
						t_++;
						if (st_y - t_ < 0) {
							break;
						}
						else {
							if (not shadow_copy.at(st_x + ((st_y - t_) * 100)).scanned) {
								if (not_mod(shadow_copy.at(st_x - layer_ + ((st_y - t_) * 100)), st_x - layer_, st_y - t_)) {
									max_up = st_y - t_;
									new_tiles.push_back({ st_x - layer_ + ((st_y - t_) * 100), 2 });
									new_lock.push_back({ st_x - layer_, st_y - t_ });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
								}
								else {
									max_up = st_y - t_;
									new_tiles.push_back({ st_x - layer_ + ((st_y - t_) * 100), 2 });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
									lock_size++;
								}
								break;
							}
						}
					}
				}
				t_ = 1;
				if (st_x + t_ > 100) {

				}
				else {
					while (shadow_copy.at(st_x + t_ + (st_y * 100)).scanned) {
						t_++;
						if (st_x + t_ > 100) {
							break;
						}
						else {
							if (st_y - layer_ < 0) layer_ = 0;
							if (not shadow_copy.at(st_x + t_ + (st_y * 100)).scanned) {
								if (not_mod(shadow_copy.at(st_x + t_ + ((st_y - layer_) * 100)), st_x + t_, st_y - layer_)) {
									max_left = st_x + t_;
									new_tiles.push_back({ st_x + t_ + ((st_y - layer_) * 100), 3 });
									new_lock.push_back({ st_x + t_, st_y - layer_ });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
								}
								else {
									max_left = st_x + t_;
									new_tiles.push_back({ st_x + t_ + ((st_y - layer_) * 100), 3 });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
									lock_size++;
								}
								break;
							}
						}
					}
				}
				t_ = 1;
				if (st_y + t_ > 60) {

				}
				else {
					while (shadow_copy.at(st_x + ((st_y + t_) * 100)).scanned) {
						t_++;
						if (st_y + t_ > 60) {
							break;
						}
						else {
							if (not shadow_copy.at(st_x + ((st_y + t_) * 100)).scanned) {
								if (not_mod(shadow_copy.at(st_x + layer_ + ((st_y + t_) * 100)), st_x + layer_, st_y + t_)) {
									max_down = st_y + t_;
									new_tiles.push_back({ st_x + layer_ + ((st_y + t_) * 100), 4 });
									new_lock.push_back({ st_x + layer_, st_y + t_ });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
								}
								else {
									max_down = st_y + t_;
									new_tiles.push_back({ st_x + layer_ + ((st_y + t_) * 100), 4 });
									if (new_lock.size() >= og_lock_size) {
										break;
									}
									lock_size++;
								}
								break;
							}
						}
					}
				}
			}
		}
		if (new_lock.size() > og_lock_size) {
			int fix_size = (new_lock.size() - og_lock_size);
			for (int i_ = 0; i_ < fix_size; i_++) {
				new_lock.pop_back();
			}
		} vector<int> erase_later{};
		vector<WorldBlock> shadow_copy_2 = w_->blocks;
		for (int i_ = 0; i_ < new_lock.size(); i_++) {
			vector<int> asd_ = new_lock.at(i_);
			shadow_copy_2.at(asd_[0] + (asd_[1] * 100)).locked = true;
			shadow_copy_2.at(asd_[0] + (asd_[1] * 100)).lock_origin = (st_x + (st_y * 100));
		}
		WorldBlock target_to_reach = shadow_copy_2.at(st_x + (st_y * 100)); // og coordinatess
		for (int i_ = 0; i_ < new_lock.size(); i_++) {
			vector<int> asd_ = new_lock.at(i_);
			vector<int> new_tiles{};
			new_tiles.push_back(asd_[0] + (asd_[1] * 100));
			int ySize = w_->blocks.size() / 100, xSize = w_->blocks.size() / ySize;
			bool reachable = false;
			vector<vector<int>> after_process{};
			for (int i2 = 0; i2 < new_tiles.size(); i2++) {
				int x_ = new_tiles.at(i2) % 100, y_ = new_tiles.at(i2) / 100;
				if ((x_ + (y_ * 100)) == st_x + (st_y * 100) or (x_ + 1 + (y_ * 100)) == st_x + (st_y * 100) or (x_ - 1 + (y_ * 100)) == st_x + (st_y * 100) or (x_ + ((y_ + 1) * 100)) == st_x + (st_y * 100) or (x_ + ((y_ - 1) * 100)) == st_x + (st_y * 100)) {
					reachable = true;
				} if (x_ < 99 and shadow_copy_2.at(x_ + 1 + (y_ * 100)).locked and shadow_copy_2.at(x_ + 1 + (y_ * 100)).lock_origin == (st_x + (st_y * 100))) {
					if (not shadow_copy_2.at(x_ + 1 + (y_ * 100)).scanned) {
						shadow_copy_2.at(x_ + 1 + (y_ * 100)).scanned = true;
						after_process.push_back({ x_ + 1, y_ });
						new_tiles.push_back(x_ + 1 + (y_ * 100));
					}
				} if (x_ > 0 and shadow_copy_2.at(x_ - 1 + (y_ * 100)).locked and shadow_copy_2.at(x_ - 1 + (y_ * 100)).lock_origin == (st_x + (st_y * 100))) {
					if (not shadow_copy_2.at(x_ - 1 + (y_ * 100)).scanned) {
						shadow_copy_2.at(x_ - 1 + (y_ * 100)).scanned = true;
						after_process.push_back({ x_ - 1, y_ });
						new_tiles.push_back(x_ - 1 + (y_ * 100));
					}
				} if (y_ < 59 and shadow_copy_2.at(x_ + ((y_ + 1) * 100)).locked and shadow_copy_2.at(x_ + ((y_ + 1) * 100)).lock_origin == (st_x + (st_y * 100))) {
					if (not shadow_copy_2.at(x_ + ((y_ + 1) * 100)).scanned) {
						shadow_copy_2.at(x_ + ((y_ + 1) * 100)).scanned = true;
						after_process.push_back({ x_, y_ + 1 });
						new_tiles.push_back(x_ + ((y_ + 1) * 100));
					}
				} if (y_ > 0 and shadow_copy_2.at(x_ + ((y_ - 1) * 100)).locked and shadow_copy_2.at(x_ + ((y_ - 1) * 100)).lock_origin == (st_x + (st_y * 100))) {
					if (not shadow_copy_2.at(x_ + ((y_ - 1) * 100)).scanned) {
						shadow_copy_2.at(x_ + ((y_ - 1) * 100)).scanned = true;
						after_process.push_back({ x_, y_ - 1 });
						new_tiles.push_back(x_ + ((y_ - 1) * 100));
					}
				}
			}
			for (vector<int> cleanup : after_process) {
				shadow_copy_2.at(cleanup[0] + ((cleanup[1]) * 100)).scanned = false;
			}
			if (not reachable) {
				erase_later.push_back(i_);
			}
		}
		int er_ = 0;
		for (int a_ : erase_later) {
			int aa = a_ - er_;
			new_lock.erase(new_lock.begin() + aa);
			er_++;
		} return new_lock;
	}
	catch (out_of_range) {
		vector<vector<int>> asd{};
		return asd;
	}
}
void call_dialog(ENetPeer* p_, string cch) {
	if (pInfo(p_)->trading_with != -1 and cch.find("trade_") == string::npos) {
		cancel_trade(p_, false, true);
		return;
	}
	vector<string> a_ = explode("|", replace_str(cch, "\n", "|"));
	for (int i_ = 0; i_ < a_.size(); i_++) {
		if (a_.at(i_) == "weatherspcl") {
			if (a_.size() != 13 and a_.size() != 17 and a_.size() != 19) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (not world_->open_to_public and owner_name != user_name and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not check_lock->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						}
						else {
							break;
						}
					}
					if (block_->fg != 5000 and block_->fg != 3832) break;
					bool update_ = false;
					if (block_->fg == 3832 and a_.size() == 19) {
						if (not isdigit(a_[i_ + 8][0])) break;
						uint32_t new_id = atoi(a_[i_ + 8].c_str());
						if (block_->id != new_id) {
							block_->id = new_id;
							update_ = true;
						}
						int new_gravity = atoi(a_[i_ + 10].c_str());
						if (new_gravity > 500) new_gravity = 500;
						if (new_gravity < -500) new_gravity = -500;
						if (block_->gravity != new_gravity) {
							block_->gravity = new_gravity;
							update_ = true;
						}
						if (not isdigit(a_[i_ + 12][0])) break;
						uint8_t new_spin = atoi(a_[i_ + 12].c_str());
						if (block_->spin != new_spin) {
							block_->spin = new_spin;
							update_ = true;
						}
						if (not isdigit(a_[i_ + 14][0])) break;
						uint8_t new_invert = atoi(a_[i_ + 14].c_str());
						if (block_->invert != new_invert) {
							block_->invert = new_invert;
							update_ = true;
						}
					}
					else if (block_->fg == 3832 and a_.size() == 17) {
						int new_gravity = atoi(a_[i_ + 8].c_str());
						if (new_gravity > 500) new_gravity = 500;
						if (new_gravity < -500) new_gravity = -500;
						if (block_->gravity != new_gravity) {
							block_->gravity = new_gravity;
							update_ = true;
						}
						if (not isdigit(a_[i_ + 10][0])) break;
						uint8_t new_spin = atoi(a_[i_ + 10].c_str());
						if (block_->spin != new_spin) {
							block_->spin = new_spin;
							update_ = true;
						}
						if (not isdigit(a_[i_ + 12][0])) break;
						uint8_t new_invert = atoi(a_[i_ + 12].c_str());
						if (block_->invert != new_invert) {
							block_->invert = new_invert;
							update_ = true;
						}
					}
					else {
						if (not isdigit(a_[i_ + 8][0])) break;
						uint32_t new_id = atoi(a_[i_ + 8].c_str());
						if (block_->fg == 5000 and items.at(new_id).blockType != BlockTypes::BACKGROUND) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("That's not a background!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							break;
						} if (block_->id != new_id) {
							block_->id = new_id;
							update_ = true;
						}
					}
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
					if (block_->enabled and update_) {
						gamepacket_t p;
						p.Insert("OnSetCurrentWeather");
						p.Insert(world_->weather);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == name_) {
								p.CreatePacket(currentPeer);
							}
						}
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "itemaddedtosucker" or a_.at(i_) == "itemremovedfromsucker") {
			if (a_.size() != 13) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (owner_name != user_name and not pInfo(p_)->dev and not owner_name.empty()) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (check_lock->owner_name != pInfo(p_)->tankIDName) break;
						}
						else {
							break;
						}
					}
					if (not items.at(block_->fg).item_sucker) break;
					if (not isdigit(a_[i_ + 8][0])) break;
					if (t_ == 6948 and block_->pr >= 1500 and a_.at(i_) != "itemremovedfromsucker" or t_ == 6946 and block_->pr >= 1500 and a_.at(i_) != "itemremovedfromsucker" or t_ == 5638 and block_->pr >= 5000 and a_.at(i_) != "itemremovedfromsucker") break;
					uint32_t add_count = atoi(a_[i_ + 8].c_str());
					if (a_.at(i_) == "itemremovedfromsucker") {
						if (add_count > block_->pr) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You are removing what you dont have.");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You are removing what you dont have.");
								p.CreatePacket(p_);
							}
							break;
						}
						int c_ = 0;
						modify_inventory(p_, block_->id, c_);
						add_count = (add_count + c_ > 200 ? (add_count > 200 ? 200 - c_ : (add_count > c_ ? 200 - add_count : 200 - c_)) : add_count);
						if (add_count > block_->pr or c_ + add_count > 200) break;
						int add_ = add_count;
						if (modify_inventory(p_, block_->id, add_) == 0) {
							block_->pr -= add_count;
						}
					}
					else {
						int c_ = 0;
						modify_inventory(p_, block_->id, c_);
						if (c_ < add_count) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You dont have " + items.at(block_->id).name);
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You dont have " + items.at(block_->id).name);
								p.CreatePacket(p_);
							}
							break;
						}
						int remove_count = add_count * -1;
						if (modify_inventory(p_, block_->id, remove_count) == 0) {
							block_->pr += add_count;
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("Items added.");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("Items added.");
								p.CreatePacket(p_);
							}
						}
					}
					bool found_ = false;
					for (int i_ = 0; i_ < world_->machines.size(); i_++) {
						WorldMachines* machine_ = &world_->machines.at(i_);
						if (machine_->x == x_ and machine_->y == y_) {
							machine_->enabled = block_->enabled;
							machine_->target_item = block_->id;
							found_ = true;
							break;
						}
					} if (not found_) {
						cout << "created new world machine" << endl;
						WorldMachines new_machine;
						new_machine.enabled = block_->enabled;
						new_machine.x = x_, new_machine.y = y_;
						new_machine.id = block_->fg;
						new_machine.target_item = block_->id;
						world_->machines.push_back(new_machine);
					}
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "itemsucker_block") {
			if (a_.size() != 13 and a_.size() != 16 and a_.size() != 14) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (owner_name != user_name and not pInfo(p_)->dev and not owner_name.empty() and a_.at(11) != "getplantationdevice" and a_.size() != 14) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (check_lock->owner_name != pInfo(p_)->tankIDName and a_.at(11) != "getplantationdevice" and a_.size() != 14) break;
						}
						else {
							break;
						}
					}
					if (not items.at(t_).item_sucker) break;
					if (a_.size() == 14 or a_.at(11) == "getplantationdevice") {
						if (block_->id != 0 and block_->fg == 5638) {
							if (items.at(block_->id).collisionType != 1 and items.at(block_->id).blockType != BACKGROUND and items.at(block_->id).blockType != SEED and not items.at(block_->id).farmable or items.at(block_->id).rarity == 999) {
								break;
							}
							if (pInfo(p_)->magnetron_x != 0 and pInfo(p_)->magnetron_y != 0 and pInfo(p_)->magnetron_x != x_ and pInfo(p_)->magnetron_x != y_) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("You received a " + items.at(5640).name + ".");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You received a " + items.at(5640).name + ".");
									p.CreatePacket(p_);
								}
								{
									pInfo(p_)->magnetron_id = block_->id;
									pInfo(p_)->magnetron_x = x_;
									pInfo(p_)->magnetron_y = y_;
									gamepacket_t p;
									p.Insert("OnPlanterActivated");
									p.Insert(block_->id);
									p.Insert(x_);
									p.Insert(y_);
									p.CreatePacket(p_);
								}
							}
							else {
								int c_ = 0;
								modify_inventory(p_, 5640, c_);
								if (c_ == 0) {
									{
										int c_ = 1;
										if (modify_inventory(p_, 5640, c_) == 0) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("You received a " + items.at(5640).name + ".");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You received a " + items.at(5640).name + ".");
												p.CreatePacket(p_);
											}
											{
												pInfo(p_)->magnetron_id = block_->id;
												pInfo(p_)->magnetron_x = x_;
												pInfo(p_)->magnetron_y = y_;
												gamepacket_t p;
												p.Insert("OnPlanterActivated");
												p.Insert(block_->id);
												p.Insert(x_);
												p.Insert(y_);
												p.CreatePacket(p_);
											}
										}
									}
								}
							}
						}
						break;
					}
					if (a_.size() == 13 and a_[i_ + 7] == "selectitem") {
						if (not isdigit(a_[i_ + 8][0])) break;
						uint32_t putting_item = atoi(a_[i_ + 8].c_str());
						if (t_ == 5638) {
							if (items.at(putting_item).untradeable or items.at(putting_item).rarity == 999 and items.at(putting_item).blockType != BlockTypes::CLOTHING and items.at(putting_item).blockType != BlockTypes::CONSUMABLE) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("This item is not compatible.");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("This item is not compatible.");
									p.CreatePacket(p_);
								}
								break;
							}
							block_->id = putting_item;
							block_->enabled = true;
						}
						else if (t_ == 6948) {
							if (items.at(putting_item).blockType == BlockTypes::SEED) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("You cannot store seeds in this machine.");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You cannot store seeds in this machine.");
									p.CreatePacket(p_);
								}
								break;
							}
							if (items.at(putting_item).collisionType != 1 or items.at(putting_item).rarity == 999) {
								if (items.at(putting_item).blockType != BACKGROUND or items.at(putting_item).rarity == 999) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("This item is not compatible.");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(p_);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("This item is not compatible.");
										p.CreatePacket(p_);
									}
									break;
								}
							}
							block_->id = putting_item;
							block_->enabled = true;
						}
						else if (t_ == 6946) {
							if (items.at(putting_item).blockType != BlockTypes::SEED) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("You can only store seeds in this machine.");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You can only store seeds in this machine.");
									p.CreatePacket(p_);
								}
								break;
							}
							block_->id = putting_item;
							block_->enabled = true;
						}
					}
					else {
						for (int b_ = 0; b_ < a_.size(); b_++) {
							if (a_.at(b_) == "retrieveitem") {
								if (block_->id != 0) {
									int c_ = 0;
									modify_inventory(p_, block_->id, c_);
									if (c_ < 200) {
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_label_with_icon|small|`2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|\nadd_textbox|`wHow many `2" + items.at(block_->id).name + "`` would you like to remove?``|left||\nadd_text_input|itemtoremove|Amount:|" + (block_->pr + c_ > 200 ? (block_->pr > 200 ? to_string(200 - c_) : (block_->pr > c_ ? to_string(200 - block_->pr) : to_string(200 - c_))) : to_string(block_->pr)) + "|20|\nend_dialog|itemremovedfromsucker|Close|Retrieve|\nadd_spacer|small|");
										p.CreatePacket(p_);
									}
								}
								break;
							}
							else if (a_.at(b_) == "additem") {
								if (block_->id != 0) {
									int c_ = 0;
									modify_inventory(p_, block_->id, c_);
									if (c_ != 0) {
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_label_with_icon|small|`2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|\nadd_smalltext|You have " + to_string(c_) + " `2" + items.at(block_->id).name + "`` in your backpack.|left|\nadd_textbox|`wHow many `2" + items.at(block_->id).name + "`` would you like to add?``|left|\nadd_text_input|itemtoadd|Amount:|" + (block_->pr + c_ > (block_->fg == 5638 ? 5000 : 1500) ? to_string((block_->fg == 5638 ? 5000 : 1500) - block_->pr) : to_string(c_)) + "|20|\nend_dialog|itemaddedtosucker|Close|Add|\nadd_spacer|small|");
										p.CreatePacket(p_);
									}
								}
								break;
							}
							else if (a_.at(b_) == "clearitem") {
								if (block_->id != 0 and block_->pr == 0) {
									if (block_->fg == 5638 and pInfo(p_)->magnetron_id != 0 and pInfo(p_)->magnetron_x == x_ and pInfo(p_)->magnetron_y == y_) {
										int c_ = 0;
										modify_inventory(p_, 5640, c_);
										if (c_ != 0) {
											c_ *= -1;
											modify_inventory(p_, 5640, c_);
											pInfo(p_)->magnetron_id = 0;
											pInfo(p_)->magnetron_x = 0;
											pInfo(p_)->magnetron_y = 0;
										}
									}
									block_->id = 0, block_->enabled = true;
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert(get_sucker(p_, world_, block_, x_, y_));
									p.CreatePacket(p_);
									break;
								}
								break;
							}
							else if (a_.at(b_).substr(0, 4) == "chk_") {
								vector<string> target_ = explode("_", a_.at(b_));
								if (target_.at(1) == "enablesucking") {
									block_->enabled = (a_.at(b_ + 1) == "1" and not block_->enabled ? true : (a_.at(b_ + 1) == "0" and block_->enabled ? false : false));
								}
							}
						}
					}
					bool found_ = false;
					for (int i_ = 0; i_ < world_->machines.size(); i_++) {
						WorldMachines* machine_ = &world_->machines.at(i_);
						if (machine_->x == x_ and machine_->y == y_) {
							machine_->enabled = block_->enabled;
							machine_->target_item = block_->id;
							found_ = true;
							break;
						}
					} if (not found_) {
						cout << "created new world machine" << endl;
						WorldMachines new_machine;
						new_machine.enabled = block_->enabled;
						new_machine.x = x_, new_machine.y = y_;
						new_machine.id = block_->fg;
						new_machine.target_item = block_->id;
						world_->machines.push_back(new_machine);
					}
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "autoactionblock") {
			if (a_.size() != 15 and a_.size() != 16) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (owner_name != user_name and not pInfo(p_)->dev) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (check_lock->owner_name != pInfo(p_)->tankIDName) break;
						}
						else {
							break;
						}
					}
					switch (t_) {
					case 6950: case 6952:
					{
						for (int b_ = 0; b_ < a_.size(); b_++) {
							if (a_.at(b_) == "refillfuel") {
								if (not isdigit(a_.at(b_ + 1)[0])) return;
								uint32_t target_amount = atoi(a_.at(b_ + 1).c_str());
								if (target_amount > pInfo(p_)->gems) target_amount = pInfo(p_)->gems;
								if (target_amount == 0) continue;
								if (block_->pr + target_amount > 8000) {
									target_amount = 8000 - block_->pr;
								}
								pInfo(p_)->gems -= target_amount;
								{
									gamepacket_t p;
									p.Insert("OnSetBux");
									p.Insert(pInfo(p_)->gems);
									p.Insert(0);
									p.CreatePacket(p_);
								}
								block_->pr += target_amount;
							}
							else if (a_.at(b_) == "selecttarget") {
								if (not isdigit(a_.at(b_ + 1)[0])) return;
								uint32_t target_item = atoi(a_.at(b_ + 1).c_str());
								if (t_ == 6952) {
									if (items.at(target_item).blockType == BlockTypes::SEED) target_item--;
									if (items.at(target_item).rarity == 999) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Sorry that item is `4NOT`` allowed in this machine!");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Sorry that item is `4NOT`` allowed in this machine!");
											p.CreatePacket(p_);
										}
										return;
									} if (items.at(target_item).blockType == BlockTypes::CLOTHING or items.at(target_item).properties & Property_Mod) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("`4NOPE!``");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`4NOPE!``");
											p.CreatePacket(p_);
										}
										return;
									}
								}
								else {
									if (items.at(target_item).blockType != BlockTypes::SEED) target_item++;
									if (items.at(target_item).rarity == 999) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Sorry that item is `4NOT`` allowed in this machine!");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Sorry that item is `4NOT`` allowed in this machine!");
											p.CreatePacket(p_);
										}
										return;
									}
									if (items.at(target_item).collisionType != 1 and items.at(target_item).blockType != BlockTypes::SEED) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("`4NOPE!``");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`4NOPE!``");
											p.CreatePacket(p_);
										}
										return;
									}
								}
								block_->id = target_item;
							}
						}
						{
							bool found_ = false;
							for (int i_ = 0; i_ < world_->machines.size(); i_++) {
								WorldMachines* machine_ = &world_->machines.at(i_);
								if (machine_->x == x_ and machine_->y == y_) {
									machine_->enabled = block_->enabled;
									machine_->target_item = block_->id;
									found_ = true;
									break;
								}
							} if (not found_) {
								cout << "created new world machine" << endl;
								WorldMachines new_machine;
								new_machine.enabled = block_->enabled;
								new_machine.x = x_, new_machine.y = y_;
								new_machine.id = block_->fg;
								new_machine.target_item = block_->id;
								world_->machines.push_back(new_machine);
							}
						}
						PlayerMoving data_{};
						data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
						BYTE* raw = packPlayerMoving(&data_, 112);
						BYTE* blc = raw + 56;
						form_visual(blc, *block_, *world_, p_, false);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[] raw, blc;
						if (block_->locked) {
							upd_lock(*block_, *world_, p_);
						}
						break;
					}
					default:
						break;
					}

				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "blaster") {
			if (a_.size() != 17) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0]) or not isdigit(a_[i_ + 8][0]) or not isdigit(a_[i_ + 10][0]) or not isdigit(a_[i_ + 12][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str()), often_ = atoi(a_[i_ + 8].c_str()), speed_ = atoi(a_[i_ + 10].c_str());
			if (speed_ > 250) speed_ = 250;
			if (speed_ < 10) speed_ = 10;
			if (often_ > 20) often_ = 20;
			if (often_ < 2) often_ = 2;
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (not world_->open_to_public and owner_name != user_name and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not check_lock->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						}
						else {
							break;
						}
					}
					if (not items.at(t_).trickster) break;
					block_->flags = (block_->flags & 0x00400000 and a_[i_ + 12] == "1" ? block_->flags ^ 0x00400000 : (a_[i_ + 12] == "0" ? block_->flags | 0x00400000 : block_->flags));
					bool found_ = false;
					block_->rate_of_fire = often_;
					block_->projectile_speed = speed_;
					for (int i_ = 0; i_ < world_->npc.size(); i_++) {
						WorldNPC* npc_ = &world_->npc.at(i_);
						if (npc_->x == x_ and npc_->y == y_) {
							npc_->enabled = (block_->flags & 0x00400000 ? true : false);
							npc_->rate_of_fire = often_;
							npc_->projectile_speed = speed_;
							npc_->kryptis = (block_->flags & 0x00200000 ? 180 : 0);
							found_ = true;
							break;
						}
					} if (not found_) {
						WorldNPC new_npc;
						new_npc.enabled = (block_->flags & 0x00400000 ? true : false);
						new_npc.x = x_, new_npc.y = y_;
						new_npc.id = block_->fg;
						new_npc.projectile_speed = speed_;
						new_npc.rate_of_fire = often_;
						new_npc.kryptis = (block_->flags & 0x00200000 ? 180 : 0);
						world_->npc.push_back(new_npc);
					}
					block_->enabled = (block_->flags & 0x00400000 ? true : false);
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(p_)->netID);
					p.Insert("Settings updated!");
					p.Insert(0), p.Insert(0);
					p.CreatePacket(p_);
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "boombox_edit") {
			if (a_.size() != 15) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (not world_->open_to_public and owner_name != user_name and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not check_lock->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						}
						else {
							break;
						}
					}
					if (not items.at(t_).can_be_changed_two_types) break;
					block_->flags = (block_->flags & 0x00800000 and a_[i_ + 8] == "0" ? block_->flags ^ 0x00800000 : (a_[i_ + 8] == "1" ? block_->flags | 0x00800000 : block_->flags));
					block_->flags = (block_->flags & 0x02000000 and a_[i_ + 10] == "0" ? block_->flags ^ 0x02000000 : (a_[i_ + 10] == "1" ? block_->flags | 0x02000000 : block_->flags));
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "switcheroo_edit") {
			if (a_.size() != 13) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (not world_->open_to_public and owner_name != user_name and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not check_lock->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						}
						else {
							break;
						}
					}
					if (not items.at(t_).entrance and not items.at(t_).can_be_changed_to_public) break;
					block_->flags = (block_->flags & 0x00800000 and a_[i_ + 8] == "0" ? block_->flags ^ 0x00800000 : (a_[i_ + 8] == "1" ? block_->flags | 0x00800000 : block_->flags));
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "trade_item") {
			if (a_.size() != 10) break;
			if (not isdigit(a_[5][0]) or not isdigit(a_[8][0])) break;
			int item_id = atoi(a_[5].c_str()), item_count = atoi(a_[8].c_str()), c_ = 0;
			modify_inventory(p_, item_id, c_);
			if (c_ < item_count or c_ == 0) break;
			mod_trade(p_, atoi(a_[5].c_str()), atoi(a_[8].c_str()));
			break;
		}
		else if (a_.at(i_) == "door_edit") {
			if (a_.size() != 19 and a_.size() != 17) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					if (items.at(t_).blockType != BlockTypes::DOOR and items.at(t_).blockType != BlockTypes::PORTAL) break;
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (not world_->open_to_public and owner_name != user_name and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not check_lock->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						}
						else {
							break;
						}
					}
					string door_name = a_[i_ + 8];
					string door_target = a_[i_ + 10];
					string door_id = a_[i_ + 12];
					if (a_.size() == 19) {
						string checkbox_locked = a_[i_ + 14];
						block_->open = (checkbox_locked == "0" ? false : true);
					}
					if (door_name.size() > 100) break;
					if (door_target.size() > 24) break;
					if (door_id.size() > 11) break;
					transform(door_target.begin(), door_target.end(), door_target.begin(), ::toupper);
					transform(door_id.begin(), door_id.end(), door_id.begin(), ::toupper);
					block_->door_destination = door_target, block_->door_id = door_id;
					block_->txt = door_name;
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112 + door_name.size());
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112 + door_name.size(), ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "vending") {
			if (a_.size() != 14 and a_.size() != 13 and a_.size() != 20 and a_.size() != 17 and a_.size() != 19 and a_.size() != 23) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			if (a_.size() == 13 and not isdigit(a_[i_ + 8][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			if (abs(x_ * 32 - pInfo(p_)->x) > 15 || abs(y_ * 32 - pInfo(p_)->y) > 15) {
				gamepacket_t p;
				p.Insert("OnTalkBubble");
				p.Insert(pInfo(p_)->netID);
				p.Insert("Get closer!");
				p.Insert(0), p.Insert(0);
				p.CreatePacket(p_);
				break;
			}
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					if (items.at(t_).blockType != BlockTypes::VENDING) break;
					if (a_.size() == 19 or a_.size() == 23) {
						if (not isdigit(a_[i_ + 11][0])) break;
						int expectprice = atoi(a_[i_ + 8].c_str()), expectitem = atoi(a_[i_ + 11].c_str()), buycount = atoi(a_[i_ + 14].c_str());
						if (a_.size() == 23) {
							buycount = atoi(a_[i_ + 11].c_str()), expectprice = atoi(a_[i_ + 14].c_str()), expectitem = atoi(a_[i_ + 17].c_str());
						}
						if (expectprice != block_->pr) break;
						if (expectitem != block_->id) break;
						if (buycount < 0) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("NEGATIVE, DOES NOT COMPUTE");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(p_);
							break;
						}
						if (buycount == 0) break;
						int normal_price = (block_->pr > 0 ? block_->pr : (block_->pr * -1));
						int actual_buy_count = (block_->pr > 0 ? buycount : (normal_price < buycount ? buycount / normal_price : normal_price / buycount) * (block_->pr * -1));
						if (actual_buy_count == 0 or actual_buy_count > block_->c_) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("There aren't enough available to fulfill your order!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("There aren't enough available to fulfill your order!");
								p.CreatePacket(p_);
							}
							break;
						}
						if (block_->pr < 0) {
							if (buycount < (block_->pr * -1)) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("You have to buy at least 1 World Lock's worth.");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You have to buy at least 1 World Lock's worth.");
									p.CreatePacket(p_);
								}
								break;
							}
						}
						int my_wls = get_wls(p_);
						int cost_ = (block_->pr > 0 ? block_->pr * buycount : (normal_price < buycount ? buycount / normal_price : normal_price / buycount));
						if (cost_ > my_wls) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You can't afford that many!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You can't afford that many!");
								p.CreatePacket(p_);
							}
							break;
						}
						int has_alr = 0;
						modify_inventory(p_, block_->id, has_alr);
						if (has_alr + actual_buy_count > 200) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You don't have room in your backpack!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You don't have room in your backpack!");
								p.CreatePacket(p_);
							}
							break;
						}
						int free_slots = get_free_slots(pInfo(p_));
						if (free_slots == 0) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You don't have room in your backpack!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You don't have room in your backpack!");
								p.CreatePacket(p_);
							}
							break;
						}
						if (a_.size() == 19) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wPurchase Confirmation``|left|1366|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_spacer|small|\nadd_textbox|`4You'll give:``|left|\nadd_spacer|small|\nadd_label_with_icon|small|(`w" + to_string(cost_) + "``) `8World Locks``|left|242|\nadd_spacer|small|\nadd_textbox|`2You'll get:``|left|\nadd_spacer|small|\nadd_label_with_icon|small|(`w" + to_string(actual_buy_count) + "``) `2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|\nadd_spacer|small|\nadd_spacer|small|\nadd_textbox|Are you sure you want to make this purchase?|left|\nembed_data|verify|1\nembed_data|buycount|" + to_string(buycount) + "\nembed_data|expectprice|" + to_string(expectprice) + "\nembed_data|expectitem|" + to_string(expectitem) + "\nend_dialog|vending|Cancel|OK|");
							p.CreatePacket(p_);
							break;
						}
						int diamond_lock = 0, world_lock = 0, grazinti_wl = 0;
						int is_viso_worldlock = cost_;
						while (is_viso_worldlock >= 100) {
							is_viso_worldlock -= 100;
							diamond_lock++;
						}
						world_lock = is_viso_worldlock;
						int c_ = 0;
						modify_inventory(p_, 242, c_);
						int turi_world_lock = c_, t_w = c_ * -1;
						c_ = 0;
						modify_inventory(p_, 1796, c_);
						int turi_diamond_lock = c_, t_d = c_ * -1;
						while (diamond_lock > turi_diamond_lock && turi_world_lock >= 100) {
							turi_diamond_lock++, turi_world_lock -= 100;
						} if (diamond_lock > turi_diamond_lock) break;
						while (world_lock > turi_world_lock && turi_diamond_lock >= 1) {
							turi_diamond_lock--, turi_world_lock += 100;
						} if (world_lock > turi_world_lock) break;
						turi_world_lock -= world_lock, turi_diamond_lock -= diamond_lock;
						int a_ = actual_buy_count;
						if (modify_inventory(p_, block_->id, a_) == 0) {
							modify_inventory(p_, 242, t_w), modify_inventory(p_, 1796, t_d);
							modify_inventory(p_, 242, turi_world_lock), modify_inventory(p_, 1796, turi_diamond_lock);
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("`7[```9" + pInfo(p_)->tankIDName + " bought " + to_string(actual_buy_count) + " " + items.at(block_->id).name + " for " + to_string(cost_) + " World Locks.```7]``");
							gamepacket_t p2(0, pInfo(p_)->netID);
							p2.Insert("OnPlayPositioned");
							p2.Insert("audio/cash_register.wav");
							PlayerMoving data_{};
							data_.x = x_ * 32 + 16, data_.y = y_ * 32 + 16;
							data_.packetType = 19, data_.plantingTree = 100;
							data_.punchX = block_->id, data_.punchY = pInfo(p_)->netID;
							int32_t to_netid = pInfo(p_)->netID;
							BYTE* raw = packPlayerMoving(&data_);
							raw[3] = 5;
							memcpy(raw + 8, &to_netid, 4);
							block_->c_ -= actual_buy_count, block_->wl += cost_;
							if (block_->c_ <= 0) {
								block_->id = 0, block_->pr = 0;
							}
							PlayerMoving data_vending{};
							data_vending.packetType = 5, data_vending.punchX = x_, data_vending.punchY = y_, data_vending.characterState = 0x8;
							BYTE* v_ = packPlayerMoving(&data_vending, 112);
							BYTE* blc = v_ + 56;
							form_visual(blc, *block_, *world_, p_, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									send_raw(currentPeer, 4, v_, 112, ENET_PACKET_FLAG_RELIABLE);
									p.CreatePacket(currentPeer);
									p2.CreatePacket(currentPeer);
									send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[]raw, v_, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, p_);
							}
							break;
						}
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("You don't have room in your backpack!");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(p_);
						{
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("You don't have room in your backpack!");
							p.CreatePacket(p_);
						}
						break;
					}
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (owner_name != user_name and not pInfo(p_)->dev) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (check_lock->owner_name != pInfo(p_)->tankIDName) break;
						}
						else {
							break;
						}
					}
					bool update_ = false;
					if (cch.find("chk_peritem|1") != string::npos and cch.find("chk_perlock|1") != string::npos) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("You can't have it both ways.");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(p_);
						{
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("You can't have it both ways.");
							p.CreatePacket(p_);
						}
						break;
					} if (a_.size() == 20 or a_.size() == 17 or a_.size() == 14) {
						for (int b_ = 0; b_ < a_.size(); b_++) {
							if (a_.at(b_).substr(0, 4) == "chk_") {
								vector<string> target_ = explode("_", a_.at(b_));
								if (target_.at(1) == "peritem") {
									if (block_->pr < 0 and a_.at(b_ + 1) == "1") {
										block_->pr *= -1, update_ = true;
									}
								}
								else if (target_.at(1) == "perlock") {
									if (block_->pr > 0 and a_.at(b_ + 1) == "1") {
										if (block_->pr > block_->c_) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("You don't have enough in there for anyone to buy at that price!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have enough in there for anyone to buy at that price!");
												p.CreatePacket(p_);
											}
											update_ = false;
											break;
										}
										block_->pr = block_->pr * -1;
										update_ = true;
									}
								}
							}
							else if (a_.at(b_) == "setprice") {
								int price_ = atoi(a_[b_ + 1].c_str());
								if (price_ == 0 or not isdigit(a_[b_ + 1][0]) and price_ >= 0) {
									block_->pr = 0;
									update_ = true;
								}
								else if (price_ < 0 or price_ > 20000) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("Well, that's a silly price.");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(p_);
									break;
								}
								else {
									if (block_->pr < 0) {
										if (price_ > block_->c_) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("You don't have enough in there for anyone to buy at that price!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have enough in there for anyone to buy at that price!");
												p.CreatePacket(p_);
											}
											update_ = false;
											break;
										} if (price_ > 200) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("That price is so low, nobody can carry a World Lock worth of items!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("That price is so low, nobody can carry a World Lock worth of items!");
												p.CreatePacket(p_);
											}
											break;
										}
									}
									block_->pr = (block_->pr < 0 ? price_ * -1 : price_);
									update_ = true;
								}
							}
							else if (a_.at(b_) == "addstock") {
								if (block_->id != 0) {
									int c_ = 0;
									modify_inventory(p_, block_->id, c_);
									int has_ = c_;
									c_ *= -1;
									if (modify_inventory(p_, block_->id, c_) == 0) {
										block_->c_ += has_;
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Added " + to_string(has_) + " items to the machine.");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Added " + to_string(has_) + " items to the machine.");
											p.CreatePacket(p_);
										}
									}
								}
								update_ = false;
								break;
							}
							else if (a_.at(b_) == "withdraw") {
								if (block_->wl != 0) {
									int a_ = block_->wl;
									if (modify_inventory(p_, 242, a_) != 0) {
										if (a_ < 100) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("You don't have room in your backpack!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have room in your backpack!");
												p.CreatePacket(p_);
											}
											break;
										}
										int diamond_locks = a_ / 100;
										int world_locks = a_ - (diamond_locks * 100);
										int turi_dl = 0;
										modify_inventory(p_, 1796, turi_dl);
										int turi_wl = 0;
										modify_inventory(p_, 242, turi_wl);
										if (turi_wl + world_locks > 200 or turi_dl + diamond_locks > 200) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert("You don't have room in your backpack!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(p_);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have room in your backpack!");
												p.CreatePacket(p_);
											}
											break;
										}
										int as2 = world_locks, as4 = diamond_locks;
										modify_inventory(p_, 242, world_locks);
										modify_inventory(p_, 1796, diamond_locks);
										block_->wl = 0;
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										string collected_ = "";
										collected_ += (as4 != 0 ? "" + to_string(as4) + " Diamond Locks" : "");
										string aa_ = (not collected_.empty() ? " and " : " ");
										collected_ += (as2 != 0 ? aa_ + to_string(as2) + " World Locks" : "");
										collected_ += ".";
										p.Insert("You collected " + collected_);
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You collected " + collected_);
											p.CreatePacket(p_);
										}
										break;
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("You collected " + to_string(block_->wl) + " World Locks.");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(p_);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You collected " + to_string(block_->wl) + " World Locks.");
											p.CreatePacket(p_);
										}
										block_->wl = 0;
									}
								}
								update_ = false;
								break;
							}
							else if (a_.at(b_) == "pullstock") {
								int c_ = block_->c_;
								if (modify_inventory(p_, block_->id, c_) == 0) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("You picked up " + to_string(block_->c_) + " " + items.at(block_->id).name + ".");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(p_);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You picked up " + to_string(block_->c_) + " " + items.at(block_->id).name + ".");
										p.CreatePacket(p_);
									}
									block_->c_ = 0, block_->id = 0, block_->pr = 0;
								}
								else if (block_->c_ > 200) {
									int has_ = 0;
									modify_inventory(p_, block_->id, has_);
									int give_ = 200 - has_;
									block_->c_ -= give_;
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("You picked up " + to_string(give_) + " " + items.at(block_->id).name + ", leaving " + to_string(block_->c_) + " in the machine.");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(p_);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You picked up " + to_string(give_) + " " + items.at(block_->id).name + ", leaving " + to_string(block_->c_) + " in the machine.");
										p.CreatePacket(p_);
									}
									modify_inventory(p_, block_->id, give_);
								}
								update_ = false;
								break;
							}
						}
					}
					else {
						if (block_->id != 0) break;
						int item_id = atoi(a_[i_ + 8].c_str());
						int c_ = 0, am_ = 0;
						modify_inventory(p_, item_id, c_);
						if (c_ == 0) break;
						if (items.at(item_id).untradeable or items.at(item_id).blockType == BlockTypes::LOCK or item_id == 1424) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert((items.at(item_id).blockType == BlockTypes::LOCK or item_id == 1424 ? "No no no." : "Can't put that in a " + items.at(block_->fg).name + "."));
							p.Insert(0), p.Insert(1);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert((items.at(item_id).blockType == BlockTypes::LOCK or item_id == 1424 ? "No no no." : "Can't put that in a " + items.at(block_->fg).name + "."));
								p.CreatePacket(p_);
							}
							break;
						}
						am_ = c_;
						c_ *= -1;
						if (modify_inventory(p_, item_id, c_) == 0) {
							block_->id = item_id;
							block_->c_ = am_;
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("`7[``" + pInfo(p_)->tankIDName + " put `2" + items.at(item_id).name + "`` in the " + items.at(block_->fg).name + ".`7]``");
							p.Insert(0);
							gamepacket_t p2;
							p2.Insert("OnConsoleMessage");
							p2.Insert("`7[``" + pInfo(p_)->tankIDName + " put `2" + items.at(item_id).name + "`` in the " + items.at(block_->fg).name + ".`7]``");
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									p.CreatePacket(currentPeer);
									p2.CreatePacket(currentPeer);
								}
							}
							{
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert(get_vending(p_, world_, block_, x_, y_));
								p.CreatePacket(p_);
							}
						}
					}
					if (update_) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert((block_->pr == 0 ? "`7[``" + pInfo(p_)->tankIDName + " disabled the Vending Machine.```7]``" : "`7[``" + pInfo(p_)->tankIDName + " changed the price of `2" + items.at(block_->id).name + "`` to " + (block_->pr < 0 ? "`6" + to_string(block_->pr * -1) + " per World Lock.```7]``" : "`5" + to_string(block_->pr) + " World Locks each.```7]``")));
						p.Insert(0);
						gamepacket_t p2;
						p2.Insert("OnConsoleMessage");
						p2.Insert((block_->pr == 0 ? "`7[``" + pInfo(p_)->tankIDName + " disabled the Vending Machine.```7]``" : "`7[``" + pInfo(p_)->tankIDName + " changed the price of `2" + items.at(block_->id).name + "`` to " + (block_->pr < 0 ? "`6" + to_string(block_->pr * -1) + " per World Lock.```7]``" : "`5" + to_string(block_->pr) + " World Locks each.```7]``")));
						PlayerMoving data_{};
						data_.packetType = 17;
						data_.netID = 44;
						data_.YSpeed = 44;
						data_.x = x_ * 32 + 16;
						data_.y = y_ * 32 + 16;
						BYTE* raw = packPlayerMoving(&data_);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								p.CreatePacket(currentPeer);
								p2.CreatePacket(currentPeer);
								packet_(currentPeer, "action|play_sfx\nfile|audio/terraform.wav\ndelayMS|0");
								send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[] raw;
					}
					PlayerMoving data_{};
					data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
					BYTE* raw = packPlayerMoving(&data_, 112);
					BYTE* blc = raw + 56;
					form_visual(blc, *block_, *world_, p_, false);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[] raw, blc;
					if (block_->locked) {
						upd_lock(*block_, *world_, p_);
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "displayblock") {
			if (a_.size() != 11) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					if (items.at(t_).blockType != BlockTypes::DISPLAY) break;
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (owner_name != user_name and not owner_name.empty() and not pInfo(p_)->dev) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (check_lock->owner_name != pInfo(p_)->tankIDName) break;
						}
						else {
							break;
						}
					}
					if (a_.size() == 11) {
						int c_ = 1;
						if (modify_inventory(p_, block_->id, c_) == 0) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You removed `5" + items.at(block_->id).name + "`` from the " + items.at(block_->fg).name + ".");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(p_);
							block_->id = 0;
							{
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, p_, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw, blc;
								if (block_->locked) {
									upd_lock(*block_, *world_, p_);
								}
							}
						}
						else {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("You don't have room to pick that up!");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(p_);
						}
					}
				}
				catch (out_of_range) {
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "trade_confirm") {
			if (a_.size() != 8) break;
			if (a_.at(5) == "back") {
				cancel_trade(p_, true);
			}
			else if (a_.at(5) == "accept") {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(p_)->world) {
						if (pInfo(currentPeer)->netID == pInfo(p_)->trading_with and pInfo(p_)->netID == pInfo(currentPeer)->trading_with) {
							pInfo(p_)->accept_the_offer = true;
							if (pInfo(currentPeer)->accept_the_offer and pInfo(p_)->accept_the_offer) {
								// jo!
								string name_ = pInfo(p_)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds.at(p - worlds.begin());
									if (not trade_space_check(p_, currentPeer)) {
										cancel_trade(p_);
										return;
									}
									else if (not trade_space_check(currentPeer, p_)) {
										cancel_trade(p_);
										return;
									}
									bool c_ = false;
									for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
										if (c_) break;
										map<string, int>::iterator it;
										for (auto it = pInfo(p_)->trade_items.at(i_).begin(); it != pInfo(p_)->trade_items.at(i_).end(); it++) {
											if (it->first == 1424) {
												for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
													if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
														uint16_t id_ = world_->blocks.at(i_).fg;
														if (id_ == 202 or id_ == 204 or id_ == 206 or id_ == 4994) {
															cancel_trade(p_);
															return;
														}
													}
												}
												c_ = true;
												break;
											}
										}
									}
									c_ = false;
									for (int i_ = 0; i_ < pInfo(currentPeer)->trade_items.size(); i_++) {
										if (c_) break;
										map<string, int>::iterator it;
										for (auto it = pInfo(currentPeer)->trade_items.at(i_).begin(); it != pInfo(currentPeer)->trade_items.at(i_).end(); it++) {
											if (it->first == 1424) {
												for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
													if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
														uint16_t id_ = world_->blocks.at(i_).fg;
														if (id_ == 202 or id_ == 204 or id_ == 206 or id_ == 4994) {
															cancel_trade(currentPeer);
															return;
														}
													}
												}
												c_ = true;
												break;
											}
										}
									}
									vector<string> traded_p;
									int time_out = 0;
									for (int i_ = 0; i_ < pInfo(p_)->trade_items.size(); i_++) {
										map<string, int>::iterator it;
										for (auto it = pInfo(p_)->trade_items.at(i_).begin(); it != pInfo(p_)->trade_items.at(i_).end(); it++) {
											traded_p.push_back(to_string(it->second) + " " + items.at(it->first).name);
											int c_ = it->second * -1;
											modify_inventory(p_, it->first, c_, true);
											if (it->first == 1424) {
												transfer_world(world_, p_, currentPeer);
											}
											else {
												int c2_ = it->second;
												modify_inventory(currentPeer, it->first, c2_, true);
											}
											PlayerMoving data_{};
											time_out += 450;
											data_.packetType = 19, data_.plantingTree = (i_ + 1) * 450, data_.netID = pInfo(currentPeer)->netID;
											data_.punchX = it->first, data_.punchY = it->first;
											int32_t to_netid = pInfo(p_)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 3;
											memcpy(raw + 8, &to_netid, 4);
											for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
												if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
												if (pInfo(currentPeer2)->world == world_->name) {
													send_raw(currentPeer2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[]raw;
											{
												gamepacket_t p((i_ + 1) * 450, pInfo(p_)->netID);
												p.Insert("OnPlayPositioned");
												p.Insert("audio/change_clothes.wav");
												p.CreatePacket(p_);
											}
											{
												gamepacket_t p((i_ + 1) * 450, pInfo(currentPeer)->netID);
												p.Insert("OnPlayPositioned");
												p.Insert("audio/change_clothes.wav");
												p.CreatePacket(currentPeer);
											}
										}
									}
									string traded_ = "";
									if (traded_p.size() != 0) {
										for (int i_ = 0; i_ < traded_p.size(); i_++) {
											if (traded_p.size() == i_ + 1)
												traded_ += traded_p.at(i_);
											else if (traded_p.size() - 2 == i_)
												traded_ += traded_p.at(i_) + " and ";
											else
												traded_ += traded_p.at(i_) + ", ";
										}
									}
									else {
										traded_ = "nothing";
									}
									traded_p.clear();
									for (int i_ = 0; i_ < pInfo(currentPeer)->trade_items.size(); i_++) {
										map<string, int>::iterator it;
										for (auto it = pInfo(currentPeer)->trade_items.at(i_).begin(); it != pInfo(currentPeer)->trade_items.at(i_).end(); it++) {
											traded_p.push_back(to_string(it->second) + " " + items.at(it->first).name);
											int c_ = it->second * -1;
											modify_inventory(currentPeer, it->first, c_, true);
											if (it->first == 1424) {
												transfer_world(world_, currentPeer, p_);
											}
											else {
												int c2_ = it->second;
												modify_inventory(p_, it->first, c2_, true);
											}
											PlayerMoving data_{};
											data_.packetType = 19, data_.plantingTree = (i_ + 1) * 450 + time_out, data_.netID = pInfo(p_)->netID;
											data_.punchX = it->first, data_.punchY = it->first;
											int32_t to_netid = pInfo(currentPeer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 3;
											memcpy(raw + 8, &to_netid, 4);
											for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
												if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
												if (pInfo(currentPeer2)->world == world_->name) {
													send_raw(currentPeer2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[]raw;
											{
												gamepacket_t p((i_ + 1) * 450 + time_out, pInfo(p_)->netID);
												p.Insert("OnPlayPositioned");
												p.Insert("audio/change_clothes.wav");
												p.CreatePacket(p_);
											}
											{
												gamepacket_t p((i_ + 1) * 450 + time_out, pInfo(currentPeer)->netID);
												p.Insert("OnPlayPositioned");
												p.Insert("audio/change_clothes.wav");
												p.CreatePacket(currentPeer);
											}
										}
									}
									string traded2_ = "";
									if (traded_p.size() != 0) {
										for (int i_ = 0; i_ < traded_p.size(); i_++) {
											if (traded_p.size() == i_ + 1)
												traded2_ += traded_p.at(i_);
											else if (traded_p.size() - 2 == i_)
												traded2_ += traded_p.at(i_) + " and ";
											else
												traded2_ += traded_p.at(i_) + ", ";
										}
									}
									else {
										traded2_ = "nothing";
									}
									{
										gamepacket_t p2;
										p2.Insert("OnConsoleMessage");
										p2.Insert("`1" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` traded " + traded2_ + " to " + pInfo(p_)->tankIDName + ".``");
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`1" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` traded " + traded_ + " to " + pInfo(currentPeer)->tankIDName + ".``");
										for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
											if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
											if (pInfo(currentPeer2)->world == world_->name) {
												p.CreatePacket(currentPeer2);
												p2.CreatePacket(currentPeer2);
											}
										}
									}
									{
										gamepacket_t p(1250, pInfo(currentPeer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/keypad_hit.wav");
										p.CreatePacket(currentPeer), p.CreatePacket(p_);
									}
									pInfo(currentPeer)->block_trade = false, pInfo(currentPeer)->accept_the_offer = false, pInfo(currentPeer)->trade_accept = false, pInfo(currentPeer)->trading_with = -1, pInfo(currentPeer)->trade_items.clear();
									pInfo(p_)->block_trade = false, pInfo(p_)->trading_with = -1, pInfo(p_)->trade_accept = false, pInfo(p_)->accept_the_offer = false, pInfo(p_)->trade_items.clear();
								}
								return;
							}
							for (int i_ = 0; i_ < pInfo(currentPeer)->trade_items.size(); i_++) {
								map<string, int>::iterator it;
								for (auto it = pInfo(currentPeer)->trade_items.at(i_).begin(); it != pInfo(currentPeer)->trade_items.at(i_).end(); it++) {
									if (it->first == 1424) {
										pInfo(p_)->accept_the_offer = false;
										send_trade_confirm_dialog(p_, currentPeer, true);
										{
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("`6[``you must wait for the other player to accept first`6]``");
											p.CreatePacket(p_);
										}
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(currentPeer)->netID);
										p.Insert("`6[``You must accept first because you're selling a World Key`6]``");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(currentPeer);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`6[``You must accept first because you're selling a World Key`6]``");
											p.CreatePacket(currentPeer);
										}
										return;
									}
								}
							}
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(p_)->netID);
							p.Insert("`6[``Trade accepted, waiting for other player to accept`6]``");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(p_);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`6[``Trade accepted, waiting for other player to accept`6]``");
								p.CreatePacket(p_);
							}
							{
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(currentPeer)->netID);
								p.Insert("`6[``Trade accepted by other player, waiting for you`6]``");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(currentPeer);
							}
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`6[``Trade accepted by other player, waiting for you`6]``");
								p.CreatePacket(currentPeer);
							}
							return;
						}
					}
				}
				gamepacket_t p;
				p.Insert("OnTextOverlay");
				p.Insert("The other person left the trade!");
				p.CreatePacket(p_);
				pInfo(p_)->block_trade = false, pInfo(p_)->trading_with = -1, pInfo(p_)->trade_accept = false, pInfo(p_)->accept_the_offer = false, pInfo(p_)->trade_items.clear();
			}
			break;
		}
		else if (a_.at(i_) == "friends_remove_finish") {
			send_friends(p_);
			break;
		}
		else if (a_.at(i_) == "friends_remove") {
			if (a_.size() != 11) break;
			if (a_.at(8) == "back") {
				send_info_friend(p_, a_[5]);
				break;
			}
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				remove_friend(p_, world_, a_[5]);
			}
			break;
		}
		else if (a_.at(i_) == "mute_friend" or a_.at(i_) == "block_friend") {
			if (a_.size() != 8) break;
			if (a_.at(5) == "back") {
				send_info_friend(p_, pInfo(p_)->last_edit);
			}
			else if (a_.at(i_) == "mute_friend" and a_.at(5) == "ok") {
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					if (pInfo(p_)->friends.at(c_).name == pInfo(p_)->last_edit) {
						if (pInfo(p_)->friends.at(c_).mute)
							pInfo(p_)->friends.at(c_).mute = false;
						else
							pInfo(p_)->friends.at(c_).mute = true;
					}
				}
				send_info_friend(p_, pInfo(p_)->last_edit);
			}
			else if (a_.at(i_) == "block_friend" and a_.at(5) == "ok") {
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					if (pInfo(p_)->friends.at(c_).name == pInfo(p_)->last_edit) {
						if (pInfo(p_)->friends.at(c_).block_trade)
							pInfo(p_)->friends.at(c_).block_trade = false;
						else
							pInfo(p_)->friends.at(c_).block_trade = true;
					}
				}
				send_info_friend(p_, pInfo(p_)->last_edit);
			}
			break;
		}
		else if (a_.at(i_) == "friends_message") {
			if (a_.size() != 13) break;
			if (a_.at(8) == "back") {
				send_info_friend(p_, a_[5]);
			}
			else if (a_.at(8) == "send") {
				string message = explode("\n", explode("|", cch).at(11)).at(0).c_str();
				SendCmd(p_, "/msg " + pInfo(p_)->last_wrenched + " " + message, true);
			}
			break;
		}
		else if (a_.at(i_) == "friends_edit" || a_.at(i_) == "friends_message") {
			if (a_.size() != 11) break;
			if (a_.at(8) == "remove" or a_.at(8) == "back") {
				edit_friend(p_, a_[5], (a_.at(8) == "back" ? true : false));
			}
			else if (a_.at(8) == "goto") {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->tankIDName == a_[5]) {
						for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
							if (pInfo(currentPeer)->friends.at(c_).name == pInfo(p_)->tankIDName) {
								if (pInfo(currentPeer)->show_location_) {
									if (pInfo(currentPeer)->world.empty()) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Hmm, my friend isn't in a world right now.");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(p_);
										break;
									}
									else if (pInfo(currentPeer)->world == pInfo(p_)->world) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("You want to warp to the same world you're in?  That's illogical, captain.");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(p_);
										break;
									}
									join_world(p_, pInfo(currentPeer)->world);
								}
								break;
							}
						}
					}
				}
			}
			else if (a_.at(8) == "msg") {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|`5Message to ``" + a_[5] + "|left|660|\nadd_spacer|small|\nadd_text_input|text|||80|left|\nadd_spacer|small|\nembed_data|friendID|" + a_[5] + "\nadd_button|send|`5Send``|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|friends_message|||\nadd_quick_exit|");
				p.CreatePacket(p_);
			}
			else if (a_.at(8) == "mute" or a_.at(8) == "trade_block") {
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					if (pInfo(p_)->friends.at(c_).name == a_[5]) {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						if (a_.at(8) == "mute") {
							if (not pInfo(p_)->friends.at(c_).mute)
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|Are you sure you want to `4Mute`` " + a_[5] + "? You will not receive any messages from this player until you unmute, consider this /ignore a friend|left|\nadd_button|ok|OK|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|mute_friend|||\nadd_quick_exit|");
							else
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|Are you sure you want to `4Un Mute`` " + a_[5] + "? You will receive any messages from this player until you mute.|left|\nadd_button|ok|OK|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|mute_friend|||\nadd_quick_exit|");
						}
						else {
							if (not pInfo(p_)->friends.at(c_).block_trade)
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|Are you sure you want to `4Disable Trade`` with " + a_[5] + "? You will not receive any trade request until you enable trading again.|left|\nadd_button|ok|OK|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|block_friend|||\nadd_quick_exit|");
							else
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|Are you sure you want to `4Enable Trade`` with " + a_[5] + "? You will receive any trade request until you disable trading again.|left|\nadd_button|ok|OK|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|block_friend|||\nadd_quick_exit|");
						}
						p.CreatePacket(p_);
					}
				}
			}
			break;
		}
		else if (a_.at(i_) == "friends_options") {
			if (a_.size() != 12) break;
			if (a_[7] == "checkbox_public") {
				if (not pInfo(p_)->show_location_ and a_[8] == "1") {
					pInfo(p_)->show_location_ = true;
				}
				else if (pInfo(p_)->show_location_ and a_[8] == "0") {
					pInfo(p_)->show_location_ = false;
				}
			}
			if (a_[9] == "checkbox_notifications") {
				if (not pInfo(p_)->show_friend_notifications_ and a_[10] == "1") {
					pInfo(p_)->show_friend_notifications_ = true;
				}
				else if (pInfo(p_)->show_friend_notifications_ and a_[10] == "0") {
					pInfo(p_)->show_friend_notifications_ = false;
				}
			}
			if (a_[5] == "back") {
				vector<string> friends_;
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					friends_.push_back(pInfo(p_)->friends.at(c_).name);
				}
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
						send_friends(p_);
						return;
					}
				}
				send_friends(p_, true);
			}
			break;
		}
		else if (a_.at(i_) == "mute_all_friends" or a_.at(i_) == "remove_all_friends" or a_.at(i_) == "block_all_friends") {
			if (a_.size() != 8) break;
			if (a_[5] == "back") {
				send_all_edit_friends(p_);
				break;
			}
			if (a_[5] == "close")
				break;
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					if (find(pInfo(p_)->last_friends_selection.begin(), pInfo(p_)->last_friends_selection.end(), c_) != pInfo(p_)->last_friends_selection.end()) {
						if (a_.at(i_) == "mute_all_friends") {
							if (pInfo(p_)->friends.at(c_).mute)
								pInfo(p_)->friends.at(c_).mute = false;
							else
								pInfo(p_)->friends.at(c_).mute = true;
						}
						else if (a_.at(i_) == "block_all_friends") {
							if (pInfo(p_)->friends.at(c_).block_trade)
								pInfo(p_)->friends.at(c_).block_trade = false;
							else
								pInfo(p_)->friends.at(c_).block_trade = true;
						}
						else if (a_.at(i_) == "remove_all_friends") {
							remove_friend(p_, world_, pInfo(p_)->friends.at(c_).name, false);
						}
					}
				}
				send_all_edit_friends(p_);
			}
			break;
		}
		else if (a_.at(i_) == "all_friends") {
			if (a_.size() < 10) break;
			if (a_[5] == "back") {
				vector<string> friends_;
				for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
					friends_.push_back(pInfo(p_)->friends.at(c_).name);
				} for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
						send_friends(p_);
						return;
					}
				}
				send_friends(p_, true);
				break;
			}
			pInfo(p_)->last_friends_selection.clear();
			string action_ = a_[5];
			try {
				for (int b_ = 0; b_ < a_.size(); b_++) {
					if (a_.at(b_).substr(0, 3) == "cf_") {
						if (a_.at(b_ + 1) == "1")
							pInfo(p_)->last_friends_selection.push_back(atoi(explode("_", a_.at(b_))[1].c_str()));
					}
				}
			}
			catch (out_of_range) {
				break;
			}
			if (pInfo(p_)->last_friends_selection.size() == 0) {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|`oYou have not selected any friends|left|\nadd_spacer|small|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button|close|`wClose``|noflags|0|0|\nend_dialog|remove_all_friends|||\nadd_quick_exit|");
				p.CreatePacket(p_);
			}
			else {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				if (action_ == "mute_multi_friends")
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|`oAre you sure you want to `4mute`` " + to_string(pInfo(p_)->last_friends_selection.size()) + " friends?|left|\nadd_spacer|small|\nadd_button|confirm|`wYes``|noflags|0|0|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button|close|`wClose``|noflags|0|0|\nend_dialog|mute_all_friends|||\nadd_quick_exit|");
				else if (action_ == "block_multi_friends")
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|`oAre you sure you want to `4block trade`` " + to_string(pInfo(p_)->last_friends_selection.size()) + " friends?|left|\nadd_spacer|small|\nadd_button|confirm|`wYes``|noflags|0|0|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button|close|`wClose``|noflags|0|0|\nend_dialog|block_all_friends|||\nadd_quick_exit|");
				else
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wConfirm``|left|1366|\nadd_textbox|`oAre you sure you want to `4remove`` " + to_string(pInfo(p_)->last_friends_selection.size()) + " friends?|left|\nadd_spacer|small|\nadd_button|confirm|`wYes``|noflags|0|0|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button|close|`wClose``|noflags|0|0|\nend_dialog|remove_all_friends|||\nadd_quick_exit|");
				p.CreatePacket(p_);
			}
			break;
		}
		else if (a_.at(i_) == "friends") {
			if (a_.size() != 8) break;
			if (a_[5] == "back") {
				send_social(p_);
			}
			else if (a_[5] == "all_friends") {
				send_all_edit_friends(p_);
			}
			else if (a_[5] == "friends_options") {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wFriend Options``|left|1366|\nadd_spacer|small|\nadd_checkbox|checkbox_public|Show location to friends|" + to_string(pInfo(p_)->show_location_) + "\nadd_checkbox|checkbox_notifications|Show friend notifications|" + to_string(pInfo(p_)->show_friend_notifications_) + "\nadd_spacer|small|\nadd_button|back|OK|noflags|0|0|\nend_dialog|friends_options|||\nadd_quick_exit|");
				p.CreatePacket(p_);
			}
			else if (a_[5] == "friend_all") {
				send_friends(p_, true);
			}
			else {
				send_info_friend(p_, a_[5]);
			}
			break;
		}
		else if (a_.at(i_) == "unaccess") {
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
				bool upd_ = false;
				for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
					if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
						WorldBlock* block_ = &world_->blocks.at(i_);
						if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
							if (find(block_->admins.begin(), block_->admins.end(), pInfo(p_)->tankIDName) != block_->admins.end()) {
								block_->admins.erase(remove(block_->admins.begin(), block_->admins.end(), pInfo(p_)->tankIDName), block_->admins.end());
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = i_ % xSize, data_.punchY = i_ / xSize, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, p_, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[]raw, blc;
								if (block_->locked) {
									upd_lock(*block_, *world_, p_);
								}
								upd_ = true;
							}
							//...
						}
						else {
							if (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) != world_->admins.end()) {
								world_->admins.erase(remove(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName), world_->admins.end());
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = i_ % xSize, data_.punchY = i_ / xSize, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, p_, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[]raw, blc;
								upd_ = true;
								gamepacket_t p2(0, pInfo(p_)->netID);
								{
									p2.Insert("OnNameChanged");
									if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0) pInfo(p_)->name_color = "`0";
									p2.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``");
								}
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										p2.CreatePacket(currentPeer);
									}
								}
							}
						}
					}
				} if (upd_) {
					packet_(p_, "action|play_sfx\nfile|audio/dialog_cancel.wav\ndelayMS|0");
					{
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("Removed your access from all locks.");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(p_);
					}
					{
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("Removed your access from all locks.");
						p.CreatePacket(p_);
					}
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert(pInfo(p_)->tankIDName + " removed their own access from all locks.");
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							p.CreatePacket(currentPeer);
						}
					}
				}
				else {
					{
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("You didn't have access on any locks!");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(p_);
					}
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					p.Insert("You didn't have access on any locks!");
					p.CreatePacket(p_);
				}
			}
			break;
		}
		else if (a_.at(i_) == "socialportal") {
			if (a_.size() != 8) break;
			string b_ = a_.at(5);
			if (b_ == "showfriend") {
				send_friends(p_);
			}
			break;
		}
		else if (a_.at(i_) == "acceptaccess") {
			if (pInfo(p_)->ac_.size() == 0) break;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == pInfo(p_)->world) {
					if (pInfo(p_)->ac_.find(pInfo(currentPeer)->netID) != pInfo(p_)->ac_.end()) {
						string name_ = pInfo(p_)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (p != worlds.end()) {
							World* world_ = &worlds.at(p - worlds.begin());
							string peer_name = pInfo(p_)->tankIDName, owner_name = world_->owner_name, user_name = pInfo(currentPeer)->tankIDName;
							try {
								int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
								int x_ = (pInfo(p_)->ac_.at(pInfo(currentPeer)->netID)) % xSize, y_ = (pInfo(p_)->ac_.at(pInfo(currentPeer)->netID)) / xSize;
								WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
								if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
									if (block_->owner_name != user_name) break;
									if (block_->admins.size() > 8) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Lock has reached access limit!");
										p.Insert(0);
										p.Insert(0);
										p.CreatePacket(p_);
										continue;
									}
									block_->admins.push_back(peer_name);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` was given access to a " + items.at(block_->fg).name + ".");
									PlayerMoving data_{};
									data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
									BYTE* raw = packPlayerMoving(&data_, 112);
									BYTE* blc = raw + 56;
									form_visual(blc, *block_, *world_, p_, false);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(p_)->world) {
											p.CreatePacket(currentPeer);
											send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
										}
									}
									delete[] raw, blc;
								}
								else {
									if (owner_name != user_name) break;
									if (world_->admins.size() > 8) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("World has reached access limit!");
										p.Insert(0);
										p.Insert(0);
										p.CreatePacket(p_);
										continue;
									}
									world_->admins.push_back(peer_name);
									gamepacket_t p2(0, pInfo(p_)->netID);
									{
										p2.Insert("OnNameChanged");
										if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0) pInfo(p_)->name_color = "`^";
										p2.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``");
									}
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` was given access to a " + items.at(block_->fg).name + ".");
									PlayerMoving data_{};
									data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
									BYTE* raw = packPlayerMoving(&data_, 112);
									BYTE* blc = raw + 56;
									form_visual(blc, *block_, *world_, p_, false);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(p_)->world) {
											p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer);
											send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
										}
									}
									delete[] raw, blc;
								}
								packet_(p_, "action|play_sfx\nfile|audio/secret.wav\ndelayMS|0");
								if (block_->locked) {
									upd_lock(*block_, *world_, p_);
								}
							}
							catch (out_of_range) { // su proxy kazkas ivede netinkamus x ir y
								break;
							}
						}
						pInfo(p_)->ac_.clear();
						return;
					}
				}
			}
			gamepacket_t p;
			p.Insert("OnTalkBubble");
			p.Insert(pInfo(p_)->netID);
			p.Insert("The lock owner has left!");
			p.Insert(0), p.Insert(0);
			p.CreatePacket(p_);
			pInfo(p_)->ac_.clear();
			break;
		}
		else if (a_.at(i_) == "worlds_list") {
			if (a_.size() != 8 and a_.size() != 5) break;
			if (a_.size() == 5) {
				send_wrench_self(p_);
				break;
			} if (pInfo(p_)->home_world == a_[5]) {
				bool a___ = false;
				for (pair<string, long long int> p : home_timed) {
					if (p.first == pInfo(p_)->tankIDName) {
						if (p.second + HOME_TIME > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							a___ = true;
							gamepacket_t no;
							no.Insert("OnTalkBubble");
							no.Insert(pInfo(p_)->netID);
							no.Insert("`4Cooldown active`` - You can use `5home warp`` in `5" + to_string(((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) - ((((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) / 60) * 60)) + " ``seconds.");
							no.Insert(0), no.Insert(0);
							no.CreatePacket(p_);
							break;
						}
					}
				}
				if (a___)
					break;
				home_timed.push_back(make_pair(pInfo(p_)->tankIDName, (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
			}
			join_world(p_, a_[5]);
			break;
		}
		else if (a_.at(i_) == "popup") {
			if (a_.size() == 8 and a_[5] == "my_worlds") {
				string home_world_ = "";
				string worlds_owned_ = "";
				if (not pInfo(p_)->home_world.empty()) {
					home_world_ += "\nadd_textbox|Your home world|left|\nadd_button|" + pInfo(p_)->home_world + "|" + pInfo(p_)->home_world + "|noflags|0|0|\nadd_spacer|small|";
				} for (int w_ = 0; w_ < pInfo(p_)->worlds_owned.size(); w_++) {
					worlds_owned_ += "\nadd_button|" + pInfo(p_)->worlds_owned.at(w_) + "|" + pInfo(p_)->worlds_owned.at(w_) + "|noflags|0|0|";
				} if (worlds_owned_.empty()) {
					worlds_owned_ = "\nadd_textbox|You do not have any World-Locked worlds.``|left|";
				}
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label|big|Worlds Locked|right\nadd_spacer|small|" + home_world_ + "\nadd_textbox|Your locked worlds|left|\nadd_textbox|You must be a Supporter or Super Supporter to warp to these worlds.|left|" + worlds_owned_ + "\nadd_quick_exit|\nadd_spacer|small|\nend_dialog|worlds_list||Back|");
				p.CreatePacket(p_);
			}
			else if (a_.size() == 8 and a_[5] == "emojis") {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|big|Growmojis|left|1366|\nadd_spacer|small|\nadd_smalltext_forced| (sigh) |left|\nadd_smalltext_forced| (mad) |left|\nadd_smalltext_forced| (smile) |left|\nadd_smalltext_forced| (tongue) |left|\nadd_smalltext_forced| (wow) |left|\nadd_smalltext_forced| (no) |left|\nadd_smalltext_forced| (shy) |left|\nadd_smalltext_forced| (wink) |left|\nadd_smalltext_forced| (music) |left|\nadd_smalltext_forced| (lol) |left|\nadd_smalltext_forced| (kiss) |left|\nadd_smalltext_forced| (agree) |left|\nadd_smalltext_forced| (cactus) |left|\nadd_smalltext_forced| (pine) |left|\nadd_smalltext_forced| (song) |left|\nadd_smalltext_forced| (lucky) |left|\nadd_spacer|small|\nadd_smalltext|`9You need to be a Super Supporter to get these Growmojis.``|left|\nadd_smalltext_forced_alpha| (yes) |0.5|left|\nadd_smalltext_forced_alpha| (love) |0.5|left|\nadd_smalltext_forced_alpha| (megaphone) |0.5|left|\nadd_smalltext_forced_alpha| (heart) |0.5|left|\nadd_smalltext_forced_alpha| (cool) |0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need 30 friends to get this Growmoji.``|left|\nadd_smalltext_forced_alpha| (see-no-evil) |0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need 40 friends to get this Growmoji.``|left|\nadd_smalltext_forced_alpha| (dance) |0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need 50 friends to get this Growmoji.``|left|\nadd_smalltext_forced_alpha| (build) |0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (oops) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (sleep) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (punch) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (bheart) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (cry) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (bunny) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (peace) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (terror) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (troll) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (fireworks) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (party) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (ghost) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (nuke) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in an event.``|left|\nadd_smalltext_forced_alpha| (halo) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (eyes) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9This Growmoji can be found in a secret event.``|left|\nadd_smalltext_forced_alpha| (weary) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (wl) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (grow) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (gems) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (gtoken) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (vend) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9You need to purchase this Growmoji from the store.``|left|\nadd_smalltext_forced_alpha| (football) | 0.5|left|\nadd_spacer|small|\nadd_smalltext|`9These Growmojis can be found in the Growmoji Chest sold by Locke the Traveling Salesman.``|left|\nadd_smalltext_forced_alpha| (alien) |0.5|left|\nadd_smalltext_forced_alpha| (evil) |0.5|left|\nadd_smalltext_forced_alpha| (pizza) |0.5|left|\nadd_smalltext_forced_alpha| (clap) |0.5|left|\nadd_smalltext_forced_alpha| (turkey) |0.5|left|\nadd_smalltext_forced_alpha| (gift) |0.5|left|\nadd_smalltext_forced_alpha| (cake) |0.5|left|\nadd_smalltext_forced_alpha| (heartarrow) |0.5|left|\nadd_smalltext_forced_alpha| (shamrock) |0.5|left|\nadd_smalltext_forced_alpha| (grin) |0.5|left|\nadd_smalltext_forced_alpha| (ill) |0.5|left|\nadd_spacer|small|\nend_dialog|worlds_list||Back|\nadd_quick_exit|\n");
				p.CreatePacket(p_);
			}
			else if (a_.size() == 8 and a_[5] == "title_edit") {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label|big|No Titles Obtained|right\nadd_spacer|small|\nadd_button||OK|noflags|0|0|\nend_dialog|title_edit||\n");
				p.CreatePacket(p_);
			}
			else if (a_.size() == 8 and a_[5] == "notebook_edit") {
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label|big|Notebook|left|0|\nadd_text_box_input|personal_note||" + pInfo(p_)->note + "|128|5|\nadd_spacer|small|\nadd_button|save|Save|noflags|0|0|\nadd_button|clear|Clear|noflags|0|0|\nadd_button|cancel|Cancel|noflags|0|0|\nend_dialog|notebook_edit||\nadd_quick_exit|\n");
				p.CreatePacket(p_);
			}
			else if (a_.size() == 8 and a_[5] == "goals") {
				struct tm newtime;
				time_t now = time(0);
				localtime_s(&newtime, &now);
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_label_with_icon|small|"+pInfo(p_)->tankIDName+"'s Goals|left|982|\nadd_spacer|small|"/*"\nadd_textbox|`9Life Goals``|left|\nadd_smalltext|`9Awesomeness: 13%``|left|\nadd_label_with_icon|small|`3Seed Goal:`` Deliver 200 Rock (0/200)``|left|3|\nadd_label_with_icon|small|`3Gem Goal:`` Smash 5000 rarity of blocks (2884/5000)``|left|112|\nadd_label_with_icon|small|`3Experience Goal:`` Defeat 10 players in Games (0/10)``|left|1488|\nadd_smalltext|Completed Life Goals will reset in 4 hours, 20 mins|left|\nadd_spacer|small|"*/"\nadd_textbox|`9Daily Quest``|left|\nadd_label_with_icon|small|"+ (newtime.tm_mday != pInfo(p_)->dd ? "Deliver `2" + to_string(item1c) + " " + items.at(item1).name + "`` and `2" + to_string(item2c) + " " + items.at(item2).name + "`` to Crazy Jim" : "`2COMPLETE!`` Check again tomorrow.") + "|left|1486|"/*"\nadd_spacer|small|\nadd_textbox|`9Biweekly Quest``|left|\nadd_label_with_icon|small|`2Quest progress``|left|5202|\nadd_textbox|- Harvest 4800 rarity from trees (0/4800)|left|\nadd_textbox|- Complete 8 surgeries (0/8)|left|\nadd_textbox|- Earn 3 Growtokens (0/3)|left|\nadd_spacer|small|\nadd_textbox|`9Role Quests|left|\nadd_button|rolesmenu|View Role Quests|noflags|0|0|\nadd_spacer|small|\nadd_textbox|`9Epic Quests``|left|\nadd_label_with_icon|small|`3Catch a Perfect Stonefish``|left|482|\nadd_label_with_icon|small|`3Sew a Wool Scarf``|left|482|\nadd_label_with_icon|small|`3Lock a world with an Emerald Lock``|left|482|\nadd_label_with_icon|small|`3Discover the Truth``|left|482|\nadd_label_with_icon|small|`3Plant a Wizard's Staff Tree``|left|482|\nadd_label_with_icon|small|`3Forge an Iron Buckle``|left|482|\nadd_label_with_icon|small|`3Dress up as Locke``|left|482|\nadd_label_with_icon|small|`3Own a Top-10 Rated world``|left|482|\nadd_label_with_icon|small|`3Achieve 100% Awesomeness``|left|482|\nadd_label_with_icon|small|`3Complete a Massive Trauma surgery``|left|482|\nadd_label_with_icon|small|`3Craft a Xenonite Crystal``|left|482|\nadd_label_with_icon|small|`3Hatch a Black Crystal Dragon``|left|482|\nadd_label_with_icon|small|`3Beat a Blanket Cape out of a Supervillain``|left|482|\nadd_label_with_icon|small|`3Find a Topaz Block in a Golden Treasure Hoard``|left|482|\nadd_label_with_icon|small|`3Buy a Riding Bumblebee or Riding Raven in the Gem Shop``|left|482|\nadd_label_with_icon|small|`3Buy a Golden Pickaxe for Growtokens``|left|482|\nadd_label_with_icon|small|`3Buy the Phlogiston for Pet Trainer Medals``|left|482|\nadd_label_with_icon|small|`3Collect all 4 treasures in Valhowla``|left|482|\nadd_label_with_icon|small|`3Get a Ghost Charm from a Spirit Storage explosion``|left|482|\nadd_label_with_icon|small|`3Get a Teddy Bear from an Awkward Friendly Unicorn``|left|482|\nadd_label_with_icon|small|`3Compact a dress into a Mystery Dress``|left|482|\nadd_label_with_icon|small|`3In a world you own, combust a stack of 200 Highly Combustible Boxes you earned``|left|482|\nadd_label_with_icon|small|`3Catch an Octopus Head``|left|482|\nadd_label_with_icon|small|`3Complete the Growtopian Of The Year achievement``|left|482|\nadd_label_with_icon|small|`3Splice a Weather Machine - Comet``|left|482|\nadd_label_with_icon|small|`3Win 200 Carnival Games``|left|482|\nadd_label_with_icon|small|`3Buy a Diamond Dragon from Locke``|left|482|\nadd_label_with_icon|small|`3Win World Of The Day or Video Of The Week``|left|482|\nadd_label_with_icon|small|`3Have 10 different Ringmaster Rings in your inventory``|left|482|\nadd_label_with_icon|small|`3Level up to level 100``|left|482|\nadd_label_with_icon|small|`3Hold 3 different Legendary items in your inventory``|left|482|\nadd_label_with_icon|small|`3Complete all 100 classic achievements``|left|482|"*/"\nadd_spacer|small|\nend_dialog|worlds_list||Back|\nadd_quick_exit|\n");
				p.CreatePacket(p_);
			}
			else if (a_.size() == 14 and a_[11] == "trade" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				string name_ = pInfo(p_)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds.at(p - worlds.begin());
					int my_netid_ = atoi(a_[5].c_str()), other_netid_ = atoi(a_[8].c_str());
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == pInfo(p_)->world and pInfo(currentPeer)->netID == other_netid_ and not pInfo(currentPeer)->invis) {
							for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
								if (pInfo(currentPeer)->friends.at(c_).name == pInfo(p_)->tankIDName) {
									if (pInfo(currentPeer)->friends.at(c_).block_trade)
										return;
								}
							}
							if (pInfo(currentPeer)->trading_with != -1 and pInfo(currentPeer)->trading_with != pInfo(p_)->netID) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("That person is busy.");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(p_);
								pInfo(p_)->block_trade = false, pInfo(p_)->trading_with = -1;
								{
									gamepacket_t p;
									p.Insert("OnForceTradeEnd");
									p.CreatePacket(p_);
								}
								return;
							}
							pInfo(p_)->trading_with = pInfo(currentPeer)->netID;
							pInfo(p_)->trade_accept = 0;
							pInfo(currentPeer)->trade_accept = 0;
							gamepacket_t p;
							p.Insert("OnStartTrade");
							p.Insert(pInfo(currentPeer)->tankIDName);
							p.Insert(pInfo(currentPeer)->netID);
							p.CreatePacket(p_);
							if (pInfo(currentPeer)->trading_with != -1) {
								// as neisivaizduoju kdl real gt taip daro bet noriu kad butu kaip rgt.
								gamepacket_t p;
								p.Insert("OnTradeStatus");
								p.Insert(pInfo(p_)->netID);
								p.Insert("");
								p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
								p.Insert("locked|0\nreset_locks|1\naccepted|0");
								p.CreatePacket(p_);
								{
									gamepacket_t p;
									p.Insert("OnTradeStatus");
									p.Insert(pInfo(p_)->netID);
									p.Insert("");
									p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
									p.Insert("locked|0\naccepted|1");
									p.CreatePacket(p_);
								}
								{
									gamepacket_t p;
									p.Insert("OnTradeStatus");
									p.Insert(pInfo(p_)->netID);
									p.Insert("");
									p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
									p.Insert("locked|0\nreset_locks|1\naccepted|0");
									p.CreatePacket(p_);
								}
								{
									gamepacket_t p;
									p.Insert("OnTradeStatus");
									p.Insert(pInfo(currentPeer)->netID);
									p.Insert("");
									p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
									p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
									p.CreatePacket(p_);
									{
										gamepacket_t p;
										p.Insert("OnTradeStatus");
										p.Insert(pInfo(currentPeer)->netID);
										p.Insert("");
										p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
										p.Insert("locked|0\nreset_locks|1\naccepted|0");
										p.CreatePacket(currentPeer);
									}
									{
										gamepacket_t p;
										p.Insert("OnTradeStatus");
										p.Insert(pInfo(currentPeer)->netID);
										p.Insert("");
										p.Insert("`o" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s offer.``");
										p.Insert("locked|0\naccepted|1");
										p.CreatePacket(currentPeer);
									}
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
										p.Insert(pInfo(p_)->netID);
										p.Insert("");
										p.Insert("`o" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``'s offer.``");
										p.Insert(make_trade_offer(pInfo(p_), true) + "locked|0\nreset_locks|1\naccepted|0");
										p.CreatePacket(currentPeer);
									}
								}
								break;
							}
							packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`#TRADE ALERT:`` `w" + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "```` wants to trade with you!  To start, use the `wWrench`` on that person's wrench icon, or type `w/trade " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``");
								p.CreatePacket(currentPeer);
							}
							break;
						}
					}
				}
			}
			else if (a_.size() == 14 and a_[11] == "mute_player" and isdigit(a_[5][0]) and isdigit(a_[8][0]) or a_.size() == 14 and a_[11] == "unmute_player" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				int my_netid_ = atoi(a_[5].c_str()), other_netid_ = atoi(a_[8].c_str());
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(p_)->world and pInfo(currentPeer)->netID == other_netid_) {
						for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
							if (pInfo(p_)->friends.at(c_).name == pInfo(currentPeer)->tankIDName) {
								if (a_[11] == "mute_player")
									pInfo(p_)->friends.at(c_).mute = true;
								else
									pInfo(p_)->friends.at(c_).mute = false;
								break;
							}
						}
						break;
					}
				}
			}
			else if (a_.size() == 14 and a_[11] == "worldban" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				SendCmd(p_, "/ban " + pInfo(p_)->last_wrenched, true);
			}
			else if (a_.size() == 14 and a_[11] == "pull" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				SendCmd(p_, "/pull " + pInfo(p_)->last_wrenched, true);
			}
			else if (a_.size() == 14 and a_[11] == "kick" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				SendCmd(p_, "/kick " + pInfo(p_)->last_wrenched, true);
			}
			else if (a_.size() == 14 and a_[11] == "punish_view" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				if (pInfo(p_)->mod == 1 || pInfo(p_)->dev == 1) {
					SendCmd(p_, "/info " + pInfo(p_)->last_wrenched, true);
				}
			}
			else if (a_.size() == 14 and a_[11] == "friend_add" and isdigit(a_[5][0]) and isdigit(a_[8][0])) {
				int my_netid_ = atoi(a_[5].c_str()), other_netid_ = atoi(a_[8].c_str());
				string name_ = pInfo(p_)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds.at(p - worlds.begin());
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == pInfo(p_)->world and pInfo(currentPeer)->netID == other_netid_) {
							if (find(pInfo(currentPeer)->pending_friends.begin(), pInfo(currentPeer)->pending_friends.end(), pInfo(p_)->tankIDName) != pInfo(currentPeer)->pending_friends.end()) {
								packet_(p_, "action|play_sfx\nfile|audio/love_in.wav\ndelayMS|0");
								long long time_t = time(NULL);
								Friends new_friend_;
								new_friend_.name = pInfo(currentPeer)->tankIDName;
								new_friend_.mute = false;
								new_friend_.block_trade = false;
								new_friend_.last_seen = time_t;
								pInfo(p_)->friends.push_back(new_friend_);
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`3FRIEND ADDED:`` You're now friends with " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``!");
								p.CreatePacket(p_);
								{
									packet_(currentPeer, "action|play_sfx\nfile|audio/love_in.wav\ndelayMS|0");
									Friends new_friend_;
									new_friend_.name = pInfo(p_)->tankIDName;
									new_friend_.mute = false;
									new_friend_.block_trade = false;
									new_friend_.last_seen = time_t;
									pInfo(currentPeer)->friends.push_back(new_friend_);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`3FRIEND ADDED:`` You're now friends with " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``!");
									p.CreatePacket(currentPeer);
								}
								pInfo(currentPeer)->pending_friends.erase(remove(pInfo(currentPeer)->pending_friends.begin(), pInfo(currentPeer)->pending_friends.end(), pInfo(p_)->tankIDName), pInfo(currentPeer)->pending_friends.end());
							}
							else {
								for (int c_ = 0; c_ < pInfo(p_)->friends.size(); c_++) {
									if (pInfo(p_)->friends.at(c_).name == pInfo(currentPeer)->tankIDName) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("That's already my friend!");
										p.Insert(0), p.Insert(0);
										return;
									}
								}
								if (abs((pInfo(currentPeer)->x / 32) - (pInfo(p_)->x / 32)) >= 3) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("`5[```4Too far away`` `0- Stand closer to`` " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "```0 first!```5]``");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(p_);
									return;
								}
								pInfo(p_)->pending_friends.push_back(pInfo(currentPeer)->tankIDName);
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("`5[``Friend request sent to " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "```5]``");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(p_);
								{
									packet_(currentPeer, "action|play_sfx\nfile|audio/tip_start.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`3FRIEND REQUEST:`` You've received a `wfriend request`` from " + pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``! To accept, press the `wwrench by his/her name`` and then choose `wAdd as friend``.");
									p.CreatePacket(currentPeer);
								}
							}
							return;
						}
					}
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(p_)->netID);
					p.Insert("Hmm, that person left.");
					p.Insert(0), p.Insert(0);
					p.CreatePacket(p_);
				}
			}
			else if (a_.size() == 8 and a_[5] == "acceptlock") {
				if (pInfo(p_)->ac_.size() == 0) break;
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == pInfo(p_)->world) {
						if (pInfo(p_)->ac_.find(pInfo(currentPeer)->netID) != pInfo(p_)->ac_.end()) {
							string name_ = pInfo(p_)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds.at(p - worlds.begin());
								string owner_name = world_->owner_name, user_name = pInfo(currentPeer)->tankIDName;
								try {
									int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
									int x_ = (pInfo(p_)->ac_.at(pInfo(currentPeer)->netID)) % xSize, y_ = (pInfo(p_)->ac_.at(pInfo(currentPeer)->netID)) / xSize;
									WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
									if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
										if (block_->owner_name != user_name) break;
									}
									else {
										if (owner_name != user_name) break;
									}
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|small|Accept Access To World|left|242|\nadd_smalltext|When you have access to a world, you are responsible for anything the world's owners or other admins do.|left|\nadd_smalltext|Don't accept access to a world unless it is from people you trust.|left|\nadd_smalltext|You can remove your access later by either wrenching the lock, or typing `2/unaccess`` to remove yourself from all locks in the world.|left|\nadd_spacer|small|\nadd_textbox|Are you sure you want to be added to this " + items.at(block_->fg).name + "?|left|\nend_dialog|acceptaccess|No|Yes|");
									p.CreatePacket(p_);
								}
								catch (out_of_range) { // su proxy kazkas ivede netinkamus x ir y
									break;
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
		else if (a_.at(i_) == "lock_edit") {
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			World* world_ = &worlds.at(p - worlds.begin());
			/*if (a_.size() != 23 and a_.size() != 25 and a_.size() != 26 and a_.size() != 11) break;
			if (not isdigit(a_[i_+2][0]) and a_.size() != 11 or not isdigit(a_[i_+5][0]) and a_.size() != 11) break;*/
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			if (p != worlds.end()) {
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
					if (items.at(t_).blockType != BlockTypes::LOCK) break;
					string owner_name = world_->owner_name, user_name = pInfo(p_)->tankIDName;
					if (a_.size() == 11) { // remove my access
						if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
							if (find(block_->admins.begin(), block_->admins.end(), user_name) != block_->admins.end()) {
								block_->admins.erase(remove(block_->admins.begin(), block_->admins.end(), user_name), block_->admins.end());
								packet_(p_, "action|play_sfx\nfile|audio/dialog_cancel.wav\ndelayMS|0");
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert(user_name + " removed their access from a " + items.at(t_).name);
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, p_, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										p.CreatePacket(currentPeer);
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									} if (pInfo(currentPeer)->world == world_->name and pInfo(currentPeer)->tankIDName == user_name) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("I've removed my access!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(currentPeer);
									}
								}
								delete[] raw, blc;
								if (block_->locked) {
									upd_lock(*block_, *world_, p_);
								}
							}
						}
						else if (find(world_->admins.begin(), world_->admins.end(), user_name) != world_->admins.end()) {
							world_->admins.erase(remove(world_->admins.begin(), world_->admins.end(), user_name), world_->admins.end());
							packet_(p_, "action|play_sfx\nfile|audio/dialog_cancel.wav\ndelayMS|0");
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert(user_name + " removed their access from a " + items.at(t_).name);
							gamepacket_t p2(0, pInfo(p_)->netID);
							{
								p2.Insert("OnNameChanged");
								if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0) pInfo(p_)->name_color = "`0";
								p2.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "``");
							}
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, p_, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer);
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								} if (pInfo(currentPeer)->world == world_->name and pInfo(currentPeer)->tankIDName == user_name) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("I've removed my access!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(currentPeer);
								}
							}
							delete[] raw, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, p_);
							}
						}
						break;
					}
					if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
						if (block_->owner_name != user_name and not pInfo(p_)->dev) break;
					}
					else {
						if (owner_name != user_name and not pInfo(p_)->dev) break;
					}
					bool reapply = false;
					for (int b_ = 0; b_ < a_.size(); b_++) {
						bool upd_ = false;
						if (a_.at(b_) == "getKey") {
							if (pInfo(p_)->tankIDName != world_->owner_name and not pInfo(p_)->dev) break;
							if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
							int c_ = 0;
							modify_inventory(p_, 1424, c_);
							if (c_ != 0) break;
							for (int i_ = 0; i_ < world_->drop.size(); i_++) {
								if (world_->drop.at(i_).x == -1 or world_->drop.at(i_).id == 0) continue;
								WorldBlock* block_ = &world_->blocks.at((world_->drop.at(i_).x / 32) + ((world_->drop.at(i_).y / 32) * 100));
								if (items.at(block_->fg).collisionType != 1) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("`4Oops!... Can't trade a world with floating items that are unblocked or in treasure chests!``");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(p_);
									return;
								}
							}
							for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
								if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
									uint16_t id_ = world_->blocks.at(i_).fg;
									if (id_ == 202 or id_ == 204 or id_ == 206 or id_ == 4994) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("To trade a world, you can only have one lock on it, the `5World Lock``.  Remove the rest!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(p_);
										return;
									}
								}
							}
							c_ = 1;
							if (modify_inventory(p_, 1424, c_) == 0) {
								packet_(p_, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								p.Insert("You got a `#World Key``! You can now trade this world to other players.");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(p_);
							}
						}
						else if (a_.at(b_) == "minimum_entry_level" and isdigit(a_.at(b_ + 1)[0])) {
							if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
							int new_entry_level_ = atoi(a_.at(b_ + 1).c_str());
							if (world_->entry_level != new_entry_level_) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(p_)->netID);
								if (new_entry_level_ < 1) {
									p.Insert("Minimum entry level can't be lower than 1.");
									p.CreatePacket(p_);
									continue;
								}
								if (new_entry_level_ > 124) {
									p.Insert("Minimum entry level can't be higher than 124.");
									p.CreatePacket(p_);
									continue;
								}
								world_->entry_level = new_entry_level_;
								p.Insert("Minimum entry level for this world is set to `2Level " + to_string(new_entry_level_) + "``.");
								p.CreatePacket(p_);
							}
						}
						else if (a_.at(b_) == "tempo" and isdigit(a_.at(b_ + 1)[0])) {
							if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
							uint32_t new_bpm_ = atoi(a_.at(b_ + 1).c_str());
							if (world_->music_bpm != new_bpm_) {
								if (new_bpm_ < 20 or new_bpm_ > 200) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("Tempo must be from 20-200 BPM.");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
									continue;
								}
								world_->music_bpm = new_bpm_, upd_ = true;
							}
						}
						//recalcLock
						else if (a_.at(b_) == "recalcLock") {
							if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {			
								cout << "reapply set to true" << endl;
								reapply = true;
							}
							//break;
						}
						else if (a_.at(b_).substr(0, 9) == "checkbox_") {
							// checkboxes
							vector<string> target_ = explode("_", a_.at(b_));
							if (target_.at(1) == "disable") {
								if (target_.size() == 4 and target_.at(2) == "music" and target_.at(3) == "render") {
									if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
									if (not world_->make_music_blocks_invisible and a_.at(b_ + 1) == "1") {
										world_->make_music_blocks_invisible = true, upd_ = true;
									}
									else if (world_->make_music_blocks_invisible and a_.at(b_ + 1) == "0") {
										world_->make_music_blocks_invisible = false, upd_ = true;
									}
								}
								else if (target_.at(2) == "music") {
									if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
									// music disable
									if (not world_->disable_music_blocks and a_.at(b_ + 1) == "1") {
										world_->disable_music_blocks = true, upd_ = true;
									}
									else if (world_->disable_music_blocks and a_.at(b_ + 1) == "0") {
										world_->disable_music_blocks = false, upd_ = true;
									}
								}
							}
							else if (target_.size() == 5 and target_.at(4) == "world") {
								if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) break;
								// set as home world
								if (pInfo(p_)->home_world != world_->name and a_.at(b_ + 1) == "1") {
									pInfo(p_)->home_world = world_->name;
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert(world_->name + " has been set as your home world!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
								}
								else if (pInfo(p_)->home_world == world_->name and a_.at(b_ + 1) == "0") {
									pInfo(p_)->home_world = "";
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert(world_->name + " has been removed as your home world!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
								}
							}
							else if (target_.at(1) == "ignore") {
								if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
									if (not block_->empty_air and a_.at(b_ + 1) == "1") {
										block_->empty_air = true;
									}
									else if (block_->empty_air and a_.at(b_ + 1) == "0") {
										block_->empty_air = false;
									}
								}
							}
							else if (target_.at(1) == "buildonly") {
								if (block_->fg == 4994) {
									if (not block_->build_only and a_.at(b_ + 1) == "1") {
										block_->build_only = true;
									}
									else if (block_->build_only and a_.at(b_ + 1) == "0") {
										block_->build_only = false;
									}
								}
							}
							else if (target_.at(1) == "admins") {
								if (block_->fg == 4994) {
									if (not block_->limit_admins and a_.at(b_ + 1) == "1") {
										block_->limit_admins = true;
									}
									else if (block_->limit_admins and a_.at(b_ + 1) == "0") {
										block_->limit_admins = false;
									}
								}
							}
							else if (target_.at(1) == "public") {
								if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
									if (not block_->open_to_public and a_.at(b_ + 1) == "1") {
										block_->open_to_public = true;
										upd_ = true;
									}
									else if (block_->open_to_public and a_.at(b_ + 1) == "0") {
										block_->open_to_public = false;
										upd_ = true;
									}
								}
								else {
									if (not world_->open_to_public and a_.at(b_ + 1) == "1") {
										world_->open_to_public = true;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0)pInfo(p_)->name_color = "`2";
										p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has set the `$World Lock`` to `$PUBLIC");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												p.CreatePacket(currentPeer);
											}
										}
									}
									else if (world_->open_to_public and a_.at(b_ + 1) == "0") {
										world_->open_to_public = false;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0)pInfo(p_)->name_color = "`2";
										p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has set the `$World Lock`` to `4PRIVATE``");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												p.CreatePacket(currentPeer);
											}
										}
									}
								}
							}
							else if (target_.size() == 2 and a_.at(b_ + 1) == "0") {
								string user_name = target_.at(1).erase(0, 1);
								if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
									if (find(block_->admins.begin(), block_->admins.end(), user_name) != block_->admins.end()) {
										block_->admins.erase(remove(block_->admins.begin(), block_->admins.end(), user_name), block_->admins.end());
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert(user_name + " was removed from a " + items.at(block_->fg).name + ".");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												p.CreatePacket(currentPeer);
											}
											if (pInfo(currentPeer)->tankIDName == user_name) {
												packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_cancel.wav\ndelayMS|0");
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(currentPeer)->netID);
												if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0)pInfo(p_)->name_color = "`2";
												p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has `4removed`` your access from a lock on world `w" + world_->name + "``.");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(currentPeer);
												if (pInfo(currentPeer)->world == world_->name) {
													PlayerMoving data_{};
													data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
													BYTE* raw = packPlayerMoving(&data_, 112);
													BYTE* blc = raw + 56;
													form_visual(blc, *block_, *world_, p_, false);
													for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
														if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
														if (pInfo(currentPeer2)->world == world_->name) {
															send_raw(currentPeer2, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
														}
													}
													delete[] raw, blc;
													if (block_->locked) {
														upd_lock(*block_, *world_, p_);
													}
												}
											}
										}
									}
								}
								else if (find(world_->admins.begin(), world_->admins.end(), user_name) != world_->admins.end()) {
									world_->admins.erase(remove(world_->admins.begin(), world_->admins.end(), user_name), world_->admins.end());
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert(user_name + " was removed from a " + items.at(block_->fg).name + ".");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == world_->name) {
											p.CreatePacket(currentPeer);
										}
										if (pInfo(currentPeer)->tankIDName == user_name) {
											packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_cancel.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(currentPeer)->netID);
											if (pInfo(p_)->mod == 0 && pInfo(p_)->dev == 0)pInfo(p_)->name_color = "`2";
											p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` has `4removed`` your access from a lock on world `w" + world_->name + "``.");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(currentPeer);
											gamepacket_t p2(0, pInfo(currentPeer)->netID);
											{
												p2.Insert("OnNameChanged");
												if (pInfo(currentPeer)->mod == 0 && pInfo(currentPeer)->dev == 0)pInfo(currentPeer)->name_color = "`0";
												p2.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``");
											}
											if (pInfo(currentPeer)->world == world_->name) {
												PlayerMoving data_{};
												data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
												BYTE* raw = packPlayerMoving(&data_, 112);
												BYTE* blc = raw + 56;
												form_visual(blc, *block_, *world_, p_, false);
												for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
													if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
													if (pInfo(currentPeer2)->world == world_->name) {
														p2.CreatePacket(currentPeer2);
														send_raw(currentPeer2, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
													}
												}
												delete[] raw, blc;
												if (block_->locked) {
													upd_lock(*block_, *world_, p_);
												}
											}
										}
									}
								}
							}
						}
						else if (a_.at(b_) == "playerNetID" and isdigit(a_.at(b_ + 1)[0])) { // access kazka
							if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
								if (block_->admins.size() > 7) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("Lock has reached access limit!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
									continue;
								}
								size_t id_ = atoi(a_.at(b_ + 1).c_str());
								if (id_ == pInfo(p_)->netID) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("I already have access!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
									continue;
								}
								/*---- end debug print ----
								0: OnTalkBubble
								1: 3
								2: `wG2W`` already has access to the lock.
								3: 0
								4: 0*/
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->netID == id_ and pInfo(currentPeer)->world == world_->name) {
										if (pInfo(currentPeer)->ac_.find(pInfo(p_)->netID) != pInfo(currentPeer)->ac_.end()) break;
										string user_name = pInfo(currentPeer)->tankIDName;
										if (user_name == block_->owner_name or find(block_->admins.begin(), block_->admins.end(), user_name) != block_->admins.end()) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` already has access to the lock.");
											p.Insert(0);
											p.Insert(0);
											p.CreatePacket(p_);
											break;
										}
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Offered " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` access to lock.");
										p.Insert(0);
										p.Insert(0);
										p.CreatePacket(p_);
										{
											pInfo(currentPeer)->ac_.insert({ pInfo(p_)->netID, (x_ + (y_ * 100)) });
											packet_(currentPeer, "action|play_sfx\nfile|audio/secret.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` wants to add you to a " + items.at(block_->fg).name + ". Wrench yourself to accept.");
											p.CreatePacket(currentPeer);
										}
										break;
									}
								}
							}
							else {
								if (world_->admins.size() > 7) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("World has reached access limit!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
									continue;
								}
								size_t id_ = atoi(a_.at(b_ + 1).c_str());
								if (id_ == pInfo(p_)->netID) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(p_)->netID);
									p.Insert("I already have access!");
									p.Insert(0);
									p.Insert(0);
									p.CreatePacket(p_);
									continue;
								}
								/*---- end debug print ----
								0: OnTalkBubble
								1: 3
								2: `wG2W`` already has access to the lock.
								3: 0
								4: 0*/
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->netID == id_ and pInfo(currentPeer)->world == world_->name) {
										if (pInfo(currentPeer)->ac_.find(pInfo(p_)->netID) != pInfo(currentPeer)->ac_.end()) break;
										string user_name = pInfo(currentPeer)->tankIDName;
										if (user_name == world_->owner_name or find(world_->admins.begin(), world_->admins.end(), user_name) != world_->admins.end()) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(p_)->netID);
											p.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` already has access to the lock.");
											p.Insert(0);
											p.Insert(0);
											p.CreatePacket(p_);
											break;
										}
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(p_)->netID);
										p.Insert("Offered " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` access to lock.");
										p.Insert(0);
										p.Insert(0);
										p.CreatePacket(p_);
										{
											pInfo(currentPeer)->ac_.insert({ pInfo(p_)->netID, (x_ + (y_ * 100)) });
											packet_(currentPeer, "action|play_sfx\nfile|audio/secret.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert(pInfo(p_)->name_color + pInfo(p_)->tankIDName + "`` wants to add you to a " + items.at(block_->fg).name + ". Wrench yourself to accept.");
											p.CreatePacket(currentPeer);
										}
										break;
									}
								}
							}
						} 
						if (upd_) {
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, p_, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, p_);
							}
						}
					}
					cout << "reapply yra " << reapply << endl;
					if (reapply) {
						//remove lock from current
						{
							vector<int> new_tiles{};
							vector<WorldBlock> shadow_copy_2 = world_->blocks;
							new_tiles.push_back(x_ + (y_ * 100));
							int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
							for (int i2 = 0; i2 < new_tiles.size(); i2++) {
								int s_x_ = new_tiles.at(i2) % 100, s_y_ = new_tiles.at(i2) / 100;
								if (s_x_ < 99 and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).locked = false;
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).lock_origin = -1;
									}
								} if (s_x_ > 0 and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).locked = false;
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).lock_origin = -1;
									}
								} if (s_y_ < 59 and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).locked = false;
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin = -1;
									}
								} if (s_y_ > 0 and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).locked = false;
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin = -1;
									}
								}
							}
						}
						int lock_size = block_->fg == 202 ? 10 : (block_->fg == 204 ? 48 : (block_->fg == 202 ? 200 : 200));
						if (not block_->empty_air) {
							{
								//apply new without empty air
								vector<vector<int>> tiles_ = lock_tiles(world_, x_, y_, lock_size);
								lock_size = tiles_.size();
								PlayerMoving data_{};
								data_.packetType = 15, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								data_.netID = pInfo(p_)->id;
								data_.plantingTree = block_->fg;
								BYTE* raw;
								if (tiles_.size() != 0) {
									raw = packPlayerMoving(&data_, 112 + tiles_.size() * 2);
									int lalala = 8;
									memcpy(raw + 8, &lock_size, 2);
									memcpy(raw + 12, &lalala, 2);
									BYTE* blc = raw + 56;
									for (int i_ = 0; i_ < tiles_.size(); i_++) {
										vector<int> update_tiles = tiles_.at(i_);
										int x = update_tiles.at(0);
										int y = update_tiles.at(1);
										int sq_ = x + (y * 100);
										WorldBlock* block_ = &world_->blocks.at(sq_);
										if (block_->locked) {
											continue;
										}
										block_->locked = true;
										block_->lock_origin = x_ + (y_ * 100);
										memcpy(blc + (i_ * 2), &sq_, 2);
									}
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name_) {
											packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
											send_raw(currentPeer, 4, raw, 112 + tiles_.size() * 2, ENET_PACKET_FLAG_RELIABLE);
										}
									}
									delete[] raw, blc;
								}
								else {
									raw = packPlayerMoving(&data_, 56);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name_) {
											packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
									}
									delete[] raw;
								}
							}
						}
						else {
							vector<int> new_tiles{};
							vector<int> lock_tiles{};
							vector<WorldBlock> shadow_copy_2 = world_->blocks;
							new_tiles.push_back(x_ + (y_ * 100));
							int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
							for (int i2 = 0; i2 < new_tiles.size(); i2++) {
								if (lock_tiles.size() >= lock_size) break;
								int s_x_ = new_tiles.at(i2) % 100, s_y_ = new_tiles.at(i2) / 100;
								if (s_x_ < 99 and not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).fg != 0 and not_mod(shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)), s_x_, s_y_) or s_x_ < 99 and not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).bg != 0 and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).fg == 0) {
									if (not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
										lock_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).locked = true;
										cout << world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).fg << " set to locked" << endl;
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).lock_origin = x_ + (y_ * 100);
									}
								} if (s_x_ > 0 and not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).fg != 0 and not_mod(shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)), s_x_, s_y_) or s_x_ > 0 and not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).bg != 0 and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).fg == 0) {
									if (not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
										lock_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).locked = true;
										cout << world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).fg << " set to locked" << endl;
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).lock_origin = x_ + (y_ * 100);
									}
								} if (s_y_ < 59 and not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).fg != 0 and not_mod(shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)), s_x_, s_y_) or s_y_ < 59 and not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).bg != 0 and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).fg == 0) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
										lock_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).locked = true;
										cout << world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).fg << " set to locked" << endl;
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin = x_ + (y_ * 100);
									}
								} if (s_y_ > 0 and not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).fg != 0 and not_mod(shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)), s_x_, s_y_) or s_y_ > 0 and not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).bg != 0 and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).fg == 0) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
										lock_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).locked = true;
										cout << world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).fg << " set to locked" << endl;
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin = x_ + (y_ * 100);
									}
								}
							}
						
							cout << "update" << endl;
							cout << block_->fg << endl;
							//upd_lock(*block_, *world_, p_);
							cout << new_tiles.size() << endl;
							lock_size = lock_tiles.size();
							cout << "total lock is " << lock_size << endl;
							if (lock_tiles.size() > 0) {
								PlayerMoving data_{};
								data_.packetType = 15, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								data_.netID = block_->owner_name == pInfo(p_)->tankIDName ? pInfo(p_)->id : -1;
								data_.plantingTree = block_->fg;
								BYTE* raw;
								raw = packPlayerMoving(&data_, 112 + lock_size * 2);
								int lalala = 8;
								memcpy(raw + 8, &lock_size, 2);
								memcpy(raw + 12, &lalala, 2);
								BYTE* blc = raw + 56;
								for (int i_ = 0; i_ < lock_tiles.size(); i_++) memcpy(blc + (i_ * 2), &lock_tiles.at(i_), 2);
								PlayerMoving data_2{};
								data_2.packetType = 5, data_2.punchX = x_, data_2.punchY = y_, data_2.characterState = 0x8;
								BYTE* raw2 = packPlayerMoving(&data_2, 112);
								BYTE* blc2 = raw2 + 56;
								form_visual(blc2, *block_, *world_, p_, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112 + lock_size * 2, ENET_PACKET_FLAG_RELIABLE);
										send_raw(currentPeer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw, blc, raw2, blc2;
							}
							else {
								cout << "prepeate" << endl;
								PlayerMoving data_{};
								data_.packetType = 15, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								data_.netID = block_->owner_name == pInfo(p_)->tankIDName ? pInfo(p_)->id : -1;
								data_.plantingTree = block_->fg;
								BYTE* raw = packPlayerMoving(&data_, 56);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (world_->name == pInfo(currentPeer)->world) {
										send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										PlayerMoving data_2{};
										data_2.packetType = 5, data_2.punchX = x_, data_2.punchY = y_, data_2.characterState = 0x8;
										BYTE* raw2 = packPlayerMoving(&data_2, 112);
										BYTE* blc2 = raw2 + 56;
										form_visual(blc2, *block_, *world_, currentPeer, false);
										send_raw(currentPeer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
										delete[] raw2, blc2;
										cout << "sent" << endl;
									}
								}
								delete[] raw;
							}
						}
					}
				}
				catch (out_of_range) { // su proxy kazkas ivede netinkamus x ir y
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "sign_edit") {
			if (a_.size() != 13) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int x_ = atoi(a_[i_ + 2].c_str()), y_ = atoi(a_[i_ + 5].c_str());
			string tekstas = a_[i_ + 8];
			if (tekstas.size() > 128) break;
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				try {
					WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
					if (block_->txt == tekstas or block_->fg == 0 or items.at(block_->fg).blockType != BlockTypes::SIGN) break;
					if (not world_->open_to_public and world_->owner_name != pInfo(p_)->tankIDName and not pInfo(p_)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end())) {
						if (block_->locked) {
							WorldBlock* check_lock = &world_->blocks.at(block_->lock_origin);
							if (not world_->open_to_public and check_lock->owner_name != pInfo(p_)->tankIDName and world_->owner_name.empty() and (find(check_lock->admins.begin(), check_lock->admins.end(), pInfo(p_)->tankIDName) == check_lock->admins.end())) break;
						} else {
							break;
						}
					}
					if (block_->fg == 1684) {
						transform(tekstas.begin(), tekstas.end(), tekstas.begin(), ::toupper);
						block_->door_id = tekstas;
					}
					else {
						block_->txt = tekstas;
						PlayerMoving data_{};
						data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
						BYTE* raw = packPlayerMoving(&data_, 112 + tekstas.size());
						BYTE* blc = raw + 56;
						form_visual(blc, *block_, *world_, p_, false);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 112 + tekstas.size(), ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[] raw, blc;
						if (block_->locked) {
							upd_lock(*block_, *world_, p_);
						}
					}
				}
				catch (out_of_range) { // su proxy kazkas ivede netinkamus x ir y
					break;
				}
			}
			break;
		}
		else if (a_.at(i_) == "trash_item" or a_.at(i_) == "drop_item" or a_.at(i_) == "trash_item2") {
			if (a_.size() != 10 and a_.at(i_) != "trash_item2") break;
			if (a_.at(i_) == "trash_item2" and a_.size() != 11) break;
			if (not isdigit(a_[i_ + 2][0]) or not isdigit(a_[i_ + 5][0])) break;
			int id_ = atoi(a_[i_ + 2].c_str()), c_ = atoi(a_[i_ + 5].c_str());
			int count = 0;
			if (id_ >= items.size() or id_ == 18 or id_ == 32 or id_ == 6336) break;
			string name_ = pInfo(p_)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds.at(p - worlds.begin());
				c_ = c_ * -1;
				if (a_.at(i_) == "trash_item" or a_.at(i_) == "trash_item2") {
					if (a_.at(i_) == "trash_item" and items.at(id_).untradeable) {
						int has_ = 0;
						modify_inventory(p_, id_, has_);
						if (has_ < c_) break;
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Recycle`` " + to_string(c_ * -1) + " `w" + items.at(id_).name + "``|left|" + to_string(id_) + "|\nembed_data|itemID|" + to_string(id_) + "\nembed_data|count|" + to_string(c_ * -1) + "\nadd_textbox|You are recycling an `9UNTRADEABLE`` item. Are you absolutely sure you want to do this? There is no way to get the item back if you select yes.|left|\nend_dialog|trash_item2|NO!|Yes, I am sure|");
						p.CreatePacket(p_);
						break;
					}
					if (modify_inventory(p_, id_, c_) == 0) {
						packet_(p_, "action|play_sfx\nfile|audio/trash.wav\ndelayMS|0");
						a_[i_ + 5].erase(0, min(a_[i_ + 5].find_first_not_of('0'), a_[i_ + 5].size() - 1));
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert(a_[i_ + 5] + " `w" + items.at(id_).name + "`` trashed.");
						p.CreatePacket(p_);
						break;
					}
					break;
				}
				if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 4758) != world_->active_jammers.end()) {
					if (world_->owner_name != pInfo(p_)->tankIDName and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(p_)->netID);
						p.Insert("The Mini-Mod says no dropping items in this world!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(p_);
						break;
					}
				}
				if (items.at(id_).untradeable or id_ == 1424) {
					gamepacket_t p;
					p.Insert("OnTextOverlay");
					p.Insert("You can't drop that.");
					p.CreatePacket(p_);
					break;
				}
				string name_ = pInfo(p_)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds[p - worlds.begin()];
					WorldDrop drop_{};
					drop_.id = id_;
					drop_.count = atoi(a_[i_ + 5].c_str());
					drop_.uid = uint16_t(world_->drop.size()) + 1;
					try {
						int a_ = rand() % 12;
						drop_.x = (pInfo(p_)->state == 16 ? pInfo(p_)->x - (a_ + 20) : (pInfo(p_)->x + 20) + a_);
						drop_.y = pInfo(p_)->y + rand() % 16;
						BlockTypes type_ = FOREGROUND;
						WorldBlock* block_ = &world_->blocks.at((pInfo(p_)->state == 16 ? drop_.x / 32 : round((double)drop_.x / 32)) + (drop_.y / 32 * 100));
						if (items.at(block_->fg).collisionType == 1 || block_->fg == 6 || items.at(block_->fg).entrance || items.at(block_->fg).toggleable and is_false_state(world_->blocks.at((pInfo(p_)->state == 16 ? drop_.x / 32 : round((double)drop_.x / 32)) + (drop_.y / 32 * 100)), 0x00400000)) {
							gamepacket_t p;
							p.Insert("OnTextOverlay");
							p.Insert(items.at(block_->fg).blockType == BlockTypes::MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
							p.CreatePacket(p_);
							break;
						}
						int count_ = 0;
						for (int i_ = 0; i_ < world_->drop.size(); i_++) {
							if (abs(world_->drop.at(i_).y - drop_.y) <= 16 and abs(world_->drop.at(i_).x - drop_.x) <= 16) {
								count_ += 1;
							}
						} if (count_ > 20) {
							gamepacket_t p;
							p.Insert("OnTextOverlay");
							p.Insert("You can't drop that here, find an emptier spot!");
							p.CreatePacket(p_);
							break;
						}
					}
					catch (out_of_range) {
						gamepacket_t p;
						p.Insert("OnTextOverlay");
						p.Insert("You can't drop that here, face somewhere with open space.");
						p.CreatePacket(p_);
						break;
					} if (modify_inventory(p_, id_, c_) == 0) {
						dropas_(world_, drop_, pInfo(p_)->netID);
					}
				}
			}
			break;
		}
		else if (a_.at(i_) == "growid_apply") {
			if (a_.size() != 13) break;
			string user_ = a_.at(i_ + 2), pass_ = a_.at(i_ + 4), pass_verify_ = a_.at(i_ + 6), email_ = a_.at(i_ + 8);
			try {
				string path_ = "players/" + user_ + "_.json";
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				bool bad_name = false;
				string check_user = user_;
				transform(check_user.begin(), check_user.end(), check_user.begin(), ::toupper);
				for (int i = 0; i < swear_words.size(); i++) {
					if (check_user.find(swear_words[i]) != string::npos) {
						bad_name = true;
						break;
					}
				}
				bool max_acc = false;
				int count__ = 0;
				string rid_check = "db/accounts/rid/" + pInfo(p_)->rid + ".txt";
				if (_access_s(rid_check.c_str(), 0) == 0) {
					string acc_count;
					ifstream f_(rid_check, ifstream::binary);
					f_ >> acc_count;
					f_.close();
					int count_ = explode("|", acc_count).size() - 1;
					if (count_ > 0) count__ += count_;
				}
				string mac_check = "db/accounts/mac/" + pInfo(p_)->mac + ".txt";
				if (_access_s(mac_check.c_str(), 0) == 0) {
					string acc_count;
					ifstream f_(mac_check, ifstream::binary);
					f_ >> acc_count;
					f_.close();
					int count_ = explode("|", acc_count).size() - 1;
					if (count_ > 0) count__ += count_;
				}
				string ip_check = "db/accounts/ip/" + pInfo(p_)->ip + ".txt";
				if (_access_s(ip_check.c_str(), 0) == 0) {
					string acc_count;
					ifstream f_(ip_check, ifstream::binary);
					f_ >> acc_count;
					f_.close();
					int count_ = explode("|", acc_count).size() - 1;
					if (count_ > 0) count__ += count_;
				}
				if (count__ > 3) max_acc = true;
				if (max_acc)
					p.Insert(r_dialog("`4Oops!``  You have too much accounts created.", user_, pass_, pass_verify_, email_));
				else if (bad_name)
					p.Insert(r_dialog("`4Oops!``  Your `wGrowID`` cannot contain `$swear words``.", user_, pass_, pass_verify_, email_));
				else if (not email(email_))
					p.Insert(r_dialog("`4Oops!``  Look, if you'd like to be able try retrieve your password if you lose it, you'd better enter a real email.  We promise to keep your data 100% private and never spam you.", user_, pass_, pass_verify_, email_));
				else if (user_.size() < 3 or user_.size() > 18)
					p.Insert(r_dialog("`4Oops!``  Your `wGrowID`` must be between `$3`` and `$18`` characters long.", user_, pass_, pass_verify_, email_));
				else if (pass_.size() < 8 or pass_.size() > 18)
					p.Insert(r_dialog("`4Oops!``  Your password must be between `$8`` and `$18`` characters long.", user_, pass_, pass_verify_, email_));
				else if (pass_ != pass_verify_)
					p.Insert(r_dialog("`4Oops!``  Passwords don't match.  Try again.", user_, pass_, pass_verify_, email_));
				else if (special_char(user_))
					p.Insert(r_dialog("`4Oops!`` You can only use letters and numbers in your GrowID.", user_, pass_, pass_verify_, email_));
				else if (_access_s(path_.c_str(), 0) == 0)
					p.Insert(r_dialog("`4Oops!`` The name `w" + user_ + "`` is so cool someone else has already taken it.  Please choose a different name.", user_, pass_, pass_verify_, email_));
				else {
					// account logs
					WriteTxt("db/accounts/rid/" + pInfo(p_)->rid, "|" + user_);
					WriteTxt("db/accounts/mac/" + pInfo(p_)->mac, "|" + user_);
					WriteTxt("db/accounts/ip/" + pInfo(p_)->ip, "|" + user_);
					// account logs
					time_t s__;
					s__ = time(NULL);
					int days_ = int(s__) / (60 * 60 * 24);
					pInfo(p_)->account_created = days_;
					pInfo(p_)->playtime = s__;
					pInfo(p_)->inv.push_back({ 18, 1 }), pInfo(p_)->inv.push_back({ 32, 1 }), pInfo(p_)->inv.push_back({ 6336, 1 });
					for (int i_ = 3; i_ <= 16; i_++) { // default inv dydis
						Items itm_{};
						itm_.id = 0, itm_.count = 0;
						pInfo(p_)->inv.push_back(itm_);
					}
					int count = 200;
					modify_inventory(p_, 9640, count = 1);//newbie award
					modify_inventory(p_, 954, count = 20);//newbie award
					modify_inventory(p_, 7164, count = 4);//newbie award
					modify_inventory(p_, 3898, count = 1);//newbie award
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wGrowID GET!``|left|206|\nadd_textbox|A `wGrowID`` with the log on of `w" + user_ + "`` created.  Write it and your password down as they will be required to log on from now on!|left|\nend_dialog|growid_apply|Continue||");
					pInfo(p_)->tankIDName = user_, pInfo(p_)->tankIDPass = pass_, pInfo(p_)->email = email_;
					{
						gamepacket_t p;
						p.Insert("SetHasGrowID");
						p.Insert(1);
						p.Insert(user_);
						p.Insert(pass_);
						p.CreatePacket(p_);
					}
					world_menu(p_);
					save_player(pInfo(p_), false);
				}
				p.CreatePacket(p_);
			}
			catch (exception) {
				cout << "something failed" << endl;
			}
			break;
		}
	}
}

void player_login(ENetPeer* peer, string cch) {
	vector<string> a_ = explode("|", replace_str(cch, "\n", "|"));
	// cia yra du budai pirmas greitesnis naudoti a_.at() o antras ciklas, bet pasirinkau cikla nes tai gali bet kada pasikeisti pvz atsiras naujas dalykas tame login pakete
	for (int i_ = 0; i_ < a_.size(); i_++) {
		if (a_.at(i_) == "tankIDName") { // zaidejo tankidname
			pInfo(peer)->tankIDName = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "tankIDPass") { // zaidejo tankIDPass
			pInfo(peer)->tankIDPass = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "requestedName") { // zaidejo requestedName
			pInfo(peer)->requestedName = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "f") {
		}
		else if (a_.at(i_) == "protocol") {
		}
		else if (a_.at(i_) == "game_version") {
		}
		else if (a_.at(i_) == "fz") {
		}
		else if (a_.at(i_) == "lmode") {
		}
		else if (a_.at(i_) == "cbits") {
		}
		else if (a_.at(i_) == "player_age") {
		}
		else if (a_.at(i_) == "GDPR") {
		}
		else if (a_.at(i_) == "meta") {
			pInfo(peer)->meta = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "fhash") {
		}
		else if (a_.at(i_) == "rid") {
			pInfo(peer)->rid = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "platformID") {
		}
		else if (a_.at(i_) == "deviceVersion") {
		}
		else if (a_.at(i_) == "country") {
			pInfo(peer)->country = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "hash") {
		}
		else if (a_.at(i_) == "mac") {
			pInfo(peer)->mac = a_.at(i_ + 1);
		}
		else if (a_.at(i_) == "wk") {
		}
		else if (a_.at(i_) == "zf") {
		}
	}
	const char* mac = pInfo(peer)->mac.c_str();
	//pInfo(peer)->rid == "" || 
	//if (pInfo(peer)->mac == "" || !isValidMacAddress(mac) || pInfo(peer)->meta != "b©©©       .......文字化け; IPA: [mod͡ʑibake.  譁�蟄怜喧縺   ﷽﷽﷽﷽﷽﷽ ﷽L̤̱̹̬͔̘̈̊̑ͯ̔͋͢͞?̡͎͎̬̫̯̭͍͕̬͎͙͔͓͖̰̺̭̭̭͛̉̃͂̚͘͝͠") {
		//packet_(peer, "action|log\nmsg|`4Server protection:`` Something is not valid.");
		//packet_(peer, "action|logon_fail");
		//enet_peer_disconnect_later(peer, 0);}
	 if (not pInfo(peer)->tankIDName.empty()) {
		switch (auth_(peer)) {
		case -1: /*blogas pass arba nera acc*/
		{
			packet_(peer, "`4Unable to log on: `oThat `wGrowID`` doesn't seem valid, or the password is wrong. If you don't have one, press `wCancel``, un-check `w'I have a GrowID'``, then click `wConnect``.", "Retrieve lost password");
			packet_(peer, "action|logon_fail");
			enet_peer_disconnect_later(peer, 0);
			return;
		}
		default:
		{
			break;
		}
		} if (pInfo(peer)->b_t + pInfo(peer)->b_s < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
			if (not pInfo(peer)->b_r.empty() or not pInfo(peer)->b_b.empty()) {
				packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
				gamepacket_t p;
				p.Insert("OnConsoleMessage");
				p.Insert("`oYou are no longer banned. Now be good! (`$Ban`` mod removed)");
				p.CreatePacket(peer);
			}
			pInfo(peer)->b_t = 0;
			pInfo(peer)->b_s = 0;
			pInfo(peer)->b_b = "";
			pInfo(peer)->b_r = "";
		}
		else {
			pInfo(peer)->name_color = (pInfo(peer)->dev == 1 ? "`6@" : (pInfo(peer)->mod == 1) ? "`#@" : "`0");
			long long int time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			int actualseconds = (pInfo(peer)->b_t + pInfo(peer)->b_s - time) / 1000;
			string time_counted = "";
			if (actualseconds / 86400 >= 1) {
				time_counted += "" + to_string(actualseconds / (24 * 3600)) + " days, ";
				actualseconds = actualseconds % (24 * 3600);
			}
			if (actualseconds / 3600 >= 1) {
				time_counted += "" + to_string(actualseconds / 3600) + " hours, ";
				actualseconds %= 3600;
			}
			if (actualseconds / 60 >= 1) {
				time_counted += "" + to_string(actualseconds / 60) + " mins, ";
				actualseconds %= 60;
			}
			time_counted += "" + to_string(actualseconds) + " secs";
			packet_(peer, "action|log\nmsg|CT:[S]_ `4Sorry, this account, device or location has been temporarily suspended.``", "");
			packet_(peer, "action|log\nmsg|CT:[S]_ `4Ban Reason: " + pInfo(peer)->b_r + "``", "");
			packet_(peer, "action|log\nmsg|CT:[S]_ If you didn't do anything wrong, it could be because you're playing from the same place or on the same device as someone who did. Contact support at `5https://privategt.com/discord`` if you have any questions.", "");
			packet_(peer, "action|log\nmsg|CT:[S]_ This is a temporary ban caused by " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` and will be removed in `0" + time_counted + "``. If that's not your name, try playing from another location or device to fix it.", "");
			packet_(peer, "action|logon_fail");
			enet_peer_disconnect_later(peer, 0);
		}
	}
	gamepacket_t p;
	p.Insert("OnSuperMainStartAcceptLogonHrdxs47254722215a");
	p.Insert(item_hash);
	p.Insert("ubistatic-a.akamaihd.net");
	p.Insert("0098/50018/cache/");
	p.Insert("cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster");
	p.Insert("proto=149|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|wing_week_day=0|server_tick=113761304|clash_active=1|drop_lavacheck_faster=1|isPayingUser=0|usingStoreNavigation=1|enableInventoryTab=1|bigBackpack=1|");
	p.CreatePacket(peer);
}
void add_peer_xp(ENetPeer* peer, int amount) {
	pInfo(peer)->xp += amount;
	int required = 50 * ((pInfo(peer)->level * pInfo(peer)->level) + 2);
	//for (int i = 0; i < 1; i++) {
		if (pInfo(peer)->xp >= 50 * ((pInfo(peer)->level * pInfo(peer)->level) + 2)) {
			pInfo(peer)->level++;
			pInfo(peer)->xp -= required;
		//	if (pInfo(peer)->xp >= 50 * ((pInfo(peer)->level * pInfo(peer)->level) + 2)) i--;
			pInfo(peer)->gems += 500;
			{
				gamepacket_t p;
				p.Insert("OnSetBux");
				p.Insert(pInfo(peer)->gems);
				p.Insert(0);
				p.CreatePacket(peer);
			}
			gamepacket_t p, p2;
			p.Insert("OnTalkBubble");
			p.Insert(pInfo(peer)->netID);
			p.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` is now level " + to_string(pInfo(peer)->level) + "!");
			p.Insert(0), p.Insert(0);
			p2.Insert("OnConsoleMessage");
			p2.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` is now level " + to_string(pInfo(peer)->level) + "!");
			PlayerMoving data_{};
			data_.packetType = 17;
			data_.netID = 46;
			data_.YSpeed = 46;
			data_.x = pInfo(peer)->x + 16;
			data_.y = pInfo(peer)->y + 16;
			BYTE* raw = packPlayerMoving(&data_);
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
				p.CreatePacket(currentPeer);
				p2.CreatePacket(currentPeer);
				send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			}
			delete[] raw;
		}
	//}
}
int choose_random(const int id_) {
	vector<int> ids_;
	int a_ = 0;
	while (items.at(id_ + a_).properties & Property_RandomGrow) {
		if (items.at(id_ + a_).blockType != BlockTypes::SEED) ids_.push_back(id_ + a_);
		a_++;
	}
	a_ = 0;
	while (items.at(id_ - a_).properties & Property_RandomGrow) {
		if (items.at(id_ - a_).blockType != BlockTypes::SEED) ids_.push_back(id_ - a_);
		a_++;
	}
	return ids_[rand() % ids_.size()];
}
bool use_mag(World* world_, WorldDrop drop_, int x_, int y_) {
	for (int i_ = 0; i_ < world_->machines.size(); i_++) {
		WorldMachines machine_ = world_->machines.at(i_);
		if (machine_.target_item == drop_.id and machine_.enabled) {
			if (machine_.id == 6948 or machine_.id == 5638 or machine_.id == 6946) {
				WorldBlock* itemas = &world_->blocks.at(machine_.x + (machine_.y * 100));
				if (itemas->pr < (machine_.id == 6948 or machine_.id == 6946 ? 1500 : 5000)) {
					PlayerMoving data_{};
					data_.packetType = 19, data_.netID = -1, data_.plantingTree = 0;
					data_.x = machine_.x * 32 + 16, data_.y = machine_.y * 32 + 16;
					data_.XSpeed = x_ * 32 + 16, data_.YSpeed = y_ * 32 + 16;
					data_.punchX = drop_.id;
					BYTE* raw = packPlayerMoving(&data_);
					raw[3] = 6;
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == world_->name) {
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					delete[]raw;
					itemas->pr += drop_.count;
					if (itemas->pr >= (machine_.id == 6948 or machine_.id == 6946 ? 1500 : 5000) or itemas->pr == drop_.count) {
						PlayerMoving data_{};
						data_.packetType = 5, data_.punchX = machine_.x, data_.punchY = machine_.y, data_.characterState = 0x8;
						BYTE* raw = packPlayerMoving(&data_, 112);
						BYTE* blc = raw + 56;
						form_visual(blc, *itemas, *world_, NULL, false);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[] raw, blc;
						if (itemas->locked) {
							upd_lock(*itemas, *world_, NULL);
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}
bool harvest_seed(World* world_, WorldBlock* block_, int x_, int y_, int drop_count, int net_id = -1, ENetPeer* p_ = NULL) {
	bool seed_drop = false;
	if (items.at(block_->fg - 1).rarity != 999 and items.at(block_->fg - 1).blockType != BlockTypes::CLOTHING and rand() % 100 < 30) {
		seed_drop = true;
		WorldDrop drop_seed_{};
		drop_seed_.id = block_->fg;
		drop_seed_.count = 1;
		drop_seed_.uid = uint16_t(world_->drop.size()) + 1;
		drop_seed_.x = (x_ * 32) + rand() % 17;
		drop_seed_.y = (y_ * 32) + rand() % 17;
		if (not use_mag(world_, drop_seed_, x_, y_)) dropas_(world_, drop_seed_);
	}
	WorldDrop drop_block_{};
	if (items.at(block_->fg).properties & Property_RandomGrow) {
		drop_block_.id = choose_random(block_->fg);
	}
	else
		drop_block_.id = block_->fg - 1;
	drop_block_.count = drop_count;
	drop_block_.uid = uint16_t(world_->drop.size()) + 1;
	drop_block_.x = (x_ * 32) + rand() % 17;
	drop_block_.y = (y_ * 32) + rand() % 17;
	if (not use_mag(world_, drop_block_, x_, y_)) dropas_(world_, drop_block_);
	if (items.at(block_->fg - 1).max_gems != 0) {
		if (p_ != NULL) {
			add_peer_xp(p_, (items.at(block_->fg).rarity / 5 > 0 ? items.at(block_->fg).rarity / 5 : 1));
		}
		int c_ = rand() % (items.at(block_->fg - 1).max_gems + 1);
		if (p_ != NULL) {
			if (has_playmod(pInfo(p_), "Lucky") and ((rand() % 100) + 1) <= 30) {
				PlayerMoving data_{};
				data_.packetType = 17;
				data_.netID = 125;
				data_.YSpeed = 125;
				data_.x = x_ * 32 + 16;
				data_.y = y_ * 32 + 16;
				BYTE* raw = packPlayerMoving(&data_);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_->name) {
						send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
					}
				}
				delete[] raw;
				c_ += (rand() % 5) + 1;
			}
		} if (c_ != 0) {
			gems_(world_, c_, x_ * 32, y_ * 32);
		}
	}
	PlayerMoving data_{};
	data_.packetType = 12, data_.netID = net_id, data_.plantingTree = block_->fg;
	data_.punchX = x_, data_.punchY = y_;
	int32_t item = -1;
	BYTE* raw = packPlayerMoving(&data_);
	memcpy(raw + 8, &item, 4);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == world_->name) {
			send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete[]raw;
	return seed_drop;
}
void punch_tile(ENetPeer* peer, int x, int y, int t_, int n_, int net_, int state_, bool tree_ = false, int count_ = 1) {
	PlayerMoving data{ net_, 0, t_, state_, n_, x, y, 0, (float)x, (float)y, 0, 0 };
	BYTE* p_ = packPlayerMoving(&data);
	p_[2] = 0, p_[3] = tree_ ? count_ : 0;
	int32_t item = pInfo(peer)->hand;
	memcpy(p_ + 8, &item, 4);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == pInfo(peer)->world)
			send_raw(currentPeer, 4, p_, 56, ENET_PACKET_FLAG_RELIABLE);
	}
	delete[]p_;
}
void DoorMove(ENetPeer* peer, int x1, int y1) {
	string name_ = pInfo(peer)->world;
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	World* world_ = &worlds.at(p - worlds.begin());
	int counted = x1 + (y1 + 1) * 100;
	int counted2 = x1 + (y1 * 100);
	for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
		int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
		if (world_->blocks.at(i_).fg == 6) {
			world_->blocks.at(i_).fg = 0;
			punch_tile(peer, i_ % xSize, i_ / xSize, 0x3, 0, 0, 0, 1);
		}
		if (i_ < 5400) {
			if (world_->blocks.at(i_).fg == 8) {
				world_->blocks.at(i_).fg = 0;
				punch_tile(peer, i_ % xSize, i_ / xSize, 0x3, 0, 0, 0, 1);
			}
		}
	}
	world_->blocks[x1 + (y1 * 100)].fg = 6;
	world_->blocks[x1 + (y1 + 1) * 100].fg = 8;
	punch_tile(peer, x1, y1, 0x3, 6, 0, 0, 1);
	punch_tile(peer, x1, y1 + 1, 0x3, 8, 0, 0, 1);
}
void LockMove(ENetPeer* peer, int wx1, int wy1) {
	string name_ = pInfo(peer)->world;
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	World* world_ = &worlds.at(p - worlds.begin());
	int lock = 242;
	for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
		int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
		if (items.at(world_->blocks.at(i_).fg).blockType == BlockTypes::LOCK) {
			lock = world_->blocks.at(i_).fg;
			world_->blocks.at(i_).fg = 0;
			punch_tile(peer, i_ % xSize, i_ / xSize, 0x3, 0, 0, 0, 1);
		}
	}
	world_->blocks[wx1 + (wy1) * 100].fg = lock;
	punch_tile(peer, wx1, wy1, 0x3, lock, 0, 0, 1);
}
void plant_(World* world_, ENetPeer* peer, WorldBlock* block_, int x_, int y_, int p_, bool upd_visual = true, bool mag_place = false) {
	block_->fruit = items.at(block_->fg).rarity == 999 ? 1 : (rand() % 4) + 1;
	if (upd_visual)
		punch_tile(peer, x_, y_, 0x3, p_, mag_place ? -1 : pInfo(peer)->netID, 0x0, 1, block_->fruit);
	block_->planted = time(nullptr) - (items.at(p_).growTime / 2);
	PlayerMoving data_{};
	data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
	BYTE* raw = packPlayerMoving(&data_, 112);
	BYTE* blc = raw + 56;
	WorldBlock* block_s = &world_->blocks.at(x_ + (y_ * 100));
	form_visual(blc, *block_s, *world_, peer, false);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (pInfo(currentPeer)->world == world_->name) {
			send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete[] raw, blc;
	if (block_->locked) {
		upd_lock(*block_, *world_, peer);
	}
}
bool ar_turi_noclipa(World* world_, int x, int y, WorldBlock* target_, ENetPeer* p_) {
	try {
		for (int i = 0; i <= 2; i++) {
			vector<int> new_tiles{};
			if (items.at(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)).fg).collisionType != 1 or items.at(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)).fg).entrance or items.at(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)).fg).toggleable) {
				if (items.at(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)).fg).entrance and is_false_state(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)), 0x00800000) and world_->owner_name != pInfo(p_)->tankIDName and not world_->open_to_public and not world_->owner_name.empty() and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
				}
				else if (items.at(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)).fg).toggleable and is_false_state(world_->blocks.at((int)x / 32 + ((int)y / 32 * 100)), 0x00400000)) {
				}
				else {
					new_tiles.push_back((int)x / 32 + ((int)y / 32 * 100));
				}
			} int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
			vector<WorldBlock> shadow_copy = world_->blocks;
			for (int i2 = 0; i2 < new_tiles.size(); i2++) {
				int x_ = new_tiles.at(i2) % 100, y_ = new_tiles.at(i2) / 100;
				if (&world_->blocks.at(x_ + (y_ * 100)) == target_ and items.at(shadow_copy.at(x_ + (y_ * 100)).fg).collisionType != 1) {
					return false;
				} if (x_ < 99 and items.at(shadow_copy.at(x_ + 1 + (y_ * 100)).fg).collisionType != 1 or x_ < 99 and items.at(shadow_copy.at(x_ + 1 + (y_ * 100)).fg).entrance or x_ < 99 and items.at(shadow_copy.at(x_ + 1 + (y_ * 100)).fg).toggleable) {
					if (items.at(shadow_copy.at(x_ + 1 + (y_ * 100)).fg).entrance and is_false_state(shadow_copy.at(x_ + 1 + (y_ * 100)), 0x00800000) and world_->owner_name != pInfo(p_)->tankIDName and not world_->open_to_public and not world_->owner_name.empty() and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
					}
					else if (items.at(shadow_copy.at(x_ + 1 + (y_ * 100)).fg).toggleable and is_false_state(shadow_copy.at(x_ + 1 + (y_ * 100)), 0x00400000)) {
					}
					else {
						if (not shadow_copy.at(x_ + 1 + (y_ * 100)).scanned) {
							shadow_copy.at(x_ + 1 + (y_ * 100)).scanned = true;
							new_tiles.push_back(x_ + 1 + (y_ * 100));
						}
					}
				} if (x_ > 0 and items.at(shadow_copy.at(x_ - 1 + (y_ * 100)).fg).collisionType != 1 or x_ > 0 and items.at(shadow_copy.at(x_ - 1 + (y_ * 100)).fg).entrance or x_ > 0 and items.at(shadow_copy.at(x_ - 1 + (y_ * 100)).fg).toggleable) {
					if (items.at(shadow_copy.at(x_ - 1 + (y_ * 100)).fg).entrance and is_false_state(shadow_copy.at(x_ - 1 + (y_ * 100)), 0x00800000) and world_->owner_name != pInfo(p_)->tankIDName and not world_->open_to_public and not world_->owner_name.empty() and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
					}
					else if (items.at(shadow_copy.at(x_ - 1 + (y_ * 100)).fg).toggleable and is_false_state(shadow_copy.at(x_ - 1 + (y_ * 100)), 0x00400000)) {
					}
					else {
						if (not shadow_copy.at(x_ - 1 + (y_ * 100)).scanned) {
							shadow_copy.at(x_ - 1 + (y_ * 100)).scanned = true;
							new_tiles.push_back(x_ - 1 + (y_ * 100));
						}
					}
				} if (y_ < 59 and items.at(shadow_copy.at(x_ + ((y_ + 1) * 100)).fg).collisionType != 1 or y_ < 59 and items.at(shadow_copy.at(x_ + ((y_ + 1) * 100)).fg).entrance or y_ < 59 and items.at(shadow_copy.at(x_ + ((y_ + 1) * 100)).fg).toggleable) {
					if (items.at(shadow_copy.at(x_ + ((y_ + 1) * 100)).fg).entrance and is_false_state(shadow_copy.at(x_ + ((y_ + 1) * 100)), 0x00800000) and world_->owner_name != pInfo(p_)->tankIDName and not world_->open_to_public and not world_->owner_name.empty() and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
					}
					else if (items.at(shadow_copy.at(x_ + ((y_ + 1) * 100)).fg).toggleable and is_false_state(shadow_copy.at(x_ + ((y_ + 1) * 100)), 0x00400000)) {
					}
					else {
						if (not shadow_copy.at(x_ + ((y_ + 1) * 100)).scanned) {
							shadow_copy.at(x_ + ((y_ + 1) * 100)).scanned = true;
							new_tiles.push_back(x_ + ((y_ + 1) * 100));
						}
					}
				} if (y_ > 0 and items.at(shadow_copy.at(x_ + ((y_ - 1) * 100)).fg).collisionType != 1 or y_ > 0 and items.at(shadow_copy.at(x_ + 1 + ((y_ - 1) * 100)).fg).entrance or y_ > 0 and items.at(shadow_copy.at(x_ + 1 + ((y_ - 1) * 100)).fg).toggleable) {
					if (items.at(shadow_copy.at(x_ + ((y_ - 1) * 100)).fg).entrance and is_false_state(shadow_copy.at(x_ + ((y_ - 1) * 100)), 0x00800000) and world_->owner_name != pInfo(p_)->tankIDName and not world_->open_to_public and not world_->owner_name.empty() and find(world_->admins.begin(), world_->admins.end(), pInfo(p_)->tankIDName) == world_->admins.end()) {
					}
					else if (items.at(shadow_copy.at(x_ + ((y_ - 1) * 100)).fg).toggleable and is_false_state(shadow_copy.at(x_ + ((y_ - 1) * 100)), 0x00400000)) {
					}
					else {
						if (not shadow_copy.at(x_ + ((y_ - 1) * 100)).scanned) {
							shadow_copy.at(x_ + ((y_ - 1) * 100)).scanned = true;
							new_tiles.push_back(x_ + ((y_ - 1) * 100));
						}
					}
				}
			}
		}
		return true;
	}
	catch (out_of_range) {
		return false;
	}
}
bool edit_tile(ENetPeer* peer, int x_, int y_, int p_, bool mag_place = false) {
	if (x_ < 0 or x_ >= 100 or y_ < 0 or y_ >= 60 or p_ < 0 or p_ >= items.size()) return false;
	string name_ = pInfo(peer)->world;
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	if (p != worlds.end()) {
		World* world_ = &worlds.at(p - worlds.begin());
		try {
			WorldBlock* block_ = &world_->blocks.at(x_ + (y_ * 100));
			uint16_t t_ = (block_->fg ? block_->fg : block_->bg);
			switch (p_) {
			case 18:
			{
				if (t_ == 0) {
					break;
				}
				if (items.at(t_).properties & Property_Mod and not pInfo(peer)->dev) {
					packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(peer)->netID);
					p.Insert(items.at(t_).blockType == BlockTypes::MAIN_DOOR ? "(stand over and punch to use)" : "It's too strong to break.");
					p.Insert(0);
					p.Insert(1);
					p.CreatePacket(peer);
					break;
				}
				else if (t_ == 758) {
					if (pInfo(peer)->i758 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->i758 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						int get37 = rand() % 37;
						string color = "";
						if (get37 == 36 || get37 == 34 || get37 == 32 || get37 == 30 || get37 == 27 || get37 == 25 || get37 == 23 || get37 == 21 || get37 == 19 || get37 == 18 || get37 == 16 || get37 == 12 || get37 == 9 || get37 == 7 || get37 == 5 || get37 == 3 || get37 == 1) color = "`4";
						else if (get37 == 0) color = "`2";
						else color = "`b";
						string wheel = "`7[``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` spun the wheel and got " + color + to_string(get37) + "``!`7]``";
						gamepacket_t p(2000), p2(2000);
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert(wheel);
						p.Insert(0);
						p2.Insert("OnConsoleMessage");
						p2.Insert(wheel);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == pInfo(peer)->world) {
								p.CreatePacket(currentPeer);
								p2.CreatePacket(currentPeer);
							}
						}
						punch_tile(peer, x_, y_, 0x8, 0, pInfo(peer)->netID, 0x0);
					}
				}
				else if (t_ == 756) {
					if (pInfo(peer)->i756 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->i756 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						int get1 = rand() % 10;
						string wheel = "`7[``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` " + (get1 == 1 ? "`2wins at slots!`" : "`4loses at slots.`") + "``7]``";
						gamepacket_t p(2000), p2(2000), p3(2000);
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert(wheel);
						p.Insert(0);
						p2.Insert("OnConsoleMessage");
						p2.Insert(wheel);
						p3.Insert("OnPlayPositioned");
						p3.Insert(get1 == 1 ? "audio/slot_win.wav" : "audio/slot_lose.wav");
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == pInfo(peer)->world) {
								p.CreatePacket(currentPeer);
								p2.CreatePacket(currentPeer);
								p3.CreatePacket(currentPeer);
							}
						}
						punch_tile(peer, x_, y_, 0x8, 0, pInfo(peer)->netID, 0x0);
					}
				}
				else if (t_ == 1482 || t_ == 2252 || t_ == 7864 || t_ == 11434) {
					struct tm newtime;
					time_t now = time(0);
					localtime_s(&newtime, &now);
					gamepacket_t p;
					p.Insert("OnTalkBubble");
					p.Insert(pInfo(peer)->netID);
					p.Insert("It's " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min) + "") + " " + (newtime.tm_hour >= 12 ? "PM" : "AM") + " on " + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "");
					p.Insert(0);
					p.Insert(1);
					p.CreatePacket(peer);
				}
				if (items.at(t_).toggleable or items.at(t_).blockType == BlockTypes::CHEMICAL_COMBINER) {
					if (block_->flags & 0x00800000 or world_->owner_name == pInfo(peer)->tankIDName or find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end() or world_->open_to_public or pInfo(peer)->dev) {
						block_->flags = (block_->flags & 0x00400000 ? block_->flags ^ 0x00400000 : block_->flags | 0x00400000);
						if (t_ == 226) {
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							if (block_->flags & 0x00400000) {
								p.Insert("Signal jammer enabled. This world is now `4hidden`` from the universe.");
							}
							else {
								p.Insert("Signal jammer disabled. This world is `2visible`` to the universe.");
							}
							p.CreatePacket(peer);
						} if (t_ == 226 or t_ == 3616 or t_ == 1276 or t_ == 1278 or t_ == 4758 or t_ == 3750 or t_ == 4992 or t_ == 3072 or t_ == 4884) {
							if (block_->flags & 0x00400000) {
								world_->active_jammers.push_back(t_);
							}
							else {
								world_->active_jammers.erase(remove(world_->active_jammers.begin(), world_->active_jammers.end(), t_), world_->active_jammers.end());
							}
						}
					}
				}
				// nuo cia non access negales nieko padaryt:
				if (items.at(t_).toggleable) {
					string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (block_->flags & 0x00800000 and not world_->owner_name.empty() and owner_name != user_name and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end() and not pInfo(peer)->dev) {
						gamepacket_t p(0, pInfo(peer)->netID);
						p.Insert("OnPlayPositioned");
						p.Insert("audio/punch_locked.wav");
						if (not pInfo(peer)->invis) {
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == name_) {
									p.CreatePacket(currentPeer);
								}
							}
						}
						else {
							p.CreatePacket(peer);
						}
						punch_tile(peer, x_, y_, 0x8, 0, pInfo(peer)->netID, 16);
						return true;
					}
				}
				if (items.at(t_).properties & Property_Public) { cout << "public block break" << endl; }
				else {
					if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
						if (block_->owner_name != pInfo(peer)->tankIDName) {
							if (items.at(t_).blockType == BlockTypes::LOCK) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								if (block_->open_to_public)
									p.Insert(block_->owner_named + "``'s `$" + items.at(t_).name + "``. (`wOpen to public``)");
								else if (find(block_->admins.begin(), block_->admins.end(), pInfo(peer)->tankIDName) != block_->admins.end())
									p.Insert(block_->owner_named + "``'s `$" + items.at(t_).name + "``. (`wAccess granted``)");
								else
									p.Insert(block_->owner_named + "``'s `$" + items.at(t_).name + "``. (`4No access``)");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
								if (not pInfo(peer)->dev) {
									{
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
									}
									return true;
								}
							}
						}
					}
					else if (block_->locked) {
						WorldBlock* block2_ = &world_->blocks.at(block_->lock_origin);
						string owner_name = block2_->owner_name, user_name = pInfo(peer)->tankIDName;
						if (owner_name != user_name and not pInfo(peer)->dev) {
							if (block2_->fg == 4994 or not block2_->open_to_public and find(block2_->admins.begin(), block2_->admins.end(), pInfo(peer)->tankIDName) == block2_->admins.end()) {
								if (block2_->fg == 4994) {
									if (not block2_->open_to_public) {
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
										return true;
									}
									if (block2_->build_only and block2_->open_to_public) {
										if (not pInfo(peer)->dev) {
											gamepacket_t p(0, pInfo(peer)->netID);
											p.Insert("OnPlayPositioned");
											p.Insert("audio/punch_locked.wav");
											if (not pInfo(peer)->invis) {
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
													if (pInfo(currentPeer)->world == name_) {
														p.CreatePacket(currentPeer);
													}
												}
											}
											else {
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("This lock allows building only!");
												p.Insert(0);
												p.Insert(1);
												p.CreatePacket(peer);
											}
											return true;
										}
									}
								}
								else {
									if (not pInfo(peer)->dev) {
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
										return true;
									}
								}
							}
						}
					}
					else if (not world_->owner_name.empty()) {
						string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
						if (owner_name != user_name) {
							if (items.at(t_).blockType == BlockTypes::LOCK) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								if (world_->open_to_public)
									p.Insert(world_->owner_named + "``'s `$" + items.at(t_).name + "``. (`wOpen to public``)");
								else if (find(world_->admins.begin(), world_->admins.end(), user_name) != world_->admins.end())
									p.Insert(world_->owner_named + "``'s `$" + items.at(t_).name + "``. (`wAccess granted``)");
								else
									p.Insert(world_->owner_named + "``'s `$" + items.at(t_).name + "``. (`4No access``)");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
								if (not pInfo(peer)->dev) {
									{
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
									}
									return true;
								}
							}
							if (not world_->open_to_public and find(world_->admins.begin(), world_->admins.end(), user_name) == world_->admins.end()) {
								if (not pInfo(peer)->dev) {
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnPlayPositioned");
									p.Insert("audio/punch_locked.wav");
									if (not pInfo(peer)->invis) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == name_) {
												p.CreatePacket(currentPeer);
											}
										}
									}
									else {
										p.CreatePacket(peer);
									}
									return true;
								}
							}
						}
					} if (world_->owner_name != pInfo(peer)->tankIDName) {
						if (items.at(t_).magplant) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Only the `9World Owner`` can activate this!");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(peer);
							return true;
						}
					}
				}
				if (items.at(t_).magplant) {
					switch (t_) {
					case 6950: case 6952:
					{
						if (block_->id != 0) {
							block_->enabled = (block_->enabled ? false : true);
							for (int i_ = 0; i_ < world_->machines.size(); i_++) {
								WorldMachines* machine_ = &world_->machines.at(i_);
								if (machine_->x == x_ and machine_->y == y_) {
									machine_->enabled = block_->enabled;
									break;
								}
							}
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, peer, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
						break;
					}
					}
				}
				if (items.at(t_).blockType == BlockTypes::CHEMICAL_COMBINER) {
					if (block_->flags & 0x00400000) {

					}
					else {
						vector<vector<int>> comb;
						bool combined = false;
						for (int i_ = 0; i_ < world_->drop.size(); i_++) {
							if (world_->drop.at(i_).id == 0) continue;
							if (x_ == (world_->drop.at(i_).x / 32) && y_ == (world_->drop.at(i_).y / 32)) {
								comb.push_back({ world_->drop.at(i_).id, world_->drop.at(i_).count });
							}
						}
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						if (comb.size() < 3) p.Insert("I need 3 ingredients!");
						if (comb.size() > 3) p.Insert("It won't mix more than 3 items at once!");
						if (comb.size() == 3) {
							for (vector<vector<int>>recipe : receptai) {
								uint32_t result_item_id = recipe.at(3).at(0);
								uint32_t result_gives_per_recipe = recipe.at(3).at(1);
								vector<int> compare1, compare2;
								vector<vector<vector<int>>> info{ {}, {} };
								for (int i_ = 0; i_ < 3; i_++) {
									compare1.push_back(recipe.at(i_)[0]);
									info[0].push_back({ recipe.at(i_)[0], recipe.at(i_)[1] });
								} for (vector<int>item_id : comb) {
									compare2.push_back(item_id.at(0));
									info[1].push_back({ item_id.at(0), item_id.at(1) });
								} sort(compare1.begin(), compare1.end()), sort(compare2.begin(), compare2.end());
								if (compare1 == compare2) {
									sort(info[0].begin(), info[0].end()), sort(info[1].begin(), info[1].end());
									bool no = false;
									for (int i_ = 0; i_ < info[0].size(); i_++) {
										if (info.at(0).at(i_).at(1) > info.at(1).at(i_).at(1)) {
											no = true;
											break;
										}
									} if (no) break;
									uint32_t result_item_count = 0;
									uint32_t times_ = 0;
									for (int i_ = 0; i_ < world_->drop.size(); i_++) {
										if (no) break;
										if (world_->drop.at(i_).id == 0) continue;
										if (x_ == (world_->drop.at(i_).x / 32) && y_ == (world_->drop.at(i_).y / 32)) {
											for (int i_2 = 0; i_2 < info[0].size(); i_2++) {
												if (info.at(0).at(i_2).at(0) == world_->drop.at(i_).id) {
													if (info.at(0).at(i_2).at(1) > info.at(1).at(i_2).at(1)) {
														break;
													}
													world_->drop.at(i_).count -= info.at(0).at(i_2).at(1);
													info.at(1).at(i_2).at(1) = world_->drop.at(i_).count;
													times_++;
													if (world_->drop.at(i_).count <= 0) {
														PlayerMoving data_{};
														data_.packetType = 14, data_.netID = -2, data_.plantingTree = world_->drop.at(i_).uid;
														BYTE* raw = packPlayerMoving(&data_);
														int32_t item = -1;
														memcpy(raw + 8, &item, 4);
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
															if (pInfo(currentPeer)->world == name_) {
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															}
														}
														world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
														delete[] raw;
													}
													else {
														PlayerMoving data_{};
														data_.packetType = 14, data_.netID = -2, data_.plantingTree = world_->drop.at(i_).uid;
														BYTE* raw = packPlayerMoving(&data_);
														int32_t item = -1;
														memcpy(raw + 8, &item, 4);
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
															if (pInfo(currentPeer)->world == name_) {
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															}
														}
														delete[] raw;
														WorldDrop drop_{};
														drop_.id = world_->drop.at(i_).id;
														drop_.count = world_->drop.at(i_).count;
														drop_.uid = uint16_t(world_->drop.size()) + 1;
														drop_.x = world_->drop.at(i_).x;
														drop_.y = world_->drop.at(i_).y;
														world_->drop.at(i_).id = 0, world_->drop.at(i_).x = -1, world_->drop.at(i_).y = -1;
														dropas_(world_, drop_);
													} if (times_ == 3) {
														times_ = 0;
														result_item_count += result_gives_per_recipe;
														for (int i_ = 0; i_ < info[0].size(); i_++) {
															if (info.at(0).at(i_).at(1) > info.at(1).at(i_).at(1)) {
																no = true;
																break;
															}
														}
													}
													break;
												}
											}
										}
									} if (result_item_count != 0) {
										combined = true;
										WorldDrop drop_block_{};
										drop_block_.id = result_item_id, drop_block_.count = result_item_count, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = (x_ * 32) + rand() % 17, drop_block_.y = (y_ * 32) + rand() % 17;
										dropas_(world_, drop_block_);
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 44, data_.YSpeed = 44, data_.x = x_ * 32 + 16, data_.y = y_ * 32 + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												packet_(currentPeer, "action|play_sfx\nfile|audio/terraform.wav\ndelayMS|0");
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
										}
										delete[]raw;
										p.Insert("SCIENCE!");
									}
									break;
								}
							}
						}
						if (not combined) p.Insert("Those items don't seem to combine!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
				}
				if (items.at(t_).blockType == BlockTypes::WEATHER) {
					int weather_id_ = get_weather_id(t_);
					long long current_time = time(nullptr);
					if (block_->last_punch_weather - current_time <= 0) {
						world_->weather = (weather_id_ != world_->weather ? weather_id_ : 0);
						block_->enabled = (world_->weather != 0 ? true : false);
						block_->last_punch_weather = current_time + 1.5;
						gamepacket_t p;
						p.Insert("OnSetCurrentWeather");
						p.Insert(world_->weather);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == name_) {
								p.CreatePacket(currentPeer);
							}
						}
					}
				}
				if (items.at(block_->fg).charger) {
					if (block_->id != 0) {
						long long current_time = time(nullptr);
						if (block_->planted - current_time > 0) {
							if (block_->hp == -1 or (items.at(t_).dropChance) < (current_time - block_->lp)) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("That's not done charging!");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(peer);
							}
						} else {
							int c_ = 1;
							if (modify_inventory(peer, 2204, c_) == 0) {
								block_->id = 0, block_->planted = 0;
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, peer, false);
								PlayerMoving data_effect_{};
								data_effect_.packetType = 19;
								data_effect_.punchX = 2204;
								data_effect_.punchY = pInfo(peer)->netID;
								data_effect_.x = x_ * 32 + 16, data_effect_.y = y_ * 32 + 16;
								BYTE* raw_effect = packPlayerMoving(&data_effect_, 56);
								raw_effect[8] = pInfo(peer)->netID, raw_effect[3] = 5;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
										send_raw(currentPeer, 4, raw_effect, 56, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw, blc, raw_effect;
								if (block_->locked) {
									upd_lock(*block_, *world_, peer);
								}
							} else {
								if (block_->hp == -1 or (items.at(t_).dropChance) < (current_time - block_->lp)) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("No room to pick it up!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
							}
						}
					}
				}
				if (items.at(t_).blockType == BlockTypes::DISPLAY) {
					string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (owner_name != user_name and not owner_name.empty() and not pInfo(peer)->dev) {
						if (block_->id != 0) {
							if (not pInfo(peer)->dev) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("Only the block's owner can break it!");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(peer);
								return true;
							}
						}
					}
					else {
						int c_ = 0;
						modify_inventory(peer, block_->id, c_);
						int slots_ = get_free_slots(pInfo(peer));
						if (c_ + 1 > 200 or c_ == 0 and slots_ == 0) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("You don't have enough space in your backpack! Free some and try again.");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(peer);
							return true;
						}
					}
				}
				pInfo(peer)->punch_count++;
				long long time_ = time(nullptr);
				uint32_t laikas = uint32_t((time_ - block_->planted <= items.at(block_->fg).growTime ? time_ - block_->planted : items.at(block_->fg).growTime));
				if (items.at(t_).blockType == BlockTypes::SEED and laikas == items.at(block_->fg).growTime) {
					int drop_count = items.at(block_->fg - 1).rarity == 1 ? (items.at(block_->fg - 1).farmable ? (rand() % 9) + 4 : (rand() % block_->fruit) + 1) : items.at(block_->fg - 1).farmable ? (rand() % 5) + 4 : (rand() % block_->fruit) + 1;
					if (pInfo(peer)->back == 1746 && pInfo(peer)->feet == 1830 || pInfo(peer)->feet == 1966) { // fuel pack
						if (items.at(block_->fg - 1).rarity < 100) {// pagal real gt jei rarity virs 100 neduoda double
							int c1746 = 1746, countofitem = 0, removepack = -1;
							modify_inventory(peer, c1746, countofitem);
							if (countofitem >= 1) {
								if (rand() % 100 < 10) { // pagal real gt 10% chance
									modify_inventory(peer, c1746, removepack);
									drop_count *= 2; // pagal real gt double drop count
									// dar reikia kazkoki particle effect issiust kai suveikia fuel pack
								}
							}
						}
					}
					if (harvest_seed(world_, block_, x_, y_, drop_count, pInfo(peer)->netID, peer)) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("A `w" + items.at(t_).name + "`` falls out!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					return true;
				}
				double increase_ = round((double)items.at(t_).breakHits / 6 / 6);
				int punch_modifier = (has_playmod(pInfo(peer), "Enhanced Digging") ? -increase_ : (has_playmod(pInfo(peer), "Death To Blocks!") ? -increase_ : (has_playmod(pInfo(peer), "Dragonborn") ? -increase_ : (has_playmod(pInfo(peer), "punch damage") ? -increase_ : (has_playmod(pInfo(peer), "diggin' it") ? -increase_ : has_playmod(pInfo(peer), "cupid's firepower") ? increase_ : (has_playmod(pInfo(peer), "eye beam") ? increase_ : 0))))));
				if (block_->hp == -1 or (items.at(t_).dropChance) < (time_ - block_->lp)) {
					int punch_ = items.at(t_).breakHits / 6 + punch_modifier;
					if (punch_ <= 2) punch_ = 3;
					else if (punch_ <= 3 and punch_modifier < 0) punch_ = 4;
					block_->hp = punch_;
					block_->lp = time_;
				}
				block_->hp -= 1;
				if (block_->hp == 0) { /*isgriove*/
					if (t_ == 392 || t_ == 3402 || t_ == 9350) { // golden booty chest ir hearstone ir super golden booty chest
						if (t_ == 3402) {
							pInfo(peer)->booty_broken++;
							if (pInfo(peer)->booty_broken >= 100) {
								pInfo(peer)->booty_broken = 0;
								int c_ = 1;
								if (modify_inventory(peer, 9350, c_) != 0) {
									string name_ = pInfo(peer)->world;
									WorldDrop drop_block_{};
									drop_block_.id = 9350, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(peer)->x + rand() % 17, drop_block_.y = pInfo(peer)->y + rand() % 17;
									dropas_(world_, drop_block_);
								}
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("You received " + items.at(9350).name + "!");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(peer);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You received " + items.at(9350).name + "!");
									p.CreatePacket(peer);
								}
								PlayerMoving data_{};
								data_.packetType = 19, data_.plantingTree = 0, data_.netID = 0;
								data_.punchX = 9350;
								data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
								int32_t to_netid = pInfo(peer)->netID;
								BYTE* raw = packPlayerMoving(&data_);
								raw[3] = 5;
								memcpy(raw + 8, &to_netid, 4);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[]raw;
							}
						}
						vector<int> list{ 5652, 3398, 386, 4422, 364, 9342, 9340, 9334, 9332, 9336, 9338, 4400, 7808, 7810, 4416, 7818, 7820, 7822, 7824, 5644, 390, 7826, 7830, 9324, 5658, 3396, 2384, 5660, 10654, 3400, 4418, 388, 3408, 1470, 3404, 3406, 10662, 2390, 5656, 5648, 2396, 384, 5664, 4424, 366 }, rare_list{ 5652, 366, 362, 1458, 2388, 10652, 4412, 10632, 10626 };
						int item = list[rand() % list.size()];
						if ((t_ == 9350 ? rand() % 250 : (has_playmod(pInfo(peer), "Lucky in Love") ? rand() % 500 : rand() % 1000)) < 1) item = rare_list[rand() % rare_list.size()];
						else item = list[rand() % list.size()];
						WorldDrop drop_block_{};
						drop_block_.id = item, drop_block_.count = (item == 7810 || item == 7808 || item == 4400 || item == 390 || item == 3408 || item == 4422 || item == 3404 ? 5 : (item == 4418 || item == 5660 ? 2 : 1)), drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = (x_ * 32) + rand() % 17, drop_block_.y = (y_ * 32) + rand() % 17;
						dropas_(world_, drop_block_);
					}
					else if (items.at(t_).magplant) {
						switch (t_) {
						case 6950: case 6952:
						{
							if (block_->pr > 0) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("`4Be careful``, if you return this to your backpack you will `4lose ALL`` Gems stored within! Use them up first!");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(peer);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4Be careful``, if you return this to your backpack you will `4lose ALL`` Gems stored within! Use them up first!");
									p.CreatePacket(peer);
								}
								return true;
							}
							break;
						}
						}
					}
					if (items.at(t_).properties & Property_AutoPickup) {
						int c_ = 1;
						if (modify_inventory(peer, t_, c_, false) == 0) {
							PlayerMoving data_{};
							data_.packetType = 14, data_.netID = -1, data_.plantingTree = t_;
							data_.x = float(x_) * 32, data_.y = float(y_) * 32;
							int32_t item = -1;
							float val = 1.00;
							BYTE* raw = packPlayerMoving(&data_);
							memcpy(raw + 8, &item, 4);
							memcpy(raw + 16, &val, 4);
							data_.netID = pInfo(peer)->netID;
							WorldDrop n_{};
							n_.id = 0, n_.count = 0, n_.uid = uint16_t(world_->drop.size()) + 1, n_.x = x_ * 32, n_.y = y_ * 32;
							world_->drop.push_back(n_);
							data_.plantingTree = int(world_->drop.size());
							data_.x = 0, data_.y = 0;
							BYTE* raw2 = packPlayerMoving(&data_);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == name_) {
									send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[]raw, raw2;
							gamepacket_t p(1);
							p.Insert("OnConsoleMessage");
							p.Insert("Collected `w1 " + items.at(t_).name + "``.``");
							p.CreatePacket(peer);
						}
						else {
							return true;
						}
					}
					else if (items.at(t_).max_gems != 0) {
						add_peer_xp(peer, (items.at(t_).rarity / 5 > 0 ? items.at(t_).rarity / 5 : 1));
						int maxgems = items.at(t_).max_gems;
						if (t_ == 120) maxgems = 50;
						int c_ = rand() % (maxgems + 1);
						if (c_ != 0) {
							bool no_seed = false, no_gems = false, no_block = false;
							for (int i_ = 0; i_ < world_->drop.size(); i_++) {
								if (abs(world_->drop.at(i_).y - y_ * 32) <= 16 and abs(world_->drop.at(i_).x - x_ * 32) <= 16) {
									if (world_->drop.at(i_).id == 112 and items.at(t_).rarity < 8) {
										no_gems = true;
									}
									else {
										no_seed = true, no_block = true;
									}
								}
							}
							if (rand() % 100 < 3) {
								WorldDrop drop_block_{};
								drop_block_.id = t_, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = (x_ * 32) + rand() % 17, drop_block_.y = (y_ * 32) + rand() % 17;
								if (not use_mag(world_, drop_block_, x_, y_) and not no_block) {
									dropas_(world_, drop_block_);
								}
							}
							else if (rand() % 100 < 37) {
								WorldDrop drop_seed_{};
								drop_seed_.id = t_ + 1, drop_seed_.count = 1, drop_seed_.uid = uint16_t(world_->drop.size()) + 1, drop_seed_.x = (x_ * 32) + rand() % 17, drop_seed_.y = (y_ * 32) + rand() % 17;
								if (not use_mag(world_, drop_seed_, x_, y_) and not no_seed) {
									dropas_(world_, drop_seed_);
								}
							}
						}
					}
					if (block_->fg == 5638 and pInfo(peer)->magnetron_id != 0 and pInfo(peer)->magnetron_x == x_ and pInfo(peer)->magnetron_y == y_) {
						int c_ = 0;
						modify_inventory(peer, 5640, c_);
						if (c_ != 0) {
							c_ *= -1;
							modify_inventory(peer, 5640, c_);
							pInfo(peer)->magnetron_id = 0;
							pInfo(peer)->magnetron_x = 0;
							pInfo(peer)->magnetron_y = 0;
						}
					}
					if (items.at(block_->fg).charger and block_->id != 0) {
						WorldDrop drop_block_{};
						drop_block_.id = 2286, drop_block_.count = 1;
						if (block_->planted - time(nullptr) <= 0) {
							drop_block_.id = 2204;
						}
						drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = (x_ * 32) + rand() % 17, drop_block_.y = (y_ * 32) + rand() % 17;
						dropas_(world_, drop_block_);
					}
					switch (items.at(block_->fg).blockType) {
					case BlockTypes::WEATHER:
					{
						if (world_->weather != 0) {
							world_->weather = 0;
							gamepacket_t p;
							p.Insert("OnSetCurrentWeather");
							p.Insert(world_->weather);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == name_) {
									p.CreatePacket(currentPeer);
								}
							}
						}
						break;
					}
					case BlockTypes::DISPLAY:
					{
						if (block_->id != 0) {
							int c_ = 1;
							modify_inventory(peer, block_->id, c_);
							PlayerMoving data_effect_{};
							data_effect_.packetType = 19;
							data_effect_.punchX = block_->id;
							data_effect_.punchY = pInfo(peer)->netID;
							data_effect_.x = x_ * 32 + 16, data_effect_.y = y_ * 32 + 16;
							BYTE* raw_effect = packPlayerMoving(&data_effect_, 56);
							raw_effect[8] = pInfo(peer)->netID, raw_effect[3] = 5;
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == name_) {
									send_raw(currentPeer, 4, raw_effect, 56, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[]raw_effect;
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("You picked up 1 " + items.at(block_->id).name + ".");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(peer);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You picked up 1 " + items.at(block_->id).name + ".");
								p.CreatePacket(peer);
							}
						}
						break;
					}
					case BlockTypes::LOCK:
					{
						// reset world settings
						if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
							vector<int> new_tiles{};
							vector<WorldBlock> shadow_copy_2 = world_->blocks;
							new_tiles.push_back(x_ + (y_ * 100));
							int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
							for (int i2 = 0; i2 < new_tiles.size(); i2++) {
								int s_x_ = new_tiles.at(i2) % 100, s_y_ = new_tiles.at(i2) / 100;
								if (s_x_ < 99 and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ + 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ + 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).locked = false;
										world_->blocks.at(s_x_ + 1 + (s_y_ * 100)).lock_origin = -1;
									}
								} if (s_x_ > 0 and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).locked and shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned) {
										shadow_copy_2.at(s_x_ - 1 + (s_y_ * 100)).scanned = true;
										new_tiles.push_back(s_x_ - 1 + (s_y_ * 100));
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).locked = false;
										world_->blocks.at(s_x_ - 1 + (s_y_ * 100)).lock_origin = -1;
									}
								} if (s_y_ < 59 and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ + 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ + 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).locked = false;
										world_->blocks.at(s_x_ + ((s_y_ + 1) * 100)).lock_origin = -1;
									}
								} if (s_y_ > 0 and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).locked and shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin == (x_ + (y_ * 100))) {
									if (not shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned) {
										shadow_copy_2.at(s_x_ + ((s_y_ - 1) * 100)).scanned = true;
										new_tiles.push_back(s_x_ + ((s_y_ - 1) * 100));
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).locked = false;
										world_->blocks.at(s_x_ + ((s_y_ - 1) * 100)).lock_origin = -1;
									}
								}
							}
							break;
						}
						world_->owner_name = "", world_->owner_named = "", world_->entry_level = 1, world_->make_music_blocks_invisible = false, world_->disable_music_blocks = false, world_->music_bpm = 100, world_->open_to_public = false;
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("`5[```w" + world_->name + "`` has had its `$World Lock`` removed!`5]``");
						gamepacket_t p2(0, pInfo(peer)->netID);
						{
							p2.Insert("OnNameChanged");
							if (pInfo(peer)->mod == 0 && pInfo(peer)->dev == 0)pInfo(peer)->name_color = "`0";
							p2.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
						}
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == name_) {
								p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer);
								if (find(world_->admins.begin(), world_->admins.end(), pInfo(currentPeer)->tankIDName) != world_->admins.end()) {
									gamepacket_t p3(0, pInfo(currentPeer)->netID);
									p3.Insert("OnNameChanged");
									if (pInfo(currentPeer)->mod == 0 && pInfo(currentPeer)->dev == 0)pInfo(currentPeer)->name_color = "`0";
									p3.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``");
									for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
										if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
										if (pInfo(currentPeer2)->world == name_) {
											p3.CreatePacket(currentPeer2);
										}
									}
								}
							}
						}
						world_->admins.clear();
						break;
					}
					default:
						break;
					}
					punch_tile(peer, x_, y_, 0x3, p_, pInfo(peer)->netID, 0x0);
				}
				else { /*-1 hp*/
					block_->lp = time_;
					if (items.at(block_->fg).blockType == BlockTypes::PROVIDER) {
						uint32_t laikas = uint32_t((time_ - block_->planted <= items.at(block_->fg).growTime ? time_ - block_->planted : items.at(block_->fg).growTime));
						if (laikas == items.at(block_->fg).growTime) {
							vector<double> ids; // svarbu: id.max_kiekis <!= 5 if size after decimal point == 2 then count fixed
							if (block_->fg == 866) { // cow
								ids = { 868.2 };
							}
							else if (block_->fg == 872) { // chicken
								ids = { 874.2 };
							}
							else if (block_->fg == 1044) { // buffalo
								ids = { 868.2 };
							}
							else if (block_->fg == 3888) { // sheep
								ids = { 3890.3 };
							}
							else if (block_->fg == 1632) { // coffee maker
								ids = { 1634 };
							}
							else if (block_->fg == 5116) { // tea set
								ids = { 5114 };
							}
							else if (block_->fg == 2798) { // well
								ids = { 822.2 };
							}
							else if (block_->fg == 10450) { // diamond builder
								ids = { 10454, 10458.50, 10458.50, 10462.20, 10464.30, 10466.30, 10468.50, 10470.30, 10472.20, 10474.30, 10476.20, 10478.20, 10480.30, 10482, 10484.30, 10460 };
							}
							else if (block_->fg == 8196) { // building blocks machine
								ids = { };
							}
							else if (block_->fg == 8172) { // Item-O-Matic
								ids = { 8174, 8176, 8178, 8180, 8182 };
							}
							else if (block_->fg == 8160) { // Item-O-Matic
								ids = { 8162, 8164, 8166, 8168, 8170 };
							}
							else if (block_->fg == 8148) { // Item-O-Matic
								ids = { 8150, 8152, 8154, 8156, 8158 };
							}
							else if (block_->fg == 8136) { // Item-O-Matic
								ids = { 8138, 8140, 8142, 8144, 8146 };
							}
							else if (block_->fg == 8124) { // Item-O-Matic
								ids = { 8126, 8128, 8130, 8132, 8134 };
							}
							else if (block_->fg == 8112) { // Item-O-Matic
								ids = { 8114, 8116, 8118, 8120, 8122 };
							}
							else if (block_->fg == 8100) { // Item-O-Matic
								ids = { 8102, 8104, 8106, 8108, 8110 };
							}
							else if (block_->fg == 8088) { // Item-O-Matic
								ids = { 8090, 8092, 8094, 8096, 8098 };
							}
							else if (block_->fg == 8076) { // Item-O-Matic
								ids = { 8078, 8080, 8082, 8084, 8086 };
							}
							else if (block_->fg == 1008) { // atm machine
								int c_ = (rand() % 100) + 1;
								if (c_ == 100) {
									//spawn effect jackpot
								}
								gems_(world_, c_, x_ * 32, y_ * 32);
							}
							else if (block_->fg == 928) { // Science station
								ids = { 914, 916, 918, 920, 924 };
							} if (ids.size() != 0) {
								double rand_item = ids[rand() % ids.size()];
								int count_ = 1;
								bool do_rand = true;
								if (to_string(rand_item).find(".") != string::npos) {
									string asd_ = explode(".", to_string(rand_item))[1];
									string s(1, asd_.at(0));
									int c_ = atoi(s.c_str());
									if (c_ != 0) {
										if (asd_.size() == 2) {
											do_rand = false;
											c_ /= 10;
										}
										count_ = c_;
									}
								}
								if (count_ > 1 and do_rand)
									count_ = (rand() % count_) + 1;
								int rand_item2 = (int)rand_item;
								WorldDrop new_drop_{};
								new_drop_.id = rand_item2, new_drop_.count = count_, new_drop_.uid = uint16_t(world_->drop.size()) + 1, new_drop_.x = (x_ * 32) + rand() % 17, new_drop_.y = (y_ * 32) + rand() % 17;
								dropas_(world_, new_drop_);
							}
							if (items.at(block_->fg).properties & Property_AutoPickup)
								block_->planted = time_;
							else
								block_->planted = time_ - ((rand() % 14400) + 1);
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, peer, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
					}
					else if (items.at(block_->fg).blockType == BlockTypes::RANDOM_BLOCK) {
						block_->roll = (rand() % 5) + 1;
						punch_tile(peer, x_, y_, 0x8, 0, pInfo(peer)->netID, 0x0, true, block_->roll);
					}
					punch_tile(peer, x_, y_, 0x8, (punch_modifier == 0 ? 6 : (punch_modifier < 0 ? 8 : 5)), pInfo(peer)->netID, 0x0, (block_->roll != 0 ? true : false), (block_->roll != 0 ? block_->roll : 0));
				}
				break;
			}
			case 32:
			{
				if (t_ == 3898) {
					string user_name = pInfo(peer)->tankIDName;
					pInfo(peer)->p_x = x_;
					pInfo(peer)->p_y = y_;
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wTelephone``|left|3898|\nadd_textbox|Dial a number to call somebody in Growtopia. Phone numbers have 5 digits, like 12345 (try it - you'd be crazy not to!). Most numbers are not in service!|left|\nadd_text_input|buttonClicked|Phone #||5|\nend_dialog|"+to_string(t_)+"|Hang Up|Dial|\n");
					p.CreatePacket(peer);
					break;
				}
				if (items.at(t_).blockType == BlockTypes::VENDING) {
					if (abs(x_ * 32 - pInfo(peer)->x) > 15 || abs(y_ * 32 - pInfo(peer)->y) > 15) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Get closer!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
						break;
					}
					string user_name = pInfo(peer)->tankIDName;
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert(((world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty()) ? get_vending_buyer_side(peer, world_, block_, x_, y_) : get_vending(peer, world_, block_, x_, y_)));
					p.CreatePacket(peer);
					break;
				}
				if (block_->fg == 202 or block_->fg == 204 or block_->fg == 206 or block_->fg == 4994) {
					string owner_name = block_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (owner_name != user_name and not pInfo(peer)->dev) {
						if (items.at(t_).blockType == BlockTypes::LOCK) {
							if (find(block_->admins.begin(), block_->admins.end(), pInfo(peer)->tankIDName) != block_->admins.end()) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_label|small|This lock is owned by `w" + block_->owner_name + "``, but I have access on it.|left\nend_dialog|lock_edit|Cancel|Remove My Access|");
								p.CreatePacket(peer);
							}
							else {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("I'm `4unable`` to pick the lock.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
							packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
							return true;
						}
					}
				}
				else if (block_->locked and items.at(p_).blockType != BlockTypes::CONSUMABLE) {
					WorldBlock* block2_ = &world_->blocks.at(block_->lock_origin);
					string owner_name = block2_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (owner_name != user_name and not pInfo(peer)->dev) {
						if (find(block2_->admins.begin(), block2_->admins.end(), user_name) == block2_->admins.end() and not block2_->open_to_public and not pInfo(peer)->dev) {
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnPlayPositioned");
							p.Insert("audio/punch_locked.wav");
							if (not pInfo(peer)->invis) {
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == name_) {
										p.CreatePacket(currentPeer);
									}
								}
							}
							else {
								p.CreatePacket(peer);
							}
							{
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("That area is owned by " + (block2_->owner_named.substr(0, 2) == "`o" ? "`w" + block2_->owner_name : block2_->owner_named) + "``");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
							return true;
						}
						if (items.at(p_).blockType == BlockTypes::LOCK) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("`w" + block2_->owner_named + "`` allows public building here, but no locks.");
							p.Insert(0);
							p.Insert(0);
							p.CreatePacket(peer);
							{
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnPlayPositioned");
								p.Insert("audio/punch_locked.wav");
								if (not pInfo(peer)->invis) {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name_) {
											p.CreatePacket(currentPeer);
										}
									}
								}
								else {
									p.CreatePacket(peer);
								}
							}
							return true;
						}
					}
				}
				else if (not world_->owner_name.empty() and items.at(p_).blockType != BlockTypes::CONSUMABLE) {
					string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (owner_name != user_name and not pInfo(peer)->dev) {
						if (items.at(t_).blockType == BlockTypes::LOCK) {
							if (find(world_->admins.begin(), world_->admins.end(), user_name) != world_->admins.end()) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_label|small|This lock is owned by `w" + world_->owner_name + "``, but I have access on it.|left\nend_dialog|lock_edit|Cancel|Remove My Access|");
								p.CreatePacket(peer);
							}
							else {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("I'm `4unable`` to pick the lock.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
							packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
							return true;
						}
						if (find(world_->admins.begin(), world_->admins.end(), user_name) == world_->admins.end() and not world_->open_to_public and not pInfo(peer)->dev) {
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnPlayPositioned");
							p.Insert("audio/punch_locked.wav");
							if (not pInfo(peer)->invis) {
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == name_) {
										p.CreatePacket(currentPeer);
									}
								}
							}
							else {
								p.CreatePacket(peer);
							}
							{
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("That area is owned by " + (world_->owner_named.substr(0, 2) == "`o" ? "`w" + world_->owner_name : world_->owner_named) + "``");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
							return true;
						}
						if (items.at(p_).blockType == BlockTypes::LOCK) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("`w" + world_->owner_named + "`` allows public building here, but no locks.");
							p.Insert(0);
							p.Insert(0);
							p.CreatePacket(peer);
							{
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnPlayPositioned");
								p.Insert("audio/punch_locked.wav");
								if (not pInfo(peer)->invis) {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name_) {
											p.CreatePacket(currentPeer);
										}
									}
								}
								else {
									p.CreatePacket(peer);
								}
							}
							return true;
						}
					}
				} if (world_->owner_name != pInfo(peer)->tankIDName) {
					if (items.at(t_).magplant or items.at(t_).item_sucker) {
						switch (t_) {
						case 6948: case 5638: case 6946:
						{
							if (not world_->owner_name.empty()) {
								bool ar_turi_mag = false;
								{
									int c_ = 0;
									if (block_->id != 0) {
										modify_inventory(peer, 5640, c_);
										if (c_ != 0) {
											if (pInfo(peer)->magnetron_x == x_ and pInfo(peer)->magnetron_y == y_ and pInfo(peer)->magnetron_id == block_->id) {
												ar_turi_mag = true;
											}
										}
									}
								}
								bool dont_give = false;
								if (items.at(block_->id).collisionType != 1 and items.at(block_->id).blockType != BACKGROUND and items.at(block_->id).blockType != SEED and not items.at(block_->id).farmable or items.at(block_->id).rarity == 999) {
									dont_give = true;
								}
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + (block_->id == 0 ? "\nadd_textbox|There is no item selected |left|" : "\nadd_label_with_icon|small|`2" + items.at(block_->id).name + "``|left|" + to_string(block_->id) + "|") + (block_->fg == 5638 and not block_->magnetron ? "\nadd_textbox|Building mode: `6DISABLED``|left|" : "\nadd_textbox|Building mode: `5ACTIVE``|left|\nadd_textbox|Use the " + items.at(5640).name + " to build `2" + items.at(block_->id).name + "`` directly from the " + items.at(block_->fg).name + "'s storage.|left|" + (not ar_turi_mag and not dont_give ? "\nadd_button|getplantationdevice|Get Remote|noflags|0|0|" : "") + "") + "\nend_dialog|itemsucker_block|Close||");
								p.CreatePacket(peer);
							}
							break;
						}
						case 6950: case 6952:
						{
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("add_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nadd_smalltext|The device will consume 2300 Gems/hr while active!|left|\nadd_smalltext|Current Fuel = `w" + to_string(block_->pr) + "/8,000``|left|\nend_dialog|autoactionblock|Close||\nadd_quick_exit|");
							p.CreatePacket(peer);
							break;
						}
						}
						if (not items.at(t_).item_sucker) return true;
					}
				}
				if (items.at(t_).can_be_changed_two_types) {
					if (world_->owner_name.empty()) {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_textbox|This object has additional properties to edit if in a locked area.|left|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|boombox_edit|Cancel|OK|");
						p.CreatePacket(peer);
					}
					else {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_checkbox|checkbox_public|Usable by public|" + (block_->flags & 0x00800000 ? "1" : "0") + "\nadd_checkbox|checkbox_silence|Silenced|" + (block_->flags & 0x02000000 ? "1" : "0") + "\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|boombox_edit|Cancel|OK|");
						p.CreatePacket(peer);
					}
					break;
				}
				if (items.at(t_).trickster) {
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9" + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_textbox|Rate of fire? (2-20 seconds)|left|\nadd_text_input|often|Seconds:|" + to_string(block_->rate_of_fire) + "|3|\nadd_textbox|Speed of projectiles? (10-250 pixels/second)|left|\nadd_text_input|speed|Speed:|" + to_string(block_->projectile_speed) + "|3|\nadd_checkbox|disable|Disabled|" + (block_->flags & 0x00400000 ? "0" : "1") + "\nadd_smalltext|You can install as many Blaster Blocks (Howlers or Tricksters) as you want in a world, but only 10 projectiles can exist at one time, so don't go crazy!|left|\nend_dialog|blaster|Cancel|Update|");
					p.CreatePacket(peer);
					break;
				}
				if (items.at(t_).entrance or items.at(t_).can_be_changed_to_public) {
					if (world_->owner_name.empty()) {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_textbox|This object has additional properties to edit if in a locked area.|left|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|switcheroo_edit|Cancel|OK|");
						p.CreatePacket(peer);
					}
					else {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_checkbox|checkbox_public|" + (items.at(t_).can_be_changed_to_public ? "Usable by public" : "Is open to public") + "|" + (block_->flags & 0x00800000 ? "1" : "0") + "\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|switcheroo_edit|Cancel|OK|");
						p.CreatePacket(peer);
					}
					break;
				}
				if (items.at(t_).magplant or items.at(t_).item_sucker) {
					switch (t_) {
					case 6948: case 5638: case 6946:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert(get_sucker(peer, world_, block_, x_, y_));
						p.CreatePacket(peer);
						break;
					}
					case 6950: case 6952:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("add_label_with_icon|big|`w" + items.at(block_->fg).name + "``|left|" + to_string(block_->fg) + "|\nadd_spacer|small|\nadd_smalltext|The device will consume 2300 Gems/hr while active!|left|\nadd_smalltext|Current Fuel = `w" + to_string(block_->pr) + "/8,000``|left|" + (block_->pr < 8000 ? "\nadd_smalltext|Refuel this with gems!|left|\nadd_text_input|refillfuel|Add Gems:|0|5|\nadd_button|addfuel|`wAdd Gems``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_smalltext|" + (block_->id == 0 ? "No block type selected!" : "Target block is: `2" + items.at(block_->id).name + "``") + "|left|\nadd_item_picker|selecttarget|`wChoose Target Item``|Choose the target item!|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|autoactionblock|Close|OK|\nadd_quick_exit|");
						p.CreatePacket(peer);
						break;
					}
					}
					break;
				}
				switch (items.at(t_).blockType) {
				case BlockTypes::WEATHER:
				{
					switch (t_) {
					case 5000:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_textbox|You can scan any Background Block to set it up in your weather machine.|left|\nadd_item_picker|choose|Item: `2" + items.at((block_->id != 0 ? block_->id : 14)).name + "``|Select any Background Block|\nend_dialog|weatherspcl|Cancel|Okay|");
						p.CreatePacket(peer);
						break;
					}
					case 3832:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_item_picker|choose|Item: `2" + items.at((block_->id != 0 ? block_->id : 14)).name + "``|Select any item to rain down|\nadd_text_input|gravity|Gravity:|" + to_string(block_->gravity) + "|5|\nadd_checkbox|spin|Spin Items|" + (block_->spin ? "1" : "0") + "\nadd_checkbox|invert|Invert Sky Colors|" + (block_->invert ? "1" : "0") + "\nend_dialog|weatherspcl|Cancel|Okay|");
						p.CreatePacket(peer);
						break;
					}
					}
					break;
				}
				case BlockTypes::DISPLAY:
				{
					string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_spacer|small|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_textbox|" + (block_->id != 0 ? "A " + items.at(block_->id).name + " is on display here." : "The Display Block is empty. Use an item on it to display the item!") + "|left|" + (block_->id != 0 and user_name == owner_name or owner_name.empty() ? "\nend_dialog|displayblock|Leave it|Pick it up|" : "\nend_dialog|displayblock|Okay||"));
					p.CreatePacket(peer);
					break;
				}
				case BlockTypes::LOCK:
				{
					if (t_ == 202 or t_ == 204 or t_ == 206 or t_ == 4994) {
						string access_list_ = "";
						for (int i_ = 0; i_ < block_->admins.size(); i_++) {
							access_list_ += "\nadd_checkbox|checkbox_/" + block_->admins.at(i_) + "|`w" + block_->admins.at(i_) + "``|1";
						}
						if (access_list_.empty())
							access_list_ = "\nadd_label|small|Currently, you're the only one with access.``|left";
						if (t_ == 4994) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_label|small|`wAccess list:``|left\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_spacer|small|" + access_list_ + "\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build or Break|" + (block_->open_to_public ? "1" : "0") + "\nadd_checkbox|checkbox_ignore|Ignore empty air|" + (block_->empty_air ? "1" : "0") + "\nadd_button|recalcLock|`wRe-apply lock``|noflags|0|0|\nadd_spacer|small|\nadd_smalltext|This lock allows Building or Breaking.|left|\nadd_smalltext|(ONLY if 'Allow anyone to Build or Break' is checked above)!|left|\nadd_spacer|small|\nadd_smalltext|Leaving this box unchecked only allows Breaking.|left|\nadd_checkbox|checkbox_buildonly|Only Allow Building!|" + (block_->build_only ? "1" : "0") + "\nadd_smalltext|People with lock access can both build and break unless you check below. The lock owner can always build and break.|left|\nadd_checkbox|checkbox_admins|Admins Are Limited|" + (block_->limit_admins ? "1" : "0") + "\nend_dialog|lock_edit|Cancel|OK|");
							p.CreatePacket(peer);
						}
						else {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_label|small|`wAccess list:``|left\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_spacer|small|" + access_list_ + "\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + (block_->open_to_public ? "1" : "0") + "\nadd_checkbox|checkbox_ignore|Ignore empty air|" + (block_->empty_air ? "1" : "0") + "\nadd_button|recalcLock|`wRe-apply lock``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|");
							p.CreatePacket(peer);
						}
					}
					else {
						string access_list_ = "";
						for (int i_ = 0; i_ < world_->admins.size(); i_++) {
							access_list_ += "\nadd_checkbox|checkbox_/" + world_->admins.at(i_) + "|`w" + world_->admins.at(i_) + "``|1";
						}
						if (access_list_.empty())
							access_list_ = "\nadd_label|small|Currently, you're the only one with access.``|left";
						string world_key = "\nadd_button|getKey|Get World Key|noflags|0|0|";
						int c_ = 0;
						modify_inventory(peer, 1424, c_);
						if (c_ != 0) {
							world_key = "";
						}
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_label|small|`wAccess list:``|left\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nadd_spacer|small|" + access_list_ + "\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + (world_->open_to_public ? "1" : "0") + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|" + (world_->disable_music_blocks ? "1" : "0") + "\nadd_text_input|tempo|Music BPM|" + to_string(world_->music_bpm) + "|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|" + (world_->make_music_blocks_invisible ? "1" : "0") + (not pInfo(peer)->home_world.empty() ? "\nadd_smalltext|Your current home world is: " + pInfo(peer)->home_world + "|left|" : "") + "\nadd_checkbox|checkbox_set_as_home_world|Set as Home World|" + (pInfo(peer)->home_world == world_->name ? "1" : "0") + "|\nadd_text_input|minimum_entry_level|World Level: |" + to_string(world_->entry_level) + "|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|sessionlength_dialog|`wSet World Timer``|noflags|0|0|\nadd_button|changecat|`wCategory: None``|noflags|0|0|" + world_key + "\nend_dialog|lock_edit|Cancel|OK|");
						p.CreatePacket(peer);
					}
					break;
				}
				case BlockTypes::SIGN:
				{
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_textbox|" + (t_ == 1684 ? "Enter an ID. You can use this as a destination for Doors.``" : "What would you like to write on this sign?``") + "|left|\nadd_text_input|sign_text||" + (t_ == 1684 ? block_->door_id : block_->txt) + "|128|\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|sign_edit|Cancel|OK|");
					p.CreatePacket(peer);
					break;
				}
				case BlockTypes::DOOR: case BlockTypes::PORTAL:
				{
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					string open_ = (block_->open ? "1" : "0");
					p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEdit " + items.at(t_).name + "``|left|" + to_string(t_) + "|\nadd_text_input|door_name|Label|" + block_->txt + "|100|\nadd_text_input|door_target|Destination|" + block_->door_destination + "|24|\nadd_smalltext|Enter a Destination in this format: `2WORLDNAME:ID``|left|\nadd_smalltext|Leave `2WORLDNAME`` blank (:ID) to go to the door with `2ID`` in the `2Current World``.|left|\nadd_text_input|door_id|ID|" + block_->door_id + "|11|\nadd_smalltext|Set a unique `2ID`` to target this door as a Destination from another!|left|" + (not world_->owner_name.empty() ? "\nadd_checkbox|checkbox_locked|Is open to public|" + open_ + "" : "") + "\nembed_data|tilex|" + to_string(x_) + "\nembed_data|tiley|" + to_string(y_) + "\nend_dialog|door_edit|Cancel|OK|");
					p.CreatePacket(peer);
					break;
				}
				}
				// wrench
				break;
			}
			default:
			{
				if (items.at(block_->fg).charger and p_ == 2286 or p_ == 2204) {
					if (p_ == 2204) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Your " + items.at(p_).name + " doesn't need charging!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					} else if (block_->id != 0) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("That charger is already in use!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					} else {
						int c_ = -1;
						if (modify_inventory(peer, p_, c_) == 0) {
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnPlayPositioned");
							p.Insert("audio/mlaunch.wav");
							block_->id = p_, block_->planted = time(nullptr) + 3600;
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, peer, false);
							PlayerMoving data_effect_{};
							data_effect_.packetType = 19;
							data_effect_.punchX = p_;
							data_effect_.punchY = pInfo(peer)->netID;
							data_effect_.x = x_ * 32 + 16, data_effect_.y = y_ * 32 + 16;
							BYTE* raw_effect = packPlayerMoving(&data_effect_, 56);
							raw_effect[8] = pInfo(peer)->netID, raw_effect[3] = 4;
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									p.CreatePacket(currentPeer);
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									send_raw(currentPeer, 4, raw_effect, 56, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
					}
					return true;
				}
				if (items.at(t_).blockType == BlockTypes::DISPLAY) {
					string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
					if (world_->owner_name.empty()) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("This area must be locked to put your item on display!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else if (owner_name != user_name and not pInfo(peer)->dev) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Only the block's owner can place items in it.");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else if (block_->id != 0) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Remove what's in there first!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else if (p_ == 1424) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("No sir.");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else if (items.at(p_).untradeable) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("You can't display untradeable items.");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else if (items.at(p_).blockType == BlockTypes::LOCK or items.at(p_).blockType == BlockTypes::DISPLAY) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Sorry, no displaying Display Blocks or Locks.");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
					}
					else {
						int c_ = -1;
						if (modify_inventory(peer, p_, c_) == 0) {
							block_->id = p_;
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnPlayPositioned");
							p.Insert("audio/blorb.wav");

							// update item visual in display block
							PlayerMoving data_effect_{};
							data_effect_.packetType = 19;
							data_effect_.punchX = p_;
							data_effect_.punchY = pInfo(peer)->netID;
							data_effect_.x = x_ * 32 + 16, data_effect_.y = y_ * 32 + 16;
							BYTE* raw_effect = packPlayerMoving(&data_effect_, 56);
							raw_effect[8] = pInfo(peer)->netID, raw_effect[3] = 4;
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, peer, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									p.CreatePacket(currentPeer);
									send_raw(currentPeer, 4, raw_effect, 56, ENET_PACKET_FLAG_RELIABLE);
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, blc, raw_effect;
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
					}
					return true;
				}
				switch (items.at(p_).blockType) {
				case BlockTypes::CLOTHING:
				{
					if (p_ <= 0 or p_ >= items.size()) break;
					int c_ = 0;
					modify_inventory(peer, p_, c_);
					if (c_ == 0) break;
					if (abs(x_ * 32 - pInfo(peer)->x) > 15 || abs(y_ * 32 - pInfo(peer)->y) > 15) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("To wear clothing, use on yourself");
						p.Insert(0);
						p.Insert(0);
						p.CreatePacket(peer);
						break;
					}
					if (pInfo(peer)->ances == p_ or pInfo(peer)->back == p_
						or pInfo(peer)->feet == p_ or pInfo(peer)->face == p_
						or pInfo(peer)->hair == p_ or pInfo(peer)->hand == p_
						or pInfo(peer)->mask == p_ or pInfo(peer)->necklace == p_
						or pInfo(peer)->pants == p_ or pInfo(peer)->shirt == p_) {
						unequip_(peer, p_);
					}
					else {
						ClothTypes type_ = items.at(p_).clothType;
						if (type_ == ClothTypes::ANCES)
							pInfo(peer)->ances = p_;
						else if (type_ == ClothTypes::BACK)
							pInfo(peer)->back = p_;
						else if (type_ == ClothTypes::FEET)
							pInfo(peer)->feet = p_;
						else if (type_ == ClothTypes::FACE)
							pInfo(peer)->face = p_;
						else if (type_ == ClothTypes::HAIR)
							pInfo(peer)->hair = p_;
						else if (type_ == ClothTypes::HAND)
							pInfo(peer)->hand = p_;
						else if (type_ == ClothTypes::MASK)
							pInfo(peer)->mask = p_;
						else if (type_ == ClothTypes::NECKLACE)
							pInfo(peer)->necklace = p_;
						else if (type_ == ClothTypes::PANTS)
							pInfo(peer)->pants = p_;
						else if (type_ == ClothTypes::SHIRT)
							pInfo(peer)->shirt = p_;
						if (items.at(p_).on_equip != "") {
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert(items.at(p_).on_equip + (items.at(p_).playmod != "" ? " (`$" + items.at(p_).playmod + "`` mod added)" : ""));
							p.CreatePacket(peer);
						}
						packet_(peer, "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0");
						update_clothes(peer);
					}
					break;
					// kai ant saves paspaudi uzsideti itema
				}
				case BlockTypes::CONSUMABLE:
				{
					if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 3616) != world_->active_jammers.end()) {
						if (world_->owner_name != pInfo(peer)->tankIDName and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Can't use consumables here!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(peer);
							break;
						}
					} switch (p_) {
					case 5664:
					{
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("Sorry, you can only send a Valentines card during Valentines!");
						p.Insert(0), p.Insert(0);
						p.CreatePacket(peer);
						break;
					}
					case 822:
					{
						if (not world_->open_to_public and world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
						if (items.at(t_).blockType == BlockTypes::MAIN_DOOR or items.at(t_).blockType == BlockTypes::BEDROCK)return true;
						PlayerMoving data_{};
						data_.packetType = 19;
						data_.punchX = 822, data_.punchY = 1;
						data_.x = x_ * 32 + 16, data_.y = y_ * 32 + 16;
						BYTE* raw = packPlayerMoving(&data_);
						raw[3] = 4, raw[8] = pInfo(peer)->netID;
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[]raw;
						block_->flags = (block_->flags & 0x04000000 ? block_->flags ^ 0x04000000 : block_->flags | 0x04000000);
						{
							if (block_->flags & 0x04000000) {
								int c_ = -1;
								modify_inventory(peer, 822, c_);
							}
							else {
								// sansas gauti atgal    
								if (rand() % 100 < 50) {
									int c_ = 1;
									modify_inventory(peer, 822, c_);
								}
							}
							PlayerMoving data_{};
							data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							BYTE* raw = packPlayerMoving(&data_, 112);
							BYTE* blc = raw + 56;
							form_visual(blc, *block_, *world_, peer, false);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
						break;
					}
					case 3400:
					{
						if (block_->fg != 10) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("`4This potion is clearly labeled for use only on rocks.``");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(peer);
							break;
						}
						int c_ = -1;
						if (modify_inventory(peer, 3400, c_) == 0) {
							block_->fg = 392;
							PlayerMoving data_{};
							data_.packetType = 17;
							data_.netID = 44;
							data_.YSpeed = 44;
							data_.x = x_ * 32 + 16;
							data_.y = y_ * 32 + 16;
							PlayerMoving data_2{};
							data_2.packetType = 5, data_2.punchX = x_, data_2.punchY = y_, data_2.characterState = 0x8;
							BYTE* raw2 = packPlayerMoving(&data_2, 112);
							BYTE* blc = raw2 + 56;
							form_visual(blc, *block_, *world_, peer, false);
							BYTE* raw = packPlayerMoving(&data_);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == world_->name) {
									packet_(currentPeer, "action|play_sfx\nfile|audio/terraform.wav\ndelayMS|0");
									send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									send_raw(currentPeer, 4, raw2, 112, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							delete[] raw, raw2, blc;
							if (block_->locked) {
								upd_lock(*block_, *world_, peer);
							}
						}
						break;
					}
					case 228: case 1062: case 1778: case 5764: case 10672:
					{
						if (items.at(t_).blockType == BlockTypes::SEED) {
							long long time_ = time(NULL);
							uint32_t laikas = uint32_t((time_ - block_->planted <= items.at(block_->fg).growTime ? time_ - block_->planted : items.at(block_->fg).growTime));
							if (laikas < unsigned int(items.at(block_->fg).growTime)) {
								long long spray_time_ = 3600; // 1 hours
								if (p_ == 1062)
									spray_time_ = _int64(2.592e+6); // 30 days
								if (p_ == 1778)
									spray_time_ = 86400; // 24 hours
								block_->planted -= spray_time_;
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								if (time_ - block_->planted <= items.at(block_->fg).growTime) {
									if (spray_time_ < 86400)
										p.Insert(items.at(block_->fg - 1).name + " Tree aged `$" + to_string(spray_time_ / 60 / 60) + "`` hours");
									else
										p.Insert(items.at(block_->fg - 1).name + " Tree aged `$" + to_string(spray_time_ / 86400) + "`` days");
								}
								else {
									p.Insert(items.at(block_->fg - 1).name + " Tree grew to full size!");
								}
								p.CreatePacket(peer);
								{
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnPlayPositioned");
									p.Insert("audio/spray.wav");
									p.CreatePacket(peer);
								}
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, peer, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw, blc;
								if (block_->locked) {
									upd_lock(*block_, *world_, peer);
								}
								int c_ = -1;
								modify_inventory(peer, p_, c_);
							}
							else {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("This tree has already bloomed, don't waste your spray on it!");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
						}
						else {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Use this on a growing tree to speed it's growth.");
							p.Insert(0);
							p.Insert(1);
							p.CreatePacket(peer);
						}
						break;
					}
					case 6336:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wGrowpedia``|left|6336|\nadd_spacer|small|\nend_dialog|dialog_growpedia||Close|\nadd_spacer|small|\nadd_spacer|small|\nadd_spacer|small|\nadd_textbox|`9Current Task:``|left || \nadd_textbox|<There isn't any tasks at the moment!>|left ||"/*"\nadd_textbox|Build Sugar Cane|left || \nadd_label_with_icon|small|20 Gems``|left|112|\nadd_smalltext|Build 50 Sugar Cane: 5/50|left || \nadd_spacer|small|\nadd_textbox|Break Sugar Cane|left || \nadd_label_with_icon|small|50 Gems``|left|112|\nadd_smalltext|Break 50 Sugar Cane: 4/50|left || \nadd_spacer|small|\nadd_textbox|Plant Sugar Cane Trees|left || \nadd_label_with_icon|small|20 Gems``|left|112|\nadd_smalltext|Plant 10 Sugar Cane Trees: 0/10|left || \nadd_spacer|small|\nadd_textbox|Harvest Sugar Cane Trees|left || \nadd_label_with_icon|small|50 Gems``|left|112|\nadd_smalltext|Harvest 10 Sugar Cane Trees: 0/10|left || \nadd_spacer|small|\nadd_button|showcompletedquests|`wCompleted Tasks``|noflags|0|0|"*/"\nend_dialog|dialog_growpedia||Close|\n");
						p.CreatePacket(peer);
						break;
					}
					case 9266:
					{
						int got = 0;
						modify_inventory(peer, p_, got);
						if (got == 0) break;
						modify_inventory(peer, p_, got = -1);
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("`5GULP! You got 10000000 (gems)!``");
						p.Insert(0);
						p.Insert(1);
						p.CreatePacket(peer);
						{
							gamepacket_t p;
							p.Insert("OnSetBux");
							p.Insert(pInfo(peer)->gems += 10000000);
							p.Insert(1);
							p.CreatePacket(peer);
						}
						break;
					}
					case 1488:
					{
						int got = 0;
						modify_inventory(peer, p_, got);
						if (got == 0) break;
						modify_inventory(peer, p_, got = -1);
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("`5GULP! You got smarter!``");
						p.Insert(0);
						p.Insert(1);
						p.CreatePacket(peer);
						add_peer_xp(peer, 10000);
						break;
					}
					case 5706:
					{
						vector<int> list{ 3567, 13, 57, 17, 381, 1139, 21, 101, 379, 117, 27, 23, 581, 195, 105, 191, 377, 1307, 697, 881, 167, 185, 1323, 165, 3783, 369, 25, 171, 53, 103, 179, 29, 249, 177, 1325, 337, 189, 169, 55, 223, 175, 885, 119, 3573, 199, 549, 681, 655, 107, 163, 31, 671, 889, 887, 193, 127, 1433, 173, 7631, 413, 3571, 3569, 2809, 9393, 225, 111, 109, 201, 59, 607, 285, 2029, 2013, 2015, 1611, 995, 997, 963, 1481, 219, 197, 2023, 2021, 9331, 1305, 823, 1039, 231, 487, 483, 2019, 427, 1757, 2009, 281, 781, 329, 459, 1041, 421, 2787, 2789, 1043, 2797, 181, 613, 65, 4983, 283, 553, 425, 4635, 987, 627, 2017, 989, 61, 4639, 973, 3523, 331, 265, 859, 433, 253, 339, 1105, 439, 4567, 333, 677, 5673, 1427, 5603, 183, 10533, 5731, 7223, 10833, 6035, 6813, 1113, 1047, 653, 2811, 4703, 1429, 847, 665 };
						vector<pair<int, int>> receivingitems;
						int free = get_free_slots(pInfo(peer)), slot = 5, getcount = 1, inventoryfull = 0, removeitem = -1;
						if (free >= slot) {
							for (int i = 0; i < slot; i++) {
								int itemid = list[rand() % list.size()];
								receivingitems.push_back(make_pair(itemid, getcount));
							}
							for (int i = 0; i < slot; i++) {
								int itemcount = 0;
								modify_inventory(peer, receivingitems[i].first, itemcount);
								if (itemcount + getcount > 200) inventoryfull = 1;
							}
							if (inventoryfull == 0) {
								for (int i = 0; i < slot; i++) modify_inventory(peer, receivingitems[i].first, receivingitems[i].second);
								modify_inventory(peer, 5706, removeitem);
							}
						}
						break;
					}
					case 2480:
					{
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wMegaphone``|left|2480|\nadd_textbox|Enter a message you want to broadcast to every player in Growtopia! This will use up 1 Megaphone.|left|\nadd_text_input|words|||128|\nembed_data|itemID|2480\nend_dialog|megaphone|Nevermind|Broadcast|\n");
						p.CreatePacket(peer);
						break;
					}
					case 1404:
					{
						if (world_->owner_name == pInfo(peer)->tankIDName or pInfo(peer)->dev) {
							int used = 0;
							if (y_ < 54) {
								if (block_->fg == 0 || block_->fg == 6 || block_->fg == 8) {
									WorldBlock* block2_ = &world_->blocks.at(x_ + ((y_ + 1) * 100));
									if (block2_->fg == 0 || block2_->fg == 6 || block2_->fg == 8) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world != pInfo(peer)->world) continue;
											pInfo(currentPeer)->x = float(x_) * 32, pInfo(currentPeer)->y = float(y_) * 32;
											gamepacket_t p(0, pInfo(currentPeer)->netID);
											p.Insert("OnSetPos");
											p.Insert(float(x_) * 32, float(y_) * 32);
											p.CreatePacket(currentPeer);
										}
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You've moved the door!");
										p.Insert(0);
										p.Insert(1);
										p.CreatePacket(peer);
										used = 1;
										int c_ = -1;
										modify_inventory(peer, p_, c_);
										DoorMove(peer, x_, y_);
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112);
										BYTE* blc = raw + 56;
										form_visual(blc, *block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
											}
										}
										delete[] raw, blc;
										if (block_->locked) {
											upd_lock(*block_, *world_, peer);
										}
									}
								}
							}
							if (used == 0) {
								packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("There's no room to put the door there! You need 2 empty spaces vertically.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
						}
						else {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("You can only use this in a world that you have world-locked!");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(peer);
						}
						break;
					}
					case 3560:
					{
						if (world_->owner_name == pInfo(peer)->tankIDName or pInfo(peer)->dev) {
							int used = 0;
							if (block_->fg == 0) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("You've moved the world lock!");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
								used = 1;
								int c_ = -1;
								modify_inventory(peer, p_, c_);
								LockMove(peer, x_, y_);
								PlayerMoving data_{};
								data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
								BYTE* raw = packPlayerMoving(&data_, 112);
								BYTE* blc = raw + 56;
								form_visual(blc, *block_, *world_, peer, false);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								if (block_->locked) {
									upd_lock(*block_, *world_, peer);
								}
							}
							if (used == 0) {
								packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("There's no room to put the lock there! You need 1 empty space vertically.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
							}
						}
						else {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("You can only use this in a world that you have world-locked!");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(peer);
						}
						break;
					}
					default:
					{
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert(items.at(p_).name + " not implemented yet but will soon!");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(peer);
						{
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert(items.at(p_).name + " not implemented yet but will soon! If you want it faster let us know!");
							p.CreatePacket(peer);
						}
						break;
					}
					}
					break;
				}
				default:
				{
					if (items.at(p_).magplant or items.at(p_).mag_multiple) {
						if (world_->owner_name != pInfo(peer)->tankIDName) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Only the world owner is allowed to place that here!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(peer);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("Only the world owner is allowed to place that here!");
								p.CreatePacket(peer);
							}
							return false;
						}
					}
					if (block_->locked) {
						WorldBlock* block2_ = &world_->blocks.at(block_->lock_origin);
						string owner_name = block2_->owner_name, user_name = pInfo(peer)->tankIDName;
						if (owner_name != user_name and not pInfo(peer)->dev) {
							if (block2_->fg == 4994 or find(block2_->admins.begin(), block2_->admins.end(), user_name) == block2_->admins.end() and not block2_->open_to_public) {
								if (block2_->fg == 4994) {
									if (not block2_->open_to_public) {
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
										if (p_ != 18) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("That area is owned by " + (block2_->owner_named.substr(0, 2) == "`o" ? "`w" + block2_->owner_name : block2_->owner_named) + "``");
											p.Insert(0);
											p.Insert(1);
											p.CreatePacket(peer);
										}
										return true;
									}
									if (not block2_->build_only and block2_->open_to_public) {
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
										if (p_ != 18) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("This lock allows breaking only!");
											p.Insert(0);
											p.Insert(1);
											p.CreatePacket(peer);
										}
										return false;
									}
								}
								else {
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnPlayPositioned");
									p.Insert("audio/punch_locked.wav");
									if (not pInfo(peer)->invis) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == name_) {
												p.CreatePacket(currentPeer);
											}
										}
									}
									else {
										p.CreatePacket(peer);
									}
									if (p_ != 18) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("That area is owned by " + (block2_->owner_named.substr(0, 2) == "`o" ? "`w" + block2_->owner_name : block2_->owner_named) + "``");
										p.Insert(0);
										p.Insert(1);
										p.CreatePacket(peer);
									}
									return false;
								}
							}
							if (items.at(p_).blockType == BlockTypes::LOCK) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("`w" + block2_->owner_name + "`` allows public building here, but no locks.");
								p.Insert(0);
								p.Insert(0);
								p.CreatePacket(peer);
								{
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnPlayPositioned");
									p.Insert("audio/punch_locked.wav");
									if (not pInfo(peer)->invis) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == name_) {
												p.CreatePacket(currentPeer);
											}
										}
									}
									else {
										p.CreatePacket(peer);
									}
								}
								return false;
							}
						}
					}
					else if (not world_->owner_name.empty() and items.at(p_).blockType != BlockTypes::CONSUMABLE) {
						string owner_name = world_->owner_name, user_name = pInfo(peer)->tankIDName;
						if (owner_name != user_name and not pInfo(peer)->dev) {
							if (find(world_->admins.begin(), world_->admins.end(), user_name) == world_->admins.end() and not world_->open_to_public) {
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnPlayPositioned");
								p.Insert("audio/punch_locked.wav");
								if (not pInfo(peer)->invis) {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name_) {
											p.CreatePacket(currentPeer);
										}
									}
								}
								else {
									p.CreatePacket(peer);
								}
								if (p_ != 18) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("That area is owned by " + (world_->owner_named.substr(0, 2) == "`o" ? "`w" + world_->owner_name : world_->owner_named) + "``");
									p.Insert(0);
									p.Insert(1);
									p.CreatePacket(peer);
								}
								return false;
							}
							if (items.at(p_).blockType == BlockTypes::LOCK) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("`w" + world_->owner_name + "`` allows public building here, but no locks.");
								p.Insert(0);
								p.Insert(0);
								p.CreatePacket(peer);
								{
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnPlayPositioned");
									p.Insert("audio/punch_locked.wav");
									if (not pInfo(peer)->invis) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == name_) {
												p.CreatePacket(currentPeer);
											}
										}
									}
									else {
										p.CreatePacket(peer);
									}
								}
								return false;
							}
						}
					}
					if (world_->owner_name.empty() and items.at(p_).blockType == BlockTypes::VENDING or world_->owner_name.empty() and items.at(p_).item_sucker) {
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("This item can only be used in World-Locked worlds!");
						p.Insert(0), p.Insert(1);
						p.CreatePacket(peer);
						return false;
					}
					// statymas
					if (items.at(p_).blockType == BlockTypes::SEED and items.at(block_->fg).blockType != BlockTypes::SEED and block_->fg != 0 or items.at(p_).blockType != BlockTypes::BACKGROUND and items.at(p_).blockType != BlockTypes::SEED and block_->fg != 0) {
						packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
						return false;
					}
					if (items.at(p_).blockType == BlockTypes::BACKGROUND and items.at(block_->fg).blockType == BlockTypes::BEDROCK or items.at(p_).blockType == BlockTypes::BACKGROUND and items.at(block_->fg).blockType == BlockTypes::MAIN_DOOR) {
						return false;
					}
					if (p_ == 5000 or p_ == 3832 or p_ == 226 or p_ == 3616 or p_ == 1276 or p_ == 1278 or p_ == 4758 or p_ == 3750 or p_ == 4992 or p_ == 3072 or p_ == 4884) {
						for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
							if (world_->blocks.at(i_).fg == p_) {
								if (p_ == 5000 or p_ == 3832) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("``You can only have one " + items.at(p_).name + " in a world.");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
									{
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/punch_locked.wav");
										if (not pInfo(peer)->invis) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == name_) {
													p.CreatePacket(currentPeer);
												}
											}
										}
										else {
											p.CreatePacket(peer);
										}
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("This world already has a `$" + items.at(p_).name + "`` somewhere on it, installing two would be dangerous!");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(peer);
								}
								return false;
							}
						}
					}
					if (items.at(p_).collisionType == 1) {
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == name_ and not pInfo(currentPeer)->ghost) {
								if (y_ == pInfo(currentPeer)->y / 32) {
									if (pInfo(currentPeer)->state == 0 and x_ * 32 < pInfo(currentPeer)->x and abs(x_ * 32 - pInfo(currentPeer)->x) < 32 or pInfo(currentPeer)->state == 16 and abs(x_ * 32 - pInfo(currentPeer)->x) < 32 or pInfo(currentPeer)->state != 16 and abs(x_ * 32 - pInfo(currentPeer)->x) < 20) {
										return false;
									}
								}
							}
						}
					}
					int c_ = -1;
					switch (items.at(p_).blockType) {
					case BlockTypes::PROVIDER:
					{
						punch_tile(peer, x_, y_, 0x3, p_, pInfo(peer)->netID, 0x0);
						long long time_ = time(nullptr);
						if (items.at(block_->fg).properties & Property_AutoPickup)
							block_->planted = time_;
						else
						{
							block_->planted = time_ - ((rand() % 14400) + 1);
							// per real gt kai kurie provider greiciau auga
							block_->planted -= (rand() % 14400) + 1;
						}
						break;
					}
					case BlockTypes::SEED:
					{
						if (items.at(block_->fg).blockType == BlockTypes::SEED) {
							long long time_ = time(nullptr);
							uint32_t laikas = uint32_t((time_ - block_->planted <= items.at(block_->fg).growTime ? time_ - block_->planted : items.at(block_->fg).growTime));
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							if (block_->sp) {
								p.Insert("It would be too dangerous to try to mix three seeds.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
								return false;
							}
							if (laikas == items.at(block_->fg).growTime) {
								p.Insert("This tree is already too big to splice another seed with.");
								p.Insert(0);
								p.Insert(1);
								p.CreatePacket(peer);
								return false;
							}
							for (int i_ = 0; i_ < items.size(); i_++) {
								if (items.at(i_).r_1 == p_ and items.at(i_).r_2 == block_->fg or items.at(i_).r_2 == p_ and items.at(i_).r_1 == block_->fg) {
									p.Insert("`w" + items.at(p_).name + "`` and `w" + items.at(block_->fg).name + "`` have been spliced to make a `$" + items.at(i_).name + " Tree``!");
									p.Insert(0);
									p.Insert(1);
									p.CreatePacket(peer);
									packet_(peer, "action|play_sfx\nfile|audio/success.wav\ndelayMS|0");
									block_->fg = i_ + 1, block_->sp = 1;
									//plant_(peer, block_, x_, y_, p_, false);
									PlayerMoving data_{};
									data_.packetType = 13, data_.plantingTree = p_;
									BYTE* raw = packPlayerMoving(&data_);
									raw[2] = 1;
									send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[]raw;
									{
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112);
										BYTE* blc = raw + 56;
										form_visual(blc, *block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
											}
										}
										delete[] raw, blc;
										if (block_->locked) {
											upd_lock(*block_, *world_, peer);
										}
									}
									if (not mag_place) modify_inventory(peer, p_, c_, false);
									return true;
								}
								else if (i_ + 1 == items.size()) {
									p.Insert("Hmm, it looks like `w" + items.at(block_->fg).name + "`` and `w" + items.at(p_).name + "`` can't be spliced.");
									p.Insert(0);
									p.Insert(1);
									p.CreatePacket(peer);
									return false;
								}
							}
						}
						break;
					}
					case BlockTypes::LOCK:
					{
						if (p_ == 202 or p_ == 204 or p_ == 206 or p_ == 4994) {
							int safe_dis = p_ == 206 ? 7 : p_ == 204 ? 3 : 0; // nes kitaip susipisa viskas
							if (x_ < safe_dis or y_ < safe_dis or 100 - safe_dis < x_ or 60 - safe_dis < y_) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("You can't place that here, move " + to_string(x_ < safe_dis ? safe_dis - x_ : y_ < safe_dis ? safe_dis - y_ : 100 - safe_dis < x_ ? x_ - (100 - safe_dis) : 60 - safe_dis < y_ ? y_ - (60 - safe_dis) : 0) + " block away from border!");
								p.Insert(0);
								p.CreatePacket(peer);
								return true;
							}
							block_->owner_name = pInfo(peer)->tankIDName;
							if (pInfo(peer)->name_color != "`0") block_->owner_named = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
							if (pInfo(peer)->mod == 1 && pInfo(peer)->dev == 1) block_->owner_named = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
							int lock_size = p_ == 202 ? 10 : (p_ == 204 ? 48 : (p_ == 202 ? 200 : 200));
							vector<vector<int>> tiles_ = lock_tiles(world_, x_, y_, lock_size);
							lock_size = tiles_.size();
							PlayerMoving data_{};
							data_.packetType = 15, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
							data_.netID = pInfo(peer)->id;
							data_.plantingTree = p_;
							BYTE* raw;
							if (tiles_.size() != 0) {
								raw = packPlayerMoving(&data_, 112 + tiles_.size() * 2);
								int lalala = 8;
								memcpy(raw + 8, &lock_size, 2);
								memcpy(raw + 12, &lalala, 2);
								BYTE* blc = raw + 56;
								for (int i_ = 0; i_ < tiles_.size(); i_++) {
									vector<int> update_tiles = tiles_.at(i_);
									int x = update_tiles.at(0);
									int y = update_tiles.at(1);
									int sq_ = x + (y * 100);
									WorldBlock* block_ = &world_->blocks.at(sq_);
									if (block_->locked) {
										continue;
									}
									block_->locked = true;
									block_->lock_origin = x_ + (y_ * 100);
									memcpy(blc + (i_ * 2), &sq_, 2);
								}
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == name_) {
										packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
										send_raw(currentPeer, 4, raw, 112 + tiles_.size() * 2, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw, blc;
							}
							else {
								raw = packPlayerMoving(&data_, 56);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == name_) {
										packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
										send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw;
							}
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Area locked.");
							p.Insert(0), p.Insert(0);
							p.CreatePacket(peer);
							{
								PlayerMoving data_{};
								data_.packetType = 13, data_.plantingTree = p_;
								BYTE* raw = packPlayerMoving(&data_);
								raw[2] = 1;
								send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								delete[]raw;
							}
							break;
						}
						if (not world_->owner_name.empty()) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("Only one `$World Lock`` can be placed in a world, you'd have to remove the other one first.");
							p.Insert(0);
							p.Insert(0);
							p.CreatePacket(peer);
							return false;
						}
						for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
							if (world_->blocks.at(i_).fg == 202 or world_->blocks.at(i_).fg == 204 or world_->blocks.at(i_).fg == 206 or world_->blocks.at(i_).fg == 4994) {
								if (world_->blocks.at(i_).owner_name != pInfo(peer)->tankIDName) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("Your `$World Lock`` can't be placed in this world unless everyone else's locks are removed.");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
									return false;
								}
							}
						}
						pInfo(peer)->worlds_owned.push_back(world_->name);
						world_->owner_name = pInfo(peer)->tankIDName;
						if (pInfo(peer)->name_color != "`0") world_->owner_named = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
						if (pInfo(peer)->mod == 1 && pInfo(peer)->dev == 1) world_->owner_named = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
						PlayerMoving data_{};
						data_.packetType = 15, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
						data_.netID = pInfo(peer)->id;
						data_.plantingTree = p_;
						BYTE* raw = packPlayerMoving(&data_, 56);
						gamepacket_t p;
						p.Insert("OnTalkBubble");
						p.Insert(pInfo(peer)->netID);
						p.Insert("`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(peer)->name_color + world_->owner_name + "```5]``");
						p.Insert(0);
						gamepacket_t p2;
						{
							p2.Insert("OnConsoleMessage");
							p2.Insert("`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(peer)->name_color + world_->owner_name + "```5]``");
						}
						gamepacket_t p3(0, pInfo(peer)->netID);
						{
							p3.Insert("OnNameChanged");
							if (pInfo(peer)->mod == 0 && pInfo(peer)->dev == 0)pInfo(peer)->name_color = "`2";
							p3.Insert(pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
						}
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == name_) {
								packet_(currentPeer, "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0");
								send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer), p3.CreatePacket(currentPeer);
							}
						}
						{
							PlayerMoving data_{};
							data_.packetType = 13, data_.plantingTree = p_;
							BYTE* raw = packPlayerMoving(&data_);
							raw[2] = 1;
							send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
						}
						break;
					}
					default:
					{
						punch_tile(peer, x_, y_, 0x3, p_, mag_place ? -1 : pInfo(peer)->netID, 0x0);
						break;
					}
					}
					if (items.at(p_).blockType == BlockTypes::BACKGROUND)
						block_->bg = p_;
					else
						block_->fg = p_;
					if (items.at(p_).blockType == BlockTypes::SEED) {
						plant_(world_, peer, block_, x_, y_, p_, true, mag_place);
					}
					if (items.at(p_).blockType == BlockTypes::PROVIDER) {
						PlayerMoving data_{};
						data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
						BYTE* raw = packPlayerMoving(&data_, 112);
						BYTE* blc = raw + 56;
						form_visual(blc, *block_, *world_, peer, false);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						if (block_->locked) {
							upd_lock(*block_, *world_, peer);
						}
					}
					block_->lp = 0;
					if (items.at(p_).multiple_sides and pInfo(peer)->state == 16) {
						block_->flags |= 0x00200000;
						PlayerMoving data_{};
						data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
						BYTE* raw = packPlayerMoving(&data_, 112);
						BYTE* blc = raw + 56;
						form_visual(blc, *block_, *world_, peer, false);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
							if (pInfo(currentPeer)->world == world_->name) {
								send_raw(currentPeer, 4, raw, 112, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						if (block_->locked) {
							upd_lock(*block_, *world_, peer);
						}
					}
					if (not mag_place) modify_inventory(peer, p_, c_, false);
					break;
				}
				}
				break;

			}

			}
		}
		catch (out_of_range) {
			return false;
		}
	}
	return true;
}
void move_(ENetPeer* peer, PlayerMoving* data) {
	data->netID = pInfo(peer)->netID;
	BYTE* raw = packPlayerMoving(data);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
		if (peer != currentPeer and pInfo(currentPeer)->world == pInfo(peer)->world)
			send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
	}
	delete[]raw;
}