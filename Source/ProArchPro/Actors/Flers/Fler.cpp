#include "Fler.h"

DEFINE_LOG_CATEGORY(LogClass_Fler);

AFler::AFler()
{
	PrimaryActorTick.bCanEverTick = false;

	m_GrowthStages = 10;
	m_CurrentGrowthStage = 0;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Coer      (*(m_PathStoring.SM_Fler_Epin_Coer_PF      ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Ecors     (*(m_PathStoring.SM_Fler_Epin_Ecors_PF     ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Jamb      (*(m_PathStoring.SM_Fler_Epin_Jamb_PF      ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Baz       (*(m_PathStoring.SM_Fler_Epin_Baz_PF       ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Por       (*(m_PathStoring.SM_Fler_Epin_Por_PF       ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Ano       (*(m_PathStoring.SM_Fler_Epin_Ano_PF       ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Lien      (*(m_PathStoring.SM_Fler_Epin_Lien_PF      ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_PetitPetal(*(m_PathStoring.SM_Fler_Epin_PetitPetal_PF));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_GrandPetal(*(m_PathStoring.SM_Fler_Epin_GrandPetal_PF));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Ovair     (*(m_PathStoring.SM_Fler_Epin_Ovair_PF     ));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> OF_SM_Etamin    (*(m_PathStoring.SM_Fler_Epin_Etamin_PF    ));

	check(OF_SM_Coer      .Succeeded());
	check(OF_SM_Ecors     .Succeeded());
	check(OF_SM_Jamb      .Succeeded());
	check(OF_SM_Baz       .Succeeded());
	check(OF_SM_Por       .Succeeded());
	check(OF_SM_Ano       .Succeeded());
	check(OF_SM_Lien      .Succeeded());
	check(OF_SM_PetitPetal.Succeeded());
	check(OF_SM_GrandPetal.Succeeded());
	check(OF_SM_Ovair     .Succeeded());
	check(OF_SM_Etamin    .Succeeded());

	m_SMC_Coer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Coer"));
	SetRootComponent(m_SMC_Coer);
	m_SMC_Coer->SetStaticMesh(OF_SM_Coer.Object);

	m_SMC_Ecors = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Ecors"));
	m_SMC_Ecors->SetupAttachment(RootComponent);

	m_SMC_Jamb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Jamb"));
	m_SMC_Jamb->SetupAttachment(RootComponent);

	m_SMC_Baz = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Baz"));
	m_SMC_Baz->SetupAttachment(RootComponent);

	m_SMC_Por = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Por"));
	m_SMC_Por->SetupAttachment(RootComponent);

	m_SMC_Ano = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Ano"));
	m_SMC_Ano->SetupAttachment(RootComponent);

	m_SMC_Lien = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Lien"));
	m_SMC_Lien->SetupAttachment(RootComponent);

	m_SMC_PetitPetal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_PetitPetal"));
	m_SMC_PetitPetal->SetupAttachment(RootComponent);

	m_SMC_GrandPetal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_GrandPetal"));
	m_SMC_GrandPetal->SetupAttachment(RootComponent);

	m_SMC_Ovair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Ovair"));
	m_SMC_Ovair->SetupAttachment(RootComponent);

	m_SMC_Etamin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_Etamin"));
	m_SMC_Etamin->SetupAttachment(RootComponent);

	// *** //

	m_SM_Ecors      = OF_SM_Ecors     .Object;
	m_SM_Jamb       = OF_SM_Jamb      .Object;
	m_SM_Baz        = OF_SM_Baz       .Object;
	m_SM_Por        = OF_SM_Por       .Object;
	m_SM_Ano        = OF_SM_Ano       .Object;
	m_SM_Lien       = OF_SM_Lien      .Object;
	m_SM_PetitPetal = OF_SM_PetitPetal.Object;
	m_SM_GrandPetal = OF_SM_GrandPetal.Object;
	m_SM_Ovair      = OF_SM_Ovair     .Object;
	m_SM_Etamin     = OF_SM_Etamin    .Object;
}

void AFler::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentGrowthStage = FMath::RandRange(0, m_GrowthStages);
	UE_LOG(LogClass_Fler, Warning, TEXT("=> %s <= CurrentGrowthStage is : %d"), *GetName(), m_CurrentGrowthStage);

	if (m_CurrentGrowthStage == 1)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
	}

	if (m_CurrentGrowthStage == 2)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
	}

	if (m_CurrentGrowthStage == 3)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
	}

	if (m_CurrentGrowthStage == 4)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
	}

	if (m_CurrentGrowthStage == 5)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
	}

	if (m_CurrentGrowthStage == 6)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
		m_SMC_Lien->SetStaticMesh(m_SM_Lien);
	}

	if (m_CurrentGrowthStage == 7)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
		m_SMC_Lien->SetStaticMesh(m_SM_Lien);
		m_SMC_PetitPetal->SetStaticMesh(m_SM_PetitPetal);
	}

	if (m_CurrentGrowthStage == 8)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
		m_SMC_Lien->SetStaticMesh(m_SM_Lien);
		m_SMC_PetitPetal->SetStaticMesh(m_SM_PetitPetal);
		m_SMC_GrandPetal->SetStaticMesh(m_SM_GrandPetal);
	}

	if (m_CurrentGrowthStage == 9)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
		m_SMC_Lien->SetStaticMesh(m_SM_Lien);
		m_SMC_PetitPetal->SetStaticMesh(m_SM_PetitPetal);
		m_SMC_GrandPetal->SetStaticMesh(m_SM_GrandPetal);
		m_SMC_Ovair->SetStaticMesh(m_SM_Ovair);
	}

	if (m_CurrentGrowthStage == 10)
	{
		m_SMC_Ecors->SetStaticMesh(m_SM_Ecors);
		m_SMC_Jamb->SetStaticMesh(m_SM_Jamb);
		m_SMC_Baz->SetStaticMesh(m_SM_Baz);
		m_SMC_Por->SetStaticMesh(m_SM_Por);
		m_SMC_Ano->SetStaticMesh(m_SM_Ano);
		m_SMC_Lien->SetStaticMesh(m_SM_Lien);
		m_SMC_PetitPetal->SetStaticMesh(m_SM_PetitPetal);
		m_SMC_GrandPetal->SetStaticMesh(m_SM_GrandPetal);
		m_SMC_Ovair->SetStaticMesh(m_SM_Ovair);
		m_SMC_Etamin->SetStaticMesh(m_SM_Etamin);
	}
}