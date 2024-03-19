# 2048_Game
 Text-Based 2048 Game in C!
 ## Starting the Game:
 - Download the repository to your computer
 - Find the folder through your terminal \n
   (*You can use the* `cd "folder location"` *command to get there in terminal*)
 - Type `make` into the terminal to run the game
   
 ## How to Play:
 - Use WASD to shift the cells up or down
 - Press Q to Quit and N to start a new game
 - The goal is to get one cell to the value 2048
 - Have fun!

 ## Errors:
 - If you are experiencing an error on a Windows or Linux device, try changing the following line in main.c
   `#ifdef __APPLE__`
 - APPLE is the platform macro for MacOS
 - Change to `_WIN32` or `_WIN64` based on your Windows system
 - Change to `__linux__` for a Linux device
