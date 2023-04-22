#include "RoomBase.h"

DEFINE_LOG_CATEGORY(LogClass_RoomBase);

ARoomBase::ARoomBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ----- Variable initialization ----- //
	this->ObjectName = GetName();

	// ----- Loading data ----- //
	// Constructor
	const ConstructorHelpers::FObjectFinder<UDataTable> OF_DT_RoomCatalog(*(this->PathStoring.DT_RoomCatalog_PF));

	// Checking
	check(OF_DT_RoomCatalog.Succeeded());

	// Initializing
	this->DT_RoomCatalog = OF_DT_RoomCatalog.Object;

	this->SMC_RoomMain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_RoomMain"));
	SetRootComponent(this->SMC_RoomMain);
}

void ARoomBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass_RoomBase, Log, TEXT("A new ARoomBase Actor (%s) has been spawned !"), *this->ObjectName);
}

void ARoomBase::Init_Main()
{
	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= is starting its Init_Main() ..."), *this->ObjectName);

	this->Init_DataTable(0);
	this->Init_Geometry();

	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= has finished its Init_Main() !"), *this->ObjectName);
}

void ARoomBase::Init_DataTable()
{
	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= is starting its Init_DataTable() ..."), *this->ObjectName);

	check(this->DT_RoomCatalog);

	FString _ContextString = "ContextString";
	TArray<FRoomCatalog_DT*> _RowArray;

	// Initializing _RowArray
	this->DT_RoomCatalog->GetAllRows(_ContextString, _RowArray);

	// Getting a random integer that will be used to get a table row
	int32 _RowIndex = FMath::RandRange(0, _RowArray.Num() - 1);

	if (_RowIndex <= _RowArray.Num())
	{
		this->DT_RoomCatalog_Row = _RowArray[_RowIndex];
		check(this->DT_RoomCatalog_Row);
		UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= was loaded with Row[%d]"), *this->ObjectName, _RowIndex);
	}
	else
	{
		UE_LOG(LogClass_RoomBase, Warning, TEXT("Index out of bounds : Row[%d] does not seem to exist"), _RowIndex);
		return;
	}

	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= has finished its Init_DataTable() !"), *this->ObjectName);
}

void ARoomBase::Init_DataTable(int32 RowIndex_p)
{
	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= is starting its Init_DataTable(int32 RowIndex_p) !"), *this->ObjectName);
	
	check(this->DT_RoomCatalog);

	FString _ContextString = "ContextString";
	TArray<FRoomCatalog_DT*> _RowArray;

	// Initializing _RowArray
	this->DT_RoomCatalog->GetAllRows(_ContextString, _RowArray);

	if (RowIndex_p <= _RowArray.Num())
	{
		this->DT_RoomCatalog_Row = _RowArray[RowIndex_p];
		check(this->DT_RoomCatalog_Row);
		UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= was loaded with Row[%d]"), *this->ObjectName, RowIndex_p);
	}
	else
	{
		UE_LOG(LogClass_RoomBase, Warning, TEXT("Index out of bounds : Row[%d] does not seem to exist"), RowIndex_p);
		return;
	}

	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= has finished its Init_DataTable(int32 RowIndex_p) !"), *this->ObjectName);
}

void ARoomBase::Init_Geometry()
{
	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= is starting its Init_Geometry() !"), *this->ObjectName);

	check(this->DT_RoomCatalog_Row);
	
	// Initializing our SM_Room from DataTable
	this->SM_Room = this->DT_RoomCatalog_Row->S_StaticMesh;
	check(this->SM_Room);

	// Setting our Geometry
	this->SMC_RoomMain->SetStaticMesh(this->SM_Room);

	UE_LOG(LogClass_RoomBase, Log, TEXT("=> %s <= has finished its Init_Geometry() !"), *this->ObjectName);
}

UStaticMesh* ARoomBase::GET_StaticMesh()
{
	check(this->SM_Room);
	return this->SM_Room;
}

TArray<AActor*> ARoomBase::GET_ActorsMainArray()
{
	return this->ActorsMain_Array;
}