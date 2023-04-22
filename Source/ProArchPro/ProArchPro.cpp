// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProArchPro.h"
#include "Modules/ModuleManager.h"
#include "UI/Slate/Styles/SlateStyleController.h"

class FProArcPro_GameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(FSlateStyleController::Get_StyleSetName());
		FSlateStyleController::Initialize();
	}

	virtual void ShutdownModule() override
	{
		FSlateStyleController::Shutdown();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FProArcPro_GameModule, ProArchPro, "ProArchPro" );
