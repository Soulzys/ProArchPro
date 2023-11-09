#pragma once

#include "StoringPath.generated.h"

USTRUCT()
struct FStoringPath
{
	GENERATED_BODY()

public:

	// ----- StaticMesh ----- //
	FString SM_AreaCubeBaseModel_PF = "StaticMesh'/Game/Geometry/SM_AreaCubeBaseModel.SM_AreaCubeBaseModel'";
	FString SM_TestingCube_PF       = "StaticMesh'/Game/Geometry/SM_TestingCube.SM_TestingCube'"            ;
	FString SM_RayDetectionCube_PF  = "StaticMesh'/Game/Geometry/SM_RayDetectionCube.SM_RayDetectionCube'"  ;
	FString SM_FillingAreaTestingRoom_PF = "StaticMesh'/Game/Geometry/Architecture/StartingRoom/SM_StartingRoom_Testing_m01_BoxSection.SM_StartingRoom_Testing_m01_BoxSection'";

	FString SM_Fler_Epin_Coer_PF       = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Coer_LP.SM_Fler_Epin_Coer_LP'";
	FString SM_Fler_Epin_Ecors_PF      = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Coer_LP.SM_Fler_Epin_Coer_LP'";
	FString SM_Fler_Epin_Jamb_PF       = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Jamb_LP.SM_Fler_Epin_Jamb_LP'";
	FString SM_Fler_Epin_Baz_PF        = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Baz_LP.SM_Fler_Epin_Baz_LP'";
	FString SM_Fler_Epin_Por_PF        = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Por_LP.SM_Fler_Epin_Por_LP'";
	FString SM_Fler_Epin_Ano_PF        = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Ano_LP.SM_Fler_Epin_Ano_LP'";
	FString SM_Fler_Epin_Lien_PF       = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Lien_LP.SM_Fler_Epin_Lien_LP'";
	FString SM_Fler_Epin_PetitPetal_PF = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_PetitPetal_LP.SM_Fler_Epin_PetitPetal_LP'";
	FString SM_Fler_Epin_GrandPetal_PF = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_GrandPetal_LP.SM_Fler_Epin_GrandPetal_LP'";
	FString SM_Fler_Epin_Ovair_PF      = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Ovair_LP.SM_Fler_Epin_Ovair_LP'";
	FString SM_Fler_Epin_Etamin_PF     = "StaticMesh'/Game/Geometry/GameAssets/Flers/Epin/SM_Fler_Epin_Etamin_LP.SM_Fler_Epin_Etamin_LP'";

	// ----- MaterialInstance ----- //
	FString MI_SKTC_Blue   = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Blue.MI_SKTC_Blue'"     ;
	FString MI_SKTC_Red    = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Red.MI_SKTC_Red'"       ;
	FString MI_SKTC_Green  = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Green.MI_SKTC_Green'"   ;
	FString MI_SKTC_Cyan   = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Cyan.MI_SKTC_Cyan'"     ;
	FString MI_SKTC_Yellow = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Yellow.MI_SKTC_Yellow'" ;
	FString MI_SKTC_Purple = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Purple.MI_SKTC_Purple'" ;
	FString MI_SKTC_Orange = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Orange.MI_SKTC_Orange'" ;
	FString MI_SKTC_Black  = "MaterialInstanceConstant'/Game/Materials/MI_SKTC_Black.MI_SKTC_Black'"   ;

	// ----- DataTable ----- //
	FString DT_RoomCatalog_PF  = "DataTable'/Game/Data/DataTables/DT_RoomCatalog.DT_RoomCatalog'"   ;
	FString DT_LightCatalog_PF = "DataTable'/Game/Data/DataTables/DT_LightCatalog.DT_LightCatalog'" ;
	FString DT_BoxesCatalog_PF = "DataTable'/Game/Data/DataTables/DT_BoxesCatalog.DT_BoxesCatalog'" ;
};
