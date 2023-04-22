#include "TestingCube.h"
#include "Engine/StaticMeshSocket.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(LogClass_TestingCube);

ATestingCube::ATestingCube()
{
	PrimaryActorTick.bCanEverTick = false;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SMC_Cube(*(this->PathStoring.SM_AreaCubeBaseModel_PF));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SMC_InsideCube(*(this->PathStoring.SM_RayDetectionCube_PF));

	check(OF_SMC_Cube.Succeeded());
	check(OF_SMC_InsideCube.Succeeded());

	this->SMC_Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Cube"));
	SetRootComponent(this->SMC_Cube);
	this->SMC_Cube->SetStaticMesh(OF_SMC_Cube.Object);
	//this->SMSK_TestingCubeSocket = this->SMC_Cube->GetSocketByName(*(this->NameStoring.SMSK_RayDetectionCube_FaceTop));

	//check(this->SMSK_TestingCubeSocket);

	this->SMC_InsideCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_InsideCube"));
	this->SMC_InsideCube->SetupAttachment(RootComponent);
	this->SMC_InsideCube->SetStaticMesh(OF_SMC_InsideCube.Object);
}

void ATestingCube::BeginPlay()
{
	Super::BeginPlay();	

	//bool bHasMeshBeenDetected = this->Trace_Ray(this->SMSK_TestingCubeSocket->RelativeLocation);
	//this->Trace_Ray(this->SMSK_TestingCubeSocket->RelativeLocation, this->SMSK_TestingCubeSocket->RelativeLocation + FVector(0.0f, 25.0f, 5.0f));

	/*if (bHasMeshBeenDetected)
	{
		UE_LOG(LogClass_TestingCube, Warning, TEXT("HIT !"));
	}
	else
	{
		UE_LOG(LogClass_TestingCube, Warning, TEXT("Not hit..."));
	}*/
}

bool ATestingCube::Trace_Ray(const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation();
	FVector _RayEndPos = RayEndPos_p + _RayStartPos;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos + FVector(0.0f, 0.0f, 0.0f), FColor::Turquoise, false, 600.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugSphere(GetWorld(), _HitResult.ImpactPoint, 50.0f, 12, FColor::Emerald, false, 600.0f, 2, 1.5f);
		UE_LOG(LogClass_TestingCube, Warning, TEXT("We have detected something named => %s <= !"), *_HitResult.GetActor()->GetName());
		return true;
	}
	else
	{
		return false;
	}
}

bool ATestingCube::Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation() + RayStartPos_p;
	FVector _RayEndPos = _RayStartPos + RayEndPos_p;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos + FVector(0.0f, 0.0f, 0.0f), FColor::Orange, false, 600.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugSphere(GetWorld(), _HitResult.ImpactPoint, 50.0f, 12, FColor::Emerald, false, 600.0f, 2, 1.5f);

		return true;
	}
	else
	{
		return false;
	}
}