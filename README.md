# Mainpage {#mainpage}

Charon UDS Client
==================

Hello and Welcome to the Charon UDS Client Documentation!  
If you are reading this, chances are that you want to implement Charon into your Software, and I'm really glad about that!

Charon stands for **C** ar **H** ealth **A** nalyze **R** ealtime **O** nboard **N** etwork.  
It means, that we want to provide an quick, easy and lightweight way to implement the UDS Standard into your Automotive Application.

Note that the Charon UDS Client is marked as a Work In Progress and that there still might be some Bugs in the Code, or Functions that are not implemented yet.

## Usage

To use the Charon UDS Client you need to set up a few things:

First, you need to provide valid implementations of at least the @ref ComInterface and the @ref TimerInterface Objects.
These are needed to let the Charon UDS Client communicate with the Hardware you want to use.
After that, include the UDSClientLib.h Header-File into your application, and feed the Interfaces you implemented and a uint8_t receive Buffer into the UDS_Init() Function and you are good to go.
With the inclusion of the Header-File you automagically are provided with all functions of the Business Logic of UDS, so send away all those requests, you might have for the Charon UDS Server.

The Client itself is meant to be used in cooperation with the Charon Server - also here on github [LINK](https://github.com/Sentinel-Software-GmbH/CHARON-Server).
UDS is a Standard based in automotive to fullfill certain services that are widespreadly used and normalizes them.
Like:
 - Bootlaoder / Update (over the air)
 - Parameter and Persistent Data Management
 - Error Logging
 - Basic Comunication Safety and Security
 - Runtime Execution
 - EOL Adaption
 - etc...

## Thanks

I started this project as my bachelor thesis and want to finish it as a fully fledged junior developer.
So thanks to all participating parties for providing me with this great opportunity to show that I have it in me.  
You guys rock.

I also want to thank you, the user, to give my measly bachelor project a chance. Any and all feedback is much appreciated.


# Building Tools and small How To:

## Tools:
### required Tools in Path:
```
CMake 
Ninja
GNU gcc for Windows
ARM NONE EABI GCC
```
use the compiler based on your target port

### optional Tools in Path:
```
Ruby
Ceedling
Python
Doxygen
HTMLHelpCompiler
CPPcheck
(Graphviz) DOT
```
for automatic build tool and unit tests.

## How To:

### CMake:
Required Tools in Path:
```
CMake
Ninja
GNU gcc for Windows
ARM NONE EABI GCC
```
For CMake you have to create a build folder. After that you can use one of the predefined patterns in your build folder:

If you want to build a Charon port in a build folder that is created outside your project folder:
```
cmake ../uds_server --preset=windows    
```
If you want to build a Charon port in a build folder that is created inside your project folder:
```
cmake ../ --preset=windows 
```

The commands above causes CMake to configure the Windows port as a debug build.
Use Ninja after configuring CMake to build your desired port.

If you want to switch ports without deleting the full build folder then follow the steps below.

Step 1:
Navigate to your build folder then find and delete the "CMakeCache.txt" if it exists.

Step 2:
Find and delete the "CMakeFiles" folder in your build folder if it exits.

Step 3:
Open CMD in your build folder and use one of the patterns below (use the port you like to build).
The previous steps causes CMake to reconfigure the project and to swap compilers. 
Then use Ninja to build.

### Ceedling:
Required Tools in Path:
```
Ruby
(Ceedling)
GNU gcc for Windows
ARM NONE EABI GCC
```
You can also use Ceedling to build unit tests and the supported Charon ports.
To build a port, navigate to the port folder and use one of the ports.
Open CMD in the chosen port folder then use ```ceedling release```  in your CMD to build .exe or .elf.
To build unit tests, open CMD in your project folder and use ```ceedling.cmd``` . 

### runCharonBuilder:
You can use the runCharonBuilder.cmd to run and configure CMake and Ninja for you.
To use the runCharonBuilder, open a CMD in your project folder and use:
```
runCharonBuilder.cmd --help
OR
runCharonBuilder.cmd -h
```
The command above will show an overview for all possible commands.
```
runCharonBuilder.cmd --windows
OR
runCharonBuilder.cmd -w 
```
The command above will create a debug build folder inside your project folder. 
After that it will configure CMake for the Windows port, it will also run Ninja.
You can choose between a debug and a release build.
To create a release build, use the command below.
```
runCharonBuilder.cmd --windows --release
OR
runCharonBuilder.cmd -w -r
```
The command above will also create a release build folder.
The commands for the other ports are the same as the CMake presets.
If you like you can use:
```
runCharonBuilder.cmd --tests
```
The command above will create a build folder and run Ceedling to create unit tests. 
```
runCharonBuilder.cmd --demo/-d
```
The command above will create a debug build folder inside your project folder based on the Windows port. 
After that it will configure CMake for the Demo port, it will also run Ninja.
It is also possible to chain commands of the same build type like the command below.
```
runCharonBuilder.cmd -w -d 
OR
runCharonBuilder.cmd -w -d -r
```



### CppCheck
Required Tools in Path:
``` 
cppCheck
Python 
(Python package Pygments)
```
To run CppCheck on charon files you can use the codeanalysis.bat.
At the current state the analysis will only apply to the following files and folders:
```
Include
src
port/windows/src
port/stm32f4-discovery/Src
port/stm32f4-discovery/Inc
```
The following files and folders will be ignored:
```
port/stm32f4-discovery/Src/stm32f4xx_hal_msp.c 
port/stm32f4-discovery/Src/stm32f4xx_it.c 
port/stm32f4-discovery/Src/system_stm32f4xx.c 
port/stm32f4-discovery/Inc/stm32f4_hal_conf.h 
port/stm32f4-discovery/Inc/stm32f4_it.h
```
To change or add new folders or files to analysis modify the codeanalysis.bat.
The Batch file will also use a python script to generate HTML file as reports.  
You can find the analysis report in the folder ```build\cppCheckReport\index.html```.   
  

### Doxygen 
Required Tools in Path:
```
Doxygen
HTMLHelpCompiler
(Graphviz) DOT
```
To generate Doxygen documentation you can use the documentation.bat.
At the current state the documentation contains all files in the following folders:
```
src 
include 
README.md 
port\windows\src 
port\windows\config 
include 
port\stm32f4-discovery\Src 
port\stm32f4-discovery\config 
documentation
```
Unit Tests are not documented.
You can find the documentation in the folder ```build\documentation\Charon_UDS_Server```.

## Note
The available preset for CMake can be found in the CMakePreset.json file. 
If you want to add an other preset please use the existing one as template.

All CMake presets containing debug information, if you want a release build you need to use:
```
cmake ../uds_server --preset=Windows -DCMAKE_BUILD_TYPE=Release
```

## Demo
For an easy overview what our Charon UDS Client is capable of, simply build the DEMO build on Client and Server.
To start: execute the Charon Server executable and after that execute the Charon Client executable which are results of the demo build.
Now you can navigate your way through the demo terminal and explore DTC and DID subfunctions with an interface.

Server side will fill the dummy data into the NVM emulator, response to the Client request and handles intern data.
Just like any port will work.

# Available presets
```
windows
demo
```
