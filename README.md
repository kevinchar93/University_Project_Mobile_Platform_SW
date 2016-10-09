# Onboard Robot Software (Final Year Project)
This repo is one of a number from my final year project at university. This in particular is for the software that runs on the robots microcontroller. More specific details about the project and the Onboard Software in particular can be found below.

<p align="center">
<img src="https://github.com/kevinchar93/University_Project_Grid_Loclisation_App/blob/master/robot1.PNG" 
alt="The Complete Robot" width="480" height="345" border="10" />
</p>

### About the Project
My final year project at university was inspired somewhat by my placement year where I worked on programming embedded systems in the form of TV set top boxes, having had this experience I decided to work on a project that dealt with some form of embedded system. In the end I decided to construct and program a robot capable of localising itself in two dimensions.

By the end of the project I'd encountered issues that made me scale down the project. Ultimately I produced a robot that is capable of localising itself in only one dimension, however another piece of software which presents a simple simulation of two dimensional localisation was implemented instead.

The project report titled "[**An Implementation of a Mobile Robot with Localisation Capabilities**](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/blob/master/An%20Implementation%20of%20a%20Mobile%20Robot%20with%20Localisation%20Capabilities.pdf)" can be found in the root directory of this repo.

In total for the project 4 deliverables were created (links to repos in brackets):
* The actual physical robot
* The software on the robot's embedded platform ([Mobile Platform SW](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW))
* Software used to control the robot remotely & estimate its position ([Grid Localisation App](https://github.com/kevinchar93/University_Project_Grid_Loclisation_App))
* A two dimensional Monte Carlo localisation simulator  ([Particle Filter Simulator App](https://github.com/kevinchar93/University_Project_Particle_Filter_Simulator_App))

## Video of Robot in Action
<p align="center">
<a href="http://www.youtube.com/watch?feature=player_embedded&v=uaJJufRfOmI
" target="_blank"><img src="http://img.youtube.com/vi/uaJJufRfOmI/0.jpg" 
alt="Zumo Robot in Maze" width="620" height="400" border="10" /></a>
</p>

### More about the Onboard Software

More specifically "Onboard Software" is the program that runs on the robots Arduino Mega micro controller, its purpose is to receive commands from another [piece of software](https://github.com/kevinchar93/University_Project_Grid_Loclisation_App) running on a remote laptop and controll the robot accordingly. The onboard software was broken down into modules each with a specific role.

| Module     | Role                                                                                                                                                                                                                                                                                                                |
|------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [Core](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/blob/master/main_mob_platform/src/main_mob_platform.ino)       | Acts as the “glue” module, it is responsible for the overall functioning of the robot. It runs the main loop that receives, processes and executes commands using functionality provided by the other modules                                                                                                       |
| [DiffDrive](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/tree/master/main_mob_platform/lib/DiffDrive)  | Provides access the robots locomotive capabilities, it has methods that take motion commands and synchronises the robot’s drive motors to move the robot to a desired position.                                                                                                                                     |
| [Lidar360](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/tree/master/main_mob_platform/lib/Lidar360)   | Provides access to the distance measurement capabilities of the robot. The module can be instructed to spin the LIDAR to a certain heading to take a measurement or take an entire 360° sweep of measurements.                                                                                                      |
| [Common](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/tree/master/main_mob_platform/lib/Common)     | Provides common functionality used throughout multiple modules in the software. It defines the instruction set the robot can perform, defines data types to be used by other modules and provides a single place to give named definitions to individual pins on the control board according to what their role is. |
| [RemoteComm](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/tree/master/main_mob_platform/lib/RemoteComm) | Responsible for establishing a connection to a remote computer using Bluetooth, and sending or receiving data on the connection once it is established.                                                                                                                                                             |

The robot’s software is based on the three-layer architecture with an implementation of a remote fetch-execute cycle, the executive and reactive layers reside in the on-board software and it uses a fetch-execute cycle to get and execute remote instructions sent to it, the **Core** module facilitates all of this.

The Core module begins by calling the “init” methods for all modules, these methods set the pins and settings each module will use. Core then waits for the user to verify that the LIDAR output on the LCD looks okay (the module may need resetting rarely) and press the continue button (A), the zero position of the LIDAR can then be set using the A (confirm) and B (spin right) buttons. Once the LIDAR is zeroed, the robot waits for a connection from the control software, when connected the instruction fetech-execute cycle begins. The diagram below illustrates this cycle:

<p align="center">
<img src="https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/blob/master/instruction_cycle_img.png" 
alt="The Onboard Software's Fetch Execute Cycle" width="811" height="958" border="10" />
</p>

See the report "[**An Implementation of a Mobile Robot with Localisation Capabilities**](https://github.com/kevinchar93/University_Project_Mobile_Platform_SW/blob/master/An%20Implementation%20of%20a%20Mobile%20Robot%20with%20Localisation%20Capabilities.pdf)" for more details.

## License

Copyright © 2016 Kevin Charles

Distributed under the MIT License
