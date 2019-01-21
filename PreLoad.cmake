## uncomment to build unix style makefiles
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

## uncomment to build visual studio solution for windows
# set (CMAKE_GENERATOR "Visual Studio 15 2017 Win64" CACHE INTERNAL "" FORCE)

option ( DX12_GLOBAL_ENABLE "DirectX12 Enable" OFF )
option ( OPENGL3_GLOBAL_ENABLE "OpenGL3 Enable" ON )

option ( GLEW_MAKE_WORKAROUND_ENABLE "When making GLEW/auto, perform `make ext` separately" ON )
option ( GLEW_GLEW_C_NEWLINE_FIX_ENABLE "After making GLEW/auto, fix newline issues within strings in glew.c" ON )
