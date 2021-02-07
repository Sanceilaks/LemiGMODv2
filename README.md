Sorry 4 bad eng)))

# LemiGMODv2

Free sdk for gmod. Few functionality and bad asg. Good luck

# No kidding

It's sdk for gmod (working in february 2021). It`s my second big project on c++. BAD STRUCTURE.

# Todo
  1) Rewrite structure
  2) Fix aimbot
  3) Fix menu color (ingame)
  4) Add more interfaces and tools

# Structure

In game_sdk:
  1) Classes for monipulating with game 
  2) Game interfaces (not all)
  3) Game data types
  
In features:
  Already realized functionality

In hook:
  Hook Manager and realized hooks

In math:
  Basic math functionality for game
 
In tools:
  Basic tools for hacks
  
 hack_core - class for basic monipulations (init and shutdown)
 interfaces - class for monipulation with interfaces. For call interface:
  1) include <interfaces.h>
  2) interfaces->intefaces_name
  
globals - hack global vars


# Tools
1) Render. Only surface drawing. (check view_render_hook)
2) Logger. Bad logger (rewrite it pls)
3) Mem tools. Just pattern_scanner, interface grabber and (in netvar) netvar system

