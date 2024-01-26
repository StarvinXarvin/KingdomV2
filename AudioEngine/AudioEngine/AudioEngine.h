#pragma once

#include "..\..\GameEngine\Engine_Globals.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>

#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <../Common/AkFilePackageLowLevelIODeferred.h> 

#include <../Common/AkFilePackage.h>
#include <../Common/AkFilePackageLUT.h>

#include <AK/Comm/AkCommunication.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Wwise_IDs.h";

CAkFilePackageLowLevelIODeferred g_lowLevelIO;

#define BANKNAME_INIT L"Init.bnk"
#define BANKNAME_NEWSOUNDBANK L"New_SoundBank.bnk"

const AkGameObjectID GAME_OBJECT_ID_SONG1 = 100;

class AudioEngine
{
private:
	bool enabled;

public:

	AudioEngine(bool start_enabled = true)
	{}

	~AudioEngine()
	{}

	bool AudioInit() {

		if (InitializeWwise() == true) {
			std::cout << "Wwise initialized" << std::endl;
		}
		else { std::cout << "Failed to initialize" << std::endl; }

		if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_SONG1, "Theme") == AK_Success) {
			std::cout << "Succesfully registered Game Object" << std::endl;
		}

		if (AK::SoundEngine::PostEvent(AK::EVENTS::SONG1_EVENT, GAME_OBJECT_ID_SONG1) == AK_Success) {
			std::cout << "Succesfully posted SONG event" << std::endl;
		}
		else { std::cout << "Failed to post SONG event" << std::endl; }

		return true;
	}

	bool AudioStart();

	//virtual engine_status PreUpdate()
	//{
	//	return ENGINE_UPDATE_CONTINUE;
	//}

	engine_status AudioUpdate() {

		AK::SoundEngine::RenderAudio();

		return ENGINE_UPDATE_CONTINUE;

	}

	//virtual engine_status PostUpdate()
	//{
	//	return ENGINE_UPDATE_CONTINUE;
	//}

	bool AudioCleanUp() {

		AK::SoundEngine::Term();
		g_lowLevelIO.Term();

		if (AK::IAkStreamMgr::Get()) {
			AK::IAkStreamMgr::Get()->Destroy();
		}

		AK::MemoryMgr::Term();

		return true;

	}

	bool InitializeWwise() {

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
};