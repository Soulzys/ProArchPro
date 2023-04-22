#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "../../Storage/StoringPath.h"
#include "BuilderBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_BuilderBase, Log, All);

class AAreaCubeFiller;
class AArchElementPattern;

USTRUCT()
struct FLightCatalog_DT : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "StaticMesh"))
	UStaticMesh* S_StaticMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MeshBlueprintPattern"))
	UClass* S_MeshBlueprintPattern;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MeshDescription"))
	FString S_MeshDescription;
};

USTRUCT()
struct FBoxesCatalog_DT : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "StaticMesh"))
	UStaticMesh* S_StaticMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MeshBlueprintPattern"))
	UClass* S_MeshBlueprintPattern;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MeshDescription"))
	FString S_MeshDescription;
};

USTRUCT()
struct FBuilderController
{
	GENERATED_BODY()

public:

	int16        S_ElementNumberToSpawn ;
	UStaticMesh* S_StaticMesh           ;
	UClass*      S_MeshBlueprintPattern ;
};

UCLASS()
class PROARCHPRO_API ABuilderBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuilderBase();

	// ----- Tools functions ----- //
	// Returns true if both arrays are matching, false if not
	bool DoFourDigitsArrayMatch(int32* FirstArray_p, int32* SecondArray_p);
	// "Rotates" a AreaCube SignatureArray (first four slots)
	void RotateSizeFourArray(int32* Array_p);
	
	// ----- Debug functions ----- //
	void DEBUG_DisplayArraySixSlots(int32* Array_p);
	void DEBUG_DisplayArraySixSlots(FString DebugText_p, int32* Array_p);
	void DEBUG_DisplayArrayFourSlots(int32* Array_p);
	void DEBUG_DisplayArrayFourSlots(FString DebugText_p, int32* Array_p);
	void DEBUG_DisplayArrayElementsNames(TArray<AActor*> Array_p);
	void DEBUG_DisplayArrayElementsNames(TArray<AAreaCubeFiller*> Array_p);
	void DEBUG_DisplayArrayElementsNames(const FString& ArrayName_p, TArray<AAreaCubeFiller*> Array_p);
	void DEBUG_DisplayArrayElementsNames(TArray<AArchElementPattern*> Array_p);
	void DEBUG_DisplayArrayElementsNames(const FString& ArrayName_p, TArray<AArchElementPattern*> Array_p);

protected:

	virtual void BeginPlay() override;
	void Get_FromLightCatalogDT(int32 RowIndex_p);
	void Get_FromBoxesCatalogDT(int32 RowIndex_p);

protected:

	// Storage structs
	FStoringPath PathStoring;

	// ----- DataTable related ----- //
	// FLightCatalog_DT
	UDataTable*       DT_LightCatalog    = nullptr;
	FLightCatalog_DT* DT_LightCatalogRow = nullptr;
	// FBoxesCatalog_DT
	UDataTable*       DT_BoxesCatalog    = nullptr;
	FBoxesCatalog_DT* DT_BoxesCatalogRow = nullptr;
	
	// ---- DataTable variables ----- //
	// FLightCatalog_DT
	UStaticMesh* Light_StaticMesh       = nullptr;
	UClass*      Light_BlueprintPattern = nullptr;
	// FBoxesCatalog_DT
	UStaticMesh* Boxes_StaticMesh       = nullptr;
	UClass*      Boxes_BlueprintPattern = nullptr;

	// Debugging variable
	FString ObjectName;

};
