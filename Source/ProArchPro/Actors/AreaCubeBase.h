#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Storage/StoringName.h"
#include "../Storage/StoringPath.h"
#include "AreaCubeBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_AreaCubeBase, Log, All);

class UStaticMeshComponent ;
class UStaticMeshSocket    ;

UCLASS()
class PROARCHPRO_API AAreaCubeBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AAreaCubeBase();

	// Getters
	int32 GET_FaceObstacleCount();
	int32* GET_PostSpawnSignArr();

protected:

	// Virtual override functions
	virtual void BeginPlay() override;

	// Virtual functions
	virtual void Init_PostSpawnSignatureArray();
	virtual bool Trace_Ray(const FVector& RayEndPos_p);
	virtual bool Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p);
	

	// ----- Normal methods ----- //
	// 

	// Main Initialize function
	void Init_Main();
	// Initialize the variables which have not yet been initialized in the Constructor
	void Init_Variables();

	void Rotate_SizeFourArray(int32* Array_p);

protected:

	// Storage structs
	FStoringPath PathStoring;
	FStoringName NameStoring;

	// Components
	UStaticMeshComponent* SMC_AreaCube = nullptr;

	// Sockets
	const UStaticMeshSocket* SMSK_AreaCube_Face_01_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_02_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_03_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_04_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_05_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_06_Out = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_01_In = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_02_In = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_03_In = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_04_In = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_05_In = nullptr;
	const UStaticMeshSocket* SMSK_AreaCube_Face_06_In = nullptr;

	// SignatureArray
	int32 PostSpawn_SignArr[6] = { 0, 0, 0, 0, 0, 0 }; // 0 = not hit, 1 = hit

	// Keeps track of how many faces have an obstacle detected by the Trace_Ray()
	int32 FaceObstacleCount;
};
