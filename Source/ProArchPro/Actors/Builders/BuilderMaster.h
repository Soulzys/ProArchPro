#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderMaster.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_BuilderMaster, Log, All);

class ARoomBase;
class ARoomBuilder;

UCLASS()
class PROARCHPRO_API ABuilderMaster : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuilderMaster();

	// This method is supposed to be called by MasterGameMode
	void Init_Main();
	void Build_Main();

protected:

	virtual void BeginPlay() override;
	void Init_SpawnActors();
	void Init_References();

protected:

	// Actors references
	ARoomBase*    RoomBase    = nullptr;
	ARoomBuilder* RoomBuilder = nullptr; // The builder for all 'Room' type Actor

	// Debugging variables
	FString ObjectName;

};
