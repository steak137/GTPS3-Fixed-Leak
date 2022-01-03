#pragma once
struct Items {
	uint16_t id = 0, count = 0;
};
struct Friends {
	string name = "";
	bool mute = false, block_trade = false;
	long long last_seen = 0;
};
struct PlayMods {
	int id = 0;
	long long time = 0;
	string user = "";
};
struct Player {
	string ip = "", lo = ""; //real ip
	int blocked = 1;
	vector<string> last_visited_worlds{}, worlds_owned{};
	vector<map<int, int>> trade_items{};
	string name_color = "`0";
	int id = 0, netID = 0, state = 0, trading_with = -1, trade_accept = 0;
	bool accept_the_offer = false;
	int x = -1, y = -1;
	int gems = 0;
	long long int xp = 0;
	map<int, int> ac_{};
	int skin = 0x8295C3FF;
	bool ghost = false, invis = false;
	int n = 0; //newbie passed save
	//  mod role dev role hiden
	string note = "";
	int supp = 0, hs = 0;
	int mod = 0, dev = 0, m_h = 0;
	long long int b_t = 0; // ban time
	long long int b_s = 0; // ban seconds
	string b_r = "", b_b = ""; // ban reason ir banned by
	string m_r = "", m_b = "";
	int hair = 0, shirt = 0, pants = 0, feet = 0, face = 0, hand = 0, back = 0, mask = 0, necklace = 0, ances = 0; /*clothes*/
	string tankIDName = "", tankIDPass = "", requestedName = "", world = "", email = "", country = "", home_world = "", last_wrenched = "";
	vector<Items> inv{};
	vector<Friends> friends{};
	vector<int> last_friends_selection{};
	vector<string> pending_friends{};
	vector<string> bans{}, logs{};
	string last_edit = "";
	bool show_location_ = true, show_friend_notifications_ = true;
	int level = 1, firesputout = 0, carnivalgameswon = 0;
	long long playtime = 0;
	long long int account_created = 0, seconds = 0;
	string aap = "notenabled", aap2 = "", rid = "", mac = "", meta = "";
	map<string, int> achievements{};
	string lastmsg = "", lastmsgworld = "";
	int c_x = 0, c_y = 0;
	int lavaeffect = 0;
	//cooldowns
	long long int i240 = 0, i756 = 0, i758 = 0;
	long long int respawn_time = 0, punch_time = 0, lava_time = 0, world_time = 0, geiger_time = 0, valentine_time = 0, remind_time = 0, warp_time = 0;
	string last_world = "";
	int hack_ = 0;
	bool invalid_data = false;
	int pps = 0;
	long long lpps = 0;
	long long int punch_count = 0;
	int geiger_ = 0;
	int geiger_x = -1, geiger_y = -1;
	bool saved_on_close = false;
	int booty_broken = 0;
	int dd = 0;
	vector<PlayMods> playmods{};
	int magnetron_id = 0;
	int magnetron_x = 0;
	int magnetron_y = 0;
	vector<vector<long long>> completed_blarneys{
		{1, 0},
		{2, 0},
		{3, 0},
		{4, 0},
		{5, 0},
		{6, 0},
		{7, 0},
		{8, 0},
		{9, 0},
	};
	bool block_trade = false;
	int p_x = 0;
	int p_y = 0;
};
#define pInfo(peer) ((Player*)(peer->data))
struct PlayerMoving {
	int32_t netID, effect_flags_check;
	int packetType, characterState, plantingTree, punchX, punchY, secondnetID;
	float x, y, XSpeed, YSpeed;
};

void send_inventory(ENetPeer* peer) {
	const int inv_size = (int)pInfo(peer)->inv.size(), packetLen = 66 + (inv_size * 4) + 4;
	BYTE* d_ = new BYTE[packetLen];
	int MessageType = 0x4, PacketType = 0x9, NetID = -1, CharState = 0x8;
	memset(d_, 0, packetLen);
	memcpy(d_, &MessageType, 1);
	memcpy(d_ + 4, &PacketType, 4);
	memcpy(d_ + 8, &NetID, 4);
	memcpy(d_ + 16, &CharState, 4);
	int endianInvVal = _byteswap_ulong(inv_size);
	memcpy(d_ + 66 - 4, &endianInvVal, 4);
	endianInvVal = _byteswap_ulong(inv_size - 1);
	memcpy(d_ + 66 - 8, &endianInvVal, 4);

	int val = 0;
	for (int i_ = 0; i_ < inv_size; i_++) {
		uint16_t item_id = pInfo(peer)->inv.at(i_).id;
		uint16_t item_count = pInfo(peer)->inv.at(i_).count;
		int val = 0;
		val |= item_id; // cia id
		val |= item_count << 16; // cia count 
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(d_ + (i_ * 4) + 66, &val, 4);
	}
	ENetPacket* const p_ = enet_packet_create(d_, packetLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p_);
	delete[] d_;
}