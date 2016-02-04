# Hell Recorder
Current version: v1.5  
Qt Version: v4.8  

Instructions to compile:  
. qmake  
. make

This program is a fun project that I created for myself that is related to a video game that I enjoy playing called Dungeon Fighter Online.  

To obtain end-game gear in this game, you have to run Hell Modes which drop epic equipment and various other items related to Hell Mode.
This program records the important information of each Hell Mode run and calculates statistics to help keep track of how a player's Hell Mode experience is going.

TODO:  
. Modify the way comparisons between epics work. Take the structs in hellrun.h and implement them as functions (perhaps) in another whole new class, probably the Epic class which I apparently left inside the repository but didn't include it into the compile.  
. Add option for what channel the run was done in (?)  
. Add a timestamp for when every run is recorded
