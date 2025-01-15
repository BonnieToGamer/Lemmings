# Lemmings Clone in C++ 🚶

This project is a clone of the classic DOS game Lemmings, originally developed by DMA Design in 1991. The goal of this clone is to replicate the original gameplay as part of a course on C++.

## Current status
The clone is still in development, with some key features already implemented, including:
* Basic Lemmings AI.
* Level loading and destruction

## Level structure:
The level file structure is quite simple but does not conform to any standard.
```
level number
level name
level image
dirt index
exit index
time limit (seconds)
save requirement
amount of lemmings
release rate
amount climbers, floaters, bombers, blockers, builders, bashers, miners, diggers
entranceX
entranceY
exitX
exitY
cameraX
cameraY
```
example level: fun1.lvl
```
1
Just dig!
map.png
0
300
1
10
50
0,0,0,0,0,0,0,10
200
29
400
129
69
0
```