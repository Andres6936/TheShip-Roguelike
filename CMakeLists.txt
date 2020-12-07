Cmake_Minimum_Required(VERSION 3.8)
Project(TheShip CXX)

# Content Package Manager
INCLUDE(CMakeModules/CPM.cmake)

CPMAddPackage(
        NAME BearLibTerminal
        VERSION 2020.12
        GITHUB_REPOSITORY Andres6936/BearLibTerminal
)

Add_Executable(TheShip
        Source/Main.cpp
        Source/Logger.cpp
        Source/Map.cpp
        Source/Object.cpp
        Source/Screens.cpp
        Source/Character.cpp
        Source/Dice.cpp
        Source/Engine.cpp
        Source/Tile.cpp
        Source/Event.cpp)

# Load and link the library BearLibTerminal
Target_Link_Libraries(TheShip PRIVATE BearLibTerminal)
