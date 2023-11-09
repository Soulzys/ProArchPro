#pragma once

#include "CoreMinimal.h"
#include "AreaCubeBase.h"
#include "PatternCube.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_PatternCube, Log, All);

class UMaterialInstance;
class AAreaCubeFiller;

UCLASS()
class PROARCHPRO_API APatternCube : public AAreaCubeBase
{
	GENERATED_BODY()

public:

	APatternCube();

	void Rotate_PostSpawnSignArr();
	bool Compare_PreSpawnPostSpawnSignArr(); // Match = true, otherwise false

	// Getters
	int32* GET_PreSpawnSignArr();
	int32 GET_PreSpawnFaceObstacleCount();
	int32 GET_PreSpawnSideFaceObstacleCount();
	bool GET_PreSpawnSignArrPattern();

	// Debug functions
	FString DEBUG_PreSpawnSignArr();
	FString DEBUG_PostSpawnSignArr();

protected:

	// Virtual override functions
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent_p) override;
	virtual bool Trace_Ray(const FVector& RayEndPos_p) override;
	virtual bool Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p) override;

private:

	// Initialize our 'PreSpawn_SignArr' from the Editor settings of our PatternCube
	void Init_PreSpawnSignatureArray();
	// Initialize our 'PreSpawn_SignArr_Pattern' from the 'PreSpawn_SignArr'
	void Init_PreSpawnSignatureArrayPattern();
	// Initialize our 'PostSpawn_SignArr' after spawning a ArcElementPattern Actor made of PatternCube Actors in the World 
	virtual void Init_PostSpawnSignatureArray() override;
	// Display all 'Init' type information through logs
	void Init_DebuggingLog();

	// Doesn't affect the 'FaceObstacleCount'. Only returns true if hitting something, false otherwise
	bool Trace_NeutralRay(const FVector& RayEndPos_p);

protected:

	// Material Instance
	UMaterialInstance* MI_SKTC_Blue  = nullptr;
	UMaterialInstance* MI_SKTC_Green = nullptr;

	// SignatureArray
	int32 PreSpawn_SignArr[6] = { 0, 0, 0, 0, 0, 0 };
	int32 PreSpawn_FaceObstacleCount;
	int32 PreSpawn_SideFaceObstacleCount;
	bool PreSpawn_SignArr_Pattern; // true = Following, false = Non-Following

	// AreaCubeFiller reference that is initialized after spawning PatternCube
	AActor* PostSpawn_CubeFillerRef = nullptr;
	bool bIsCubeFillerMatching;

	// Debugging variables
	FString ObjectName;

protected:

	// ----- Editor Faces Controller ----- //

	// This is basically to set the PreSpawn_SignatureArray

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 01"))
	bool bFace_01_Signature = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 02"))
	bool bFace_02_Signature = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 03"))
	bool bFace_03_Signature = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 04"))
	bool bFace_04_Signature = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 05"))
	bool bFace_05_Signature = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Management", meta = (DisplayName = "Face 06"))
	bool bFace_06_Signature = false;
};
