Cmake_Minimum_Required(VERSION 3.8)
Project(TheShip C)

# Content Package Manager
INCLUDE(CMakeModules/CPM.cmake)

CPMAddPackage(
        NAME BearLibTerminal
        VERSION 2020.12
        GITHUB_REPOSITORY Andres6936/BearLibTerminal
)

Add_Executable(TheShip
        Source/Main.c
        Source/Logger.c
        Source/Map.c
        Source/Object.c
        Source/Screens.c
        Source/Character.c
        Source/Dice.c
        Source/Engine.c
        Source/Tile.c
        Source/Event.c)

# Load and link the library BearLibTerminal
Target_Link_Libraries(TheShip PRIVATE BearLibTerminal)
