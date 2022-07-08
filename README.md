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


## Bulding Tools:

CMAKE:
For CMAKE use this Pattern in your Build folder:
```
cmake ../uds_client --preset=Windows

```