Cmake_Minimum_Required(VERSION 3.8)
Project(TheShip C)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Lib)
Add_Executable(TheShip
        Source/Main.c
        Source/Logger.c
        Source/Map.c
        Source/Object.c
        Source/Screens.c
        Source/Character.c
        Source/Dice.c
        Source/Engine.c)

# Load and link the library BearLibTerminal
Target_Link_Libraries(TheShip BearLibTerminal)
