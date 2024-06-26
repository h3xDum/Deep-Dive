
## Features
* Load & Render 3D modules from .OBJ files
* Textures / Material (optional)
* Phong Lightning

## Installation
* First we will need to make a build folder and use CMake
  to configure our project there
```bash
mkdir build  
cd build && cmake .. && make 
```

* Now the project should have been built successfully,
  if encountered an error it might be due to lacking dependencies.
  All the external dependencies are imported in the 'external' folder,
  you can download them yourself directly to the computer with your
  package manger, for example GLFW on Ubuntu will be like so
```bash
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```


## Usage 
You can run the engine as is simply by going inside the 'bin' directory located  
in the root folder and running the 'GameEngine'
```bash 
cd bin && ./GameEngine
```
