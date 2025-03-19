# Simple3DEngine

## About the project
Simple 3D engine capable of loading and rendering wireframe 3D models in perspective. It uses c++ and simple graphics library called SFML. Math is handeled by custom math library allowing for operations on 4D vectors and 4x4 matricies. Engine, by default renders the famous utah teapot, rotating around the up-axis.

### Features
  * Operations on vectors and matrices
  * Translation and rotation in 3D
  * Perspecitve projection
  * Loading 3D model from file
  * Simple performence profiling - frame time display
  * Coordinate system used: X - forward, Y - right, Z - up

### Technologies used
  * SFML 2.5.1
  * c++14

## Showcase
![teapot](https://github.com/BOOGIE-MAN/Simple3DEngine/assets/54042389/905214ef-01c9-4e35-9d72-15c71a0bee5b)

## How to run it
It can be run through Visual Studio 2022 only in x86 mode in either Debug or Release[prefered]

### Platform
Windows 10

### File Input restrictions
In order to load the model it has to be placed under (ProjectDirectory)\Resources\Model in a .txt file in the following format: first (space/tab separeted) model vertecies must be specified with 'v' at the begining of the line then indicies of trinagles begining with 't' with the same format as vertecies(indexing goes from 1 to number of triangles).

## Idea
This project was written to help me understand the basics of 3D graphics better.
