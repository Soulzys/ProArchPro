#include "AreaCubeBase.h"
#include "Engine/StaticMeshSocket.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(LogClass_AreaCubeBase);

AAreaCubeBase::AAreaCubeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Class variable initialization
	this->FaceObstacleCount = 0;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_AreaCube(*(this->PathStoring.SM_AreaCubeBaseModel_PF));

	check(OF_SM_AreaCube.Succeeded());

	this->SMC_AreaCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_AreaCube"));
	SetRootComponent(this->SMC_AreaCube);
	this->SMC_AreaCube->SetStaticMesh(OF_SM_AreaCube.Object);
	this->SMC_AreaCube->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->SMSK_AreaCube_Face_01_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_01_Out));
	this->SMSK_AreaCube_Face_02_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_02_Out));
	this->SMSK_AreaCube_Face_03_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_03_Out));
	this->SMSK_AreaCube_Face_04_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_04_Out));
	this->SMSK_AreaCube_Face_05_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_05_Out));
	this->SMSK_AreaCube_Face_06_Out = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_06_Out));
	this->SMSK_AreaCube_Face_01_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_01_In));
	this->SMSK_AreaCube_Face_02_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_02_In));
	this->SMSK_AreaCube_Face_03_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_03_In));
	this->SMSK_AreaCube_Face_04_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_04_In));
	this->SMSK_AreaCube_Face_05_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_05_In));
	this->SMSK_AreaCube_Face_06_In = this->SMC_AreaCube->GetSocketByName(*(this->NameStoring.SMSK_AreaCubeBaseModel_Face_06_In));

	check(this->SMSK_AreaCube_Face_01_Out);
	check(this->SMSK_AreaCube_Face_02_Out);
	check(this->SMSK_AreaCube_Face_03_Out);
	check(this->SMSK_AreaCube_Face_04_Out);
	check(this->SMSK_AreaCube_Face_05_Out);
	check(this->SMSK_AreaCube_Face_06_Out);
	check(this->SMSK_AreaCube_Face_01_In);
	check(this->SMSK_AreaCube_Face_02_In);
	check(this->SMSK_AreaCube_Face_03_In);
	check(this->SMSK_AreaCube_Face_04_In);
	check(this->SMSK_AreaCube_Face_05_In);
	check(this->SMSK_AreaCube_Face_06_In);
}

void AAreaCubeBase::BeginPlay()
{
	Super::BeginPlay();
	
	this->Init_Main();
}

void AAreaCubeBase::Init_Main()
{
	this->Init_Variables();
}

void AAreaCubeBase::Init_Variables()
{

}

bool AAreaCubeBase::Trace_Ray(const FVector& RayEndPos_p)
{
	/*check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation()         ;
	FVector _RayEndPos   = RayEndPos_p + _RayStartPos ;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Cyan, false, 10.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Green, false, 10.0f);
		//FaceObstacleCount++; // Do we need this within this class ? 
		return true;
	}
	else
	{
		return false;
	}*/

	return false;
}

bool AAreaCubeBase::Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p)
{
	return false;
}

void AAreaCubeBase::Init_PostSpawnSignatureArray()
{
	
}

int32 AAreaCubeBase::GET_FaceObstacleCount()
{
	if (this->FaceObstacleCount < 0 && this->FaceObstacleCount > 6)
	{
		check(0 == 1);
	}

	return this->FaceObstacleCount;
}

int32* AAreaCubeBase::GET_PostSpawnSignArr()
{
	return this->PostSpawn_SignArr;
}

void AAreaCubeBase::Rotate_SizeFourArray(int32* Array_p)
{
	int32 _Index_0 = Array_p[0]; // 1
	int32 _Index_1 = Array_p[1]; // 0
	int32 _Index_2 = Array_p[2]; // 0
	int32 _Index_3 = Array_p[3]; // 1

	Array_p[0] = _Index_3; // 1
	Array_p[1] = _Index_0; // 1
	Array_p[2] = _Index_1; // 0
	Array_p[3] = _Index_2; // 0 
}