#include "PatternCube.h"
#include "Engine/StaticMeshSocket.h"
#include "DrawDebugHelpers.h"
#include "AreaCubeFiller.h"

DEFINE_LOG_CATEGORY(LogClass_PatternCube);

APatternCube::APatternCube()
{
	// Initializing variables
	this->PreSpawn_FaceObstacleCount = 0;
	this->PreSpawn_SideFaceObstacleCount = 0;
	this->PreSpawn_SignArr_Pattern = false;
	this->bIsCubeFillerMatching = false;
	this->ObjectName = GetName();

	// Loading
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Blue (*(this->PathStoring.MI_SKTC_Blue ));
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> OF_MI_SKTC_Green(*(this->PathStoring.MI_SKTC_Green));

	// Checking
	check(OF_MI_SKTC_Blue .Succeeded());
	check(OF_MI_SKTC_Green.Succeeded());

	// Assigning
	this->MI_SKTC_Blue  = OF_MI_SKTC_Blue .Object;
	this->MI_SKTC_Green = OF_MI_SKTC_Green.Object;

	SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Green);
	SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Green);
	SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Green);
	SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Green);
	SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Green);
	SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Green);
}

void APatternCube::BeginPlay()
{
	Super::BeginPlay();

	// Initializing PatternCube's PreSpawn and PostSpawn SignatureArray
	this->Init_PreSpawnSignatureArray ();
	this->Init_PreSpawnSignatureArrayPattern();
	this->Init_PostSpawnSignatureArray();
	this->Init_DebuggingLog();
}

void APatternCube::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent_p)
{
	Super::PostEditChangeProperty(PropertyChangedEvent_p);

	// If bFace_x_Signature == true --> Face is turned blue
	// Else --> Face is turned green
	(this->bFace_01_Signature) ? SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(0, this->MI_SKTC_Green);
	(this->bFace_02_Signature) ? SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(1, this->MI_SKTC_Green);
	(this->bFace_03_Signature) ? SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(2, this->MI_SKTC_Green);
	(this->bFace_04_Signature) ? SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(3, this->MI_SKTC_Green);
	(this->bFace_05_Signature) ? SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(4, this->MI_SKTC_Green);
	(this->bFace_06_Signature) ? SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Blue) : SMC_AreaCube->SetMaterial(5, this->MI_SKTC_Green);
}

void APatternCube::Init_PreSpawnSignatureArray()
{
	// Face 01
	if (this->bFace_01_Signature)
	{
		this->PreSpawn_SignArr[0] = 1;
		this->PreSpawn_FaceObstacleCount++;
		this->PreSpawn_SideFaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[0] = 0;
	}

	// Face 02
	if (this->bFace_02_Signature)
	{
		this->PreSpawn_SignArr[1] = 1;
		this->PreSpawn_FaceObstacleCount++;
		this->PreSpawn_SideFaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[1] = 0;
	}

	// Face 03
	if (this->bFace_03_Signature)
	{
		this->PreSpawn_SignArr[2] = 1;
		this->PreSpawn_FaceObstacleCount++;
		this->PreSpawn_SideFaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[2] = 0;
	}

	// Face 04
	if (this->bFace_04_Signature)
	{
		this->PreSpawn_SignArr[3] = 1;
		this->PreSpawn_FaceObstacleCount++;
		this->PreSpawn_SideFaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[3] = 0;
	}

	// Face 05
	if (this->bFace_05_Signature)
	{
		this->PreSpawn_SignArr[4] = 1;
		this->PreSpawn_FaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[4] = 0;
	}

	// Face 06
	if (this->bFace_06_Signature)
	{
		this->PreSpawn_SignArr[5] = 1;
		this->PreSpawn_FaceObstacleCount++;
	}
	else
	{
		this->PreSpawn_SignArr[5] = 0;
	}

	UE_LOG(LogClass_PatternCube, Log, TEXT("PatternCube's (%s) PreSpawn_SignArr has been initialized : { %d, %d, %d, %d, %d, %d }"),
		*GetName(),
		this->PreSpawn_SignArr[0],
		this->PreSpawn_SignArr[1],
		this->PreSpawn_SignArr[2],
		this->PreSpawn_SignArr[3],
		this->PreSpawn_SignArr[4],
		this->PreSpawn_SignArr[5]);
}

void APatternCube::Init_PreSpawnSignatureArrayPattern()
{
	if (this->PreSpawn_SignArr[0] == 1)
	{
		if (this->PreSpawn_SignArr[1] == 1)
		{
			this->PreSpawn_SignArr_Pattern = true;
		}
	}

	if (this->PreSpawn_SignArr[1] == 1)
	{
		if (this->PreSpawn_SignArr[2] == 1)
		{
			this->PreSpawn_SignArr_Pattern = true;
		}
	}

	if (this->PreSpawn_SignArr[2] == 1)
	{
		if (this->PreSpawn_SignArr[3] == 1)
		{
			this->PreSpawn_SignArr_Pattern = true;
		}
	}

	if (this->PreSpawn_SignArr[3] == 1)
	{
		if (this->PreSpawn_SignArr[0] == 1)
		{
			this->PreSpawn_SignArr_Pattern = true;
		}
	}
}

void APatternCube::Init_PostSpawnSignatureArray()
{
	// Do not get confused with the Editor Faces Controller variables
	// These ones are to initialize the PostSpawn_SignatureArray
	bool _bFace_01_Signature = this->Trace_Ray(SMSK_AreaCube_Face_01_In->RelativeLocation, SMSK_AreaCube_Face_01_Out->RelativeLocation);
	bool _bFace_02_Signature = this->Trace_Ray(SMSK_AreaCube_Face_02_In->RelativeLocation, SMSK_AreaCube_Face_02_Out->RelativeLocation);
	bool _bFace_03_Signature = this->Trace_Ray(SMSK_AreaCube_Face_03_In->RelativeLocation, SMSK_AreaCube_Face_03_Out->RelativeLocation);
	bool _bFace_04_Signature = this->Trace_Ray(SMSK_AreaCube_Face_04_In->RelativeLocation, SMSK_AreaCube_Face_04_Out->RelativeLocation);
	bool _bFace_05_Signature = this->Trace_Ray(SMSK_AreaCube_Face_05_In->RelativeLocation, SMSK_AreaCube_Face_05_Out->RelativeLocation);
	bool _bFace_06_Signature = this->Trace_Ray(SMSK_AreaCube_Face_06_In->RelativeLocation, SMSK_AreaCube_Face_06_Out->RelativeLocation);

	(_bFace_01_Signature) ? PostSpawn_SignArr[0] = 1 : PostSpawn_SignArr[0] = 0;
	(_bFace_02_Signature) ? PostSpawn_SignArr[1] = 1 : PostSpawn_SignArr[1] = 0;
	(_bFace_03_Signature) ? PostSpawn_SignArr[2] = 1 : PostSpawn_SignArr[2] = 0;
	(_bFace_04_Signature) ? PostSpawn_SignArr[3] = 1 : PostSpawn_SignArr[3] = 0;
	(_bFace_05_Signature) ? PostSpawn_SignArr[4] = 1 : PostSpawn_SignArr[4] = 0;
	(_bFace_06_Signature) ? PostSpawn_SignArr[5] = 1 : PostSpawn_SignArr[5] = 0;

	// Determine whether it has a Following or a Non-Following pattern


	UE_LOG(LogClass_PatternCube, Log, TEXT("PatternCube's (%s) PostSpawn_SignArr has been initialized : { %d, %d, %d, %d, %d, %d }"),
		*GetName(),
		PostSpawn_SignArr[0],
		PostSpawn_SignArr[1],
		PostSpawn_SignArr[2],
		PostSpawn_SignArr[3],
		PostSpawn_SignArr[4],
		PostSpawn_SignArr[5]);
}

void APatternCube::Init_DebuggingLog()
{
	UE_LOG(LogClass_PatternCube, Log, TEXT("=> %s <= Initialization Logs ... "), *this->ObjectName);
	UE_LOG(LogClass_PatternCube, Log, TEXT("**********"));
	UE_LOG(LogClass_PatternCube, Log, TEXT("PreSpawn_SignArr : { %d, %d, %d, %d, %d, %d }"), 
																  this->PreSpawn_SignArr[0],
																  this->PreSpawn_SignArr[1],
																  this->PreSpawn_SignArr[2],
																  this->PreSpawn_SignArr[3],
																  this->PreSpawn_SignArr[4],
																  this->PreSpawn_SignArr[5]);

	UE_LOG(LogClass_PatternCube, Log, TEXT("PostSpawn_SignArr : { %d, %d, %d, %d, %d, %d }"), 
																		PostSpawn_SignArr[0],
																		PostSpawn_SignArr[1],
																		PostSpawn_SignArr[2],
																		PostSpawn_SignArr[3],
																		PostSpawn_SignArr[4],
																		PostSpawn_SignArr[5]);
	UE_LOG(LogClass_PatternCube, Log, TEXT("PreSpawn_SideFaceObstacleCount : %d"), this->PreSpawn_SideFaceObstacleCount);
	if (this->PreSpawn_SignArr_Pattern)
	{
		UE_LOG(LogClass_PatternCube, Log, TEXT("PreSpawn_SignArr_Pattern : Following"));
	}
	else
	{
		UE_LOG(LogClass_PatternCube, Log, TEXT("PreSpawn_SignArr_Pattern : Non-Following"));
	}
	UE_LOG(LogClass_PatternCube, Log, TEXT("**********"));
}

bool APatternCube::Trace_Ray(const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation();
	FVector _RayEndPos = RayEndPos_p + _RayStartPos;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Orange, false, 20.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Red, false, 20.0f);
		FaceObstacleCount++; // Do we need this within this class ? 
		return true;
	}
	else
	{
		return false;
	}
}

bool APatternCube::Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation() + RayStartPos_p ;
	FVector _RayEndPos   = GetActorLocation() + RayEndPos_p   ;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Orange, false, 20.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Red, false, 20.0f);
		FaceObstacleCount++; // Do we need this within this class ? 
		return true;
	}
	else
	{
		return false;
	}
}

bool APatternCube::Trace_NeutralRay(const FVector& RayEndPos_p)
{
	check(GetWorld());

	FHitResult _HitResult;

	FVector _RayStartPos = GetActorLocation();
	FVector _RayEndPos = RayEndPos_p + _RayStartPos;

	FCollisionQueryParams _TraceParams;
	_TraceParams.bTraceComplex = true;

	bool _IsHit = GetWorld()->LineTraceSingleByChannel(_HitResult, _RayStartPos, _RayEndPos, ECC_Visibility, _TraceParams);

	DrawDebugLine(GetWorld(), _RayStartPos, _RayEndPos, FColor::Blue, false, 20.0f, 0, 2.5f);

	if (_IsHit)
	{
		DrawDebugBox(GetWorld(), _HitResult.ImpactPoint, FVector(5.0f), FColor::Black, false, 20.0f);

		if (_HitResult.GetActor() != nullptr)
		{
			this->PostSpawn_CubeFillerRef = _HitResult.GetActor();
			UE_LOG(LogClass_PatternCube, Warning, TEXT("An actor was spotted : => %s <="), *this->PostSpawn_CubeFillerRef->GetName());
		}
				
		return true;
	}
	else
	{
		return false;
	}
}

int32* APatternCube::GET_PreSpawnSignArr()
{
	return this->PreSpawn_SignArr;
}

int32 APatternCube::GET_PreSpawnFaceObstacleCount()
{
	if (this->PreSpawn_FaceObstacleCount < 0 && this->PreSpawn_FaceObstacleCount > 6)
	{
		check(0 == 1);
	}

	return this->PreSpawn_FaceObstacleCount;
}

int32 APatternCube::GET_PreSpawnSideFaceObstacleCount()
{
	if (this->PreSpawn_FaceObstacleCount < 0 && this->PreSpawn_FaceObstacleCount > 4)
	{
		check(0 == 1);
	}

	return this->PreSpawn_SideFaceObstacleCount;
}

bool APatternCube::GET_PreSpawnSignArrPattern()
{
	return this->PreSpawn_SignArr_Pattern;
}

void APatternCube::Rotate_PostSpawnSignArr()
{
	this->Rotate_SizeFourArray(PostSpawn_SignArr);
}

FString APatternCube::DEBUG_PostSpawnSignArr()
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

FString APatternCube::DEBUG_PreSpawnSignArr()
{
	FString _Index_0 = FString::FromInt(this->PreSpawn_SignArr[0]);
	FString _Index_1 = FString::FromInt(this->PreSpawn_SignArr[1]);
	FString _Index_2 = FString::FromInt(this->PreSpawn_SignArr[2]);
	FString _Index_3 = FString::FromInt(this->PreSpawn_SignArr[3]);
	FString _Index_4 = FString::FromInt(this->PreSpawn_SignArr[4]);
	FString _Index_5 = FString::FromInt(this->PreSpawn_SignArr[5]);

	FString _PreSpawnSignArr = "{ " + 
									_Index_0 + ", " + 
									_Index_1 + ", " + 
									_Index_2 + ", " + 
									_Index_3 + ", " + 
									_Index_4 + ", " + 
									_Index_5 + 
								" }";

	return _PreSpawnSignArr;
}

bool APatternCube::Compare_PreSpawnPostSpawnSignArr()
{
	if (PreSpawn_SignArr[0] == this->PostSpawn_SignArr[0])
	{
		if (PreSpawn_SignArr[1] == this->PostSpawn_SignArr[1])
		{
			if (PreSpawn_SignArr[2] == this->PostSpawn_SignArr[2])
			{
				if (PreSpawn_SignArr[3] == this->PostSpawn_SignArr[3])
				{
					if (PreSpawn_SignArr[4] == this->PostSpawn_SignArr[4])
					{
						if (PreSpawn_SignArr[5] == this->PostSpawn_SignArr[5])
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}