# Basic-2d-Renderer
A simple 2D renderer that allows you to draw out shapes and apply rigid transformations to them.

This was written in C++ using the SFML library.

This originally started as a school project but I might work on it more.

## Build
To build the project you have to have Premake and Make installed

Go into the `/build/` directory and run

```
premake
```

This will build the Makefile

To build the release version, run

```
make config=release
```

To  build the debug version, run

```
make
```

Then go into the `/bin/Release/` directory and run

```
.\Renderer.exe
```

## Controls


* P -> draw point - click to draw point
* L -> draw line  - click to draw line
* S -> draw shape - right click to stop and create the shape
* D -> delete item of the stack, press P, L, or S to delete Point, Line, or Shape respectively
* C -> clear all shapes, lines, points, etc
* R -> Reflect   - type index of shape to reflect   - type index of reflection line
* O -> Rotate    - type index of shape to rotate    - type index of rotation point  - type angle in three digits (clockwise)
* T -> Translate - type index of shape to translate - type x offset in 4 digits (the first is a negative bit) - type y ...
