# Darnel Engine

The beginnings of the Darnel Engine. Not sure what it will do as of yet, but it will probably be related to 3D/2D graphics, sound, games, and the like.


## Command line

First, setup "PreLoad.cmake" to your liking..

Then, populate "vendor/<lib>/bin" with library file and include directory for submoduled vendor libraries you have prebuilt. Otherwise, the source code will be downloaded and built.

Then run:
- `mkdir -p build`
- `cd build`
- `cmake ..`
- `cmake --build .`

NOTE: running install targets is undefined

## TODO
- Add parent/child functionality to windows
- Separate platform specific build options (so far only assumes windows)
