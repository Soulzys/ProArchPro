#include "SMainMenu.h"
#include "../../../HUD/MasterHUD.h"
#include "../../Styles/SlateMasterStyle.h"
#include "../../Styles/SlateStyleController.h"
#include "../Basics/SButtonBase.h"
#include "GameFramework/PlayerController.h"

DEFINE_LOG_CATEGORY(LogClass_SMainMenu);

#define LOCTEXT_NAMESPACE "MainMenu"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMainMenu::Construct(const FArguments& InArgs_p)
{
	const FSlateMasterStyleStruct& _MasterStyle = FSlateStyleController::GET_SlateMasterStyleStruct();

	this->OwningHUD = InArgs_p._OwningHUD;

	ChildSlot
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		.BorderImage(&_MasterStyle.SB_Background_Plain_Black)
		[
			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(65.0f, 0.0f, 0.0f, 0.0f))
			.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
			[
				SNew(SVerticalBox)
			
				// Space Top
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(225.0f)
					[
						SNew(SBorder)
						.BorderImage(&_MasterStyle.SB_Background_Plain_Transparent)
					]
				]

				// Menu_01
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
					[
						SNew(SButtonBase)
						.ARGM_Width(200.0f)
						.ARGM_Height(65.0f)
						.SATTR_ButtonStyle(&_MasterStyle.BS_Base_Transparent_Text)
						.SATTR_TextStyle(&_MasterStyle.TXTS_Default_Bold_Medium)
						.ATTR_Text(LOCTEXT("Menu_Testing", "TESTING"))
						.ATTR_TextColor(_MasterStyle.SC_Basic_White)
						.ATTR_TextColorHovered(_MasterStyle.SC_Basic_Black)
						.EVENT_OnButtonClicked(this, &SMainMenu::ON_ButtonTesting_Clicked)
					]
				]
				
				// Space Menu_01 || Menu_02
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(100.0f)
					[
						SNew(SBorder)
						.BorderImage(&_MasterStyle.SB_Background_Plain_Transparent)
					]
				]

				// Menu_02
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
					[
						SNew(SButtonBase)
						.ARGM_Width(200.0f)
						.ARGM_Height(65.0f)
						.SATTR_ButtonStyle(&_MasterStyle.BS_Base_Transparent_Text)
						.SATTR_TextStyle(&_MasterStyle.TXTS_Default_Bold_Medium)
						.ATTR_Text(LOCTEXT("Menu_Parameters", "PARAMETERS"))
						.ATTR_TextColor(_MasterStyle.SC_Basic_White)
						.ATTR_TextColorHovered(_MasterStyle.SC_Basic_Black)
						.EVENT_OnButtonClicked(this, &SMainMenu::ON_ButtonTesting_Clicked)
					]
				]

				// Space Menu_02 || Menu_03
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(100.0f)
					[
						SNew(SBorder)
						.BorderImage(&_MasterStyle.SB_Background_Plain_Transparent)
					]
				]

				// Menu_03
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
					[
						SNew(SButtonBase)
						.ARGM_Width(200.0f)
						.ARGM_Height(65.0f)
						.SATTR_ButtonStyle(&_MasterStyle.BS_Base_Transparent_Text)
						.SATTR_TextStyle(&_MasterStyle.TXTS_Default_Bold_Medium)
						.ATTR_Text(LOCTEXT("Menu_Quitting", "QUIT"))
						.ATTR_TextColor(_MasterStyle.SC_Basic_White)
						.ATTR_TextColorHovered(_MasterStyle.SC_Basic_Black)
						.EVENT_OnButtonClicked(this, &SMainMenu::ON_ButtonQuitting_Clicked)
					]
				]
			]			
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMainMenu::ON_ButtonTesting_Clicked()
{
	UE_LOG(LogClass_SMainMenu, Warning, TEXT("Button Menu_Testing clicked !"));

	this->OwningHUD->Set_MenuMain_Visibility(EVisibility::Collapsed);
	this->OwningHUD->Set_Game_InputMode(FInputModeGameAndUI());
	this->OwningHUD->Run_Testing();
}

void SMainMenu::ON_ButtonParameters_Clicked()
{
	UE_LOG(LogClass_SMainMenu, Warning, TEXT("Button Menu_Parameters clicked !"));
}

void SMainMenu::ON_ButtonQuitting_Clicked()
{
	UE_LOG(LogClass_SMainMenu, Warning, TEXT("Button Menu_Quitting clicked !"));

	APlayerController* PC = this->OwningHUD->PlayerOwner ;
	check(PC)                                            ;
	PC->ConsoleCommand("quit")                           ; // Closing the currently running game
}

#undef LOCTEXT_NAMESPACE