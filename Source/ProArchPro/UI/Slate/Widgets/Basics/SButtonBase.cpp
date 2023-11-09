#include "SButtonBase.h"
#include "../../Styles/SlateMasterStyle.h"
#include "../../Styles/SlateStyleController.h"

#define LOCTEXT_NAMESPACE "ButtonBase"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SButtonBase::Construct(const FArguments& InArgs_p)
{
	const FSlateMasterStyleStruct& _MasterStyle = FSlateStyleController::GET_SlateMasterStyleStruct();

	this->ARGM_Width            =  InArgs_p._ARGM_Width            ;
	this->ARGM_Height           =  InArgs_p._ARGM_Height           ;
	this->SATTR_ButtonStyle     = *InArgs_p._SATTR_ButtonStyle     ;
	this->SATTR_TextStyle       = *InArgs_p._SATTR_TextStyle       ;
	this->ATTR_Text             =  InArgs_p._ATTR_Text             ;
	this->ATTR_TextColor        =  InArgs_p._ATTR_TextColor        ;
	this->ATTR_TextColorHovered =  InArgs_p._ATTR_TextColorHovered ;
	this->EVENT_OnButtonClicked =  InArgs_p._EVENT_OnButtonClicked ;

	ChildSlot
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		// Main container
		SNew(SBox)
		.WidthOverride(this->ARGM_Width)
		.HeightOverride(this->ARGM_Height)
		[
			// Button || Behavior only, no display
			SNew(SButton)
			.OnClicked(this, &SButtonBase::ON_ButtonClicked_INTERNAL)
			.ContentPadding(FMargin(0))
			.ButtonStyle(&this->SATTR_ButtonStyle)
			[
				// Background
				SNew(SBorder)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0))
				.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
				[
					SAssignNew(ISW_TextBlock, STextBlock)
					.Text(this->ATTR_Text)
					.TextStyle(&this->SATTR_TextStyle)
					.ColorAndOpacity(this->ATTR_TextColor)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SButtonBase::OnMouseEnter(const FGeometry& MyGeo_p, const FPointerEvent& MouseEvent_p)
{
	SetCursor(EMouseCursor::Hand);
	this->ISW_TextBlock->SetColorAndOpacity(this->ATTR_TextColorHovered);
}

void SButtonBase::OnMouseLeave(const FPointerEvent& MouseEvent_p)
{
	SetCursor(EMouseCursor::Default);
	this->ISW_TextBlock->SetColorAndOpacity(this->ATTR_TextColor);
}

FReply SButtonBase::ON_ButtonClicked_INTERNAL()
{
	check(this->EVENT_OnButtonClicked.IsBound());

	this->EVENT_OnButtonClicked.Execute();

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE