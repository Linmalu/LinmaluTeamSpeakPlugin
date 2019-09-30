//#pragma once
//#define LINMALU_NAME "LinmaluMinecraftVoicechatPlugin"
//#define LINMALU_VERSION "TeamSpeak3_1.1"
//#define LINMALU_AUTHOR "린마루(Linmalu)"
//#define LINMALU_DESCRIPTION "마인크래프트와 연동하여 음성채팅을 할 수 있는 플러그인 \r\n Homepage : http://blog.linmalu.com/"
//#define TYPE_MESSAGE 1
//#define TYPE_ERROR_MESSAGE 2
//#define TYPE_PLAYER_MESSAGE 3
//#define TYPE_DISTANCE 100
//#define TYPE_PLAYER_LOCATION 101
//#define TYPE_OTHER_PLAYER_LOCATION 102
//#define TYPE_MUTE 103
//#define TYPE_UNMUTE 104
//#define TYPE_ALL_MUTE 105
//#define TYPE_ALL_UNMUTE 106
//#define TYPE_PLAY_MUSIC 110
//#define TYPE_STOP_MUSIC 111
//#define TYPE_LOC_MUSIC 112
//#define TYPE_JOIN_CLIENT 200
//
//#include <iostream>
//#include <string>
//#include <thread>
//#include <Windows.h>
//
//#include "teamspeak/public_rare_definitions.h"
//#include "teamspeak/public_errors.h"
//#include "ts3_functions.h"
//#include "plugin.h"
//#pragma comment(lib, "ws2_32.lib")
//
//struct TS3Functions getTs3Functions();
//
//char* mtou8(const char* msg);
////void clientMessage(const char* format, ...);
////void errorMessage(const char* format, ...);
//void clientMessage(bool error, const char* format, ...);
//
//class Minecraft
//{
//private:
//	static Minecraft* minecraft;
//public:
//	static void connectMinecraft(uint64 serverID);
//	static void disconnectMinecraft();
//	static void joinClientMessage(anyID clientID);
//private:
//	CRITICAL_SECTION cs;
//	uint64 serverID;
//	anyID clientID;
//	char* ip;
//	int key;
//	SOCKET client;
//	char* out_buffer;
//	int out_size;
//	char* in_buffer;
//	int in_size;
//	int in_index;
//	uint64 musicID;
//public:
//	Minecraft(uint64 serverID);
//	~Minecraft();
//	void run();
//	void converterData(char*& data, int size);
//	void addData(int data);
//	void addData(const void* data, int size);
//	bool sendMessageData(bool converte, int type, const char* format, ...);
//	bool sendPacket(bool converte = true);
//	bool readPacket();
//	bool getData(anyID& result);
//	bool getData(float& result);
//	bool getData(int& result);
//	bool getData(char*& result);
//	bool playMusic(const char* file);
//	bool stopMusic();
//	bool locMusic(TS3_VECTOR& vector);
//};
