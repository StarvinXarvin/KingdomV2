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

	AudioEngine(bool start_enabled = true);

	~AudioEngine();

	bool AudioInit();

	bool AudioStart();

	//virtual engine_status PreUpdate()
	//{
	//	return ENGINE_UPDATE_CONTINUE;
	//}

	engine_status AudioUpdate();

	//virtual engine_status PostUpdate()
	//{
	//	return ENGINE_UPDATE_CONTINUE;
	//}

	bool AudioCleanUp();

	bool InitializeWwise();
};