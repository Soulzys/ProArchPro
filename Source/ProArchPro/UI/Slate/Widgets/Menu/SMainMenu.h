#pragma once

#include "SlateBasics.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_SMainMenu, Log, All);

class AMasterHUD;

class SMainMenu : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenu) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AMasterHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs_p);

private:

	// Slate data
	TWeakObjectPtr<AMasterHUD> OwningHUD;

private:

	void ON_ButtonTesting_Clicked();
	void ON_ButtonParameters_Clicked();
	void ON_ButtonQuitting_Clicked();

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
