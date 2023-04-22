#include "BuilderMaster.h"
#include "../Architecture/RoomBase.h"
#include "RoomBuilder.h"

DEFINE_LOG_CATEGORY(LogClass_BuilderMaster);

ABuilderMaster::ABuilderMaster()
{
	PrimaryActorTick.bCanEverTick = false;

	// Variable initialization
	this->ObjectName = GetName();
}

void ABuilderMaster::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("A new ABuilderMaster Actor (%s) has been spawned !"), *this->ObjectName);
}

void ABuilderMaster::Init_Main()
{
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= is starting its Init_Main() ..."), *this->ObjectName);

	this->Init_SpawnActors();
	this->Init_References();

	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= has finished its Init_Main() !"), *this->ObjectName);
}

void ABuilderMaster::Init_SpawnActors()
{
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= is starting its Init_SpawnActors() ..."), *this->ObjectName);

	check(GetWorld());

	this->RoomBase    = GetWorld()->SpawnActor<ARoomBase>   ();
	this->RoomBuilder = GetWorld()->SpawnActor<ARoomBuilder>();

	check(this->RoomBase   );
	check(this->RoomBuilder);

	// Calling the Initialization methods of the Actors that have been spawned
	this->RoomBase->Init_Main();
	
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= has finished its Init_SpawnActors() !"), *this->ObjectName);
}

void ABuilderMaster::Init_References()
{
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= is starting its Init_References() ..."), *this->ObjectName);

	check(this->RoomBase);
	check(this->RoomBuilder);

	this->RoomBuilder->SET_RoomBase(this->RoomBase);

	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= has finished its Init_References() !"), *this->ObjectName);
} 

void ABuilderMaster::Build_Main()
{
	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= is starting its Build_Main() ... "), *this->ObjectName);

	check(this->RoomBuilder);
	
	this->RoomBuilder->Build_Room();

	UE_LOG(LogClass_BuilderMaster, Log, TEXT("=> %s <= has finished its Build_Main() !"), *this->ObjectName);
}