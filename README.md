# Darnel Engine

The beginnings of the Darnel Engine. Not sure what it will do as of yet, but it will probably be related to 3D/2D graphics, sound, games, and the like.

Largely follows The Cherno's [Game Engine](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) series on youtube.

## Command line

NOTE: running install targets is undefined

First, setup "PreLoad.cmake" to your liking..

Then, populate "vendor/<lib>/bin" with library file and include directory for submoduled vendor libraries you have prebuilt. Otherwise, the source code will be downloaded and built.

Then run:

### As-is
- `cmake -S . -B build`
- `cmake --build build`

### Release
- `cmake -S . -B Release -DCMAKE_BUILD_TYPE=Release`
- `cmake --build Release`

### Debug
- `cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build Debug`

## TODO
- Render multiple windows simultaneously
- Separate platform specific build options (so far only assumes windows)
