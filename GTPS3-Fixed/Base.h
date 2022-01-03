#pragma once
using namespace std;
using json = nlohmann::json;
BYTE* item_data;
int item_hash, item_data_size;
vector<string> swear_words = {};
ENetHost* server;
vector<vector<vector<int>>> receptai = {
	{{914, 5}, {916, 5}, {924, 10}, {770, 1}},
	{{914, 30}, {916, 6}, {920, 5}, {906, 1}},
	{{914, 10}, {916, 5}, {918, 1}, {902, 3}},
	{{914, 5}, {924, 4}, {920, 2}, {926, 5}},
	{{914, 6}, {924, 3}, {918, 4}, {1114, 1}},
	{{914, 15}, {920, 4}, {918, 2}, {978, 4}},
	{{917, 10}, {924, 3}, {918, 3}, {772, 1}},
	{{917, 2}, {920, 4}, {918, 3}, {904, 1}},
	{{924, 20}, {920, 4}, {918, 5}, {922, 1}},
	{{914, 20}, {916, 10}, {922, 1}, {1162, 1}},
	{{914, 10}, {920, 2}, {922, 1}, {1746, 5}},
	{{914, 20}, {918, 15}, {922, 10}, {1542, 1}},
	{{916, 8}, {924, 4}, {922, 1}, {2588, 1}},
	{{916, 1}, {918, 1}, {922, 1}, {1866, 2}},
	{{924, 3}, {920, 3}, {922, 3}, {908, 1}},
	{{924, 4}, {918, 3}, {922, 1}, {1310, 1}},
	{{920, 200}, {918, 200}, {922, 200}, {910, 1}},
	{{914, 10}, {922, 10}, {1962, 10}, {4582, 1}},
	{{916, 9}, {924, 5}, {1962, 1}, {4552, 1}},
	{{6970, 50}, {7006, 50}, {6986, 50}, {6948, 1}},
	{{7156, 20}, {6986, 5}, {7154, 5}, {7150, 1}},
	{{7006, 10}, {6970, 5}, {6988, 5}, {7008, 1}},
	{{6828, 2}, {186, 100}, {6972, 20}, {6934, 1}},
	{{6834, 2}, {186, 100}, {6960, 2}, {6936, 1}},
	{{6250, 2}, {186, 100}, {6978, 20}, {6930, 1}},
	{{6940, 2}, {186, 100}, {6976, 2}, {6944, 1}},
	{{6236, 1}, {6962, 1}, {6992, 5}, {6918, 1}},
	{{6238, 1}, {6960, 5}, {7012, 1}, {6920, 1}},
	{{6988, 100}, {7010, 15}, {6976, 50}, {6946, 1}},
	{{6244, 1}, {260, 100}, {6962, 2}, {6928, 1}},
	{{6256, 1}, {260, 100}, {6994, 10}, {6932, 1}},
	{{6238, 1}, {260, 100}, {6960, 2}, {6926, 1}},
	{{7308, 1}, {260, 100}, {7012, 10}, {7306, 1}},
	{{6926, 1}, {6972, 1}, {7010, 1}, {6922, 1}},
	{{6240, 1}, {6972, 1}, {6992, 10}, {6924, 1}},
	{{7158, 20}, {7160, 3}, {6978, 3}, {7152, 1}},
	{{6994, 100}, {6978, 100}, {6964, 100}, {6950, 1}},
	{{6980, 100}, {6998, 100}, {7016, 100}, {6952, 1}},
	{{6984, 75}, {7018, 75}, {6968, 75}, {6954, 1}}
};
vector<string> get_properties(unsigned char btype, unsigned char bcateg) {
	vector<string> list;
	if ((btype & 0x40) > 0) {
		list.push_back("NoShadow");
	} if ((btype & 0x20) > 0) {
		list.push_back("NoSelf");
	} if ((btype & 2) > 0) {
		list.push_back("Wrenchable");
	} if ((btype & 8) > 0) {
		list.push_back("Dropless");
	} if ((btype & 0x10) > 0) {
		list.push_back("NoSeed");
	} if ((btype & 4) > 0) {
		list.push_back("Permanent");
	} if ((btype & 1) > 0) {
		list.push_back("MultiFacing");
	} if ((btype & 0x80) > 0) {
		list.push_back("WorldLock");
	} if ((bcateg & 0x80) > 0) {
		list.push_back("Untradable");
	} if ((bcateg & 0x20) > 0) {
		list.push_back("Foreground");
	} if ((bcateg & 0x10) > 0) {
		list.push_back("Public");
	} if ((bcateg & 1) > 0) {
		list.push_back("Beta");
	} if ((bcateg & 4) > 0) {
		list.push_back("Mod");
	} if ((bcateg & 8) > 0) {
		list.push_back("RandomGrow");
	} if ((bcateg & 0x40) > 0) {
		list.push_back("Holiday");
	} if ((bcateg & 2) > 0) {
		list.push_back("AutoPickup");
	}
	return list;
}
string getItemCategory(const char actionType, string name_) {
	switch (actionType) {
		case 0:
			return "Fist";
		case 1:
			return "Wrench";
		case 2:
			return "Door";
		case 3:
			return "Lock";
		case 4:
			return "Gems";
		case 5:
			return "Treasure";
		case 6:
			return "Deadly_Block";
		case 7:
			return "Trampoline_Block";
		case 8:
			return "Consummable";
		case 9:
			return "Gateway";
		case 10:
			return "Sign";
		case 11:
			return "SFX_Foreground";
		case 12:
			return "Toggleable_Foreground";
		case 13:
			return "Main_Door";
		case 14:
			return "Platform";
		case 15:
			return "Bedrock";
		case 16:
			return "Pain_Block";
		case 17:
			return "Foreground_Block";
		case 18:
			return "Background_Block";
		case 19:
			return "Seed";
		case 20:
			return "Clothing";
		case 21:
			return "Animated_Foreground_Block";
		case 22:
			return "SFX_Background";
		case 23:
			return "Toggleable_Background";
		case 24:
			return "Bouncy";
		case 25:
			return "Spike";
		case 26:
			return "Portal";
		case 27:
			return "Checkpoint";
		case 28:
			return "Sheet_Music";
		case 29:
			return "Slippery_Block";
		case 48:
			return "Unknown";
		case 31:
			return "Switch_Block";
		case 32:
			return "Chest";
		case 33:
			return "Mailbox";
		case 34:
			return "Bulletin_Board";
		case 35:
			return "Event_Mystery_Block";
		case 36:
			return "Random_Block";
		case 37:
			return "Component";
		case 38:
			return "Provider";
		case 39:
			return "Chemical_Combiner";
		case 40:
			return "Achievement_Block";
		case 41:
			return "Weather_Machine";
		case 42:
			return "Scoreboard";
		case 43:
			return "Sungate";
		case 44:
			return "Profile";
		case 45:
			return "Toggleable_Deadly_Block";
		case 46:
			return "Heart_Monitor";
		case 47:
			return "Donation_Box";
		case 49:
			return "Mannequin";
		case 50:
			return "Security_Camera";
		case 51:
			return "Magic_Egg";
		case 52:
			return "Game_Block";
		case 53:
			return "Game_Generator";
		case 54:
			return "Xenonite";
		case 55:
			return "Phone_Booth";
		case 56:
			return "Crystal";
		case 57:
			return "Crime_Villain";
		case 58:
			return "Clothing_Compactor";
		case 59:
			return "Spotlight";
		case 60:
			return "Pushing_Block";
		case 61:
			return "Display";
		case 62:
			return "Vending";
		case 63:
			return "Fish";
		case 64:
			return "Fish_Tank_Port";
		case 65:
			return "Solar_Collector";
		case 66:
			return "Forge";
		case 67:
			return "Giving_Tree";
		case 68:
			return "Giving_Tree_Stump";
		case 69:
			return "Steam_Block";
		case 70:
			return "Steam_Pain_Block";
		case 71:
			return "Steam_Music_Block";
		case 72:
			return "Silkworm";
		case 73:
			return "Sewing_Machine";
		case 74:
			return "Country_Flag";
		case 75:
			return "Lobster_Trap";
		case 76:
			return "Painting_Easel";
		case 77:
			return "Battle_Pet_Cage";
		case 78:
			return "Pet_Trainer";
		case 79:
			return "Steam_Engine";
		case 80:
			return "Lock_Bot";
		case 81:
			return "Weather_Machine_S1";
		case 82:
			return "Spirit_Storage";
		case 83:
			return "Display_Shelf";
		case 84:
			return "VIP";
		case 85:
			return "Chal_Timer";
		case 86:
			return "Chal_Flag";
		case 87:
			return "Fish_Mount";
		case 88:
			return "Portrait";
		case 89:
			return "Weather_Machine_S2";
		case 90:
			return "Fossil";
		case 91:
			return "Fossil_Prep_Station";
		case 92:
			return "DNA_Processor";
		case 93:
			return "Blaster";
		case 94:
			return "Valhowla_Treasure";
		case 95:
			return "Chemsynth";
		case 96:
			return "Chemsynth_Tank";
		case 97:
			return "Untrade_A_Box";
		case 98:
			return "Oven";
		case 99:
			return "Audio";
		case 100:
			return "Geiger_Charger";
		case 101:
			return "Adventure_Reset";
		case 102:
			return "Tomb_Robber";
		case 103:
			return "Faction";
		case 104:
			return "Red_Faction";
		case 105:
			return "Green_Faction";
		case 106:
			return "Blue_Faction";
		case 107:
			return "Artifact";
		case 108:
			return "LemonJelly";
		case 109:
			return "FishTrainingTank";
		case 110:
			return "FishingBlock";
		case 111:
			return "ItemSucker";
		case 112:
			return "Planter";
		case 113:
			return "Robot";
		case 114:
			return "Command";
		case 115:
			return "Ticket";
		case 116:
			return "Stats_Block";
		case 117:
			return "Field_Node";
		case 118:
			return "Ouija_Board";
		case 119:
			return "Architect_Machine";
		case 120:
			return "Starship";
		case 121:
			return "Spike";
		case 122:
			return "Gravity_Well";
		case 123:
			return "Autobreak_Blocks";
		case 124:
			return "Autobreak_Trees";
		case 125:
			return "Autobreak";
		case 126:
			return "TimedBlock";
		case 127:
			return "TimedPlatform";
		case 128:
			return "Mud_Puddle";
		case 129:
			return "Root_Cutting";
		case 130:
			return "Safe_Vault";
		default:
			return "";
	}
}
string join(const vector<string> v, const char delimeter) {
	string str;
	for (auto p = v.begin(); p != v.end(); ++p) {
		str += *p;
		if (p != (v.end() - 1))
			str += delimeter;
	}
	return str;
}

inline vector<string> explode(const string& delimiter, const string& str) {
	vector<string> arr;
	SIZE_T strleng = str.length(); // buvo const int strleng = str.length();
	SIZE_T delleng = delimiter.length(); // buvo const int delleng = delimiter.length();
	if (delleng == 0)
		return arr;
	SIZE_T i = 0; // buvo int i = 0;
	SIZE_T k = 0; // buvo int k = 0;
	while (i < strleng) {
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng) {
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else {
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}

BlockTypes get_blocktype(string c_, string name_) {
	if (c_ == "Foreground_Block") {
		return BlockTypes::FOREGROUND;
	} else if (c_ == "Background_Block") {
		return BlockTypes::BACKGROUND;
	} else if (c_ == "Seed") {
		return BlockTypes::SEED;
	} else if (c_ == "Consummable") {
		return BlockTypes::CONSUMABLE;
	} else if (c_ == "Pain_Block") {
		return BlockTypes::PAIN_BLOCK;
	} else if (c_ == "Main_Door") {
		return BlockTypes::MAIN_DOOR;
	} else if (c_ == "Bedrock") {
		return BlockTypes::BEDROCK;
	} else if (c_ == "Door") {
		return BlockTypes::DOOR;
	} else if (c_ == "Fist") {
		return BlockTypes::FIST;
	} else if (c_ == "Sign") {
		return BlockTypes::SIGN;
	} else if (c_ == "Back") {
		return BlockTypes::BACKGROUND;
	} else if (c_ == "Sheet_Music") {
		return BlockTypes::BACKGROUND;
	} else if (c_ == "Wrench") {
		return BlockTypes::WRENCH;
	} else if (c_ == "Checkpoint") {
		return BlockTypes::CHECKPOINT;
	} else if (c_ == "Lock") {
		return BlockTypes::LOCK;
	} else if (c_ == "Gateway") {
		return BlockTypes::GATEWAY;
	} else if (c_ == "Clothing") {
		return BlockTypes::CLOTHING;
	} else if (c_ == "Platform") {
		return BlockTypes::PLATFORM;
	} else if (c_ == "SFX_Foreground") {
		return BlockTypes::SFX_FOREGROUND;
	} else if (c_ == "Gems") {
		return BlockTypes::GEMS;
	} else if (c_ == "Toggleable_Foreground") {
		return BlockTypes::TOGGLE_FOREGROUND;
	} else if (c_ == "Chemical_Combiner") {
		return BlockTypes::CHEMICAL_COMBINER;
	} else if (c_ == "Treasure") {
		return BlockTypes::TREASURE;
	} else if (c_ == "Deadly_Block") {
		return BlockTypes::DEADLY;
	} else if (c_ == "Trampoline_Block") {
		return BlockTypes::TRAMPOLINE;
	} else if (c_ == "Animated_Foreground_Block") {
		return BlockTypes::ANIM_FOREGROUND;
	} else if (c_ == "Portal") {
		return BlockTypes::PORTAL;
	} else if (c_ == "Random_Block") {
		return BlockTypes::RANDOM_BLOCK;
	} else if (c_ == "Bouncy") {
		return BlockTypes::BOUNCY;
	} else if (c_ == "Chest") {
		return BlockTypes::CHEST;
	} else if (c_ == "Switch_Block") {
		return BlockTypes::SWITCH_BLOCK;
	} else if (c_ == "Magic_Egg") {
		return BlockTypes::MAGIC_EGG;
	} else if (c_ == "Crystal") {
		return BlockTypes::CRYSTAL;
	} else if (c_ == "Mailbox") {
		return BlockTypes::MAILBOX;
	} else if (c_ == "Bulletin_Board") {
		return BlockTypes::BULLETIN_BOARD;
	} else if (c_ == "Faction") {
		return BlockTypes::FACTION;
	} else if (c_ == "Component") {
		return BlockTypes::COMPONENT;
	} else if (c_ == "Weather_Machine") {
		return BlockTypes::WEATHER;
	} else if (c_ == "ItemSucker") {
		return BlockTypes::SUCKER;
	} else if (c_ == "Fish_Tank_Port") {
		return BlockTypes::FISH;
	} else if (c_ == "Steam_Block") {
		return BlockTypes::STEAM;
	} else if (c_ == "ground_Block") {
		return BlockTypes::GROUND_BLOCK;
	} else if (c_ == "Display") {
		return BlockTypes::DISPLAY;
	} else if (c_ == "Untrade_A_Box" || c_ == "Safe_Vault") {
		return BlockTypes::STORAGE;
	} else if (c_ == "Vending") {
		return BlockTypes::VENDING;
	} else if (c_ == "Donation_Box") {
		return BlockTypes::DONATION;
	} else if (c_ == "Phone_Booth") {
		return BlockTypes::PHONE;
	} else if (c_ == "Sewing_Machine") {
		return BlockTypes::SEWINGMACHINE;
	} else if (c_ == "Crime_Villain") {
		return BlockTypes::CRIME_VILLAIN;
	} else if (c_ == "Provider") {
		return BlockTypes::PROVIDER;
	} else {
		return BlockTypes::UNKNOWN;
	}
}
char* text_(ENetPacket* packet) {
	char zero = 0;
	memcpy(packet->data + packet->dataLength - 1, &zero, 1);
	return (char*)(packet->data + 4);
}
inline int message_(ENetPacket* packet) {
	if (packet->dataLength > 3u) {
		return *(packet->data);
	}
	return 0;
}
inline void send_(ENetPeer* peer, int num, char* data, const int len) {
	const auto packet = enet_packet_create(nullptr, len + 5, ENET_PACKET_FLAG_RELIABLE);
	memcpy(packet->data, &num, 4);
	if (data != nullptr) {
		memcpy(packet->data + 2, data, len);
	}
	char zero = 0;
	memcpy(packet->data + 2 + len, &zero, 1);
	enet_peer_send(peer, 0, packet);
}
int init_enet(int port) {
	enet_initialize();
	ENetAddress address;
	enet_address_set_host(&address, "0.0.0.0");
	address.port = 17092;
	server = enet_host_create(&address, 1024, 10, 0, 0);
	server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(server);
	return 0;
}
ClothTypes get_clothtype(string t_, BlockTypes a_) {
	if (a_ == BlockTypes::CLOTHING) {
		if (t_ == "Hat") {
			return ClothTypes::HAIR;
		} else if (t_ == "Shirt") {
			return ClothTypes::SHIRT;
		} else if (t_ == "Pants") {
			return ClothTypes::PANTS;
		} else if (t_ == "Feet") {
			return ClothTypes::FEET;
		} else if (t_ == "Face") {
			return ClothTypes::FACE;
		} else if (t_ == "Hand") {
			return ClothTypes::HAND;
		} else if (t_ == "Back") {
			return ClothTypes::BACK;
		} else if (t_ == "Hair") {
			return ClothTypes::HAIR;
		} else if (t_ == "Chest") {
			return ClothTypes::NECKLACE;
		} else if (t_ == "Ances") {
			return ClothTypes::ANCES;
		} else if (t_ == "Mask") {
			return ClothTypes::MASK;
		} else if (t_ == "Necklace") {
			return ClothTypes::NECKLACE;
		} else {
			return ClothTypes::NONE;
		}
	} else {
		return ClothTypes::NONE;
	}
}
inline uint32_t get_hash(unsigned char* str, const int len) {
	unsigned char* n = static_cast<unsigned char*>(str);
	uint32_t acc = 0x55555555;
	if (len == 0) {
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	} else {
		for (int i = 0; i < len; i++)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	return acc;
}

int get_punch_id(const int id_) {
	switch (id_) {
		case 138: return 1;
		case 366: return 2;
		case 1464: return 2;
		case 472: return 3;
		case 768: return 5;
		case 900: return 6;
		case 910: return 7;
		case 930: return 8;
		case 1010: return 8;
		case 1016: return 9;
		case 5138: return 10;
		case 1204: return 10;
		case 1378: return 11;
		case 1440: return 12;
		case 1484: return 13;
		case 1512: return 14;
		case 1542: return 15;
		case 1576: return 16;
		case 1676: return 17;
		case 1710: return 18;
		//case 1748: return 19; tipo sitas jau yra   
		case 1780: return 20;
		case 1782: return 21;
		case 1804: return 22;
		case 5140: return 22;
		case 1868: return 23;
		case 1874: return 24;
		case 1946: return 25;
		case 1952: return 26;
		case 1956: return 27;
		case 1748: return 28;
		case 2908: return 29;
		case 6312: return 29;
		case 8554: return 29;
		case 1980: return 30;
		case 2066: return 31;
		case 2212: return 32;
		case 2218: return 33;
		case 2220: return 34;
		case 2266: return 35;
		case 2386: return 36;
		case 2388: return 37;
		case 2450: return 38;
		case 2476: return 39;
		case 4748: return 40;
		case 2512: return 41;
		case 2572: return 42;
		case 2592: return 43;
		case 2596: return 43;
		case 2720: return 44;
		case 2752: return 45;
		case 2754: return 46;
		case 2756: return 47;
		case 2802: return 49;
		case 2866: return 50;
		case 2876: return 51;
		case 2878: return 52;
		case 2880: return 52;
		case 2906: return 53;
		case 2886: return 54;
		case 2890: return 55;
		case 3066: return 57;
		case 3124: return 58;
		case 3168: return 59;
		case 3214: return 60;
		case 9194: return 60;
		case 7408: return 61;
		case 3274: return 62;
		case 3300: return 64;
		case 3418: return 65;
		case 3476: return 66;
		case 3686: return 68;
		case 3716: return 69;
		case 4290: return 71;
		case 4474: return 72;
		case 4464: return 73;
		case 4746: return 75;
		case 4778: return 76;
		case 6026: return 76;
		case 4996: return 77;
		case 4840: return 78;
		case 5206: return 79;
		case 5480: return 80;
		case 6110: return 81;
		case 6308: return 82;
		case 6310: return 83;
		case 6298: return 84;
		case 6756: return 85;
		case 7044: return 86;
		case 6892: return 87;
		case 7088: return 89;
		case 7098: return 90;
		case 7192: return 91;
		case 7136: return 92;
		case 3166: return 93;
		case 7216: return 94;
		case 7196: return 95;
		case 7392: return 96;
		case 7384: return 98;
		case 7414: return 99;
		case 7402: return 100;
		case 7424: return 101;
		case 7488: return 103;
		case 7586: return 104;
		case 7650: return 105;
		case 6804: return 106;
		case 7568: return 107;
		case 7570: return 107;
		case 7572: return 107;
		case 7574: return 107;
		case 7668: return 108;
		case 7660: return 109;
		case 7736: return 111;
		case 9116: return 111;
		case 9118: return 111;
		case 9120: return 111;
		case 9122: return 111;
		case 7836: return 112;
		case 7838: return 112;
		case 7840: return 112;
		case 7842: return 112;
		case 7950: return 113;
		case 8002: return 114;
		case 8022: return 116;
		case 8036: return 118;
		case 8038: return 120;
		case 8816: return 128;
		case 8818: return 128;
		case 8820: return 128;
		case 8822: return 128;
		case 8910: return 129;
		case 8942: return 130;
		case 8944: return 131;
		case 8432: return 132;
		case 8434: return 132;
		case 8436: return 132;
		case 8438: return 132;
		case 8950: return 132;
		case 8960: return 134;
		case 9006: return 135;
		case 9058: return 136;
		case 9136: return 139;
		case 9138: return 140;
		case 9236: return 140;
		case 9410: return 150;
	}
	return 0;
}
struct dotted : numpunct<char> {
	char do_thousands_sep()   const { return ','; }
	string do_grouping() const { return "\3"; }
	static void imbue(ostream& os) { os.imbue(locale(os.getloc(), new dotted)); }
};
string replace_str(string& str, const string& from, const string& to) {
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}
int items_dat() {
	string n_ = "items.dat";
	ifstream file(n_, ios::binary | ios::ate);
	__int64 size = file.tellg(); // buvo int size = file.tellg();
	if (size == -1) return -1;
	item_data_size = (int)size;
	char* data = new char[size];
	file.seekg(0, ios::beg);
	file.read((char*)(data), size);
	item_data = new BYTE[60 + size];
	int MessageType = 0x4, PacketType = 0x10, NetID = -1, CharState = 0x8;
	memset(item_data, 0, 60);
	memcpy(item_data, &MessageType, 4);
	memcpy(item_data + 4, &PacketType, 4);
	memcpy(item_data + 8, &NetID, 4);
	memcpy(item_data + 16, &CharState, 4);
	memcpy(item_data + 56, &size, 4);
	file.seekg(0, std::ios::beg);
	file.read((char*)(item_data + 60), size);
	item_hash = get_hash((unsigned char*)data, (const int)size);
	int memPos = 0, itemCount;
	int16_t itemsdatVersion = 0;
	memcpy(&itemsdatVersion, data + memPos, 1);
	memPos += 2;
	memcpy(&itemCount, data + memPos, 4);
	const string key_ = "PBG892FXX982ABC*";
	memPos += 4;
	for (int i = 0; i < itemCount; i++) {
		ItemDB def;
		memcpy(&def.id, data + memPos, 4);
		memPos += 4;
		def.editableType = data[memPos];
		if (def.editableType == 3 || def.editableType == 31 || def.editableType == 1 || def.editableType == 21 || def.editableType == 23) {
			def.multiple_sides = 1;
		}
		memPos += 1;
		def.itemCategory = data[memPos];
		memPos += 1;
		def.actionType = data[memPos];
		if (def.actionType == 85) {
			def.timer = 1;
		} else if (def.actionType == 9) {
			def.entrance = 1;
		}
		else if (def.actionType == -122) {
			def.infinitymachine = 1;
		}
		else if (def.actionType == 82) {
			def.spirit = 1;
		}
		else if (def.actionType == 100) {
			def.charger = 1;
		}
		else if (def.actionType == 55) {
			def.trans = 1;
		}
		else if (def.actionType == 93) {
			def.trickster = 1;
		} else if (def.actionType == 12 or def.actionType == 45 or def.actionType == 32 or def.actionType == 31 or def.actionType == 122) {
			if (def.actionType == 31) {
				def.can_be_changed_to_public = 1;
			} else if (def.actionType == 12) {
				def.can_be_changed_two_types = 1;
			}
			def.toggleable = 1;
		} else if (def.actionType == 124 or def.actionType == 123) {
			def.magplant = 1;
		} else if (def.actionType == 111) {
			def.item_sucker = 1;
		} else if (def.actionType == 125) {
			def.mag_multiple = 1;
		}
		memPos += 1;
		def.hitSoundType = data[memPos];
		memPos += 1;
		int16_t strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.name += data[memPos] ^ (key_[(j + def.id) % key_.length()]);
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.texture += data[memPos];
			memPos++;
		}
		memcpy(&def.textureHash, data + memPos, 4);
		memPos += 4;
		def.itemKind = memPos[data];
		memPos += 1;
		memcpy(&def.val1, data + memPos, 4);
		memPos += 4;
		def.textureX = data[memPos];
		memPos += 1;
		def.textureY = data[memPos];
		memPos += 1;
		def.spreadType = data[memPos];
		memPos += 1;
		def.isStripeyWallpaper = data[memPos];
		memPos += 1;
		def.collisionType = data[memPos];
		if (def.collisionType == 1) {
			def.solid = 1;
		}
		memPos += 1;
		def.breakHits = data[memPos];
		if (def.breakHits <= 0 or def.breakHits > 42 * 6)
			def.breakHits = 42 * 6;
		memPos += 1;
		memcpy(&def.dropChance, data + memPos, 4);
		memPos += 4;
		def.clothingType = data[memPos];
		memPos += 1;
		memcpy(&def.rarity, data + memPos, 2);
		memPos += 2;
		def.maxAmount = data[memPos];
		memPos += 1;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraFile += data[memPos];
			memPos++;
		}
		memcpy(&def.extraFileHash, data + memPos, 4);
		memPos += 4;
		memcpy(&def.audioVolume, data + memPos, 4);
		memPos += 4;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petName += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petPrefix += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petSuffix += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petAbility += data[memPos];
			memPos++;
		}
		def.seedBase = data[memPos];
		memPos += 1;
		def.seedOverlay = data[memPos];
		memPos += 1;
		def.treeBase = data[memPos];
		memPos += 1;
		def.treeLeaves = data[memPos];
		memPos += 1;
		memcpy(&def.seedColor, data + memPos, 4);
		memPos += 4;
		memcpy(&def.seedOverlayColor, data + memPos, 4);
		memPos += 4;
		memPos += 4;
		memcpy(&def.growTime, data + memPos, 4);
		memPos += 4;
		memcpy(&def.val2, data + memPos, 2);
		memPos += 2;
		memcpy(&def.isRayman, data + memPos, 2);
		memPos += 2;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraOptions += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.texture2 += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraOptions2 += data[memPos];
			memPos++;
		}
		memPos += 80;
		if (itemsdatVersion >= 11) {
			strLen = *(int16_t*)&data[memPos];
			memPos += 2;
			for (int j = 0; j < strLen; j++) {
				def.punchOptions += data[memPos];
				memPos++;
			}
		}
		if (itemsdatVersion >= 12) memPos += 13;
		if (itemsdatVersion >= 13) memPos += 4;
		if (itemsdatVersion >= 14) memPos += 4;
		if (i != def.id) return -1;
		string category = getItemCategory(def.actionType, def.name);
		string clothingType_ = "";
		if (def.actionType == 20) {
			switch (def.clothingType) {
			case 0: clothingType_ = "Hair";
				break;
			case 1: clothingType_ = "Shirt";
				break;
			case 2: clothingType_ = "Pants";
				break;
			case 3: clothingType_ = "Feet";
				break;
			case 4: clothingType_ = "Face";
				break;
			case 5: clothingType_ = "Hand";
				break;
			case 6: clothingType_ = "Back";
				break;
			case 7: clothingType_ = "Mask";
				break;
			case 8: clothingType_ = "Necklace";
				break;
			case 9: clothingType_ = "Ances";
				break;
			default: break;
			}
		}
		if ((def.id % 2) == 1) category = "Seed";
		vector<string> prop_ = get_properties(def.actionType, def.itemCategory);
		string thisss = (prop_.empty() ? "0" : join(prop_, ','));
		vector<string> properties = explode(",", thisss);
		def.properties = Property_Zero;
		for (string& prop : properties) {
			if (prop == "NoSeed") {
				def.properties += Property_NoSeed;
			} if (prop == "Dropless") {
				def.properties += Property_Dropless;
			} if (prop == "Beta") {
				def.properties += Property_Beta;
			} if (prop == "Mod") {
				def.properties += Property_Mod;
			} if (prop == "Untradable") {
				def.properties += Property_Untradable;
				def.untradeable = 1;
			} if (prop == "Wrenchable") {
				def.properties += Property_Wrenchable;
			} if (prop == "MultiFacing") {
				def.properties += Property_MultiFacing;
			} if (prop == "Permanent") {
				def.properties += Property_Permanent;
			} if (prop == "AutoPickup") {
				def.properties += Property_AutoPickup;
			} if (prop == "WorldLock") {
				def.properties += Property_WorldLock;
			} if (prop == "NoSelf") {
				def.properties += Property_NoSelf;
			} if (prop == "RandomGrow") {
				def.properties += Property_RandomGrow;
			} if (prop == "Public") {
				def.properties += Property_Public;
			} if (prop == "Foreground") {
				def.properties += Property_Foreground;
			} if (prop == "OnlyCombiner") {
				def.properties += Property_Chemical;
			}
		}
		if (def.id == 3 or def.id == 1458) {
			cout << def.id << " >> " << def.collisionType << " >> " << def.toggleable << " >> " << def.entrance << endl;
		}
		def.blockType = get_blocktype(category, def.name);
		def.clothType = get_clothtype(clothingType_, def.blockType);
		if (def.id == 3292 or def.id == 270)
			cout << def.id << " " << def.name << " " << clothingType_ << endl;
		def.effect = get_punch_id(def.id);
		items.push_back(def);
		if (items.at(def.id).properties & Property_RandomGrow) {
			if (def.name.find("Tangram Block") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Tangram Block Seed" : "Tangram Block");
			else if (def.name.find("Card Block") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Card Block Seed" : "Card Block");
			else if (def.name.find("Growsaber") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Growsaber Seed" : "Growsaber");
			else if (def.name.find("Surgical") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Surgical Tool Seed" : "Surgical Tool");
			else if (def.name.find("Super Shirt") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Shirt Seed" : "Super Shirt");
			else if (def.name.find("Muscle Shirt") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Muscle Shirt Seed" : "Muscle Shirt");
			else if (def.name.find("Heroic Tights") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Heroic Tights Seed" : "Heroic Tights");
			else if (def.name.find("Super Tights") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Tights Seed" : "Super Tights");
			else if (def.name.find("Heroic Boots") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Heroic Boots Seed" : "Heroic Boots");
			else if (def.name.find("Superhero Mask") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Superhero Mask Seed" : "Superhero Mask");
			else if (def.name.find("Crimefighter Mask") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Crimefighter Mask Seed" : "Crimefighter Mask");
			else if (def.name.find("Super Cape") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Cape Seed" : "Super Cape");
			else if (def.name.find("Superheroine Top") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Superheroine Top Seed" : "Superheroine Top");
			else if (def.name.find("Super Eye Mask") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Eye Seed" : "Super Eye");
			else if (def.name.find("Super Logo") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Logo Seed" : "Super Logo");
			else if (def.name.find("Superpower") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Superpower Seed" : "Superpower");
			else if (def.name.find("Villain Portrait") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Villain Portrait Seed" : "Villain Portrait");
			else if (def.name.find("Super Logo") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Super Logo Seed" : "Super Logo");
			else if (def.name.find("Fashionable Dress") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Fashionable Dress Seed" : "Fashionable Dress");
			else if (def.name.find("Stylin' Dress") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Stylin' Dress Seed" : "Stylin' Dress");
			else if (def.name.find("High Heels") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "High Heels Seed" : "High Heels");
			else if (def.name.find("Fashion Purse") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Fashion Purse Seed" : "Fashion Purse");
			else if (def.name.find("Number Block") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Number Block Seed" : "Number Block");
			else if (def.name.find("Number") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Number Seed" : "Number");
			else if (def.name.find("Paint Bucket") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Paint Bucket Seed" : "Paint Bucket");
			else if (def.name.find("Crayon") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Crayon Block Seed" : "Crayon Block");
			else if (def.name.find("Command") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Command Tool Seed" : "Command Tool");
			else if (def.name.find("Growmoji") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Growmoji Seed" : "Growmoji");
			else if (def.name.find("Guild Flag") != string::npos)
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? "Guild Flag Seed" : "Guild Flag");
			else {
				int a_ = 0;
				int last_id = 0;
				while (items.at(def.id - a_).properties & Property_RandomGrow) {
					if (items.at(def.id - a_).blockType != BlockTypes::SEED) last_id = def.id - a_;
					a_++;
				}
				items.at(def.id).name = (def.name.find("Seed") != string::npos ? items.at(last_id+1).name : items.at(last_id).name);
			}
		}
	}
	delete[] data;
	ifstream file_info("informacija.txt");
	if (file_info.is_open()) {
		string line_info;
		while (getline(file_info, line_info)) {
			vector<string> d_ = explode("|", line_info);
			if (d_[1] == "Earth")
				items[atoi(d_[0].c_str())].chi = 0;
			else if (d_[1] == "Fire")
				items[atoi(d_[0].c_str())].chi = 1;
			else if (d_[1] == "Wind")
				items[atoi(d_[0].c_str())].chi = 2;
			else if (d_[1] == "Water")
				items[atoi(d_[0].c_str())].chi = 3;
			else
				items[atoi(d_[0].c_str())].chi = 4;
			items[atoi(d_[0].c_str())].description = d_[6];
			if (d_[2] != "" and d_[3] != "" and isdigit(d_[2][0]) and isdigit(d_[3][0])) {
				items[atoi(d_[0].c_str())].r_1 = atoi(d_[2].c_str()), items[atoi(d_[0].c_str())].r_2 = atoi(d_[3].c_str());
			}
			if (d_[4] != "") {
				items[atoi(d_[0].c_str())].on_equip = d_[4];
			}
			if (d_[5] != "") {
				items[atoi(d_[0].c_str())].on_remove = d_[5];
			}
			if (d_[8] != "" and isdigit(d_[8][0])) {
				items[atoi(d_[0].c_str())].max_gems = atoi(d_[8].c_str());
			}
			if (d_[10] != "") {
				items[atoi(d_[0].c_str())].playmod = d_[10];
			}
		}
		file_info.close();
		{
			ifstream file_info("en");
			if (file_info.is_open()) {
				string line_info;
				while (getline(file_info, line_info)) {
					transform(line_info.begin(), line_info.end(), line_info.begin(), ::toupper);
					swear_words.push_back(line_info);
				}
			}
			file_info.close();
			{
				ifstream file_info("farmables.txt");
				if (file_info.is_open()) {
					string line_info;
					while (getline(file_info, line_info)) {
						for (int i_ = 0; i_ < items.size(); i_++) {
							if (items.at(i_).name == line_info)
								items.at(i_).farmable = true;
						}
					}
				}
				file_info.close();
				{
					ifstream file_info("combiner.txt");
					if (file_info.is_open()) {
						string line_info;
						while (getline(file_info, line_info)) {
							vector<vector<int>> form_recipe;
							vector<string> ok = explode("|", line_info);
							for (string lalala : ok) {
								vector<string> beveik = explode(" ", lalala);
								string check_ = beveik[0];
								int count_ = 1;
								if (isdigit(check_[0])) {
									count_ = atoi(check_.c_str());
								}
								if (count_ != 1) {
									replace_str(lalala, check_ + " ", "");
								}
								if (lalala.find("pairs of ") != string::npos or lalala.find("pair of ") != string::npos)
									lalala = explode((lalala.find("pairs of ") != string::npos ? "pairs of " : "pair of "), lalala)[1];
								string ex = lalala;
								ex.erase(ex.size() - 1);
								for (int i_ = 0; i_ < items.size(); i_++) {
									if (items.at(i_).name == lalala or items.at(i_).name == ex) {
										form_recipe.push_back({ items.at(i_).id, count_ });
										break;
									}
								}
							}
							if (form_recipe.size() == 4) receptai.push_back(form_recipe);
						}
					}
				}
			}
		}
	}
	items.at(5000).blockType = WEATHER;
	items.at(3832).blockType = WEATHER;
	return 0;
}
string replace_str2(string str, const string& from, const string& to) {
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}
int roundUp(int numToRound, int multiple) {
	assert(multiple);
	return ((numToRound + multiple - 1) / multiple) * multiple;
}
string to_lower(string s) {
	for (char& c : s)
		c = tolower(c);
	return s;
}
bool special_char(const string& str_) {
	if (str_.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != string::npos)
		return true;
	return false;
}

bool email(const string& str) {
	if (str.size() > 64 or str.empty())
		return false;
	const string::const_iterator at = std::find(str.cbegin(), str.cend(), '@'), dot = std::find(at, str.cend(), '.');
	if ((at == str.cend()) or (dot == str.cend()))
		return false;
	if (std::distance(str.cbegin(), at) < 1 or std::distance(at, str.cend()) < 5)
		return false;
	return true;
}

double RoundForGivenPrecision(const double dNumber, int iDecimalPlaces) {
	long long multiplier = (long long)pow(10, iDecimalPlaces);
	__int64 value = dNumber < 0 ? (long long)((nextafter(dNumber, -DBL_MAX) * multiplier) - 0.5) : (long long)((nextafter(dNumber, DBL_MAX) * multiplier) + 0.5);
	return value / double(multiplier);
}
void space_(string& usrStr) {
	char cha1, cha2;
	for (int i = 0; i < usrStr.size() - 1; ++i) {
		cha1 = usrStr.at(i), cha2 = usrStr.at(i + 1);
		if ((cha1 == ' ') && (cha2 == ' ')) {
			usrStr.erase(usrStr.begin() + 1 + i);
			--i;
		}
	}
}
string join(const vector<string>& v, const string& delimiter) {
	string result;
	for (size_t i = 0; i < v.size(); ++i) {
		result += (i ? delimiter : "") + v[i];
	}
	return result;
}