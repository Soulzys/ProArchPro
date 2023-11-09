# ProArchPro

# Project description

This project is part of a larger procedural generation project. It shall eventually be combined with the Viltek project, as the two are complementary. 

ProArchPro focuses on filling a closed space (such as a room) with static meshes in a procedural and meaningful way. 

The logic is as follow : 
- retrieves a room asset from a DataTable **(1)**
- sizes up the room's inside space by making use of AAreaCubeFiller actor combined with static mesh sockets **(2)**
- stores the valuable information **(3)**, then cleans up the room by removing the AAreaCubeFiller **(4)**
- spawns the desired blueprint actor **(5)** appropriately in the room **(6)**

*For more information, seek for the Viltek project README.*


---


**(1)** *Content/Data/DataTables/DT_RoomCatalog*

**(2)** All the room static meshes have to be set with sockets in a specific way in order for the algorithm to work. You can see a simple example of it with *Content/Geometry/SM_Room_01*. For the actual room used in the project, go to *Content/Geometry/Architecture/ShowRoom.*

**(3)** Such information are stored in TArray that you can find in the ARoomBuilder class.

**(4)** You can see this step by commenting out the *this->Spawn_ActorInRoom(EDataTable...)...* at line 32 in the RoomBuilder.cpp file.

**(5)** Blueprint actors have to be created beforehand and added to a dedicated DataTable. Within the Blueprint, the faces that are supposed to be in contact with an obstacle (usually either a wall, the ceiling or the ground floor) are coloured in blue. 

**(6)** According to the way the Blueprint actors have been set up, the algorithm will spawn them so that the actors' blue faces are in contact with an obstacle.


# Project manipulation

At this stage, only two things can be easily modified within the project.  
When you run the project, you only need to then click on the ***Testing*** button. 

*Note : as the player, you are spawned outside of the room as it was thought to be a better spot to observe the room. However, you can change that by going to the Unreal Editor and moving the PlayerStart downwards so that the next time you run the game, you will be spawned within the room.*

## 1/ The number of Blueprint actors to spawn.
Go to RoomBuilder.cpp and modify the last integer on the line 32, after *this->BuilderController*. During the demo, the original value should be 5. 


## 2/ The way the actors are spawned.
Go to Content/Blueprints/GameAssets/Boxes, open BP_Box_m01, then select the *BP_PatternCube* in the *Components* panel (usually on the left side of the screen) and in the *Details* panel, look for the *Obstacle Management* within the *Child Actor Template*, in the *Child Actor Component* section. There, you can tick the any of the six faces of the cube. 
Reminder : blue = facing / in contact with an obstacle, green = not facing / not in contact with any obstacle directly.

### Examples: 
*(a)* If you only tick Face 05 as true (meaning the face appears blue) and left the other faces unticked (green), the actors will only be spawned "sticked" to the ceiling and never in contact with a wall.
*(b)* If you tick both Face 03 and Face 06 and left all the other faces unticked, the actors will only be spawned "sticked" on a wall and to the floor (or to any horizontal surface facing upward).

### ***NOTHING*** else is meant to be modified. Doing so is highly susceptible to end up with the project crashing. 

*Note: this project should be able to be converted to a UE5 without any modification required.*
 
