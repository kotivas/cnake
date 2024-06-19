# 🐍 Cnake
The snake game written in C++ using SDL2 library

inspired by [Google Snake Game](https://g.co/kgs/BTjXHz)

Also available [page on itch.io](https://kotivas.itch.io/cnake)

## 📷 Gameplay
![gameplay](https://github.com/kotivas/cnake/blob/main/gameplay.gif)

<sup><sub>release 1.0</sub></sup>

## 🛠️ Compiling
After installing **[SDL2](https://github.com/libsdl-org/SDL/releases/)**, **[SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases)**, **[SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases)** and **[SDL2_image](https://github.com/libsdl-org/SDL_image/releases/)**, execute the following commands
```bash
git clone https://github.com/kotivas/cnake
cd cnake
cmake -B build
cmake --build build
```
The compiled executable file will be located in ``build`` folder

> [!WARNING]
> cnake executable and folder ``assets`` should be in the one folder
> 
> Otherwise the game will not be able to find assets.

## 💜 Thanks
I express special gratitude to my friends,
GrayCircle and VaneZ, who supported and helped develop
the game all throughout its development
