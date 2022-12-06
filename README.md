# Project Rocket League

## Welcome to Rocket League!

In this project, the development of the Rocket League video game in its 2D version was carried out. <br/>

[Directives](https://docs.google.com/document/d/1ydDQTjWoBjPnxWz0Sg475QeaCKU-irbYuRWb0VkcJ2o/edit?usp=sharing).

Developers:
* [Sprenger, Roberta](https://github.com/robyspr)
* [Cuppari, Franco](https://github.com/francupp9-12)
* [Waisten, Lucas](https://github.com/LucasWaisten)

## Supported Platforms and Tools
### C++ Support

| Dimension   | Supported Version | 
|-------------|-------------------|
| Ubuntu      | >= 18.04          |
| C++ Version | >= 17             | 
| CMake       | >= 3.16           | 
| GCC         | >= 7.3.1          | 
| Catch2      | >= 1.11.0         |
| Box2D       | >= 2.4.0          |
| libSDLpp    | >= 0.17.0         |

## Getting Started

See the [RocketLeague User's Guide](UserGuide.md) for
documentation.

How to play, see in [Manual Game](Manual.md)
## For Development
The proyect nose que [RocketLeague Code Documentation](CodeDocumentation.md)

## Features
* ### Car:
*  **Jump**: jump and double jump.
*  **Flips**: both sides.
*  **Shots**:
-  **Purple Shot**
-  **Gold Shot**

* ### Game
  - **Duration**
  - **Stats**

  - **Scene**

  - **Camera**

  - **Repeat**

  - **Collisions**

* ### GUI:

  -  **Score**

  -  **Time**

* ### Animation

  -  **Car movements**.
  - **Ball spin**

* ### Sound

  -  **Ambience Music**
* ### Configuration


  Macros in Match.cpp:
  - GRAVITY,
  - TIME_TO_PLAY


  Macros in Car.cpp:
  - FLIPYHEIGHT
  - ONEJUMP
  - ONEJUMPFORCE
  - TWOJUMPFORCE
  - XFORCE
  - TURBOXFORCE


  Macron in ball.cpp:
  - BALL_RESTITUTION

* ### Tests

  - a) **Server Protocolo**

  - b) **Cliente Protocolo**

  - c) **Manejo de partidas**

* ### Documentation

  - a) **User's Guide**

  - b) **Documentation Development**

  - c) **Project Manual**