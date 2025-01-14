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
## Known mistakes
These are some the mistakes I've realised I've done, but it's too late to change.

### Scene/Gameobjects
It's possible to add gameobjects to a scene. But that creates a problem because I can only add gameobjects to the scene. I can't add gameobjects as children of other gameobjects. This causes some strange code in the repo.
This has been somewhat fixed. Affected code should be gone...

### Timer
The timer object is a bit of a strange one. Since it is derived from the game object class, but it behaves differently. This can be fixed by adding a `Engine::Event` to the Timer and changing the update behaviour to call invoke the event. But there is still a glaring issue with the Timer class. It's that it relies on the update loop. If the game where to freeze or for some reason the update loop takes longer than expected the timer may fire to early. To prevent this it could be multithreaded and  timers could be on a separate thread.
Again this has been somewhat fixed by making it optional to use both as an independent object and a child game object.