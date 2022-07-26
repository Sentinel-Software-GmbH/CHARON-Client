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

## Thanks

I started this project as my bachelor thesis and want to finish it as a fully fledged junior developer.
So thanks to all participating parties for providing me with this great opportunity to show that I have it in me.  
You guys rock.

I also want to thank you, the user, to give my measly bachelor project a chance. Any and all feedback is much appreciated.


# Building Tools and small How To:

### CMAKE:
For CMAKE use one of the predefined pattern in your build folder as example:

If you want to build your port in a build folder that is outside your project folder:
```
cmake ../uds_server --preset=Windows    
```
If you want to build your port in a build folder that is inside your project folder:
```
cmake ../ --preset=Windows 
```
The command above causes CMake to configure the windows port as debug build.
Use ninja after configuring CMake to build your desired port.

If you want to switch Ports without deleting the full build folder then follow the steps.

Step 1:
Navigate to your build folder then find and delete the CMakeCache.txt if it exists.

Step 2:
Find and delete the CMakeFiles folder in your build folder if it exits.

Step 3:
Open cmd in your build folder and use one of the pattern below(use the Port you like to build).
The previous steps causes CMake to reconfigure the project and swapping compilers. 
Then use ninja to build.

### Ceedling:
Navigate to the Port folder and use one of the Ports.
Open cmd in the chosen port folder then use "ceedling release" ind your cmd to build .exe or .elf.


### runCharonBuilder:
You can use the runCharonBuilder.cmd to run and configure cmake and ninja for you.
To Use the runCharonBuilder open a cmd in your Project folder and use:
```
runCharonBuilder.cmd --port Windows
```
The command above will create a debug build folder inside your project folder. After that CMake configures everything needed to build the Windows Port,
it will also run ninja.
You can choose between debug and release build, to create a release build use the command below.
```
runCharonBuilder.cmd --release Windows
```
The command above will also create a release build folder.
The command for the other ports are the same as the CMake presets.
If you like you can use:
```
runCharonBuilder.cmd --port unittest
```
This command will create a build folder and run ceedling to create unit tests. 

## Note
All CMake presets containing debug information, if you want a release build you need to use:

```
cmake ../uds_server --preset=Windows -DCMAKE_BUILD_TYPE=Release
```


# Available presets
```
Windows
```
