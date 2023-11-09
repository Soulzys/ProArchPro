#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Storage/StoringPath.h"
#include "Fler.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogClass_Fler, Log, All);

class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class PROARCHPRO_API AFler : public AActor
{
	GENERATED_BODY()
	
public:	

	AFler();

protected:

	virtual void BeginPlay() override;

protected:

	FStoringPath m_PathStoring;

	UStaticMeshComponent* m_SMC_Coer       = nullptr;
	UStaticMeshComponent* m_SMC_Ecors      = nullptr;
	UStaticMeshComponent* m_SMC_Jamb       = nullptr;
	UStaticMeshComponent* m_SMC_Baz        = nullptr;
	UStaticMeshComponent* m_SMC_Por        = nullptr;
	UStaticMeshComponent* m_SMC_Ano        = nullptr;
	UStaticMeshComponent* m_SMC_Lien       = nullptr;
	UStaticMeshComponent* m_SMC_PetitPetal = nullptr;
	UStaticMeshComponent* m_SMC_GrandPetal = nullptr;
	UStaticMeshComponent* m_SMC_Ovair      = nullptr;
	UStaticMeshComponent* m_SMC_Etamin     = nullptr;

	UStaticMesh* m_SM_Ecors      = nullptr;
	UStaticMesh* m_SM_Jamb       = nullptr;
	UStaticMesh* m_SM_Baz        = nullptr;
	UStaticMesh* m_SM_Por        = nullptr;
	UStaticMesh* m_SM_Ano        = nullptr;
	UStaticMesh* m_SM_Lien       = nullptr;
	UStaticMesh* m_SM_PetitPetal = nullptr;
	UStaticMesh* m_SM_GrandPetal = nullptr;
	UStaticMesh* m_SM_Ovair      = nullptr;
	UStaticMesh* m_SM_Etamin     = nullptr;

	int8 m_GrowthStages;
	int8 m_CurrentGrowthStage;
};
