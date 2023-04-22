#include "BuilderBase.h"
#include "../AreaCubeFiller.h"
#include "../ArchElementPattern.h"


DEFINE_LOG_CATEGORY(LogClass_BuilderBase);

ABuilderBase::ABuilderBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ----- Variable initialization ----- //
	this->ObjectName = GetName();

	// ----- Loading data ----- //
	// Constructor
	const ConstructorHelpers::FObjectFinder<UDataTable> OF_DT_LightCatalog(*(this->PathStoring.DT_LightCatalog_PF));
	const ConstructorHelpers::FObjectFinder<UDataTable> OF_DT_BoxesCatalog(*(this->PathStoring.DT_BoxesCatalog_PF));

	// Checking
	check(OF_DT_LightCatalog.Succeeded());
	check(OF_DT_BoxesCatalog.Succeeded());

	// Initializing
	this->DT_LightCatalog = OF_DT_LightCatalog.Object;
	this->DT_BoxesCatalog = OF_DT_BoxesCatalog.Object;
}

void ABuilderBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilderBase::Get_FromBoxesCatalogDT(int32 RowIndex_p)
{
	check(this->DT_BoxesCatalog);

	FString _ContextString = "ContextString";
	TArray<FBoxesCatalog_DT*> _RowArray;

	this->DT_BoxesCatalog->GetAllRows(_ContextString, _RowArray);

	if (RowIndex_p <= _RowArray.Num())
	{
		this->DT_BoxesCatalogRow = _RowArray[RowIndex_p];
		check(this->DT_BoxesCatalogRow);
	}
	else
	{
		return;
	}

	this->Boxes_StaticMesh       = this->DT_BoxesCatalogRow->S_StaticMesh           ;
	this->Boxes_BlueprintPattern = this->DT_BoxesCatalogRow->S_MeshBlueprintPattern ;
	check(this->Boxes_StaticMesh)       ;
	check(this->Boxes_BlueprintPattern) ;
}

void ABuilderBase::Get_FromLightCatalogDT(int32 RowIndex_p)
{
	check(this->DT_LightCatalog);

	FString _ContextString = "ContextString";
	TArray<FLightCatalog_DT*> _RowArray;

	// Initializing _RowArray
	this->DT_LightCatalog->GetAllRows(_ContextString, _RowArray);

	if (RowIndex_p <= _RowArray.Num())
	{
		this->DT_LightCatalogRow = _RowArray[RowIndex_p];
		check(this->DT_LightCatalogRow);
		UE_LOG(LogClass_BuilderBase, Log, TEXT("=> %s <= 'DT_LightCatalogRow' was loaded with DT_LightCatalog[%d]"), *this->ObjectName, RowIndex_p);
	}
	else
	{
		UE_LOG(LogClass_BuilderBase, Warning, TEXT("Index out of bounds : DT_LightCatalog[%d] does not seem to exist"), RowIndex_p);
		return;
	}

	// Initializing DataTable variables
	this->Light_StaticMesh       = this->DT_LightCatalogRow->S_StaticMesh           ;
	this->Light_BlueprintPattern = this->DT_LightCatalogRow->S_MeshBlueprintPattern ;

	check(this->Light_StaticMesh      );
	check(this->Light_BlueprintPattern);

	UE_LOG(LogClass_BuilderBase, Log, TEXT("=> %s <= has initialized 'Light_StaticMesh' and 'Light_BlueprintPattern'"), *this->ObjectName);
}

bool ABuilderBase::DoFourDigitsArrayMatch(int32* FirstArray_p, int32* SecondArray_p)
{
	if (FirstArray_p[0] == SecondArray_p[0])
	{
		if (FirstArray_p[1] == SecondArray_p[1])
		{
			if (FirstArray_p[2] == SecondArray_p[2])
			{
				if (FirstArray_p[3] == SecondArray_p[3])
				{
					// The array are matching
					return true;
				}
			}
		}
	}

	// The array are not matching
	return false;
}

void ABuilderBase::RotateSizeFourArray(int32* Array_p)
{
	int32 _Index_0 = Array_p[0]; // 1
	int32 _Index_1 = Array_p[1]; // 0
	int32 _Index_2 = Array_p[2]; // 0
	int32 _Index_3 = Array_p[3]; // 1

	Array_p[0] = _Index_3; // 1
	Array_p[1] = _Index_0; // 1
	Array_p[2] = _Index_1; // 0
	Array_p[3] = _Index_2; // 0 
}

void ABuilderBase::DEBUG_DisplayArraySixSlots(int32* Array_p)
{
	UE_LOG(LogClass_BuilderBase, Log, TEXT("{ %d, %d, %d, %d, %d, %d }"), Array_p[0], Array_p[1], Array_p[2], Array_p[3], Array_p[4], Array_p[5]);
}

void ABuilderBase::DEBUG_DisplayArraySixSlots(FString DebugText_p, int32* Array_p)
{
	UE_LOG(LogClass_BuilderBase, Log, TEXT("%s { %d, %d, %d, %d, %d, %d }"), *DebugText_p, Array_p[0], Array_p[1], Array_p[2], Array_p[3], Array_p[4], Array_p[5]);
}

void ABuilderBase::DEBUG_DisplayArrayFourSlots(int32* Array_p)
{
	UE_LOG(LogClass_BuilderBase, Log, TEXT("{ %d, %d, %d, %d }"), Array_p[0], Array_p[1], Array_p[2], Array_p[3]);
}

void ABuilderBase::DEBUG_DisplayArrayFourSlots(FString DebugText_p, int32* Array_p)
{
	UE_LOG(LogClass_BuilderBase, Log, TEXT("%s { %d, %d, %d, %d }"), *DebugText_p, Array_p[0], Array_p[1], Array_p[2], Array_p[3]);
}

void ABuilderBase::DEBUG_DisplayArrayElementsNames(TArray<AActor*> Array_p)
{
	for (int32 i = 0; i < Array_p.Num(); i++)
	{
		UE_LOG(LogClass_BuilderBase, Log, TEXT("Array[%d] : => %s <="), i, *Array_p[i]->GetName());
	}
}

void ABuilderBase::DEBUG_DisplayArrayElementsNames(TArray<AAreaCubeFiller*> Array_p)
{
	if (Array_p.Num() == 0)
	{
		UE_LOG(LogClass_BuilderBase, Log, TEXT("This array is empty !"));
	}
	else
	{
		for (int32 i = 0; i < Array_p.Num(); i++)
		{
			UE_LOG(LogClass_BuilderBase, Log, TEXT("Array[%d] : => %s <="), i, *Array_p[i]->GetName());
		}
	}	
}

void ABuilderBase::DEBUG_DisplayArrayElementsNames(const FString& ArrayName_p, TArray<AAreaCubeFiller*> Array_p)
{
	if (Array_p.Num() == 0)
	{
		UE_LOG(LogClass_BuilderBase, Log, TEXT("%s is empty !"), *ArrayName_p);
	}
	else
	{
		for (int32 i = 0; i < Array_p.Num(); i++)
		{
			UE_LOG(LogClass_BuilderBase, Log, TEXT("%s[%d] : => %s <="), *ArrayName_p, i, *Array_p[i]->GetName());
		}
	}
}

void ABuilderBase::DEBUG_DisplayArrayElementsNames(TArray<AArchElementPattern*> Array_p)
{
	for (int32 i = 0; i < Array_p.Num(); i++)
	{
		UE_LOG(LogClass_BuilderBase, Log, TEXT("Array[%d] : => %s <="), i, *Array_p[i]->GetName());
	}
}

void ABuilderBase::DEBUG_DisplayArrayElementsNames(const FString& ArrayName_p, TArray<AArchElementPattern*> Array_p)
{
	if (Array_p.Num() == 0)
	{
		UE_LOG(LogClass_BuilderBase, Log, TEXT("%s is empty !"), *ArrayName_p);
	}
	else
	{
		for (int32 i = 0; i < Array_p.Num(); i++)
		{
			UE_LOG(LogClass_BuilderBase, Log, TEXT("%s[%d] : => %s <="), *ArrayName_p, i, *Array_p[i]->GetName());
		}
	}
}