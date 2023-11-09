#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Storage/StoringPath.h"
#include "../Storage/StoringName.h"
#include "TestingCube.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_TestingCube, Log, All);

class UStaticMeshComponent;

UCLASS()
class PROARCHPRO_API ATestingCube : public AActor
{
	GENERATED_BODY()
	
public:	

	ATestingCube();

protected:

	virtual void BeginPlay() override;

	bool Trace_Ray(const FVector& RayEndPos_p);
	bool Trace_Ray(const FVector& RayStartPos_p, const FVector& RayEndPos_p);

protected:

	FStoringPath PathStoring;
	FStoringName NameStoring;

	UStaticMeshComponent* SMC_Cube = nullptr;
	UStaticMeshComponent* SMC_InsideCube = nullptr;

	const UStaticMeshSocket* SMSK_TestingCubeSocket = nullptr;
};
