
#include "AudioEngine.h"



//AudioEngine::AudioEngine(bool start_enabled)
//{
//}
//
//AudioEngine::~AudioEngine()
//{
//}
//
//bool AudioEngine::Init() {
//
//	if (InitializeWwise() == true) {
//		std::cout << "Wwise initialized" << std::endl;
//	}
//	else { std::cout << "Failed to initialize" << std::endl; }
//
//	if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_SONG1, "Theme") == AK_Success) {
//		std::cout << "Succesfully registered Game Object" << std::endl;
//	}
//
//	if (AK::SoundEngine::PostEvent(AK::EVENTS::SONG1_EVENT, GAME_OBJECT_ID_SONG1) == AK_Success) {
//		std::cout << "Succesfully posted SONG event" << std::endl;
//	}
//	else { std::cout << "Failed to post SONG event" << std::endl; }
//
//	return true;
//
//}
//
//bool AudioEngine::InitializeWwise() {
//
//	AkMemSettings memSettings;
//	AK::MemoryMgr::GetDefaultSettings(memSettings);
//
//	if (AK::MemoryMgr::Init(&memSettings) == AK_Success) {
//		std::cout << "Memory Manager initialized" << std::endl;
//	}
//	else { std::cout << "Memory Manager failed to initialize" << std::endl; return false; }
//
//	AkStreamMgrSettings stmSettings;
//	AK::StreamMgr::GetDefaultSettings(stmSettings);
//
//	if (!AK::StreamMgr::Create(stmSettings)) {
//		std::cout << "Failed to create Streaming Manager" << std::endl;
//	}
//	else { std::cout << "Streaming Manager succesfully created" << std::endl; return false; }
//
//	AkDeviceSettings deviceSettings;
//	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
//
//
//
//	if (g_lowLevelIO.Init(deviceSettings) == AK_Success) {
//		std::cout << "Created the streaming device and Low Level I/O system" << std::endl;
//	}
//	else { std::cout << "Could not create the streaming device Low Level I/O system" << std::endl; return false; }
//
//	AkInitSettings initSettings;
//	AkPlatformInitSettings platformInitSettings;
//	AK::SoundEngine::GetDefaultInitSettings(initSettings);
//	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
//
//	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) == AK_Success) {
//		std::cout << "Sound Engine initialized" << std::endl;
//	}
//	else { std::cout << "Could not initialize the Sound Engine" << std::endl; return false; }
//
//	g_lowLevelIO.SetBasePath(AKTEXT("..\\Wwise\\SoundBanks\\GeneratedSoundBanks\\Windows"));
//	AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));
//
//	AkBankID bankID;
//
//	if (AK::SoundEngine::LoadBank(BANKNAME_INIT, bankID) != AK_Success) {
//		std::cout << "Could not load init bank" << std::endl; return false;
//	}
//	else { std::cout << "Successfully loaded init bank" << std::endl; }
//
//	if (AK::SoundEngine::LoadBank(BANKNAME_NEWSOUNDBANK, bankID) != AK_Success) {
//		std::cout << "Could not load new bank" << std::endl; return false;
//	}
//	else { std::cout << "Successfully loaded new bank" << std::endl; }
//
//	return true;
//
//}
//
//engine_status AudioEngine::Update()
//{
//
//	AK::SoundEngine::RenderAudio();
//
//	return ENGINE_UPDATE_CONTINUE;
//
//}
//
//bool AudioEngine::CleanUp() {
//
//	AK::SoundEngine::Term();
//	g_lowLevelIO.Term();
//
//	if (AK::IAkStreamMgr::Get()) {
//		AK::IAkStreamMgr::Get()->Destroy();
//	}
//
//	AK::MemoryMgr::Term();
//
//	return true;
//
//}