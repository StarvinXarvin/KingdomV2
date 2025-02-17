# Kingdom

University project made by [CITM](https://www.citm.upc.edu/ing/), Centre de la Imatge i la Tecnologia Multimedia students of the TTC (Talent Tech Center) in Barcelona, in which we made a 3D Game Engine in C & C++ during our 3rd year of Game Development Bachelor's Degree.

## Features
* Functional UI, Window, Renderer, Input and System settings.
* Creates empty GameObjects, Cube, Cone, Pyramid...
* Able to Drag and Drop .fbx, .png and .dds files.
* About window...
* FPS-like camera
* Able to Raycast and Mouse Picking. Selects the corresponding GameObject
* Save scene as .mdng
* Save meshes as .mesh
* Save materials a .dds
* File Explorer that reads Assets/ and Library/. Can delete files from there.

## Libraries Used
* [Assimp](https://assimp-docs.readthedocs.io/)
* [DevIL](http://openil.sourceforge.net/)
* [Dear ImGui v1.73, Docking Test Branch](https://github.com/ocornut/imgui)
* [GLM](https://glm.g-truc.net/0.9.5/index.html)
* [glew](http://glew.sourceforge.net/)
* [nlohmann-json](https://github.com/nlohmann/json)
* [OpenGL](https://www.opengl.org/)
* [SDL2](https://www.libsdl.org/](https://wiki.libsdl.org/))
* [std:c++20](https://en.cppreference.com/w/cpp/20)

## Installation
No previous installations are required to use the engine, just download and execute the .exe file *Kingdom* from releases.

## Camera Controls
| Key | Description |
| :----: | :-----------: | 
| <code>WASD + MOUSE RMB</code> | FPS-like movement | 
| <code>L-ALT + MOUSE LMB</code> | Orbit around the point | 
| <code>MOUSE WHEEL UP</code> | Zoom in | 
| <code>MOUSE WHEEL DOWN</code> | Zoom out | 
| <code>F</code> | When a GameObject is selected, focus the camera on it | 
| <code>SHIFT</code> | Hold it to duplicate movement speed | 
| <code>ESC</code> | Exits the Engine | 
To test the Raycast, in the Menu bar select Debug > Raycast debug and start clicking around!

## Authors

+ [Jonathan Cacay Llanes](https://github.com/xGauss05)
+ [Ethan Martín Parra](https://github.com/Ethanm-0371)
+ [Pau Fusco Zamora](https://github.com/PauFusco)
