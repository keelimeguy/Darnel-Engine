# Darnel Engine

The beginnings of the Darnel Engine. Not sure what it will do as of yet, but it will probably be related to 3D/2D graphics, sound, games, and the like.


## Command line

First, setup "PreLoad.cmake" to your liking..

Then run:
- `mkdir -p build`
- `cd build`
- `cmake ..`


## TODO
- Add parent/child functionality to windows
- Search locally for prebuilt vendor libraries first (before downloading submodules and building from source)
- Separate platform specific build options (so far only assumes windows)
