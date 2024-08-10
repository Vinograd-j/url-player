# This is the URL-PLAYER

### You can use this program to listen to music from YouTube without going to YouTube itself.

------------

# !!!
#### *The program does not download anything, does not violate anyone's rights, it simply structures your compositions in the form of a list and helps you open them and listen to them in the background*

#### *The program is made using graphic libraries that involve design by code. Therefore, the design will be quite primitive. I count on your understanding.*
------------

### How to build this project from sources:

You should **download** and **build** two libs: [SFML](https://www.sfml-dev.org/download/sfml/2.6.1/ "SFML") and [TGUI](https://tgui.eu/download/ "TGUI")

Next, build a CMake project using this flags:  `-DSFML_PATH` - To specify the path in which SFML is built, **AND** `-DTGUI_PATH` - To specify the path in which SFML is buit.

Then you can compile this project. 

#### What i used:
**Compiler**: [MinGW x32](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-i686-posix-dwarf-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z "MinGW x32 link")

**Generator**: MinGW Makefiles

#### Pay attention!
[SFML](https://www.sfml-dev.org/download/sfml/2.6.1/ "SFML") requests a compiler version specific to it. Check on the SFML website when downloading. Otherwise, the project will not build. I recommend using one version of the compiler for the entire project. You can use compiler I have mentioned above for **SFML 2.6.1**

------------



## What it looks like:

#### Main menu:
![image](https://github.com/user-attachments/assets/b5c2034e-0ea6-4e2b-8c0d-4f34b366aa39)

#### Menu for adding new song:
![image](https://github.com/user-attachments/assets/a61bdaab-dc97-4376-a16a-34045fe10390)

#### Song deletion dialog window:
![image](https://github.com/user-attachments/assets/f291b3fc-4df6-4652-ad3f-800422018738)
