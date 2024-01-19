# 🐍 Cnake
The snake game written in C++ using SDL2 library

inspired by [Google Snake Game](https://g.co/kgs/BTjXHz)

## 📷 Gameplay
![gameplay](https://github.com/kotivas/cnake/blob/main/gameplay.gif)

<sup><sub>release 1.0</sub></sup>

## 🛠️ Compiling

### 🐧 Unix-like
After installing **[SDL2](https://github.com/libsdl-org/SDL/releases/)**, **[SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases)**, **[SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases)** and **[SDL2_image](https://github.com/libsdl-org/SDL_image/releases/)**, execute the following commands
```bash
git clone https://github.com/kotivas/cnake
cd cnake
mkdir obj bin
make
```
The compiled executable file will be located in ``./bin/``

> [!WARNING]
> Be sure to run with `./bin/cnake` **out of the bin directory** of the repository.
> 
> Otherwise the game will not be able to find assets.

### 🪟 Windows
After installing **[Mingw32](https://gnutoolchains.com/mingw32/)**, follow these steps

1. Download source code

2. Create folder ``sdl2``

3. Download **[SDL2-devel-mingw](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.zip)**, **[SDL2_mixer-devel-mingw](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-devel-2.6.3-mingw.zip)**, **[SDL2_tff-devel-mingw](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-mingw.zip)**, **[SDL2_image-devel-mingw](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.zip)** and extract folder ``i686-w64-mingw32`` from all this archives into the ``sdl2`` folder

> [!IMPORTANT]
> The folder structure should look like this:
> ```bash
> cnake
> ├── sdl2
> │   ├── include
> │   │   └── SDL2
> │   └── lib
> │       ├── cmake
> │       │   ├── SDL2
> │       │   ├── SDL2_image
> │       │   ├── SDL2_mixer
> │       │   └── SDL2_ttf
> │       └── pkgconfig
> ```

4. Run the makefile through mingw

5. The compiled executable file will be located in ``bin/``

> [!WARNING]
> cnake.exe and folder ``assets`` should be in the one folder
> 
> Otherwise the game will not be able to find assets.

## 💜 Thanks
I express special gratitude to my friends,
GrayCircle and VaneZ, who supported and helped develop
the game all throughout its development
