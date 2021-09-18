# RUCengine

![RUCengine](https://github.com/rucafer/RUCengine/blob/master/Branding/Logo.png?raw=true)

RUCengine is a simple game engine created for educational purposes. It is not meant to be used for any serious or commercial product, as it is far from being a Minimum Viable Product and does not offer any kind of support. It was inspired by the YouTube tutorials found at [thecherno.com/engine](https://thecherno.com/engine)

## Goal
The goal of this project is to gain a better understanding about how modern game engines work, as well as experimenting and implementing some rendering techniques used by games and graphic applications. For that reason, the project is not trying to be a Minimum Viable Product and feautures are not implemented in any order. The implementation might be simple, as the project aims to cover a great ammount of feautres, but performance, platform independece, scalability and code quality is also taken into account.

## Features
- Basic 2D rendering: quads can be drawn at a given position with a texture or plain color
- Platform agnostic: although the engine currently works only on Windows with OpenGL, all the platform dependent code is abstracted and encapsulated so that adding new platforms (Linux, MacOS, Android, iOS...) or graphic APIs (DirectX, Vulkan, Metal...) can be done creating new implementations deriving from the given interfaces, without having to rewrite the renderer, input system, window handling...
- Shaders and materials: the engine is capable of compiling GLSL custom shaders. These shaders (and the default ones) can be used to create materials so that the manual upload of uniforms is no longer necessary
- Input system: input can be read without having to use platform specific code
- Basic framebuffer implementaion: the scene is currently rendered to a framebuffer, making posprocessing and advanced rendering techniques possible on the future
- Event system
- Layers: the application can be organized in different layers (e.g., 2D rendering, UI, debug UI...), which are updated and rendered independently in the given order
- Cameras: orthographic cameras have been implemented (and perspective cameras are currently being worked on)
- ImGui: it can be used to draw debug UI or to create custom tools for the engine
- spdlog: wrapper macros have been created making the debugging process easier (currently it only supports logging to the debug console)  

## Installation
RUCengine only supports Windows. Visual Studio 2019 is recommended as other versions have not been tested
[CMake](https://cmake.org/download/) is needed for the creation of the Visual Studio solution

**1. Downloading the repository**

Clone the repository with `git clone --recursive https://github.com/rucafer/RUCengine`.

**2. Setting up the Visual Studio solution**

Create a `Build` directory inside the reposiotry folder and navigate there. Then run `cmake ..`

**3. Compiling the project**

Open `RUCengine.sln`, compile and run the project inside Visual Studio


## Next steps
- 3D model loading and rendering
- Simple lighting algorithms
- Entity Component Systems with native scripting (C++)
- Scenes
- Loading assets form files (materials, scenes...) 
