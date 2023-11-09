#include "MasterGameMode.h"
#include "../../Actors/Pawns/SpectatorBase.h"
#include "../../Actors/Builders/BuilderMaster.h"
#include "../../UI/HUD/MasterHUD.h"

DEFINE_LOG_CATEGORY(LogClass_MasterGameMode);

AMasterGameMode::AMasterGameMode()
{
	HUDClass         = AMasterHUD::StaticClass()     ;
	DefaultPawnClass = ASpectatorBase::StaticClass() ;

	this->ObjectName = GetName();
}

void AMasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass_MasterGameMode, Log, TEXT("A new AMasterGameMode GameModeBase (%s) has been spawned !"), *this->ObjectName);

	this->Init_Main();
}

void AMasterGameMode::Init_Main()
{
	UE_LOG(LogClass_MasterGameMode, Log, TEXT("=> %s <= is starting its Init_Main() ... "), *this->ObjectName);

	this->Init_References();
	//this->Init_SpawningActors();
	//this->Init_UI();

	UE_LOG(LogClass_MasterGameMode, Log, TEXT("=> %s <= has finished its Init_Main() !"), *this->ObjectName);
}

void AMasterGameMode::Init_References()
{
	this->MasterHUD = Cast<AMasterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(this->MasterHUD);
	this->MasterHUD->SET_MasterGameMode(this);
}

void AMasterGameMode::Init_SpawningActors()
{
	UE_LOG(LogClass_MasterGameMode, Log, TEXT("=> %s <= is starting its Init_SpawningActors() ... "), *this->ObjectName);

	check(GetWorld());

	this->BuilderMaster = GetWorld()->SpawnActor<ABuilderMaster>();

	check(this->BuilderMaster);

	this->BuilderMaster->Init_Main();

	UE_LOG(LogClass_MasterGameMode, Log, TEXT("=> %s <= has finished its Init_SpawningActors() !"), *this->ObjectName);
}

void AMasterGameMode::Run_Testing()
{
	this->Init_SpawningActors();
	this->BuilderMaster->Build_Main();
}

