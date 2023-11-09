#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MasterGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_MasterGameMode, Log, All);

class ABuilderMaster;
class AMasterHUD;

UCLASS()
class PROARCHPRO_API AMasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMasterGameMode();

	void Run_Testing();

protected:

	virtual void BeginPlay() override;

protected:

	// Debugging variables
	FString ObjectName;

private:
	
	void Init_Main();
	// Spawn the needed actors
	// Namely : 'BuilderMaster'
	void Init_SpawningActors();
	// e.g : MasterHUD
	void Init_References();

private:

	ABuilderMaster* BuilderMaster = nullptr;
	AMasterHUD* MasterHUD = nullptr;
	
};
