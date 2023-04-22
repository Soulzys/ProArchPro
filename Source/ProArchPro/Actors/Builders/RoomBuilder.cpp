#include "RoomBuilder.h"
#include "../Architecture/RoomBase.h"
#include "../AreaCubeFiller.h"
#include "../PatternCube.h"
#include "../ArchElementPattern.h"
#include "../Architecture/ArchElements/ArcElemBase.h"
#include "Engine/StaticMeshSocket.h"

DEFINE_LOG_CATEGORY(LogClass_RoomBuilder);

ARoomBuilder::ARoomBuilder()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initializating variables
	this->ObjectName = GetName();
	this->AreaCubeFillerCount = 0;
}

void ARoomBuilder::BeginPlay()
{
	Super::BeginPlay();	

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("A new ARoomBuilder Actor (%s) has been spawned !"), *this->ObjectName);
}

void ARoomBuilder::Build_Room()
{
	this->Fill_Volume(40, 7);
	this->TESTING_SelectAndRemove();
	this->Spawn_AllActors();
	this->Spawn_ActorInRoom(EDataTable::EDT_BOX, 0, this->BuilderController, 5);

	//this->Fill_Volume(this->SM_AreaFillerTestingMesh, FVector(0));
}

void ARoomBuilder::SET_RoomBase(ARoomBase* RoomBase_p)
{
	check(RoomBase_p);

	this->RoomBase = RoomBase_p;

	check(this->RoomBase);

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= 'RoomBase' var was initialized with => %s <= ref !"), *this->ObjectName, *this->RoomBase->GetName());
}

void ARoomBuilder::Fill_RectangleVolume(const FVector& Vert_01_p, const FVector& Vert_02_p, const FVector& Vert_03_p, const FVector& Vert_04_p, const FVector& RoomActorOriginLoc_p)
{
	int32 _Rect_Length = (int32)FVector::Dist(Vert_01_p, Vert_02_p) / 100.0f; // We divide it by 100.0f to get meters instead of cm
	int32 _Rect_Width  = (int32)FVector::Dist(Vert_01_p, Vert_03_p) / 100.0f;
	int32 _Rect_Height = (int32)FVector::Dist(Vert_01_p, Vert_04_p) / 100.0f;

	// The Vert01_p is used for the meshes with more than 4 sockets
	// Be careful of the direction of the mesh ! If not positioned well, _SpawnOriginLoc will get messed up
	FVector _SpawnOriginLoc = RoomActorOriginLoc_p + Vert_01_p + FVector(50.0f, -50.0f, 50.0f);

	check(GetWorld());

	for (int32 zlo = 0; zlo <= _Rect_Height - 1; zlo++)
	{
		for (int32 ylo = 0; ylo <= _Rect_Length - 1; ylo++)
		{
			for (int32 xlo = 0; xlo <= _Rect_Width - 1; xlo++)
			{
				// Why 100.0f ? Because the AreaCubeFiller's mesh is a 1x1 meter cube
				// Consequently, if the mesh size changes, this also needs to be change 
				FVector _SpawnLoc = FVector(_SpawnOriginLoc + (xlo * FVector(100.0f, 0.0f, 0.0f)) + (ylo * FVector(0.0f, -100.0f, 0.0f)) + (zlo * FVector(0.0f, 0.0f, 100.0f)));

				AAreaCubeFiller* _AreaCube = GetWorld()->SpawnActor<AAreaCubeFiller>(_SpawnLoc, FRotator(0));

				check(_AreaCube);

				if (_AreaCube->GET_FaceObstacleCount() == 0)
				{
					this->AreaCubeFiller_Array_0_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 1)
				{
					this->AreaCubeFiller_Array_1_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 2)
				{
					this->AreaCubeFiller_Array_2_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 3)
				{
					this->AreaCubeFiller_Array_3_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 4)
				{
					this->AreaCubeFiller_Array_4_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 5)
				{
					this->AreaCubeFiller_Array_5_Obstacle.Add(_AreaCube);
				}

				if (_AreaCube->GET_FaceObstacleCount() == 6)
				{
					this->AreaCubeFiller_Array_6_Obstacle.Add(_AreaCube);
				}
			}
		}
	}

	this->AreaCubeFillerCount = this->AreaCubeFiller_Array_0_Obstacle.Num() + 
								this->AreaCubeFiller_Array_1_Obstacle.Num() + 
								this->AreaCubeFiller_Array_2_Obstacle.Num() + 
								this->AreaCubeFiller_Array_3_Obstacle.Num() + 
								this->AreaCubeFiller_Array_4_Obstacle.Num() + 
								this->AreaCubeFiller_Array_5_Obstacle.Num() + 
								this->AreaCubeFiller_Array_6_Obstacle.Num();

	// So to not get error while logging below
	check(this->RoomBase);

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 0 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_0_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 1 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_1_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 2 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_2_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 3 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_3_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 4 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_4_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 5 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_5_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller spawned by => %s <= to => %s <= with 6 FaceObstacleCount : %d"), *this->ObjectName, *this->RoomBase->GetName(), this->AreaCubeFiller_Array_6_Obstacle.Num());
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total count of AreaCubeFiller : %d"), this->AreaCubeFillerCount);
}

void ARoomBuilder::Fill_RectangleVolume_TESTING(const FVector& Vert_01_p, const FVector& Vert_02_p, const FVector& Vert_03_p, const FVector& Vert_04_p, const FVector& ActorOriginLoc_p)
{
	int32 _Rect_Length = (int32)FVector::Dist(Vert_01_p, Vert_02_p) / 100.0f; // We divide it by 100.0f to get meters instead of cm
	int32 _Rect_Width  = (int32)FVector::Dist(Vert_01_p, Vert_03_p) / 100.0f;
	int32 _Rect_Height = (int32)FVector::Dist(Vert_01_p, Vert_04_p) / 100.0f;

	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Vert_01_p : %s"), *Vert_01_p.ToString());
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Vert_02_p : %s"), *Vert_02_p.ToString());
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Vert_03_p : %s"), *Vert_03_p.ToString());
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Vert_04_p : %s"), *Vert_04_p.ToString());

	// The Vert01_p is used for the meshes with more than 4 sockets
	// Be careful of the direction of the mesh ! If not positioned well, _SpawnOriginLoc will get messed up
	FVector _SpawnOriginLoc = ActorOriginLoc_p + Vert_01_p + FVector(50.0f, -50.0f, 50.0f);

	check(GetWorld());

	for (int32 zlo = 0; zlo <= _Rect_Height - 1; zlo++)
	{
		for (int32 ylo = 0; ylo <= _Rect_Length - 1; ylo++)
		{
			for (int32 xlo = 0; xlo <= _Rect_Width - 1; xlo++)
			{
				// Why 100.0f ? Because the AreaCubeFiller's mesh is a 1x1 meter cube
				// Consequently, if the mesh size changes, this also needs to be change 
				FVector _SpawnLoc = FVector(_SpawnOriginLoc + (xlo * FVector(100.0f, 0.0f, 0.0f)) + (ylo * FVector(0.0f, -100.0f, 0.0f)) + (zlo * FVector(0.0f, 0.0f, 100.0f)));

				AAreaCubeFiller* _AreaCube = GetWorld()->SpawnActor<AAreaCubeFiller>(_SpawnLoc, FRotator(0));

				check(_AreaCube);
			}
		}
	}
}

TArray<AAreaCubeFiller*> ARoomBuilder::Get_AreaCubeFiller_Array(int32 ObstacleCount_p)
{
	switch (ObstacleCount_p)
	{
		case 0:
			return this->AreaCubeFiller_Array_0_Obstacle;
			break;
		case 1:
			return this->AreaCubeFiller_Array_1_Obstacle;
			break;
		case 2:
			return this->AreaCubeFiller_Array_2_Obstacle;
			break;
		case 3:
			return this->AreaCubeFiller_Array_3_Obstacle;
			break;
		case 4:
			return this->AreaCubeFiller_Array_4_Obstacle;
			break;
		case 5:
			return this->AreaCubeFiller_Array_5_Obstacle;
			break;
		case 6:
			return this->AreaCubeFiller_Array_6_Obstacle;
			break;
		default:
			TArray<AAreaCubeFiller*> DefaultArray;
			return DefaultArray;
			break;
	}	
}

void ARoomBuilder::Fill_Volume()
{
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is starting Fill_Volume() ... "), *this->ObjectName);

	check(this->RoomBase);

	TArray<UStaticMeshSocket*> _SocketsArray = this->RoomBase->GET_StaticMesh()->Sockets ;
	FVector _RoomBaseOriginLoc               = this->RoomBase->GetActorLocation()        ;

	// Checking division by 0
	check(_SocketsArray.Num() > 0);
	
	// We divide it by 4 because we assume all the sockets of the mesh are to compute its volume
	// Basically, _LoopCount is the number of rectangle volume we need to computer to get the full volume of RoomBase
	int32 _LoopCount = _SocketsArray.Num() / 4;

	for (int32 i = 0; i < _LoopCount; i++)
	{
		this->Fill_RectangleVolume(
									_SocketsArray[0 + (i * 4)]->RelativeLocation,
									_SocketsArray[1 + (i * 4)]->RelativeLocation, 
									_SocketsArray[2 + (i * 4)]->RelativeLocation, 
									_SocketsArray[3 + (i * 4)]->RelativeLocation, 
									_RoomBaseOriginLoc
								  );
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has finished Fill_Volume() !"), *this->ObjectName);
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has now spawned all necessary AreaCubeFiller !"), *this->ObjectName);
}

void ARoomBuilder::Fill_Volume(UStaticMesh* StaticMesh_p)
{
	check(StaticMesh_p);

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is starting Fill_Volume() ... "), *this->ObjectName);

	TArray<UStaticMeshSocket*> _SocketsArray = StaticMesh_p->Sockets ;
	FVector _OriginLoc                       = GetActorLocation()    ;

	// Checking division by 0
	check(_SocketsArray.Num() > 0);

	// We divide it by 4 because we assume all the sockets of the mesh are to compute its volume
	// Basically, _LoopCount is the number of rectangle volume we need to computer to get the full volume of RoomBase
	int32 _LoopCount = _SocketsArray.Num() / 4;

	for (int32 i = 0; i < _LoopCount; i++)
	{
		this->Fill_RectangleVolume(
			_SocketsArray[0 + (i * 4)]->RelativeLocation,
			_SocketsArray[1 + (i * 4)]->RelativeLocation,
			_SocketsArray[2 + (i * 4)]->RelativeLocation,
			_SocketsArray[3 + (i * 4)]->RelativeLocation,
			_OriginLoc
		);
	}
	
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has finished Fill_Volume() !"), *this->ObjectName);
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has now spawned all necessary AreaCubeFiller !"), *this->ObjectName);
}

void ARoomBuilder::Fill_Volume(uint8 LoopCount_p)
{
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is starting Fill_Volume() ... "), *this->ObjectName);

	check(this->RoomBase);

	TArray<UStaticMeshSocket*> _SocketsArray = this->RoomBase->GET_StaticMesh()->Sockets;
	FVector _RoomBaseOriginLoc = this->RoomBase->GetActorLocation();

	// Checking division by 0
	check(_SocketsArray.Num() > 0);

	// We divide it by 4 because we assume all the sockets of the mesh are to compute its volume
	// Basically, _LoopCount is the number of rectangle volume we need to computer to get the full volume of RoomBase
	//int32 _LoopCount = _SocketsArray.Num() / 4;

	for (int32 i = 0; i < LoopCount_p; i++)
	{
		this->Fill_RectangleVolume(
			_SocketsArray[0 + (i * 4)]->RelativeLocation,
			_SocketsArray[1 + (i * 4)]->RelativeLocation,
			_SocketsArray[2 + (i * 4)]->RelativeLocation,
			_SocketsArray[3 + (i * 4)]->RelativeLocation,
			_RoomBaseOriginLoc
		);
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has finished Fill_Volume() !"), *this->ObjectName);
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has now spawned all necessary AreaCubeFiller !"), *this->ObjectName);
}

void ARoomBuilder::Fill_Volume(uint16 StartingIndex_p, uint8 LoopCount_p)
{
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is starting Fill_Volume() ... "), *this->ObjectName);

	check(this->RoomBase);

	TArray<UStaticMeshSocket*> _SocketsArray = this->RoomBase->GET_StaticMesh()->Sockets;
	FVector _RoomBaseOriginLoc = this->RoomBase->GetActorLocation();

	// Checking division by 0
	check(_SocketsArray.Num() > 0);

	// We divide it by 4 because we assume all the sockets of the mesh are to compute its volume
	// Basically, _LoopCount is the number of rectangle volume we need to computer to get the full volume of RoomBase
	//int32 _LoopCount = _SocketsArray.Num() / 4;

	for (int32 i = 0; i < LoopCount_p; i++)
	{
		this->Fill_RectangleVolume(
			_SocketsArray[StartingIndex_p + 0 + (i * 4)]->RelativeLocation,
			_SocketsArray[StartingIndex_p + 1 + (i * 4)]->RelativeLocation,
			_SocketsArray[StartingIndex_p + 2 + (i * 4)]->RelativeLocation,
			_SocketsArray[StartingIndex_p + 3 + (i * 4)]->RelativeLocation,
			_RoomBaseOriginLoc
		);
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has finished Fill_Volume() !"), *this->ObjectName);
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has now spawned all necessary AreaCubeFiller !"), *this->ObjectName);
}

void ARoomBuilder::Fill_Volume_TESTING(UStaticMesh* StaticMesh_p)
{
	check(StaticMesh_p);
	
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is starting Fill_Volume() ... "), *this->ObjectName);

	TArray<UStaticMeshSocket*> _SocketsArray = StaticMesh_p->Sockets;
	FVector _OriginLoc = GetActorLocation();

	// Checking division by 0
	check(_SocketsArray.Num() > 0);

	// We divide it by 4 because we assume all the sockets of the mesh are to compute its volume
	// Basically, _LoopCount is the number of rectangle volume we need to computer to get the full volume of RoomBase
	int32 _LoopCount = _SocketsArray.Num() / 4;

	for (int32 i = 0; i < _LoopCount; i++)
	{
		this->Fill_RectangleVolume_TESTING(
			_SocketsArray[0 + (i * 4)]->RelativeLocation,
			_SocketsArray[1 + (i * 4)]->RelativeLocation,
			_SocketsArray[2 + (i * 4)]->RelativeLocation,
			_SocketsArray[3 + (i * 4)]->RelativeLocation,
			_OriginLoc
		);
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has finished Fill_Volume() !"), *this->ObjectName);
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= has now spawned all necessary AreaCubeFiller !"), *this->ObjectName);
}

void ARoomBuilder::Spawn_ActorInRoom(EDataTable DataTable_p, int16 RowIndex_p, const FBuilderController& BuilderController_p, int16 ActorsNbToSpawn_p)
{
	// Getting a row out of FLightCatalog_DT
	// Basically, initializing 'DT_LightCatalogRow' and the other DataTable variables
	this->Loading_StructBuilder(DataTable_p, RowIndex_p, ActorsNbToSpawn_p);
	//Get_FromLightCatalogDT(1)                  ;
	this->Loading_PatternCubeBaseReferences(this->BuilderController)  ;
	this->Refining_FirstStep()                 ;
	this->Refining_SecondStep()                ;
	this->Refining_ThirdStep()                 ;
	this->Spawn_BlueprintActors()              ;
	this->Refining_FourthStep()                ;
	this->Spawn_Actor(this->BuilderController) ;
	this->Cleaning_Room()                      ;
	this->Reinit_Variables()                   ;
}

void ARoomBuilder::Spawn_AllActors()
{
	//this->Spawn_ActorInRoom(EDataTable::EDT_BOX, 0, this->BuilderController, 2);
	//this->Spawn_ActorInRoom(EDataTable::EDT_LIGHT, 1, this->BuilderController, 2);

	//this->Cleaning_Room();
}

void ARoomBuilder::Loading_StructBuilder(EDataTable DataTable_p, int16 RowIndex_p, int16 ActorsNbToSpawn_p)
{
	switch (DataTable_p)
	{
		case EDataTable::EDT_LIGHT:
			Get_FromLightCatalogDT(RowIndex_p)                                      ;
			this->BuilderController.S_StaticMesh           = Light_StaticMesh       ;
			this->BuilderController.S_MeshBlueprintPattern = Light_BlueprintPattern ;
			break                                                                   ;
		case EDataTable::EDT_BOX:
			Get_FromBoxesCatalogDT(RowIndex_p)                                      ;
			this->BuilderController.S_StaticMesh           = Boxes_StaticMesh       ;
			this->BuilderController.S_MeshBlueprintPattern = Boxes_BlueprintPattern ;
			break                                                                   ;
		default:
			break;
	}

	// Initializing the actor number we want to spawn
	this->BuilderController.S_ElementNumberToSpawn = ActorsNbToSpawn_p;
}

void ARoomBuilder::Loading_PatternCubeBaseReferences(const FBuilderController& BuilderController_p)
{
	check(GetWorld());

	AArchElementPattern* _Light_BlueprintActor = nullptr ;
	TArray<AActor*>      _ChildrenArray                  ;
	APatternCube*        _PatternCubeBase = nullptr      ;
	
	// First step : spawning the 'ArcElementPattern' BlueprintActor in the world to get a reference
	// NB : we are only spawning it temporaly as it is only for initializing references
	_Light_BlueprintActor = GetWorld()->SpawnActor<AArchElementPattern>(BuilderController_p.S_MeshBlueprintPattern, FVector(10000.0f, 0.0f, 0.0f), FRotator(0));
	check(_Light_BlueprintActor);

	_Light_BlueprintActor->GetAllChildActors(_ChildrenArray, false);
	check(_ChildrenArray[0]);

	_PatternCubeBase = Cast<APatternCube>(_ChildrenArray[0]);
	check(_PatternCubeBase);

	// Initializing the class variables
	this->PatternCubeBase_PreSpawnSignArr               = _PatternCubeBase->GET_PreSpawnSignArr()               ;
	this->PatternCubeBase_PostSpawnSignArr              = _PatternCubeBase->GET_PostSpawnSignArr()              ;
	this->PatternCubeBase_PreSpawnFaceObstacleCount     = _PatternCubeBase->GET_PreSpawnFaceObstacleCount()     ;
	this->PatternCubeBase_PreSpawnSideFaceObstacleCount = _PatternCubeBase->GET_PreSpawnSideFaceObstacleCount() ;
	this->PatternCubeBase_FollowingPattern              = _PatternCubeBase->GET_PreSpawnSignArrPattern()        ;

	// ---- LOGGING : display all information about our PatternCubeBase
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("******************************")                                                                                                            );
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("-> PatternCubeBase_PreSpawnSignArr          <- : %s"), *_PatternCubeBase->DEBUG_PreSpawnSignArr()                                           );
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("-> PatternCubeBase_PostSpawnSignArr         <- : %s"), *_PatternCubeBase->DEBUG_PostSpawnSignArr()                                          );
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("-> PatternCubeBase_PreFaceObstacleCount     <- : %d"), this->PatternCubeBase_PreSpawnFaceObstacleCount                                      );
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("-> PatternCubeBase_PreSideFaceObstacleCount <- : %d"), this->PatternCubeBase_PreSpawnSideFaceObstacleCount                                  );
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("-> PatternCubeBase_FollowingPattern         <- : %s"), (this->PatternCubeBase_FollowingPattern ? TEXT("Following") : TEXT("Non-Following")) );
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("******************************")                                                                                                            );
	// ----

	// ----- Removing stuff we won't use anymore in order to free up space ----- //
	// Emptying the array
	_ChildrenArray.Empty();
	// Resetting our pointer to NULL
	_PatternCubeBase = nullptr;
	// Destroying our '_Light_BlueprintActor'
	_Light_BlueprintActor->Destroy();
		
	// ---- LOGGING : display our BuilderController information
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("----- BuilderController -----"));
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("S_ElementNumberToSpawn : %d"), this->BuilderController.S_ElementNumberToSpawn);
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("----------"));
	// ----

	// Loading our WorkingArray
	this->WorkingArray = this->Get_AreaCubeFiller_Array(this->PatternCubeBase_PreSpawnFaceObstacleCount);

	// Checking if our WorkingArray contains at least one element, and therefore at least one potential match
	if (this->WorkingArray.Num() == 0)
	{
		UE_LOG(LogClass_RoomBuilder, Warning, TEXT("There is no potentially matching AreaCubeFiller in this room... (Exiting function...)"));
		return;
	}
	
	// ---- LOGGING : display all elements that are being added to our Working Array
	for (int32 i = 0; i < this->WorkingArray.Num(); i++)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= was added to our Working Array"), *this->WorkingArray[i]->GetName());
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Working Array elements count : %d"), this->WorkingArray.Num());
	// ----
}

void ARoomBuilder::Refining_FirstStep()
{
	// First refining step : checking top and bottom faces

	// ---- LOGGING : state of our WorkingArray
	for (int32 i = 0; i < this->WorkingArray.Num(); i++)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray[%d] : %s"), i, *this->WorkingArray[i]->DEBUG_PostSpawnSignArr());
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray current size : %d"), this->WorkingArray.Num());
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("------------------------------"));
	// ----

	int32 _DeletedRowCount = 0                       ;
	int32 _ArraySize      = this->WorkingArray.Num() ;

	for (int32 i = 0; i < _ArraySize; i++)
	{
		int32* _SignArr = this->WorkingArray[i - _DeletedRowCount]->GET_PostSpawnSignArr();

		// Checking if Top Face OR Bottom Face don't match
		if (this->PatternCubeBase_PreSpawnSignArr[4] != _SignArr[4] || this->PatternCubeBase_PreSpawnSignArr[5] != _SignArr[5])
		{
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is being removed from WorkingArray"), *this->WorkingArray[i - _DeletedRowCount]->GetName());
			this->WorkingArray.RemoveAt(i - _DeletedRowCount);
			_DeletedRowCount++;
		}
	}

	// ---- LOGGING : state of our WorkingArray
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("------------------------------"));
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total number of elements removed from WorkingArray : %d"), _DeletedRowCount);

	for (int32 i = 0; i < this->WorkingArray.Num(); i++)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray[%d] : %s"), i, *this->WorkingArray[i]->GetName());
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray current size : %d"), this->WorkingArray.Num());
	// ----
}

void ARoomBuilder::Refining_SecondStep()
{
	// Second refining step : checking the Side Faces Pattern (only if ObstacleCount == 2)
	// Possible patterns : 'Following Pattern' and 'Non-Following Pattern' 
	// Following Patterns example : { 1, 1, 0, 0 } 
	// Non-Following Pattern example : { 1, 0, 1, 0 }
	// 
	// The goal is to check whether rotation of the Actor could eventually make the two Signature Array match
	// It is irrelevant to check ObstacleCount == 0 || == 1 || == 3 || == 4 

	if (this->PatternCubeBase_PreSpawnSideFaceObstacleCount == 2)
	{
		int32 _DeletedRowCount = 0;
		int32 _ArraySize = this->WorkingArray.Num();

		// If our PatternCubeBase_FaceObstacleCount has a Following Pattern
		if (this->PatternCubeBase_FollowingPattern)
		{
			UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Yes bitch, I have a following pattern"));
			for (int32 i = 0; i < _ArraySize; i++)
			{
				bool _bIsSideFaceObstacleFollowingPattern = this->WorkingArray[i - _DeletedRowCount]->GET_SideFaceObstacleFollowingPattern();

				// If the AreaCubeFiller just above has a Non-Following Pattern, then remove it from the working array
				if (!_bIsSideFaceObstacleFollowingPattern)
				{
					UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is being removed from WorkingArray"), *this->WorkingArray[i - _DeletedRowCount]->GetName());
					this->WorkingArray.RemoveAt(i - _DeletedRowCount);
					_DeletedRowCount++;
				}
			}
		}
		// If our _PatternCubeBase_SideFaceObstacleCount has a Non-Following Pattern 
		else
		{
			for (int32 i = 0; i < _ArraySize; i++)
			{
				bool _bIsSideFaceObstacleFollowingPattern = this->WorkingArray[i - _DeletedRowCount]->GET_SideFaceObstacleFollowingPattern();

				// If the AreaCubeFiller just above has a Following Pattern, then remove it from the working array
				if (_bIsSideFaceObstacleFollowingPattern)
				{
					UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= is being removed from WorkingArray"), *this->WorkingArray[i - _DeletedRowCount]->GetName());
					this->WorkingArray.RemoveAt(i - _DeletedRowCount);
					_DeletedRowCount++;
				}
			}
		}

		// ---- LOGGING : state of our Working Array
		UE_LOG(LogClass_RoomBuilder, Warning, TEXT("------------------------------"));
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("Total number of elements removed from WorkingArray : %d"), _DeletedRowCount);

		for (int32 i = 0; i < this->WorkingArray.Num(); i++)
		{
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray[%d] : => %s <="), i, *this->WorkingArray[i]->GetName());
		}

		UE_LOG(LogClass_RoomBuilder, Log, TEXT("WorkingArray current size : %d"), this->WorkingArray.Num());
		// ----
	}
}

void ARoomBuilder::Refining_ThirdStep()
{
	// Third refining step : checking if we already have some matching AreaCubeFiller
	// If not, calculate the rotation needed for the Mesh's Transform to match the AreaCubeFiller rotation [...]
	// [...] and set the AreaCubeFiller's RotationCount variable accordingly

	for (int32 i = 0; i < this->WorkingArray.Num(); i++)
	{
		int32* _SignArr            = this->WorkingArray[i]->GET_PostSpawnSignArr()                      ;
		bool   _bAreArraysMatching = DoFourDigitsArrayMatch(this->PatternCubeBase_PreSpawnSignArr, _SignArr) ;

		// If both arrays are matching
		if (_bAreArraysMatching)
		{
			this->WorkingArray[i]->SET_RotationCount(0);
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= RotationCount : 0"), *this->WorkingArray[i]->GetName());
		}
		else
		{
			int32 _RotationCount = 0;

			// As long as both arrays are not matching...
			while (!DoFourDigitsArrayMatch(this->PatternCubeBase_PreSpawnSignArr, _SignArr))
			{
				RotateSizeFourArray(_SignArr);

				_RotationCount++;

				// The point here is to not make it spin to infinity
				if (_RotationCount > 6)
				{
					UE_LOG(LogClass_RoomBuilder, Warning, TEXT("ERROR ! -> _RotationCount <- is superior than 6 ! This is not supposed to be possible !"));
					break;
				}
			}

			this->WorkingArray[i]->SET_RotationCount(_RotationCount);
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= RotationCount : %d"), *this->WorkingArray[i]->GetName(), _RotationCount);
		}
	}
}

void ARoomBuilder::Spawn_BlueprintActors()
{
	// Spawning the Blueprint Actors
	// NOTE : for testing purposes, will be spawned everything that can be spawned

	for (int32 i = 0; i < this->WorkingArray.Num(); i++)
	{
		// If it's a perfect match and there is no need to apply any rotation
		if (this->WorkingArray[i]->GET_RotationCount() == 0)
		{
			FVector _Loc = this->WorkingArray[i]->GetActorLocation();

			AArchElementPattern* _SpawningActor = GetWorld()->SpawnActor<AArchElementPattern>(this->BuilderController.S_MeshBlueprintPattern, _Loc, FRotator(0));
			check(_SpawningActor);

			this->BlueprintActorsArray.Add(_SpawningActor);
		}
		// If it is not a perfect match, then we need to apply some rotation
		else
		{
			int16 _RotationFactor = this->WorkingArray[i]->GET_RotationCount() ;
			float _Z_Rotation     = 90.0f * (float)_RotationFactor             ;

			FVector  _Loc = this->WorkingArray[i]->GetActorLocation() ;
			FRotator _Rot = FRotator(0.0f, _Z_Rotation, 0.0f)         ;

			AArchElementPattern* _SpawningActor = GetWorld()->SpawnActor<AArchElementPattern>(this->BuilderController.S_MeshBlueprintPattern, _Loc, _Rot);
			check(_SpawningActor);

			// Rotating all the PatternCube's PostSpawn_SignArr of all the ArchElementPattern actors
			for (int32 bo = 0; bo < _RotationFactor; bo++)
			{
				_SpawningActor->Rotate_EveryChildPostSpawnSignArr();
			}

			this->BlueprintActorsArray.Add(_SpawningActor);
		}
	}

	// DEBBUGING
	for (int32 i = 0; i < this->BlueprintActorsArray.Num(); i++)
	{
		this->BlueprintActorsArray[i]->DEBUG_DisplayEveryChildPreSpawnSignArr()  ;
		this->BlueprintActorsArray[i]->DEBUG_DisplayEveryChildPostSpawnSignArr() ;
	}
}

void ARoomBuilder::Refining_FourthStep()
{
	// Fourth refining step : checking if all the PatternCube of all ArchElementPattern 
	// matches with all their AreaCubeFiller counterparts
	int32 _DeletedRowCount = 0                                ;
	int32 _ArraySize       = this->BlueprintActorsArray.Num() ;

	for (int32 i = 0; i < _ArraySize; i++)
	{
		bool _bIsMatching = this->BlueprintActorsArray[i - _DeletedRowCount]->Compare_EveryChildPreSpawnPostSpawnSignArr();
		
		if (!_bIsMatching)
		{
			UE_LOG(LogClass_RoomBuilder, Warning, TEXT("Removing BlueprintActorsArray[%d] : %s"), i - _DeletedRowCount, *this->BlueprintActorsArray[i - _DeletedRowCount]->GetName());
			this->BlueprintActorsArray[i - _DeletedRowCount]->Destroy();
			this->BlueprintActorsArray.RemoveAt(i - _DeletedRowCount);
			this->WorkingArray.RemoveAt(i - _DeletedRowCount);
			_DeletedRowCount++;
		}
	}
}

void ARoomBuilder::Spawn_Actor(const FBuilderController& BuilderController_p)
{
	check(this->RoomBase);

	// ---------------------------------------------------------------------------- //
	// Removing and cleaning all the BlueprintActors that were spawned
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Destroying all BlueprintActors and removing their references from the array"));

	for (int32 i = 0; i < this->BlueprintActorsArray.Num(); i++)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("Destroying => %s <= ..."), *this->BlueprintActorsArray[i]->GetName());
		this->BlueprintActorsArray[i]->Destroy();
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("Emptying -> BlueprintActorsArray <- ..."));
	this->BlueprintActorsArray.Empty();

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("All BlueprintActors have now been destroyed and their array has been cleaned"));
	// ---------------------------------------------------------------------------- //
	
	//
	//

	// Spawning the Actors
	for (int32 i = 0; i < BuilderController_p.S_ElementNumberToSpawn; i++)
	{
		int16 _RandomIndex = FMath::RandRange(0, this->WorkingArray.Num() - 1);

		// If it's a perfect match and there is no need to apply any rotation
		if (this->WorkingArray[_RandomIndex]->GET_RotationCount() == 0)
		{
			FVector _Loc = this->WorkingArray[_RandomIndex]->GetActorLocation();

			AArcElemBase* _SpawningActor = GetWorld()->SpawnActor<AArcElemBase>(_Loc, FRotator(0));
			check(_SpawningActor);
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= was spawned"), *_SpawningActor->GetName());

			// NTM : perhaps change the 'this->BuilderController' to 'BuilderController_p'
			_SpawningActor->Set_MainStaticMesh(this->BuilderController.S_StaticMesh);
			this->WorkingArray.RemoveAt(_RandomIndex);
			this->RoomBase->GET_ActorsMainArray().Add(_SpawningActor);
			
		}
		// If it is not a perfect match, then we need to apply some rotation
		else
		{
			int16 _RotationFactor = this->WorkingArray[_RandomIndex]->GET_RotationCount() ;
			float _Z_Rotation     = 90.0f * (float)_RotationFactor                        ;

			FVector  _Loc = this->WorkingArray[_RandomIndex]->GetActorLocation() ;
			FRotator _Rot = FRotator(0.0f, _Z_Rotation, 0.0f)                    ;

			AArcElemBase* _SpawningActor = GetWorld()->SpawnActor<AArcElemBase>(_Loc, _Rot);
			check(_SpawningActor);
			UE_LOG(LogClass_RoomBuilder, Log, TEXT("=> %s <= was spawned"), *_SpawningActor->GetName());

			_SpawningActor->Set_MainStaticMesh(this->BuilderController.S_StaticMesh);
			this->WorkingArray.RemoveAt(_RandomIndex);
			this->RoomBase->GET_ActorsMainArray().Add(_SpawningActor);
		}
	}
}

void ARoomBuilder::Reinit_Variables()
{
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("Reinitializing all spawning actors variables..."))                                                                ;
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("----- Original values..."))                                                                                       ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArraySixSlots("PatternCubeBase_PreSpawnSignArr :", this->PatternCubeBase_PreSpawnSignArr)                                                        ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArraySixSlots("PatternCubeBase_PostSpawnSignArr :", this->PatternCubeBase_PostSpawnSignArr)                                                      ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_PreSpawnFaceObstacleCount : %d"), this->PatternCubeBase_PreSpawnFaceObstacleCount)                ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_PreSpawnSideFaceObstacleCount : %d"), this->PatternCubeBase_PreSpawnSideFaceObstacleCount)        ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_FollowingPattern : %s"), (this->PatternCubeBase_FollowingPattern ? TEXT("True") : TEXT("False"))) ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArrayElementsNames("WorkingArray", this->WorkingArray)                                                                                           ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArrayElementsNames("BlueprintActorsArray", this->BlueprintActorsArray)                                                                           ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("BuilderController.S_MeshBlueprintPattern : %s"), *this->BuilderController.S_MeshBlueprintPattern->GetName())      ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("BuilderController.S_StaticMesh : %s"), *this->BuilderController.S_StaticMesh->GetName())                          ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("BuilderController.S_ElementNumberToSpawn : %d"), this->BuilderController.S_ElementNumberToSpawn)                  ;
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("-----"))                                                                                                          ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("Cleaning..."))                                                                                                    ;

	// PatternCubeBase_PreSpawnSignArr
	this->PatternCubeBase_PreSpawnSignArr[0] = 0;
	this->PatternCubeBase_PreSpawnSignArr[1] = 0;
	this->PatternCubeBase_PreSpawnSignArr[2] = 0;
	this->PatternCubeBase_PreSpawnSignArr[3] = 0;
	this->PatternCubeBase_PreSpawnSignArr[4] = 0;
	this->PatternCubeBase_PreSpawnSignArr[5] = 0;
	this->PatternCubeBase_PreSpawnSignArr = nullptr;

	// PatternCubeBase_PostSpawnSignArr
	this->PatternCubeBase_PostSpawnSignArr[0] = 0;
	this->PatternCubeBase_PostSpawnSignArr[1] = 0;
	this->PatternCubeBase_PostSpawnSignArr[2] = 0;
	this->PatternCubeBase_PostSpawnSignArr[3] = 0;
	this->PatternCubeBase_PostSpawnSignArr[4] = 0;
	this->PatternCubeBase_PostSpawnSignArr[5] = 0;
	this->PatternCubeBase_PostSpawnSignArr = nullptr;

	// PatternCubeBase_PreSpawnFaceObstacleCount
	this->PatternCubeBase_PreSpawnFaceObstacleCount = 0;

	// PatternCubeBase_PreSpawnSideFaceObstacleCount
	this->PatternCubeBase_PreSpawnSideFaceObstacleCount = 0;

	// PatternCubeBase_FollowingPattern
	this->PatternCubeBase_FollowingPattern = false;

	// WorkingArray
	this->WorkingArray.Empty();

	// BlueprintActorsArray
	this->BlueprintActorsArray.Empty();

	// BuilderController
	this->BuilderController.S_MeshBlueprintPattern = nullptr ;
	this->BuilderController.S_StaticMesh           = nullptr ;
	this->BuilderController.S_ElementNumberToSpawn = 0       ;

	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("Cleaning ended."))                                                                                                ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("----- Cleaned values..."))                                                                                        ;	

	if (this->PatternCubeBase_PreSpawnSignArr != nullptr)
	{
		DEBUG_DisplayArraySixSlots("PatternCubeBase_PreSpawnSignArr :", this->PatternCubeBase_PreSpawnSignArr);
	}
	else
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("PatternCubeBase_PreSpawnSignArr has been reinitialized. It is now pointing to a nullptr."));
	}

	if (this->PatternCubeBase_PostSpawnSignArr != nullptr)
	{
		DEBUG_DisplayArraySixSlots("PatternCubeBase_PostSpawnSignArr :", this->PatternCubeBase_PostSpawnSignArr);
	}
	else
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("PatternCubeBase_PostSpawnSignArr has been reinitialized. It is now pointing to a nullptr."));
	}

	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_PreSpawnFaceObstacleCount : %d"), this->PatternCubeBase_PreSpawnFaceObstacleCount)                ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_PreSpawnSideFaceObstacleCount : %d"), this->PatternCubeBase_PreSpawnSideFaceObstacleCount)        ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("PatternCubeBase_FollowingPattern : %s"), (this->PatternCubeBase_FollowingPattern ? TEXT("True") : TEXT("False"))) ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArrayElementsNames("WorkingArray", this->WorkingArray)                                                                                           ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;
	DEBUG_DisplayArrayElementsNames("BlueprintActorsArray", this->BlueprintActorsArray)                                                                           ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("***"))                                                                                                            ;

	if (this->BuilderController.S_MeshBlueprintPattern != nullptr)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("BuilderController.S_MeshBlueprintPattern : %s"), *this->BuilderController.S_MeshBlueprintPattern->GetName())      ;
	}
	else
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("BuilderController.S_MeshBlueprintPattern has been reinitialized. It is now pointing to a nullptr."));
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("***"));

	if (this->BuilderController.S_StaticMesh != nullptr)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("BuilderController.S_StaticMesh : %s"), *this->BuilderController.S_StaticMesh->GetName());
	}
	else
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("BuilderController.S_StaticMesh has been reinitialized. It is now pointing to a nullptr."));
	}

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("***"));

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("BuilderController.S_ElementNumberToSpawn : %d"), this->BuilderController.S_ElementNumberToSpawn) ;
	UE_LOG(LogClass_RoomBuilder, Warning, TEXT("-----"))                                                                                     ;
	UE_LOG(LogClass_RoomBuilder, Log,     TEXT("Cleaning..."))                                                                               ;
}

void ARoomBuilder::Cleaning_Room()
{
	// Destroy all AreaCubeFiller for visibility and debugging purposes
	this->Destroy_EveryElementInArray("AreaCubeFiller_Array_0_Obstacle", this->AreaCubeFiller_Array_0_Obstacle);
	this->Destroy_EveryElementInArray("AreaCubeFiller_Array_1_Obstacle", this->AreaCubeFiller_Array_1_Obstacle);
	this->Destroy_EveryElementInArray("AreaCubeFiller_Array_2_Obstacle", this->AreaCubeFiller_Array_2_Obstacle);
	this->Destroy_EveryElementInArray("AreaCubeFiller_Array_3_Obstacle", this->AreaCubeFiller_Array_3_Obstacle);
	//this->Destroy_EveryElementInArray(this->AreaCubeFiller_Array_4_Obstacle);
	//this->Destroy_EveryElementInArray(this->AreaCubeFiller_Array_5_Obstacle);
	//this->Destroy_EveryElementInArray(this->AreaCubeFiller_Array_6_Obstacle);
}

void ARoomBuilder::Destroy_EveryElementInArray(const FString& ArrayName_p, TArray<AAreaCubeFiller*> Array_p)
{
	for (int32 i = 0; i < Array_p.Num(); i++)
	{
		UE_LOG(LogClass_RoomBuilder, Log, TEXT("Destroying %s[%d] : => %s <= "), *ArrayName_p, i, *Array_p[i]->GetName());
		Array_p[i]->Destroy();
	}
	
	UE_LOG(LogClass_RoomBuilder, Log, TEXT("All elements of %s have now been destroyed !"), *ArrayName_p);
	
	Array_p.Empty();

	UE_LOG(LogClass_RoomBuilder, Log, TEXT("%s is now empty !"), *ArrayName_p);
}

void ARoomBuilder::TESTING_SelectAndRemove()
{
	AAreaCubeFiller* _SelectedCube = this->AreaCubeFiller_Array_3_Obstacle[0];
	check(_SelectedCube);
	_SelectedCube->Trace_AllInternalRays();
	this->AreaCubeFiller_Array_3_Obstacle.Remove(_SelectedCube);
	_SelectedCube->Destroy();
}