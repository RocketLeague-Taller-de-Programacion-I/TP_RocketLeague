# RocketLeague User's Guide
[Go Back](README.md)
## Welcome to Rocket League!

To get started, you need to install all dependencies used in this project. <br/>

### Step to follow
Open the Ubuntu command line, the Terminal either through the _Ctrl+Alt+T_ 
shortcut or through the Application launcher search.
#### Step One
Clone the repository with [git](https://git-scm.com/doc) In the folder you choose.
```
$ git clone https://github.com/RocketLeague-Taller-de-Programacion-I/TP_RocketLeague.git RocketLeague
```
#### Step Two
Init and update the submodule.
```
$ cd RocketLeague 
RocketLeague$ git submodule init
RocketLeague$ git submodule update
```
#### Step Three
Then build the project.

We will use the [cmake](https://cmake.org/download/) tool to build and compile the project.
```
$ cd RocketLeague
$ mkdir build
$ cd build
build$ cmake .. && make -j4
```
#### Step Four
Start to play between two player.

Init server first.
```
build$ ./server_main <SERVPORT>
```
Then, init two client.
```
build$ ./client_main <HOST> <SERVPORT>
build$ ./client_main <HOST> <SERVPORT>
```