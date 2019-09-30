//#include "Linmalu.h"
//
//using namespace std;
//
//char* mtou8(const char* str)
//{
//	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
//	wchar_t* wmsg = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, str, -1, wmsg, len);
//	len = WideCharToMultiByte(CP_UTF8, 0, wmsg, -1, 0, 0, 0, 0);
//	char* msg = new char[len];
//	WideCharToMultiByte(CP_UTF8, 0, wmsg, -1, msg, len, 0, 0);
//	delete[] wmsg;
//	return msg;
//}
//
////void clientMessage(const char* format, ...)
////{
////	va_list args;
////	va_start(args, format);
////	clientMessage(false, format, args);
////	va_end(args);
////}
//
//void clientMessage(bool error, const char* format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	int size = _vscprintf(format, args) + 1;
//	char* msg = new char[size];
//	vsprintf_s(msg, size, format, args);
//	va_end(args);
//	string message;
//	message.append("[b][");
//	message.append(LINMALU_NAME);
//	message.append("][/b] ");
//	if (error)
//	{
//		message.append("[color=red]");
//	}
//	message.append(msg);
//	delete[] msg;
//	msg = mtou8(message.data());
//	getTs3Functions().printMessageToCurrentTab(msg);
//	delete[] msg;
//}
//
//Minecraft* Minecraft::minecraft = NULL;
//
//void Minecraft::connectMinecraft(uint64 serverID)
//{
//	if (minecraft)
//	{
//		disconnectMinecraft();
//	}
//	minecraft = new Minecraft(serverID);
//}
//
//void Minecraft::disconnectMinecraft()
//{
//	if (minecraft)
//	{
//		minecraft = NULL;
//		delete minecraft;
//	}
//}
//
//void Minecraft::joinClientMessage(anyID clientID)
//{
//	if (minecraft)
//	{
//		EnterCriticalSection(&minecraft->cs);
//		minecraft->addData(TYPE_JOIN_CLIENT);
//		minecraft->addData(clientID);
//		minecraft->sendPacket();
//		LeaveCriticalSection(&minecraft->cs);
//	}
//}
//
//Minecraft::Minecraft(uint64 serverID)
//{
//	InitializeCriticalSection(&cs);
//	this->serverID = serverID;
//	if (getTs3Functions().getClientID(serverID, &clientID) == ERROR_ok)
//	{
//		if (getTs3Functions().getConnectionVariableAsString(serverID, clientID, CONNECTION_SERVER_IP, &ip) == ERROR_ok)
//		{
//			thread t(&Minecraft::run, this);
//			t.detach();
//		}
//		else
//		{
//			clientMessage(true, "서버주소를 받아오는데 실패했습니다.");
//		}
//	}
//	else
//	{
//		clientMessage(true, "클라이언트ID를 받아오는데 실패했습니다.");
//	}
//}
//
//Minecraft::~Minecraft()
//{
//	DeleteCriticalSection(&cs);
//	stopMusic();
//	if (ip)
//	{
//		ts3plugin_freeMemory(ip);
//	}
//	if (client > 0)
//	{
//		closesocket(client);
//	}
//	if (in_buffer)
//	{
//		delete[] in_buffer;
//	}
//	if (out_buffer)
//	{
//		delete[] out_buffer;
//	}
//}
//
//void Minecraft::run()
//{
//	SOCKADDR_IN addr = { 0 };
//	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = inet_addr(ip);
//	addr.sin_port = htons(23456);
//	while (true)
//	{
//		client = socket(addr.sin_family, SOCK_STREAM, IPPROTO_TCP);
//		srand((int)time(NULL));
//		key = rand() * rand() * rand() * rand();
//		out_buffer = nullptr;
//		out_size = 0;
//		in_buffer = nullptr;
//		in_size = 0;
//		in_index = 0;
//		addData(clientID);
//		addData(key);
//		key = htonl(key);
//		if (client != SOCKET_ERROR && connect(client, (SOCKADDR*)&addr, sizeof(addr)) != SOCKET_ERROR && sendPacket(false) && sendMessageData(false, TYPE_MESSAGE, LINMALU_VERSION))
//		{
//			clientMessage(false, "");
//			clientMessage(false, "마인크래프트서버와 연결되었습니다.");
//			TS3_VECTOR vector1 = { 0, 1, 0 };
//			getTs3Functions().systemset3DListenerAttributes(serverID, NULL, NULL, &vector1);
//			while (true)
//			{
//				if (readPacket())
//				{
//					int type;
//					if (getData(type))
//					{
//						anyID clientIDs[2] = { 0 };
//						vector1 = { 0, 0, 0 };
//						TS3_VECTOR vector2 = { 0, 0, 0 };
//						anyID* pClientList;
//						char* msg;
//						switch (type)
//						{
//						case TYPE_MESSAGE:
//							if (getData(msg))
//							{
//								clientMessage(false, msg);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] MESSAGE : Not read Data");
//							}
//							break;
//						case TYPE_DISTANCE:
//							float distanceFactor;
//							float rolloffScale;
//							if (getData(distanceFactor) && getData(rolloffScale))
//							{
//								getTs3Functions().systemset3DSettings(serverID, 20 / distanceFactor, rolloffScale);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] DISTANCE : Not read Data - %f / %f", distanceFactor, rolloffScale);
//							}
//							break;
//						case TYPE_PLAYER_LOCATION:
//							if (getData(vector1.x) && getData(vector1.y) && getData(vector1.z) && getData(vector2.x) && getData(vector2.y) && getData(vector2.z))
//							{
//								getTs3Functions().systemset3DListenerAttributes(serverID, &vector1, &vector2, NULL);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] PLAYER_LOCATION : Not read Data - %f / %f / %f / %f / %f / %f", vector1.x, vector1.y, vector1.z, vector2.x, vector2.y, vector2.z);
//							}
//							break;
//						case TYPE_OTHER_PLAYER_LOCATION:
//							if (getData(clientIDs[0]) && getData(vector1.x) && getData(vector1.y) && getData(vector1.z))
//							{
//								getTs3Functions().channelset3DAttributes(serverID, clientIDs[0], &vector1);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] OTHER_PLAYER_LOCATION : Not read Data - %d / %f / %f / %f", clientIDs[0], vector1.x, vector1.y, vector1.z);
//							}
//							break;
//						case TYPE_MUTE:
//							if (getData(clientIDs[0]))
//							{
//								getTs3Functions().requestMuteClients(serverID, clientIDs, NULL);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] MUTE : Not read Data");
//							}
//							break;
//						case TYPE_UNMUTE:
//							if (getData(clientIDs[0]))
//							{
//								getTs3Functions().requestUnmuteClients(serverID, clientIDs, NULL);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] UNMUTE : Not read Data");
//							}
//							break;
//						case TYPE_ALL_MUTE:
//							if (!getTs3Functions().getClientList(serverID, &pClientList))
//							{
//								getTs3Functions().requestMuteClients(serverID, pClientList, NULL);
//								getTs3Functions().freeMemory(pClientList);
//							}
//							break;
//						case TYPE_ALL_UNMUTE:
//							if (!getTs3Functions().getClientList(serverID, &pClientList))
//							{
//								getTs3Functions().requestUnmuteClients(serverID, pClientList, NULL);
//								getTs3Functions().freeMemory(pClientList);
//							}
//							break;
//						case TYPE_PLAY_MUSIC:
//							if (getData(msg))
//							{
//								if (playMusic(msg))
//								{
//									sendMessageData(true, TYPE_PLAYER_MESSAGE, "%s파일이 없거나 WAV파일이 아닙니다.", msg);
//								}
//								else
//								{
//									sendMessageData(true, TYPE_PLAYER_MESSAGE, "%s파일을 재생합니다.", msg);
//								}
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] TYPE_PLAY_WAV : Not read Data");
//							}
//							break;
//						case TYPE_STOP_MUSIC:
//							if (stopMusic())
//							{
//								sendMessageData(true, TYPE_PLAYER_MESSAGE, "음악재생을 종료했습니다.");
//							}
//							else
//							{
//								sendMessageData(true, TYPE_PLAYER_MESSAGE, "음악이 재생중이 아닙니다.");
//							}
//							break;
//						case TYPE_LOC_MUSIC:
//							if (getData(vector1.x) && getData(vector1.y) && getData(vector1.z))
//							{
//								locMusic(vector1);
//							}
//							else
//							{
//								sendMessageData(true, TYPE_ERROR_MESSAGE, "[ERROR] TYPE_LOC_WAV : Not read Data - %f / %f / %f", vector1.x, vector1.y, vector1.z);
//							}
//							break;
//						}
//					}
//				}
//				else
//				{
//					break;
//				}
//			}
//			clientMessage(false, "마인크래프트서버와 연결이 종료되었습니다.");
//		}
//		else
//		{
//			clientMessage(true, "마인크래프트서버 연결 실패");
//		}
//		closesocket(client);
//		if (MessageBoxA(NULL, "마인크래프트서버에 다시 접속하시겠습니까?", LINMALU_NAME, MB_RETRYCANCEL | MB_ICONQUESTION) == IDCANCEL)
//		{
//			break;
//		}
//		if (minecraft != this)
//		{
//			break;
//		}
//	}
//}
//
//void Minecraft::converterData(char*& data, int size)
//{
//	char* key = (char*)&(Minecraft::key);
//	int index = 0;
//	for (int i = 0; i < size; ++i)
//	{
//		data[i] ^= key[index];
//		if (++index >= sizeof(Minecraft::key))
//		{
//			index = 0;
//		}
//	}
//}
//
//void Minecraft::addData(int data)
//{
//	data = htonl(data);
//	addData(&data, sizeof(data));
//}
//
//void Minecraft::addData(const void* data, int size)
//{
//	char* buffer = new char[out_size + size];
//	if (out_buffer)
//	{
//		memcpy_s(buffer, out_size, out_buffer, out_size);
//		delete[] out_buffer;
//	}
//	out_buffer = buffer;
//	memcpy_s(buffer + out_size, size, data, size);
//	out_size += size;
//}
//
//bool Minecraft::sendMessageData(bool converte, int type, const char* format, ...)
//{
//	EnterCriticalSection(&cs);
//	addData(type);
//	va_list args;
//	va_start(args, format);
//	int size = _vscprintf(format, args) + 1;
//	char* msg = new char[size];
//	vsprintf_s(msg, size, format, args);
//	va_end(args);
//	addData(msg, size - 1);
//	delete[] msg;
//	bool b = sendPacket(converte);
//	LeaveCriticalSection(&cs);
//	return b;
//}
//
//bool Minecraft::sendPacket(bool converte)
//{
//	if (out_size <= 0)
//	{
//		return false;
//	}
//	int index = 0;
//	int size = sizeof(out_size);
//	int data = htonl(out_size);
//	while (index < size)
//	{
//		int result = send(client, (char*)&data + index, size - index, NULL);
//		if (result <= 0)
//		{
//			return false;
//		}
//		index += result;
//	}
//	if (converte)
//	{
//		converterData(out_buffer, out_size);
//	}
//	index = 0;
//	while (index < out_size)
//	{
//		int result = send(client, out_buffer + index, out_size - index, NULL);
//		if (result <= 0)
//		{
//			return false;
//		}
//		index += result;
//	}
//	delete[] out_buffer;
//	out_buffer = nullptr;
//	out_size = 0;
//	return true;
//}
//
//bool Minecraft::readPacket()
//{
//	if (in_buffer)
//	{
//		delete[] in_buffer;
//	}
//	in_index = 0;
//	int size = sizeof(int);
//	in_buffer = new char[size];
//	while (in_index < size)
//	{
//		int result = recv(client, in_buffer + in_index, size - in_index, NULL);
//		if (result <= 0)
//		{
//			return false;
//		}
//		in_index += result;
//	}
//	memcpy_s(&in_size, size, in_buffer, size);
//	delete[] in_buffer;
//	in_size = htonl(in_size);
//	in_index = 0;
//	in_buffer = new char[in_size + 1];
//	in_buffer[in_size] = '\0';
//	while (in_index < in_size)
//	{
//		int result = recv(client, in_buffer + in_index, in_size - in_index, NULL);
//		if (result <= 0)
//		{
//			return false;
//		}
//		in_index += result;
//	}
//	in_index = 0;
//	converterData(in_buffer, in_size);
//	return true;
//}
//
//bool Minecraft::getData(anyID& result)
//{
//	int data = 0;
//	if (getData(data))
//	{
//		result = data;
//		return true;
//	}
//	return false;
//}
//
//bool Minecraft::getData(float& result)
//{
//	int num;
//	if (getData(num))
//	{
//		result = *(float*)&num;
//		return true;
//	}
//	return false;
//}
//
//bool Minecraft::getData(int& result)
//{
//	if (in_size - in_index < 4)
//	{
//		return false;
//	}
//	result = *(int*)(in_buffer + in_index);
//	in_index += sizeof(result);
//	result = htonl(result);
//	return true;
//}
//
//bool Minecraft::getData(char*& result)
//{
//	if (in_size - in_index < 1)
//	{
//		return false;
//	}
//	result = in_buffer + in_index;
//	in_index = in_size;
//	return true;
//}
//
//bool Minecraft::playMusic(const char* file)
//{
//	if (musicID)
//	{
//		stopMusic();
//	}
//	file = mtou8(file);
//	bool b = getTs3Functions().playWaveFileHandle(serverID, file, FALSE, &musicID);
//	delete[] file;
//	return b;
//}
//
//bool Minecraft::stopMusic()
//{
//	if (musicID)
//	{
//		bool b = getTs3Functions().closeWaveFileHandle(serverID, musicID);
//		musicID = NULL;
//		return b;
//	}
//	return false;
//}
//
//bool Minecraft::locMusic(TS3_VECTOR& vector)
//{
//	return musicID && getTs3Functions().set3DWaveAttributes(serverID, musicID, &vector);
//}
