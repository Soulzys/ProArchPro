#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MasterHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_MasterHUD, Log, All);

class AMasterGameMode;

UCLASS()
class PROARCHPRO_API AMasterHUD : public AHUD
{
	GENERATED_BODY()

public:

	void Run_Testing();

	void Set_Game_InputMode(const FInputModeDataBase& InData_p);
	void Set_MenuMain_Visibility(const EVisibility& Visibility_p);

	// ***** SETTERS ***** //
	void SET_MasterGameMode(AMasterGameMode* MasterGameMode_p);

protected:

	// All the Menu-type widgets
	TSharedPtr<class SMainMenu> MenuMain = nullptr;

protected:

	virtual void BeginPlay() override;
	
private:

	AMasterGameMode* MasterGameMode = nullptr;
};
