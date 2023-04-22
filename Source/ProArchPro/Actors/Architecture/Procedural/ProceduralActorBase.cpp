#include "ProceduralActorBase.h"

DEFINE_LOG_CATEGORY(LogClass_ProceduralActorBase);

AProceduralActorBase::AProceduralActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AProceduralActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}