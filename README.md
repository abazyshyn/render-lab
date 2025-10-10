## Render Lab 🔭

This project is a showcase of my skills in C++, OpenGL, GLSL.

## Quickstart ⏱

#### Note: Currently, only the Debug build is available.

### Windows:
1. Build and run the project using [Visual Studio](https://visualstudio.microsoft.com/vs/) (for that everything configured in CMakeSettings.json).

### Linux:
1. Make the desired build script executable:
```bash
# Debug
$ chmod +x scripts/build/linux/debug.sh

# RelWithDebInfo
$ chmod +x scripts/build/linux/rel_with_deb_info.sh

# Release
$ chmod +x scripts/build/linux/release.sh

# MinSizeRel
$ chmod +x scripts/build/linux/min_size_rel.sh
```
2. Run the desired build script:
```bash
# Debug
$ ./scripts/build/linux/debug.sh

# RelWithDebInfo
$ ./scripts/build/linux/rel_with_deb_info.sh

# Release
$ ./scripts/build/linux/release.sh

# MinSizeRel
$ ./scripts/build/linux/min_size_rel.sh
```
3. If the script fails, you may need to install some dependencies using your package manager (e.g., `pacman`).
4. Run the program - `./bin/your_os_and_architechture/RenderLab/your_desired_build/RenderLab`.

## Controls 🕹
- WSAD - movement
- CTRL + SHIFT + C - hide cursor
- CTRL + SHIFT + X - show cursor
- SHIFT + Q - turn on wireframe mode
- CTRL + Q - turn off wireframe mode

## Development process 🧰
### Endless grid for debugging
![demo-grid](https://github.com/user-attachments/assets/74ce3c59-9e38-4efc-9873-68f2be778b9d)

### Geometry shader for debugging normal vectors
<img width="1920" height="1032" alt="" src="https://github.com/user-attachments/assets/1ef7b2ea-a7f0-4265-9efe-b423fa5da1bc" /> 

### Basic light (ambient, diffuse, specular) 
<img width="1920" height="1032" alt="" src="https://github.com/user-attachments/assets/9df96853-01c1-4def-b6a4-8e01175df5c6" />
