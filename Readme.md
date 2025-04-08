# Readme

# Introduction

This project labeled **ADHD** (*Analog to Digital ~~Time~~ Hour Display*) is a project so dear to our hearts. We  are in fact the second generation that got it and tried to implement it after taking the torch from our collegues from the MAIN (Comptuer Science and Mathematics) specialty.

To sum it up roughly, this project aims to use analog clocks and manipulate their hands to get a digital display. 

# Details

Now if you are not interested in the details just feel free to skip ahead, because we are about to dig so very deep in the details. (You have been warned).

Okay. If you stayed then get ready because it is about to get dirty.

So, the ultimate goal for this project is as we said to create an actual **PHYSICAL** system that displays time digitally using analog clocks. More specifically here is our vision:

- **Rectangular 3D printed pieces**: to serve as the clocks hands. their size is yet to determine considering the couple on the motors (more on that later).
- **Dual shaft motors**: with their eventual drivers,  to rotate the hands of the clocks, basically one per clock.
- **Microcontroller boards**: to control the motors/drivers.
- **Microcontroller Development Board**: to control the microcontroller boards.
- **Printed Circuit Boards**: to bring the electronics together.
- **Wooden board:** to serve as the base of the system, its dimensions are yet to be determined considering those of the 3D printed pieces above. It is going to be carved from the back to hold the electronics (motors and company), from the front to delimit the space occupied by each clock and its hands, painted and varnished to look cute 😊.

To be even more precise here is what we were aiming to use:

- **Rectangular 3D printed pieces**:
    - Number: 48
    - Color: White (#FFFFFF)
    - Material:  ****Polylactic Acid (PLA)
    - Dimensions: 4 x 1 x .1 cm (1.58 x .4 x .04 in for our freedom language speakers)
- **Dual shaft motors**:
    - Number: 24
    - Reference: VID28
    - Datasheet: https://cdck-file-uploads-europe1.s3.dualstack.eu-west-1.amazonaws.com/arduino/original/3X/b/0/b0aa1434329fd55ba59f10d853612d71be1a5b07.pdf
- **Microcontroller boards**:
    - Number: 10
    - Reference: Raspberry Pi Pico
    - Datasheet: https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html
- **Microcontroller Development Board**:
    - Number: 1
    - Reference: Raspberry Pi 0 W
    - Datasheet: https://datasheets.raspberrypi.com/rpizero2/raspberry-pi-zero-2-w-product-brief.pdf
- **Wooden board**:
    - Number: 1
    - Color: Wood (#A1662F)
    - Material: Wood
    - Dimensions: 90 x 40 x 7 cm (35.4 x 15.7 x 2.75)

As you might have noticed this list of material is designed for a 8 x 3 clocks display (which is actually the minimum allowed by logic) but it is obviously scalable (to double the size for example 16 x 6 clock display).

Now with the list of material needed we can move on to the implementation.

For this part, we thought about dividing the work into two major parts:

## Simulation

Before starting to build the actual physical system, we tried to use a simulator to make sure that everything works just fine.

This part constitutes 90 % of our work. And here’s the idea behind it. We devide the simulation into two parts:

- Receptor
    
    This part will simulate our system. With a window containing the 24 clocks with two hands each waiting for instruction on the angles to then turn those angles into a number of steps and then move according to the logic of the mototrs used.
    
- Supervisor
    
    This one will simulate the master that will be responsible of sending the data with the angles to the simulator.
    

And so, using TCP sockets, SFML graphic library, and many more interesting subtilities, we succeeded to make this simulation. Follow along to know how it works.

## Reality

You guessed it right! The idea was for us to after succeeding to get the satisfying result we have been looking for, then, and only then, will we be able to make a couple of tweaks and adjustments in the codes to then upload them on the boards. 

And this time instead of using TCP sockets we are planning to use I²C communication to spread the payload among the boards.

Now that you have a small idea about what our project is about, tag along to see what we were able to make so far.

# Coding!

Well to begin, start by cloning this repository by running the command

```bash
git clone https://github.com/Midosamaa/Clocks
```

This will get you a copy of the preoject.

Make sure everything is set up by running ths command in the directory where you cloned the project

```bash

tree
```

The output should look like this

```bash
.
├── elec
│   ├── led_control.ino
│   ├── serial.cpp
│   └── simple
│       └── simple.ino
└── simulation
    ├── receptor
    │   ├── communication.cpp
    │   ├── communication.h
    │   ├── main.cpp
    │   └── makefile
    └── supervisor_with_window
        ├── features
        │   ├── Clock.cpp
        │   ├── Clock.h
        │   ├── Hand.cpp
        │   └── Hand.h
        ├── main.cpp
        ├── makefile
        ├── transitions
        │   ├── DigitConfiguration.cpp
        │   ├── DigitConfiguration.h
        │   ├── Transition.cpp
        │   └── Transition.h
        └── type_transitions
            ├── type_transitions.cpp
            └── type_transitions.h
```

If that is the case allow me to enlighten you on what does every folder you see contain.

- elec: this folder contains everything that is related to the real physical system with electronics, boards and so on.
    - led_control.ino: this is the first program we used to test the Raspberry pi pico by controlling the led.
    - serial.cpp:
    - simple
        - simple.ino
- simulation: this folder contains our simulation work as said before.
    - receptor: this is the folder that will simulate the system as we have seen earlier.
        - communication.cpp:
        - communication.h:
        - main.cpp
        - Makefile
    - supervisor_with_window: this folder contains everything necessary for the simulation to run.
        - features: this folder contains the block pieces making our system
            - Clock.cpp:
            - Clock.h:
            - Hand.cpp:
            - Hand.h:
        - main.cpp:
        - makefile:
        - transitions: this folder contains the mechanics of moving the hands according to the logic allowed by the physics of the motors.
            - DigitConfiguration.cpp:
            - DigitConfiguration.h:
            - Transition.cpp:
            - Transition.h:
        - type_transitions: this folder contains the main transitions we implemented.
            - type_transitions.cpp:
            - type_transitions.h:
        

Now that everything is set. We can get to the fun part! Using our simulator.

But before you get too excited get back to your seat and make sure you have all the necessary libraries on your machine.

Run the command 

```bash
sudo apt-get install libsfml-dev
```

This will download the SFML library that we used for this project. And if you are more interested in this library take a peek at their website at https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/.

Well now that your machine is ready, let us get started.

First, go to the directory in which you cloned the repository, and access the supervisor_with_window folder by running the command

```bash
cd simulation/supervisor_with_window
```

Then just in case one of our ✨ brilliant ✨ members pushed before cleaning. Run the command

```bash
make clean
```

And then build the executable by running the command

```bash
make
```

After waiting for a couple of seconds for the compilation to finish you can finally run the simulation.

To do so there is a couple of things you need to know. 

If you know anything about programming, to run the executable you need exactly three arguments besides the latter.

1. Direction: you have to enter the number coresponding to one of these directions
    
    1 : Right to Left
    2 : Left to Right
    3 : Bottom to Top
    4 : Top to Bottom
    
2. Transition type: you have to enter the name of a transition. These transitions are the ones that we implemented in the type_transitions files (keep an ear out, there might be updates in the future).
    - 'pacman': Pac-Man animation eating the old time
    - 'wave'
    - 'stars'
    - 'words'
3. Transition details: for this field you need to fill the details depending on the transition you chose in the second fields.
    - 'pacman'  : transitionDetail = NULL) and Direction is either vertical (2) or horizontal (1)
    - 'wave'    : Wave animation (transitionDetail = number of waves)
    - 'stars'   : Star animation (transitionDetail = number of stars)
    - 'words'   : Temporary word display before showing time (transitionDetail = word to display)

Concretely, here is what your command should look like

```bash
./clock_display 2 pacman NULL
```

or

```bash
./clock_display 4 words "IT IS TIME"
```

or

```bash
./clocks_display 3 stars 4
```

or 

```bash
./clocks_display 1 wave 2
```

And well, that is basically everything we have to present.

A program that shows you the current time, and then when the time changes, you will see the transition you chose before showing the updated time.