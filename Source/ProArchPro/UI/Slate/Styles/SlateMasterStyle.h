#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "SlateMasterStyle.generated.h"

USTRUCT()
struct FSlateMasterStyleStruct : public FSlateWidgetStyle
{
	GENERATED_BODY()

public:

	static const FName TypeName;

	virtual const FName GetTypeName() const override { return TypeName; };
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FSlateMasterStyleStruct& GetDefault();

	// Pattern : TXTS_ + status + _ + font name + _ + font size
	// NB : 'status' examples : Default, Button, DescriptiveText, HelpText, etc
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Regular_Small  ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Regular_Medium ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Regular_Large  ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Bold_Small     ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Bold_Medium    ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Bold_Large     ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Italic_Small   ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Italic_Medium  ;
	UPROPERTY(EditAnywhere, Category = "TextBlock Styles") FTextBlockStyle TXTS_Default_Italic_Large   ;

	// Pattern example : SC_ + status + _ + utility + _ + color
	// NB : 'utility' examples : TextColor, BackgroundColor, BorderColor, etc
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_White  ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Black  ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Red    ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Green  ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Blue   ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Yellow ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Purple ;
	UPROPERTY(EditAnywhere, Category = "Slate Colors") FSlateColor SC_Basic_Cyan   ;

	// Pattern : SB_ + utility + _ + color style + _ + color
	// NB : 'color style' examples : Plain, Gradiant, Multicolor, etc
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Black       ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_White       ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Red         ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Green       ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Blue        ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Yellow      ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Purple      ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Cyan        ;
	UPROPERTY(EditAnywhere, Category = "Slate Brushes") FSlateBrush SB_Background_Plain_Transparent ;

	// Pattern : BS_ + button type + _ + color style + content
	// NB : 'content' examples : Text, Icon, etc
	UPROPERTY(EditAnywhere, Category = "Button Styles") FButtonStyle BS_Base_Transparent_Text;
};

UCLASS()
class USlateMasterStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public : 

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (ShowOnlyInnerProperties))
	FSlateMasterStyleStruct SlateMasterStyleStruct;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&SlateMasterStyleStruct);
	}
	
};
