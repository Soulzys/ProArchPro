#include "ArchElementPattern.h"
#include "AreaCubeFiller.h"
#include "DrawDebugHelpers.h"
#include "PatternCube.h"

DEFINE_LOG_CATEGORY(LogClass_ArchElementPattern);

AArchElementPattern::AArchElementPattern()
{
	PrimaryActorTick.bCanEverTick = false;

	// Variable initialization
	this->bIsObstructed = false;
}

void AArchElementPattern::BeginPlay()
{
	Super::BeginPlay();

	this->Init_Variables();

	TArray<AActor*> _ChildArray;
	GetAllChildActors(_ChildArray, false);

	//FVector ChildActor_01 = _ChildArray[0]->GetActorLocation();
	//FVector ChildActor_02 = _ChildArray[1]->GetActorLocation();
	//FVector ChildActor_03 = _ChildArray[2]->GetActorLocation();

	FTransform ChildActor_01_Transform = _ChildArray[0]->GetActorTransform();
	FTransform Toto = GetActorTransform();

	FVector ChildActor_01_Location = ChildActor_01_Transform.GetLocation();
	FTransform ChildActor_01_RelativeTransform = ChildActor_01_Transform.GetRelativeTransform(Toto);
	FVector ChildActor_01_RelativeLocation = ChildActor_01_RelativeTransform.GetLocation();

	//DrawDebugLine(GetWorld(), ChildActor_01, ChildActor_02, FColor::Orange, false, 120.0f, 0, 2.0f);
	//DrawDebugLine(GetWorld(), ChildActor_01, ChildActor_03, FColor::Orange, false, 120.0f, 0, 2.0f);

	//UE_LOG(LogClass_ArchElementPattern, Warning, TEXT("ChildActor_02 location : %s"), *ChildActor_02.ToString());
}

void AArchElementPattern::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent_p)
{
	Super::PostEditChangeProperty(PropertyChangedEvent_p);
}

void AArchElementPattern::Init_Variables()
{
	TArray<AActor*> _Childs_Array;

	// Filling our _Childs_Array
	GetAllChildActors(_Childs_Array, false);

	for (int32 i = 0; i < _Childs_Array.Num(); i++)
	{

	}
}

void AArchElementPattern::Rotate_EveryChildPostSpawnSignArr()
{
	TArray<AActor*> _Childs_Array;

	GetAllChildActors(_Childs_Array, false);

	for (int32 i = 0; i < _Childs_Array.Num(); i++)
	{
		Cast<APatternCube>(_Childs_Array[i])->Rotate_PostSpawnSignArr();
	}
}

bool AArchElementPattern::Compare_EveryChildPreSpawnPostSpawnSignArr()
{
	TArray<AActor*> _Childs_Array;
	GetAllChildActors(_Childs_Array, false);

	for (int32 i = 0; i < _Childs_Array.Num(); i++)
	{
		bool _bIsMatching = Cast<APatternCube>(_Childs_Array[i])->Compare_PreSpawnPostSpawnSignArr();

		if (!_bIsMatching)
		{
			return false; // One of the child's PreSpawnSignArr does not match PostSpawnSignArr
		}
	}

	return true;
}

void AArchElementPattern::SET_bIsObstructed(bool Value_p)
{
	this->bIsObstructed = Value_p;
}

void AArchElementPattern::DEBUG_DisplayEveryChildPreSpawnSignArr()
{
	TArray<AActor*> _Childs_Array;
	GetAllChildActors(_Childs_Array, false);

	for (int32 i = 0; i < _Childs_Array.Num(); i++)
	{
		UE_LOG(LogClass_ArchElementPattern, Log, TEXT("=> %s <= PreSpawn_SignArr : %s"), *_Childs_Array[i]->GetName(), *Cast<APatternCube>(_Childs_Array[i])->DEBUG_PreSpawnSignArr());
	}

	UE_LOG(LogClass_ArchElementPattern, Log, TEXT("*****"));
}

void AArchElementPattern::DEBUG_DisplayEveryChildPostSpawnSignArr()
{
	TArray<AActor*> _Childs_Array;
	GetAllChildActors(_Childs_Array, false);

	for (int32 i = 0; i < _Childs_Array.Num(); i++)
	{
		UE_LOG(LogClass_ArchElementPattern, Log, TEXT("=> %s <= PostSpawn_SignArr : %s"), *_Childs_Array[i]->GetName(), *Cast<APatternCube>(_Childs_Array[i])->DEBUG_PostSpawnSignArr());
	}

	UE_LOG(LogClass_ArchElementPattern, Log, TEXT("*****"));
}