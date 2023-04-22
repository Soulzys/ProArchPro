#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ProceduralActorBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_ProceduralActorBase, Log, All);

class UStaticMesh;

USTRUCT()
struct FProceduralMeshBase_DT : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Index"))
	int32 S_Index;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "StaticMesh"))
	UStaticMesh* S_StaticMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh Name"))
	FName S_MeshName;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh Description"))
	FString S_MeshDescription;

};

UCLASS()
class PROARCHPRO_API AProceduralActorBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AProceduralActorBase();

protected:

	virtual void BeginPlay() override;

};
