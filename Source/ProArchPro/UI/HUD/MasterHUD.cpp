#include "MasterHUD.h"
#include "../Slate/Widgets/Menu/SMainMenu.h"
#include "../../Controllers/GameModes/MasterGameMode.h"

DEFINE_LOG_CATEGORY(LogClass_MasterHUD);

void AMasterHUD::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine);
	check(GEngine->GameViewport);

	SAssignNew(this->MenuMain, SMainMenu).OwningHUD(this);

	check(this->MenuMain);

	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(this->MenuMain.ToSharedRef()));

	this->MenuMain->SetVisibility(EVisibility::Collapsed);

	// Setting the starting screen
	this->MenuMain->SetVisibility(EVisibility::Visible);

	// *** Player Owner *** //
	// Assuming we start with the main menu
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void AMasterHUD::Run_Testing()
{
	check(this->MasterGameMode);
	this->MasterGameMode->Run_Testing();
}

void AMasterHUD::Set_Game_InputMode(const FInputModeDataBase& InData_p)
{
	PlayerOwner->SetInputMode(InData_p);
}

void AMasterHUD::Set_MenuMain_Visibility(const EVisibility& Visibility_p)
{
	check(this->MenuMain);
	this->MenuMain->SetVisibility(Visibility_p);

	if (Visibility_p == EVisibility::Visible)
	{
		UE_LOG(LogClass_MasterHUD, Log, TEXT("'MenuMain's visibility was set to : VISIBLE"));
	}

	if (Visibility_p == EVisibility::Collapsed)
	{
		UE_LOG(LogClass_MasterHUD, Log, TEXT("'MenuMain's visibility was set to : COLLAPSED"));
	}

	if (Visibility_p == EVisibility::Hidden)
	{
		UE_LOG(LogClass_MasterHUD, Log, TEXT("'MenuMain's visibility was set to : HIDDEN"));
	}
}

// ***** SETTERS ***** //

void AMasterHUD::SET_MasterGameMode(AMasterGameMode* MasterGameMode_p)
{
	check(MasterGameMode_p);
	this->MasterGameMode = MasterGameMode_p;
}