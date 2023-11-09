#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchElementPattern.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_ArchElementPattern, Log, All);

UCLASS()
class PROARCHPRO_API AArchElementPattern : public AActor
{
	GENERATED_BODY()
	
public:	

	AArchElementPattern();

	void Rotate_EveryChildPostSpawnSignArr();
	bool Compare_EveryChildPreSpawnPostSpawnSignArr();


	// Setters
	void SET_bIsObstructed(bool Value_p);

	// Debug functions
	void DEBUG_DisplayEveryChildPreSpawnSignArr();
	void DEBUG_DisplayEveryChildPostSpawnSignArr();

protected:

	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent_p) override;

private:

	// Initialize the class variables such as 'bIsObstructed'
	void Init_Variables();

protected:

	bool bIsObstructed;

};
