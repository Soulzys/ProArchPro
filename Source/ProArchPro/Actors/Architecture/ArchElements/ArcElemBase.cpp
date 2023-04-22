#include "ArcElemBase.h"

AArcElemBase::AArcElemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	this->SMC_Main = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Main"));
	SetRootComponent(this->SMC_Main);
}

void AArcElemBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AArcElemBase::Set_MainStaticMesh(UStaticMesh* StaticMesh_p)
{
	check(StaticMesh_p);

	this->SMC_Main->SetStaticMesh(StaticMesh_p);
}