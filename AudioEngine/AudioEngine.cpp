#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>

#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <../Common/AkFilePackageLowLevelIODeferred.h> 

#include <../Common/AkFilePackage.h>
#include <../Common/AkFilePackageLUT.h>

#include <AK/Comm/AkCommunication.h>

CAkFilePackageLowLevelIODeferred g_lowLevelIO;

#include "Wwise_IDs.h";

#define BANKNAME_INIT L"Init.bnk"
#define BANKNAME_NEWSOUNDBANK L"New_SoundBank.bnk"

const AkGameObjectID GAME_OBJECT_ID_THUD = 100;

int Init() {
	if (InitializeWwise() == true) {
		std::cout << "Wwise initialized" << std::endl;
	}
	else { std::cout << "Failed to initialize" << std::endl; }

	if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_THUD, "Theme") == AK_Success) {
		std::cout << "Succesfully registered Game Object" << std::endl;
	}

	if (AK::SoundEngine::PostEvent(AK::EVENTS::THUD_EVENT, GAME_OBJECT_ID_THUD) == AK_Success) {
		std::cout << "Succesfully posted THUD event" << std::endl;
	}
	else { std::cout << "Failed to post THUD event" << std::endl; }

	AK::SoundEngine::RenderAudio();

	AK::SoundEngine::Term();
	g_lowLevelIO.Term();

	if (AK::IAkStreamMgr::Get()) {
		AK::IAkStreamMgr::Get()->Destroy();
	}

	AK::MemoryMgr::Term();
}

bool Engine_ModuleScene::InitializeWwise() {

	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) == AK_Success) {
		std::cout << "Memory Manager initialized" << std::endl;
	}
	else { std::cout << "Memory Manager failed to initialize" << std::endl; return false; }

	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	if (!AK::StreamMgr::Create(stmSettings)) {
		std::cout << "Failed to create Streaming Manager" << std::endl;
	}
	else { std::cout << "Streaming Manager succesfully created" << std::endl; return false; }

	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);



	if (g_lowLevelIO.Init(deviceSettings) == AK_Success) {
		std::cout << "Created the streaming device and Low Level I/O system" << std::endl;
	}
	else { std::cout << "Could not create the streaming device Low Level I/O system" << std::endl; return false; }

	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) == AK_Success) {
		std::cout << "Sound Engine initialized" << std::endl;
	}
	else { std::cout << "Could not initialize the Sound Engine" << std::endl; return false; }

	g_lowLevelIO.SetBasePath(AKTEXT("..\\Wwise\\SoundBanks\\GeneratedSoundBanks\\Windows"));
	AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));

	AkBankID bankID;

	if (AK::SoundEngine::LoadBank(BANKNAME_INIT, bankID) != AK_Success) {
		std::cout << "Could not load init bank" << std::endl; return false;
	}
	else { std::cout << "Successfully loaded init bank" << std::endl; }

	if (AK::SoundEngine::LoadBank(BANKNAME_NEWSOUNDBANK, bankID) != AK_Success) {
		std::cout << "Could not load new bank" << std::endl; return false;
	}
	else { std::cout << "Successfully loaded new bank" << std::endl; }

	return true;

}