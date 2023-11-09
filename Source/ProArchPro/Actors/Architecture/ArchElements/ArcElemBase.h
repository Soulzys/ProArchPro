#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Storage/StoringPath.h"
#include "../../../Storage/StoringName.h"
#include "ArcElemBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROARCHPRO_API AArcElemBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AArcElemBase();

	void Set_MainStaticMesh(UStaticMesh* StaticMesh_p);

protected:

	virtual void BeginPlay() override;

protected:

	FStoringPath PathStoring;
	FStoringName NameStoring;

	UStaticMeshComponent* SMC_Main = nullptr;
};
