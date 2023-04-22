#include "SlateStyleController.h"
#include "Slate/SlateGameResources.h"

TSharedPtr<FSlateStyleSet> FSlateStyleController::SlateStyleController_Instance = nullptr;

void FSlateStyleController::Initialize()
{
	if (!SlateStyleController_Instance.IsValid())
	{
		SlateStyleController_Instance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*SlateStyleController_Instance);
	}
}

void FSlateStyleController::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlateStyleController_Instance);
	ensure(SlateStyleController_Instance.IsUnique());
	SlateStyleController_Instance.Reset();
}

FName FSlateStyleController::Get_StyleSetName()
{
	static FName _StyleSetName(TEXT("SlateStyleController"));
	return _StyleSetName;
}

const ISlateStyle& FSlateStyleController::GET_StyleSet()
{
	return *SlateStyleController_Instance;
}

TSharedRef<class FSlateStyleSet> FSlateStyleController::Create()
{
	TSharedRef<FSlateStyleSet> _StyleRef = FSlateGameResources::New
		(FSlateStyleController::Get_StyleSetName(), "/Game/Data/Slate/Styles", "/Game/Data/Slate/Styles");

	return _StyleRef;
}