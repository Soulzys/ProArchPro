#include "SpectatorBase.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

DEFINE_LOG_CATEGORY(LogClass_SpectatorBase);

ASpectatorBase::ASpectatorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	this->SSC_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SSC_Collision"));
	this->SSC_Collision->InitSphereRadius(35.0f);
	this->SSC_Collision->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	this->SSC_Collision->CanCharacterStepUpOn = ECB_No;
	this->SSC_Collision->SetShouldUpdatePhysicsVolume(true);
	this->SSC_Collision->SetCanEverAffectNavigation(false);
	this->SSC_Collision->bDynamicObstacle = true;

	RootComponent = this->SSC_Collision;

	this->PMC_Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("PMC_Movement"));

	this->BaseTurnRate = 45.0f;
	this->BaseLookUpRate = 45.0f;
}

void ASpectatorBase::Init_InputBindings()
{
	static bool _bAreBindingsAdded = false;

	if (!_bAreBindingsAdded)
	{
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_MoveForward", EKeys::W, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_MoveForward", EKeys::S, -1.0f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_MoveRight", EKeys::A, -1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_MoveRight", EKeys::D, 1.0f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_TurnRate", EKeys::Left, -1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_TurnRate", EKeys::Right, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_Turn", EKeys::MouseX, 1.0f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_LookUpRate", EKeys::Gamepad_RightY, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("SpectatorBase_LookUp", EKeys::MouseY, -1.0f));

		UE_LOG(LogClass_SpectatorBase, Log, TEXT("New bindings added !"));

		_bAreBindingsAdded = true;
	}
}

void ASpectatorBase::BeginPlay()
{
	Super::BeginPlay();	
}

void ASpectatorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// My own personal bindings
	this->Init_InputBindings();

	PlayerInputComponent->BindAxis("SpectatorBase_MoveForward", this, &ASpectatorBase::MoveForward            );
	PlayerInputComponent->BindAxis("SpectatorBase_MoveRight"  , this, &ASpectatorBase::MoveRight              );
	PlayerInputComponent->BindAxis("SpectatorBase_MoveUp"     , this, &ASpectatorBase::MoveUp_World           );
	PlayerInputComponent->BindAxis("SpectatorBase_Turn"       , this, &ASpectatorBase::AddControllerYawInput  );
	PlayerInputComponent->BindAxis("SpectatorBase_TurnRate"   , this, &ASpectatorBase::TurnAtRate             );
	PlayerInputComponent->BindAxis("SpectatorBase_LookUp"     , this, &ASpectatorBase::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("SpectatorBase_LookUpRate" , this, &ASpectatorBase::LookUpAtRate           );
}

void ASpectatorBase::MoveForward(float Value_p)
{
	if (Value_p != 0.0f)
	{
		if (Controller)
		{
			FRotator const _ControlSpaceRot = Controller->GetControlRotation();

			// Transforms to world space and adds it
			AddMovementInput(FRotationMatrix(_ControlSpaceRot).GetScaledAxis(EAxis::X), Value_p);
			
			//UE_LOG(LogClass_SpectatorBase, Log, TEXT("Vrrrrooooooooouuumm..."));
		}
	}
}

void ASpectatorBase::MoveRight(float Value_p)
{
	if (Value_p != 0.0f)
	{
		if (Controller)
		{
			FRotator const _ControlSpaceRot = Controller->GetControlRotation();

			// Transforms to world space and adds it
			AddMovementInput(FRotationMatrix(_ControlSpaceRot).GetScaledAxis(EAxis::Y), Value_p);
		}
	}
}

void ASpectatorBase::MoveUp_World(float Value_p)
{
	if (Value_p != 0.0f)
	{
		AddMovementInput(FVector::UpVector, Value_p);
	}
}

void ASpectatorBase::TurnAtRate(float Rate_p)
{
	// Calculates delta for this frame from the rate information
	AddControllerYawInput(Rate_p * this->BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ASpectatorBase::LookUpAtRate(float Rate_p)
{
	// Same as above
	AddControllerPitchInput(Rate_p * this->BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}