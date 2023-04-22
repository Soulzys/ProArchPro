#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpectatorBase.generated.h"

// This class is basically a c/p version of the DefaultPawn class

DECLARE_LOG_CATEGORY_EXTERN(LogClass_SpectatorBase, Log, All);

class USphereComponent;
class UPawnMovementComponent;

UCLASS()
class PROARCHPRO_API ASpectatorBase : public APawn
{
	GENERATED_BODY()

public:

	ASpectatorBase();

protected:

	UPROPERTY(EditAnywhere, Category = "Spectator Pawn")
	USphereComponent* SSC_Collision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spectator Pawn")
	UPawnMovementComponent* PMC_Movement = nullptr;

	// Movement variables
	float BaseTurnRate;
	float BaseLookUpRate;

protected:

	// Movement functions
	virtual void MoveForward(float Value_p);
	virtual void MoveRight(float Value_p);
	virtual void MoveUp_World(float Value_p);
	virtual void TurnAtRate(float Rate_p);
	virtual void LookUpAtRate(float Rate_p);

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void Init_InputBindings();
};
