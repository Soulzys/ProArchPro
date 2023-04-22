#include "TestingBuilder.h"

ATestingBuilder::ATestingBuilder()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_MainTestingRoom(*(PathStoring.SM_FillingAreaTestingRoom_PF));
	
	check(OF_SM_MainTestingRoom.Succeeded());

	this->SM_MainTestingRoom = OF_SM_MainTestingRoom.Object;

	this->SMC_MainTesting = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Main"));
	SetRootComponent(this->SMC_MainTesting);
	this->SMC_MainTesting->SetStaticMesh(this->SM_MainTestingRoom);
}

void ATestingBuilder::BeginPlay()
{
	Super::BeginPlay();

	Fill_Volume(this->SM_MainTestingRoom);
	Spawn_ActorInRoom(EDataTable::EDT_BOX, 0, BuilderController, 1);
}