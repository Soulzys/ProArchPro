#include "AreaCubeFiller.h"
#include "Engine/StaticMeshSocket.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(LogClass_AreaCubeFiller);

AAreaCubeFiller::AAreaCubeFiller()
{
	// Variables instantiation
	this->bSideFaceObstacleFollowingPattern = false;
	this->RotationCount = 0;
	this->ArrayPosition = 0;

	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Blue  (*(PathStoring.MI_SKTC_Blue  ));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Red   (*(PathStoring.MI_SKTC_Red   ));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Green (*(PathStoring.MI_SKTC_Green ));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Cyan  (*(PathStoring.MI_SKTC_Cyan  ));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Yellow(*(PathStoring.MI_SKTC_Yellow));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Purple(*(PathStoring.MI_SKTC_Purple));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Orange(*(PathStoring.MI_SKTC_Orange));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Black (*(PathStoring.MI_SKTC_Black ));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Face_DetectionCube(*(PathStoring.SM_RayDetectionCube_PF));

	check(OF_MI_SKTC_Blue  .Succeeded());
	check(OF_MI_SKTC_Red   .Succeeded());
	check(OF_MI_SKTC_Green .Succeeded());
	check(OF_MI_SKTC_Cyan  .Succeeded());
	check(OF_MI_SKTC_Yellow.Succeeded());
	check(OF_MI_SKTC_Purple.Succeeded());
	check(OF_MI_SKTC_Orange.Succeeded());
	check(OF_MI_SKTC_Black .Succeeded());

	check(OF_SM_Face_DetectionCube.Succeeded());

	this->MI_SKTC_Blue   = OF_MI_SKTC_Blue  .Object;
	this->MI_SKTC_Red    = OF_MI_SKTC_Red   .Object;
	this->MI_SKTC_Green  = OF_MI_SKTC_Green .Object;
	this->MI_SKTC_Cyan   = OF_MI_SKTC_Cyan  .Object;
	this->MI_SKTC_Yellow = OF_MI_SKTC_Yellow.Object;
	this->MI_SKTC_Purple = OF_MI_SKTC_Purple.Object;
	this->MI_SKTC_Orange = OF_MI_SKTC_Orange.Object;
	this->MI_SKTC_Black  = OF_MI_SKTC_Black .Object;

	//
	//

	this->SMC_Face_01_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_01_DetectionCube"));
	this->SMC_Face_01_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_01_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_01_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_01_In->RelativeLocation);

	//
	//

	this->SMC_Face_02_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_02_DetectionCube"));
	this->SMC_Face_02_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_02_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_02_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_02_In->RelativeLocation);

	//
	//

	this->SMC_Face_03_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_03_DetectionCube"));
	this->SMC_Face_03_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_03_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_03_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_03_In->RelativeLocation);

	//
	//

	this->SMC_Face_04_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_04_DetectionCube"));
	this->SMC_Face_04_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_04_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_04_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_04_In->RelativeLocation);
	
	//
	//

	this->SMC_Face_05_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_05_DetectionCube"));
	this->SMC_Face_05_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_05_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_05_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_05_In->RelativeLocation);

	//
	//

	this->SMC_Face_06_DetectionCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Face_06_DetectionCube"));
	this->SMC_Face_06_DetectionCube->SetupAttachment(RootComponent);
	this->SMC_Face_06_DetectionCube->SetStaticMesh(OF_SM_Face_DetectionCube.Object);
	this->SMC_Face_06_DetectionCube->SetRelativeLocation(SMSK_AreaCube_Face_06_In->RelativeLocation);
}

void AAreaCubeFiller::BeginPlay()
{
	Super::BeginPlay();
	
	this->Init_PostSpawnSignatureArray();
	this->Init_Variables();
}

void AAreaCubeFiller::Init_PostSpawnSignatureArray()
{
	// Tracing the ray from all faces, initializing 'FaceObstacleCount' on the way
	bool _bFace_01_Signature = this->Trace_Ray(SMSK_AreaCube_Face_01_In->RelativeLocation, SMSK_AreaCube_Face_01_Out->RelativeLocation);
	bool _bFace_02_Signature = this->Trace_Ray(SMSK_AreaCube_Face_02_In->RelativeLocation, SMSK_AreaCube_Face_02_Out->RelativeLocation);
	bool _bFace_03_Signature = this->Trace_Ray(SMSK_AreaCube_Face_03_In->RelativeLocation, SMSK_AreaCube_Face_03_Out->RelativeLocation);
	bool _bFace_04_Signature = this->Trace_Ray(SMSK_AreaCube_Face_04_In->RelativeLocation, SMSK_AreaCube_Face_04_Out->RelativeLocation);
	bool _bFace_05_Signature = this->Trace_Ray(SMSK_AreaCube_Face_05_In->RelativeLocation, SMSK_AreaCube_Face_05_Out->RelativeLocation);
	bool _bFace_06_Signature = this->Trace_Ray(SMSK_AreaCube_Face_06_In->RelativeLocation, SMSK_AreaCube_Face_06_Out->RelativeLocation);

	// Initializing the Actor PostSpawn_SignatureArray
	(_bFace_01_Signature) ? PostSpawn_SignArr[0] = 1 : PostSpawn_SignArr[0] = 0;
	(_bFace_02_Signature) ? PostSpawn_SignArr[1] = 1 : PostSpawn_SignArr[1] = 0;
	(_bFace_03_Signature) ? PostSpawn_SignArr[2] = 1 : PostSpawn_SignArr[2] = 0;
	(_bFace_04_Signature) ? PostSpawn_SignArr[3] = 1 : PostSpawn_SignArr[3] = 0;
	(_bFace_05_Signature) ? PostSpawn_SignArr[4] = 1 : PostSpawn_SignArr[4] = 0;
	(_bFace_06_Signature) ? PostSpawn_SignArr[5] = 1 : PostSpawn_SignArr[5] = 0;

	// Setting the Actor color regarding its 'FaceObstacleCount' value
	this->Set_MeshColor(FaceObstacleCount);

	// Displaying the Actor PostSpawn_SignatureArray through the logs
	UE_LOG(LogClass_AreaCubeFiller, Log, TEXT("AreaCubeFiller's (%s) PostSpawn_SignArr has been initialized : { %d, %d, %d, %d, %d, %d }"),
		*GetName(),
		PostSpawn_SignArr[0],
		PostSpawn_SignArr[1],
		PostSpawn_SignArr[2],
		PostSpawn_SignArr[3],
		PostSpawn_SignArr[4],
		PostSpawn_SignArr[5]);
}

void AAreaCubeFiller::Init_Variables()
{
	this->Determine_SideFaceObstacleFollowingPattern();
}

bool AAreaCubeFiller::Trace_Ray(const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation()         ;
	FVector _RayEndPos   = RayEndPos_p + _RayStartPos ;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Cyan, false, 5.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Green, false, 5.0f);
		FaceObstacleCount++; // Coming from the mother class 
		return true;
	}
	else
	{
		return false;
	}
}

bool AAreaCubeFiller::Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation() + RayStartPos_p ;
	FVector _RayEndPos   = GetActorLocation() + RayEndPos_p   ;

	FCollisionQueryParams _TraceParams ;
	_TraceParams.bTraceComplex = true  ;
	
	bool _bIsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);
	
	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Cyan, false, 5.0f, 0, 2.5f);

	if (_bIsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Green, false, 5.0f);
		FaceObstacleCount++; // Coming from the mother class 

		return true;
	}
	else
	{
		return false;
	}
}

void AAreaCubeFiller::Set_MeshColor(int32 FaceObstacleCount_p)
{
	switch (FaceObstacleCount_p)
	{
		case 0:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Green);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Green);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Green);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Green);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Green);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Green);
			break;
		case 1:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Blue);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Blue);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Blue);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Blue);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Blue);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Blue);
			break;
		case 2:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Cyan);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Cyan);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Cyan);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Cyan);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Cyan);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Cyan);
			break;
		case 3:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Purple);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Purple);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Purple);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Purple);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Purple);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Purple);
			break;
		case 4:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Yellow);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Yellow);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Yellow);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Yellow);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Yellow);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Yellow);
			break;
		case 5:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Orange);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Orange);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Orange);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Orange);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Orange);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Orange);
			break;
		case 6:
			SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Red);
			SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Red);
			SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Red);
			SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Red);
			SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Red);
			SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Red);
			break;
		default:
			UE_LOG(LogClass_AreaCubeFiller, Warning, TEXT("You must only input a number 0 >= && <= 6"));
			return;
			break;
	}
}

int8 AAreaCubeFiller::GET_RotationCount()
{
	if (this->RotationCount < 0 || this->RotationCount > 3)
	{
		check(0 == 1);
	}

	return this->RotationCount;
}

int16 AAreaCubeFiller::GET_ArrayPosition()
{
	if (this->ArrayPosition < 0)
	{
		check(0 == 1);
	}

	return this->ArrayPosition;
}

bool AAreaCubeFiller::GET_SideFaceObstacleFollowingPattern()
{
	return this->bSideFaceObstacleFollowingPattern;
}

void AAreaCubeFiller::SET_RotationCount(int8 RotationCount_p)
{
	if (RotationCount_p >= 0 && RotationCount_p <= 3)
	{
		this->RotationCount = RotationCount_p;
	}
	else
	{
		UE_LOG(LogClass_AreaCubeFiller, Warning, TEXT("Error ! %d is not comprise between 0 and 3. Cannot set this value to -> RotationCount <- !"), RotationCount_p);
	}
}

FString AAreaCubeFiller::DEBUG_PostSpawnSignArr()
{	
	FString _Index_0 = FString::FromInt(PostSpawn_SignArr[0]);
	FString _Index_1 = FString::FromInt(PostSpawn_SignArr[1]);
	FString _Index_2 = FString::FromInt(PostSpawn_SignArr[2]);
	FString _Index_3 = FString::FromInt(PostSpawn_SignArr[3]);
	FString _Index_4 = FString::FromInt(PostSpawn_SignArr[4]);
	FString _Index_5 = FString::FromInt(PostSpawn_SignArr[5]);

	FString _PostSpawnSignArr = "{ " + 
									_Index_0 + ", " + 
									_Index_1 + ", " + 
									_Index_2 + ", " + 
									_Index_3 + ", " + 
									_Index_4 + ", " + 
									_Index_5 +
								" }";

	return _PostSpawnSignArr;
}

void AAreaCubeFiller::Determine_SideFaceObstacleFollowingPattern()
{
	// Note : no need to mind about bSideFaceObstacleFollowingPattern == false as it is set to false by default in the Constructor

	int32* _SignArr = GET_PostSpawnSignArr();

	if (_SignArr[0] == 1)
	{
		if (_SignArr[1] == 1)
		{
			this->bSideFaceObstacleFollowingPattern = true;
		}
	}

	if (_SignArr[1] == 1)
	{
		if (_SignArr[2] == 1)
		{
			this->bSideFaceObstacleFollowingPattern = true;
		}
	}

	if (_SignArr[2] == 1)
	{
		if (_SignArr[3] == 1)
		{
			this->bSideFaceObstacleFollowingPattern = true;
		}
	}

	if (_SignArr[3] == 1)
	{
		if (_SignArr[0] == 1)
		{
			this->bSideFaceObstacleFollowingPattern = true;
		}
	}
}

void AAreaCubeFiller::RayTrace_InternalCube(const FVector& RayStartPos_p, const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation() + RayStartPos_p ;
	FVector _RayEndPos   = GetActorLocation() + RayEndPos_p   ;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _bIsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Red, false, 5.0f, 0, 2.5f);

	if (_bIsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Green, false, 5.0f);

		if (_HitResult.GetActor()->IsA(AAreaCubeFiller::StaticClass()))
		{
			FString _ComponentName = _HitResult.GetComponent()->GetName();

			FString _TrimStart = "SMC_Face_0"          ;
			FString _TrimEnd   = "_DetectionCube"      ;
			_ComponentName.RemoveFromStart(_TrimStart) ;
			_ComponentName.RemoveFromEnd(_TrimEnd)     ;

			if (_ComponentName == "1")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_01)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_01, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}

			if (_ComponentName == "2")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_02)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_02, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}

			if (_ComponentName == "3")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_03)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_03, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}

			if (_ComponentName == "4")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_04)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_04, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}

			if (_ComponentName == "5")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_05)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_05, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}

			if (_ComponentName == "6")
			{
				AAreaCubeFiller* _CubeFiller = Cast<AAreaCubeFiller>(_HitResult.GetActor())  ;
				check(_CubeFiller)                                                           ;
				_CubeFiller->Reset_FaceSignArr(EFaceIndex::EFDX_FACE_06)                     ;
				_CubeFiller->Set_FaceColor(EFaceIndex::EFDX_FACE_06, EFaceColor::EFCL_BLACK) ;
				_CubeFiller = nullptr                                                        ;
			}
		}
	}
}

void AAreaCubeFiller::Trace_AllInternalRays()
{
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_01_In->RelativeLocation, SMSK_AreaCube_Face_01_Out->RelativeLocation * 1.25f);
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_02_In->RelativeLocation, SMSK_AreaCube_Face_02_Out->RelativeLocation * 1.25f);
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_03_In->RelativeLocation, SMSK_AreaCube_Face_03_Out->RelativeLocation * 1.25f);
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_04_In->RelativeLocation, SMSK_AreaCube_Face_04_Out->RelativeLocation * 1.25f);
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_05_In->RelativeLocation, SMSK_AreaCube_Face_05_Out->RelativeLocation * 1.25f);
	this->RayTrace_InternalCube(SMSK_AreaCube_Face_06_In->RelativeLocation, SMSK_AreaCube_Face_06_Out->RelativeLocation * 1.25f);
}

void AAreaCubeFiller::Reset_FaceSignArr(EFaceIndex FaceIndex_p)
{
	switch (FaceIndex_p)
	{
		case EFaceIndex::EFDX_FACE_01:
			PostSpawn_SignArr[0] = 2;
			break;
		case EFaceIndex::EFDX_FACE_02:
			PostSpawn_SignArr[1] = 2;
			break;
		case EFaceIndex::EFDX_FACE_03:
			PostSpawn_SignArr[2] = 2;
			break;
		case EFaceIndex::EFDX_FACE_04:
			PostSpawn_SignArr[3] = 2;
			break;
		case EFaceIndex::EFDX_FACE_05:
			PostSpawn_SignArr[4] = 2;
			break;
		case EFaceIndex::EFDX_FACE_06:
			PostSpawn_SignArr[5] = 2;
			break;
		default:
			UE_LOG(LogClass_AreaCubeFiller, Warning, TEXT("I was called by default"));
			break;
	}
}

void AAreaCubeFiller::Set_FaceColor(EFaceIndex FaceIndex_p, EFaceColor FaceColor_p)
{
	switch (FaceIndex_p)
	{
		case EFaceIndex::EFDX_FACE_01:
			SMC_AreaCube->SetMaterial(0, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		case EFaceIndex::EFDX_FACE_02:
			SMC_AreaCube->SetMaterial(1, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		case EFaceIndex::EFDX_FACE_03:
			SMC_AreaCube->SetMaterial(2, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		case EFaceIndex::EFDX_FACE_04:
			SMC_AreaCube->SetMaterial(3, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		case EFaceIndex::EFDX_FACE_05:
			SMC_AreaCube->SetMaterial(4, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		case EFaceIndex::EFDX_FACE_06:
			SMC_AreaCube->SetMaterial(5, this->Get_FaceMaterialColor(FaceColor_p));
			break;
		default:
			break;
	}
}

UMaterialInstance* AAreaCubeFiller::Get_FaceMaterialColor(EFaceColor FaceColor_p)
{
	UMaterialInstance* _MatIns = nullptr;

	switch (FaceColor_p)
	{
		case EFaceColor::EFCL_BLUE:
			_MatIns = this->MI_SKTC_Blue;
			break;
		case EFaceColor::EFCL_RED:
			_MatIns = this->MI_SKTC_Red;
			break;
		case EFaceColor::EFCL_GREEN:
			_MatIns = this->MI_SKTC_Green;
			break;
		case EFaceColor::EFCL_CYAN:
			_MatIns = this->MI_SKTC_Cyan;
			break;
		case EFaceColor::EFCL_YELLOW:
			_MatIns = this->MI_SKTC_Yellow;
			break;
		case EFaceColor::EFCL_PURPLE:
			_MatIns = this->MI_SKTC_Purple;
			break;
		case EFaceColor::EFCL_ORANGE:
			_MatIns = this->MI_SKTC_Orange;
			break;
		case EFaceColor::EFCL_BLACK:
			_MatIns = this->MI_SKTC_Black;
			break;
		default:
			break;
	}

	return _MatIns;
}