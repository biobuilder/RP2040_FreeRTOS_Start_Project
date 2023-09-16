This is the starter FreeRTOS c/c++ code repository for the RP2040 board using Visual Studio Code on Windows.
These instructions are specifically designed to pair Visual Studio Code with the Pico Debug Probe.  

This repository includes everything needed to get up and going without having to clone the entire FreeRTOS Kernel to each new repository.
The trick is to point CMake to the FreeRTOS Kernel source folder, which is located somewhere else on your machine.
Visual Studio Code must be run with the pico-prefix (on windows) or with the proper directives in CMake to access the Pico SDK.  
The main FreeRTOSConfig.h configuration is local to the project itself, so you can configure the RTOS for each specific project.

An integrated development environment allows you to write code, compile it and debug it all in the same place.  With great difficulty, Visual Studio Code can be fangled into this configuration.  Warning: coding the RP2040 through Visual Studio Code with the Pico debugger in Windows is a real bugger.  You'll spend a lot of hours debugging the environment - but once it is set up, you'll benefit from an excellent code editor and debugging tool. 


Installing the integrated development environment package (Visual Studio Code):
1. Download and install the "pico-setup-windows-x64-standalone.exe" from Raspberry Pi Foundation
 - The specific url is located here: "https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe"
2. When you start Visual Studio Code, type "pico" in the search bar and pick the "pico - Visual Studio Code" shortcut
 - This initializes Visual Studio Code with a bunch of different parameters so that you can use the Pico Debug Probe to upload / debug in real time
3. Plug in your Pico Debug probe and attach it to the target microcontroller
4. Make sure the Serial Wire Debug pins are attached (SD, SC, and Ground)
 - Review https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html
5. Optionally, hook up the UART pins to inspect characters coming in over the hardware serial port
6. The Pico Debug Probe has a UART to USB converter, which you may view by selecting the proper COM port in the Serial Monitor tab down on the bottom of Visual Studio Code after compiling the code

Setting up FreeRTOS:
1. Clone (download) the FreeRTOS Kernel to some folder on your computer (https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/main)
2. Copy the absolute path to this kernel (i.e. "C:/path/to/FreeRTOS-Kernel)
3. Update "CMakeLists.txt" in the top-level folder of your main code repository to include this path
 - The specific line reads: "set(FREERTOS_KERNEL_PATH "C:/path/to/FreeRTOS-Kernel" CACHE PATH "Path to the FreeRTOS Kernel")"

Debugging / Compiling / Uploading the code:
1. Clone (download) this starter code repository into some folder on your computer.
2. When first setting up the repository, or when copying it, you may need to delete the Build folder before it will compile successfully.
3. You may need to Configure the project. Ctrl + Shift + P and then run CMake: Configure.
 - Sometimes, this doesn't work.  So if you get hung up anywhere, you may need to Delete Cache and Reconfigure.  Run CMake: Delete Cache and Reconfigure.  
4. You may need to set the Kit in Visual Studio Code the first time
 - Ctrl + Shift + P -> CMake scan for kits
 - Then, Ctrl + Shift + P -> CMake select kit
    * select PICO ARM GCC or GCC 10.3.1 arm-none-eabi
5. Then, navigate to any of the source files (ending with.c) or go to the debug tab on the left toolbar
6. Pick "Pico Debug Cortex Debug" and upload to the attached RP2040
 - Visual Studio will ask you which target to build
 - You can either build everything or you can build the project executable target (it's the name specified by the source folder, or custom name you gave it)
7. Binaries will be generated in the "Build/src/" folder
 - The binary file ending with ".elf" is a debug binary
 - The binary file ending with ".uf2" is the main runtime binary
8. Hit Debug and select the Pico Debug option
  - When you're done debugging, click the square on the top to stop the debugger
  - Resetting (power cycling) the Raspberry Pi after debugging allows code execution to continue
9. Optionally, the code can be uploaded directly to the RP2040 over USB
 - Hold Bootsel and attach the RP2040 to the computer via USB
 - A folder will pop up on the host computer
 - Copy and paste the compiled binary ending with ".uf2" into this folder
 - The RP2040 will begin to execute the code

Adding to the code:
When creating a new source code folder, such as for a library, you have to tell CMake that these files exits.  Edit the following files:
1. CMakeLists.txt in the overarching directory folder must include the new subdirectory
  e.g. "add_subdirectory(mylibrary)"

2. CMakeLists.txt in the source directory must be updated 
  - add all the source files\
    e.g. "set(  SOURCE_FILES\ 
               main.c\
               application.c\
               ../somelibrary/somefile.c\
               )"
  - add all the pertinent directories to this particular target\
  e.g. "target_include_directories(${PROJECT_NAME}\
                                  PRIVATE ${CMAKE_CURRENT_LIST_DIR}\
                                  PRIVATE ../somelibrary/somesubfolder\
                                  )"\

CMake is very tedious and there are about 30 different ways to accomplish the same result.  Make sure that you are explicit with your code or else CMake will refuse to link the code together into a coherent structure.  


Sharing with Source Control:

When cloning your project to a new machine, or when changing the source file for the FreeRTOS Kernel, CMake must be pointed to the new source code of the FreeRTOS Kernel.
The only working method so far on this Windows machine is to add the definition explicitly in CMake:
 - From within the top level CMakeLists.txt, add the following line:
 set(FREERTOS_KERNEL_PATH "E:/path/to/FreeRTOS-Kernel" CACHE PATH "Path to the FreeRTOS Kernel")
Adding an additional build argument in CMake Settings does not seem to be working:
-DFREERTOS_KERNEL_PATH="E:/path/to/FreeRTOS-Kernel"
The Set Build Environment in CMake Tools settings (in Visual Studio Code) does not seem to be working:
  example: FREERTOS_KERNEL_PATH E:\path\to\FreeRTOS-Kernel

When working on a shared repository, tell GIT to ignore the highest level CMakeLists.txt file so that the CMake FreeRTOS Kernel file path will remain local

You may also want to git ignore the entire Build folder.

The FreeRTOSConfig.h file must be included somewhere in your project.  The compiler finds this through the variable FREERTOS_CONFIG_FILE_DIRECTORY.
This variable is defined in the top level CMakeLists.txt.  Edit this variable if you wish to move FreeRTOSConfig.h somewhere else.

Sometimes, you may wish to build separate sub projects within this main project folder.  You'll need to add the folder, a new CMakeLists.txt, add a new subdirectory() in your top level CMakeLists.txt, so on and so forth.  CMake needs you to tell it everything.  
When building a new subproject (such as another project within a sub folder), set the compiler target to the project you wish to debug\
  Ctrl + Shift + P -> CMake: Select Build Target\
  Ctrl + Shift + P -> CMake: Select Debug Target\
    - Can optionally select the entire repository as build targets, but this may take a long time\

Sometimes, build errors are present with CMake, especially when you change the name of higher level folders.  To get rid of these errors, delete the entire Build folder which erases cached data.  You may also run the CMake command: Delete Cache and Reconfigure.  There are so many chached and hidden variables in CMake that it can easily get confused and quit working.  Reconfiguring and deleting these caches may help resolve unknown build errors with CMake.  If you can't make it work, you may need to reinstall everything from scratch.  Make sure to delete all of the cached files from Visual Studio Code's AppData cache.  The system holds a lot of promise but is very tedious and cryptic.  

If you get the following error:

error: internal malfunction: bad programmer detected.\
setting global environment variable WILL_NOT_WORK to True.\ 
 -> have you tried plugging the schnitzelfritz into the gomberwhopper?\
 -> did you forget to include the <internal_obfuscator_cache>?\
 -> have you considered another field of expertise?\

Don't let it make you quit, you will get it eventually.  This basic repository took 30 hours to set up - spend more time coding and less time messing around with the environment.  Or try your luck with another IDE / operating system / compiler.  Good luck. 
