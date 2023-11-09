#pragma once

#include "SlateBasics.h"

class AMasterHUD;

DECLARE_DELEGATE(FButtonClicked)

class SButtonBase : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SButtonBase) {}
	
	SLATE_ARGUMENT(float, ARGM_Width)
	SLATE_ARGUMENT(float, ARGM_Height)

	SLATE_STYLE_ARGUMENT(FButtonStyle, SATTR_ButtonStyle)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, SATTR_TextStyle)
	
	SLATE_ATTRIBUTE(FText, ATTR_Text)
	SLATE_ATTRIBUTE(FSlateColor, ATTR_TextColor)
	SLATE_ATTRIBUTE(FSlateColor, ATTR_TextColorHovered)

	SLATE_EVENT(FButtonClicked, EVENT_OnButtonClicked)

	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs_p);

	FReply ON_ButtonClicked_INTERNAL();

private:

	// *** Slate data *** //
	// HUD Owner (MasterHUD)
	TWeakObjectPtr<AMasterHUD> OwningHUD;
	// All the internal slate widgets ('ISW' = Internal Slate Widget)
	TSharedPtr<STextBlock> ISW_TextBlock;

	// *** Slate Arguments *** //
	float ARGM_Width  ;
	float ARGM_Height ;

	// *** Slate Style Argument *** //
	FButtonStyle    SATTR_ButtonStyle ;
	FTextBlockStyle SATTR_TextStyle   ;

	// *** Slate Attributes *** // 
	TAttribute<FText>       ATTR_Text      ;
	TAttribute<FSlateColor> ATTR_TextColor ;
	TAttribute<FSlateColor> ATTR_TextColorHovered;


	// Slate Event
	FButtonClicked EVENT_OnButtonClicked;

private:

	// *** Callbacks *** //
	virtual void OnMouseEnter(const FGeometry& MyGeo_p, const FPointerEvent& MouseEvent_p) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent_p) override;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
