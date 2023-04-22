#pragma once

#include "CoreMinimal.h"
#include "AreaCubeBase.h"
#include "AreaCubeFiller.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_AreaCubeFiller, Log, All);

class UMaterialInstance;

UENUM()
enum class EFaceIndex : uint8
{
	EFDX_FACE_01 = 1 UMETA(DisplayName = "Face_01"), 
	EFDX_FACE_02 = 2 UMETA(DisplayName = "Face_02"), 
	EFDX_FACE_03 = 3 UMETA(DisplayName = "Face_03"), 
	EFDX_FACE_04 = 4 UMETA(DisplayName = "Face_04"), 
	EFDX_FACE_05 = 5 UMETA(DisplayName = "Face_05"), 
	EFDX_FACE_06 = 6 UMETA(DisplayName = "Face_06")
};

UENUM()
enum class EFaceColor : uint8
{
	EFCL_BLUE   = 0 UMETA(DisplayName = "Blue"  ), 
	EFCL_RED    = 1 UMETA(DisplayName = "Red"   ), 
	EFCL_GREEN  = 2 UMETA(DisplayName = "Green" ), 
	EFCL_CYAN   = 3 UMETA(DisplayName = "Cyan"  ), 
	EFCL_YELLOW = 4 UMETA(DisplayName = "Yellow"), 
	EFCL_PURPLE = 5 UMETA(DisplayName = "Purple"), 
	EFCL_ORANGE = 6 UMETA(DisplayName = "Orange"), 
	EFCL_BLACK  = 7 UMETA(DisplayName = "Black" )
};

UCLASS()
class PROARCHPRO_API AAreaCubeFiller : public AAreaCubeBase
{
	GENERATED_BODY()

public:

	AAreaCubeFiller();

	// ----- Normal methods ----- //
	// 
	// Get the Following Pattern type of the AreaCube
	// If the Pattern is Following, the function returns true
	void Determine_SideFaceObstacleFollowingPattern();

	void Trace_AllInternalRays();
	void Set_FaceColor(EFaceIndex FaceIndex_p, EFaceColor FaceColor_p);
	
	// Getters
	int8 GET_RotationCount();
	int16 GET_ArrayPosition();
	bool GET_SideFaceObstacleFollowingPattern();

	// Setters
	void SET_RotationCount(int8 RotationCount_p);

	// For debug purposes
	FString DEBUG_PostSpawnSignArr();

protected:
	
	// *** Virtual override functions *** //
	virtual void BeginPlay() override;

	// *** Virtual functions *** // 
	virtual bool Trace_Ray(const FVector& RayEndPos_p) override;
	virtual bool Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p) override;
	void RayTrace_InternalCube(const FVector& RayStartPos_p, const FVector& RayEndPos_p);

private:

	// *** Virtual override functions *** //
	virtual void Init_PostSpawnSignatureArray() override;

	// *** Normal functions *** //
	// Setting the MaterialInstance (basically the color) for all faces based on 'FaceObstacleCount'
	// 0 --> Green
	// 1 --> Blue
	// 2 --> Cyan
	// 3 --> Purple
	// 4 --> Yellow
	// 5 --> Orange
	// 6 --> Red
	void Set_MeshColor(int32 FaceObstacleCount_p);
	UMaterialInstance* Get_FaceMaterialColor(EFaceColor FaceColor_p);

	void Reset_FaceSignArr(EFaceIndex FaceIndex_p);

	// Initializing the class variables
	void Init_Variables();

protected:

	// MaterialInstance
	UMaterialInstance* MI_SKTC_Blue   = nullptr ;
	UMaterialInstance* MI_SKTC_Red    = nullptr ;
	UMaterialInstance* MI_SKTC_Green  = nullptr ;
	UMaterialInstance* MI_SKTC_Cyan   = nullptr ;
	UMaterialInstance* MI_SKTC_Yellow = nullptr ;
	UMaterialInstance* MI_SKTC_Purple = nullptr ;
	UMaterialInstance* MI_SKTC_Orange = nullptr ;
	UMaterialInstance* MI_SKTC_Black  = nullptr ;

	// Number of rotation that is necessary for the cube to be aligned with the PatternCubeBase
	int8 RotationCount;

	// The position of the CubeFiller within the 'AreaCubeFiller_Array_X_Obstacle' array
	// Used when we delete the CubeFiller and therefore need to remove the CubeFiller from the array
	// As we currently use Array.Remove(), we still have no use for it yet. 
	// It would be a way to optimize our code in a near (or not) future
	int16 ArrayPosition;

	// If the AreaCubeFiller has a Following Pattern, then this is true
	bool bSideFaceObstacleFollowingPattern;

	UStaticMeshComponent* SMC_Face_01_DetectionCube = nullptr;
	UStaticMeshComponent* SMC_Face_02_DetectionCube = nullptr;
	UStaticMeshComponent* SMC_Face_03_DetectionCube = nullptr;
	UStaticMeshComponent* SMC_Face_04_DetectionCube = nullptr;
	UStaticMeshComponent* SMC_Face_05_DetectionCube = nullptr;
	UStaticMeshComponent* SMC_Face_06_DetectionCube = nullptr;
};
