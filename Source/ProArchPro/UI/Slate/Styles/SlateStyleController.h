#pragma once

#include "SlateBasics.h"
#include "SlateMasterStyle.h"

class FSlateStyleController
{
public:

	static void Initialize();
	static void Shutdown();
	static FName Get_StyleSetName();
	static const ISlateStyle& GET_StyleSet();
	static const struct FSlateMasterStyleStruct& GET_SlateMasterStyleStruct()
	{
		return FSlateStyleController::GET_StyleSet().GetWidgetStyle<FSlateMasterStyleStruct>("SWS_Master");
	}

private:

	static TSharedPtr<class FSlateStyleSet> SlateStyleController_Instance;
	static TSharedRef<class FSlateStyleSet> Create();
};
