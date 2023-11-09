#include "SlateMasterStyle.h"

const FName FSlateMasterStyleStruct::TypeName = TEXT("FSlateMasterStyleStruct");

void FSlateMasterStyleStruct::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&SB_Background_Plain_Black)       ;
	OutBrushes.Add(&SB_Background_Plain_White)       ;
	OutBrushes.Add(&SB_Background_Plain_Red)         ;
	OutBrushes.Add(&SB_Background_Plain_Green)       ;
	OutBrushes.Add(&SB_Background_Plain_Blue)        ;
	OutBrushes.Add(&SB_Background_Plain_Yellow)      ;
	OutBrushes.Add(&SB_Background_Plain_Purple)      ;
	OutBrushes.Add(&SB_Background_Plain_Cyan)        ;
	OutBrushes.Add(&SB_Background_Plain_Transparent) ;
}

const FSlateMasterStyleStruct& FSlateMasterStyleStruct::GetDefault()
{
	static FSlateMasterStyleStruct _DefaultStruct;
	return _DefaultStruct;
}