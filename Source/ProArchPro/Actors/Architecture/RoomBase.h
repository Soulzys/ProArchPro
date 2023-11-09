#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "../../Storage/StoringPath.h"
#include "RoomBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_RoomBase, Log, All);

class UStaticMeshComponent ;
class UDataTable           ;
class UStaticMesh          ;

UENUM()
enum class EVolumeLayer : uint8
{
	EVLT_USABLE       = 0 UMETA(DisplayName = "Usable Layer"), 
	EVLT_ARCHITECTURE = 1 UMETA(DisplayName = "Architecture Layer")
};

USTRUCT()
struct FRoomCatalog_DT : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "StaticMesh"))
	UStaticMesh* S_StaticMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketsVolumeArray"))
	TArray<uint8> S_SocketsVolumeArray;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "VolumeLayerEnum"))
	TArray<EVolumeLayer> S_VolumeLayerEnum;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MeshDescription"))
	FString S_MeshDescription;
};

UCLASS()
class PROARCHPRO_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ARoomBase();
	void Init_Main();

	// Getters
	UStaticMesh* GET_StaticMesh();
	TArray<AActor*> GET_ActorsMainArray();

protected:

	virtual void BeginPlay() override;
	void Init_DataTable(); // Get a random table row
	void Init_DataTable(int32 RowIndex_p);
	void Init_Geometry();

protected:

	// Storage structs
	FStoringPath PathStoring;

	// Geometry components
	UStaticMeshComponent* SMC_RoomMain = nullptr;

	// DataTable related
	UDataTable*      DT_RoomCatalog     = nullptr; // Our complete DataTable
	FRoomCatalog_DT* DT_RoomCatalog_Row = nullptr; // Our specific DataTable row
	UStaticMesh*     SM_Room            = nullptr; // Our specific DataTable row StaticMesh

	// Referencing all the actors within the Room
	TArray<AActor*> ActorsMain_Array;

	// Debugging variables
	FString ObjectName;
};
