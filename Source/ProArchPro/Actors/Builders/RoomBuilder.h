#pragma once

#include "CoreMinimal.h"
#include "BuilderBase.h"
#include "RoomBuilder.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_RoomBuilder, Log, All);

class ARoomBase           ;
class AAreaCubeFiller     ;
class AArchElementPattern ;

UENUM()
enum class EDataTable : uint8
{
	EDT_LIGHT = 0 UMETA(DisplayName = "FLightCatalog_DT"), 
	EDT_BOX   = 1 UMETA(DisplayName = "FBoxCatalog_DT")
};

UCLASS()
class PROARCHPRO_API ARoomBuilder : public ABuilderBase
{
	GENERATED_BODY()
	
public:	

	ARoomBuilder();

	void Build_Room();

	// Setters
	void SET_RoomBase(ARoomBase* RoomBase_p);

protected:

	virtual void BeginPlay() override;

	// Fill a rectangle shaped volume with AreaCubeFiller Actors
	void Fill_RectangleVolume(const FVector& Vert_01_p, const FVector& Vert_02_p, const FVector& Vert_03_p, const FVector& Vert_04_p, const FVector& RoomActorOriginLoc_p);
	void Fill_RectangleVolume_TESTING(const FVector& Vert_01_p, const FVector& Vert_02_p, const FVector& Vert_03_p, const FVector& Vert_04_p, const FVector& ActorOriginLoc_p);
	// Fill a volume that is made of several rectangles with AreaCubeFiller Actors
	void Fill_Volume();
	void Fill_Volume(UStaticMesh* StaticMesh_p);
	void Fill_Volume(uint8 LoopCount_p);
	void Fill_Volume(uint16 StartingIndex_p, uint8 LoopCount_p);
	void Fill_Volume_TESTING(UStaticMesh* StaticMesh_p);
	// Gets the appropriate AreaCubeFiller array regarding of the desired obstacle count
	TArray<AAreaCubeFiller*> Get_AreaCubeFiller_Array(int32 ObstacleCount_p);

	// Main function to place actors
	void Spawn_ActorInRoom(EDataTable DataTable_p, int16 RowIndex_p, const FBuilderController& BuilderController_p, int16 ActorsNbToSpawns_p);

	void Destroy_EveryElementInArray(const FString& ArrayName_p, TArray<AAreaCubeFiller*> Array_p);

private:

	// ----- Internal methods only used for computing how and where to spawn actor in the Room ----- //
	void Loading_StructBuilder(EDataTable DataTable_p, int16 RowIndex_p, int16 ActorsNbToSpawns_p);
	void Loading_PatternCubeBaseReferences(const FBuilderController& BuilderController_p);
	void Spawn_BlueprintActors();
	void Spawn_Actor(const FBuilderController& BuilderController_p);
	void Spawn_AllActors();
	// Refinement methods
	void Refining_FirstStep();
	void Refining_SecondStep();
	void Refining_ThirdStep();
	void Refining_FourthStep();
	// Memory management methods
	void Reinit_Variables();
	// Debugging management methods
	void Cleaning_Room();

	// TESTING
	void TESTING_SelectAndRemove();

protected:

	// Actor references
	ARoomBase* RoomBase = nullptr;

	// AreaCubeFiller var
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_0_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_1_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_2_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_3_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_4_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_5_Obstacle;
	TArray<AAreaCubeFiller*> AreaCubeFiller_Array_6_Obstacle;

	int32 AreaCubeFillerCount;

	// Debugging variables
	FString ObjectName;

	// Struct
	FBuilderController BuilderController;

private:

	// Internal variables only used for computing how and where to spawn actor in the Room
	int32* PatternCubeBase_PreSpawnSignArr               ;
	int32* PatternCubeBase_PostSpawnSignArr              ;
	int8   PatternCubeBase_PreSpawnFaceObstacleCount     ;
	int8   PatternCubeBase_PreSpawnSideFaceObstacleCount ;
	bool   PatternCubeBase_FollowingPattern              ;
	TArray<AAreaCubeFiller*> WorkingArray                ;
	TArray<AArchElementPattern*> BlueprintActorsArray    ;
};
