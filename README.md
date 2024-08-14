# This is the URL-PLAYER

### You can use this program to listen to music from YouTube without going to YouTube itself.

------------

## !!!
#### *The program does not download anything, does not violate anyone's rights, it simply structures your compositions in the form of a list and helps you open them and listen to them in the background*

#### *The program is made using graphic libraries that involve design by code. Therefore, the design will be quite primitive. I count on your understanding.*
------------

## How to build this project from sources:

1. Download this repository
2. Create the build directory
3. Call cmake with your generator without flags
4. Compile the project with MSVC (because WebView2 will be assembled with this project, and it requires MSVC)

### What i used:
**Compiler**: MSVC

**Generator**: MinGW Makefiles

### Pay attention!
[SFML](https://www.sfml-dev.org/download/sfml/2.6.1/ "SFML") requests a compiler version specific to it. Check on the SFML website when downloading. Otherwise, the project will not build. I recommend using one version of the compiler for the entire project. You can use compiler I have mentioned above for **SFML 2.6.1**

------------

## What it looks like:

#### Main menu:
![image](https://github.com/user-attachments/assets/b5c2034e-0ea6-4e2b-8c0d-4f34b366aa39)

#### Menu for adding new song:
![image](https://github.com/user-attachments/assets/a61bdaab-dc97-4376-a16a-34045fe10390)

#### Song deletion dialog window:
![image](https://github.com/user-attachments/assets/f291b3fc-4df6-4652-ad3f-800422018738)
