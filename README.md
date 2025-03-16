# Autonomous Newbie Project

## Table of Contents
1. [Introduction](#intro)
2. [Installation](#installation)
3. [Tasks](#tasks)
4. [Project Tree](#project-tree)
5. [Contact Details](#contact-details)



## Intro
In the Autonomous subgroup you will be required to independently plan and
develop programs requiring knowledge outside the scope of your university learning. As
such we emplore you to employ critical reasoning and research to help guide your
development. This project will expose you to ROS 2 (Robot Operating System 2), a
middleware underpinning the majority of development within our team. Using which
you will create a **velocity controller** that subscribes to coordinates and
responds with velocity controls in order to reach a desired moving target point.

You are allowed to ask Autonomous senior members for logistical help (Setting up
your development environment), or guidance if you are truly stuck. However, we
ask that people work independently and refrain from collaborating with others.
This is ultimately a final assessment of applicants' own abilities.   

### Key outcomes:
-	Demonstrate programming competency.
-	Demonstrate the ability to learn new concepts.
-	Demonstrate ability to commit required work hours.

## Installation
Follow the appropriate installation method for your operating system on the
official ROS2 Humble docs:
https://docs.ros.org/en/humble/Installation.html


## Tasks
### Part 1:
**This project relies heavily on basic knowledge of ROS2 concepts**. Before you
start you must complete the beginner tutorials also provided on the official
ROS2 Humble Documentation.

### Part 2:
Provided in the install folder is a ROS2 package
(autonomous_take_home_projest_runner)  with the *runner* executable. You will
use this to publish data which your node will subscribe and respond to.
To run the data runner you need to source the installation folder:

At the root of the project directory run:
```bash
source ./install/setup.bash
```
Then lauch the node using:
```bash
ros2 run autonomous_take_home_projest_runner runner data.csv
```
This will run for around 11 seconds.
practice using the CLI commands to analyse the messages being published.

### Part 3:
Create a node to subscribe to the published topic and calculate characteristics
of the target location's motion. These should then be published on the
'response' topic using the '/msgs/response' message, under the 'target' attribute.

### Part 4:
The 'target_location' data is meant to represent a desired position the vehicle
routes to. You can imagine it is produced by path planner designed that
inexplicably provides erroneous data from time to time. You must, classify and
filter erroneous 'target_location' data, that does not adhere to the feasibility
conditions, listed in the handout. Publish the *last valid target location*
under "Response.lvtl".

### Part 5:
Simulate the kinematics of a vehicle using a unicyle model that tracks the
*target location*. The vehicle should only be allowed to moved forwards and
turn. Lateral movement is not valid. Publish these values under
"Response.vehicle". You will also need to publish the point that the vehicle is
current navigating to on "Response.target_location".

## Project tree
 * [install](./install) 
   * [autonomous_take_home_project](./install/autonomous_take_home_project) (your
     install location)
   * [autonomous_take_home_project_runner](./install/autonomous_take_home_project_runner) 
     (test runner binaries)
   *  [msgs](./install/msgs) (custom ROS2 messages install location) 
   *  [setup.*](./install/setup.sh) (environmnet setup scripts) 
 * [src](./src)
   * [autonomous_take_home_project](./src/autonomous_take_home_project)
     (your package to make)
     * [CMakeLists.txt](./src/autonomous_take_home_project/CMakeLists.txt) (update
       with build process) - ask for help if needed
     * [package.xml](./src/autonomous_take_home_project/package.xml) (update with dependencies)
     * [include](./src/autonomous_take_home_project/include) 
       * [autonomous_take_home_project](./src/autonomous_take_home_project/include/autonomous_take_home_project) (any includes you
       share between source files)
     * [src](./src/autonomous_take_home_project/src) (your source code)
       * [main.cpp](./src/autonomous_take_home_project/src/main.cpp) 
   * [msgs](./src/msgs) (custom ROS2 messages package)
     * [msg](./src/msgs/msg)
       * [LocationStamped.msg](./src/msgs/msg/LocationStamped.msg)
       * [Response.msg](./src/msgs/msg/Response.msg)
       * [Kinematics.msg](./src/msgs/msg/Kinematics.msg)
     * [package.xml](./src/msgs/package.xml) (don't touch)
     * [CMakeLists.txt](./src/msgs/CMakeLists.txt) (don't touch)
 * [data.csv](./data.csv) (simulation data)

Your ROS2 Node should be written in the
[./src/autonomous_take_home_project/src](./src/autonomous_take_home_project/src)
folder. When built using *colcon*, package binaries will appear under
[./install/autonomous_take_home_project](./install/autonomous_take_home_project).


The package provided is a stand in for a C++ package. It has not been properly
configured with the correct dependencies and will not build if you attempt to include
using any libraries. Delete and recreate it if you wish to create your node
using python.
The msgs package must be made a dependency of your package, you will learn how to do
this using the provided tutorials. The runner is built to communicate with the
msgs provided in the handout msgs package. 

To be able to run your executable you will need to ensure you have *sourced* the
package.

eg:<br>(Linux)
```bash
source ./install/setup.bash
```

When you wish to test the functionality of your node make sure to run your
node in one terminal, and then in a second terminal run the runner (remember to
source the workspace in both).

### Setup help for windows users:
We recommend using *Windows Subsystem for Linux* (WSL). Please refer to this guide
by Microsoft for installation:
https://learn.microsoft.com/en-us/windows/wsl/install