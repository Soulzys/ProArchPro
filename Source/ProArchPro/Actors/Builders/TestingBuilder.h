#pragma once

#include "CoreMinimal.h"
#include "RoomBuilder.h"
#include "TestingBuilder.generated.h"

UCLASS()
class PROARCHPRO_API ATestingBuilder : public ARoomBuilder
{
	GENERATED_BODY()
	
public:

	ATestingBuilder();

protected:

	virtual void BeginPlay() override;

private:

	UStaticMeshComponent* SMC_MainTesting = nullptr;
	UStaticMesh* SM_MainTestingRoom = nullptr;

};
