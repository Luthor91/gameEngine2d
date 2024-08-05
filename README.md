# Game Engine 2D

## Introduction

Welcome to the Game Engine project! This engine is designed to provide a robust and flexible library for developing 2D games and apps in C. It includes features such as sprite rendering, basic animations, and simple physics.

The engine is designed to be easy to use and understand, with a simple API that allows developers to easily create games and apps, even if it's for C projects only so good luck.

The informations below are maybe incompletes, I try to maintains this documentation up to date but it's pretty complicated, that's why some words are in Baguette language.

## Features

- **Display Image**: Efficient rendering of 2D images.
- **Display Animation**: Support for sprite animations.
- **Basic Physics**: Simple physics simulation for game objects.

## Structure

- **Assets**: Contains basic assets for tests, including pictures and font.
- **Examples**: Contains tests functions.
- **Outils**: Contains useless files to monitoring and calculate performances of the engine.

## Core
Contains all the logic of the engine.
- **Animation**: 
  - All handlers for animations, including starting, looping, and updating animations. Stopping in WIP.
- **Events**: 
  - Manages user input and other event handling within the engine.
- **Font**: 
  - Handles text rendering using different fonts.
- **Graphics**: 
  - Manages the loading, rendering, and manipulation of graphical assets.
- **Physics**: 
  - Provides basic physics simulation including applying forces and impulses.
- **Renderer**: 
  - Manages the rendering pipeline, including rendering order and optimization.
- **Shape**: 
  - Handles geometric shapes, useful for collision detection and simple rendering.
- **Spatial**: 
  - Manages positionning of every objects.
- **Tilemap**: 
  - Supports the creation and management of tile-based maps.
- **UI**: 
  - Provides a framework for user interface elements such as buttons, grids, and soon progress bars.
- **Utilities**: 
  - A collection of helper functions and utilities to support the engine's functionality.

## Current Tasks

- **Simplifying Positionning**: SImplifying the pseudo-CSS created to help positionning UI elements
- **Events and Rendering**: Both are already functionnal but we maybe need to simplifying the writing of those functionnality
- **Rendering Optimization**: Optimize the rendering procedure for better performance.

## Planned Features

- **Texture Clipping**: Support for clipping textures into precise shapes.
- **Collisions**: Implement collision detection.
- **Simplified Positioning System**: A straightforward system for positioning game objects.
- **Sound**: Integrate sound effects and music.
- **UI System**:
  - Rows
  - Columns
  - Grid
- **Progress Bar**: Display progress bars.
- **Raycast**: Implement raycasting for various purposes.
- **Dialogue Manager**: Manage in-game dialogues.
- **Custom Data Storage**: Utilize a custom system for data storage.
- **Shader**: XX.


## Installation

### Prerequisites

Before you begin, ensure you have met the following requirements:

- **Operating System**: Windows, Linux, or macOS
- **Compiler**: GCC, MinGW, or any C compiler
- **Dependencies**: SDL2, SDL2_image, SDL2_ttf

### Windows 10 (Recommended to use WSL)

For now, it's heavily recommended to skip steps 1 and 2, I have some troubles to installs dependencies on windaube.

1. Install [Chocolatey](https://chocolatey.org/install).

2. Install dependencies using Chocolatey:

    ```sh
    choco install make
    ```

3. It is recommended to use WSL (Windows Subsystem for Linux) with Ubuntu for better compatibility. Install WSL and Ubuntu:

    - Open PowerShell as Administrator and run:

        ```sh
        wsl --update
        wsl --install -d ubuntu
        ```

    - Set up your Ubuntu user and password after the first launch.

4. Open Ubuntu in WSL and navigate to your project directory:

    ```sh
    cd /mnt/c/path/to/your/project
    ```

5. Install dependencies on Ubuntu:

    ```sh
    sudo apt update
    sudo apt install git make
    ```

6. Clone the repository:

    ```sh
    git clone https://github.com/luthor91/gameEngine2d.git
    cd gameEngine2d
    ```

7. Build the project:

    ```sh
    make linstall
    ```

### Linux

1. Install dependencies:

    ```sh
    sudo apt update
    sudo apt install git make
    ```

2. Clone the repository:

    ```sh
    git clone https://github.com/luthor91/gameEngine2d.git
    cd gameEngine2d
    ```

3. Build the project:

    ```sh
    make linstall
    ```

### Arch Linux

1. Install dependencies:

    ```sh
    yay -Syu git make
    ```

2. Clone the repository:

    ```sh
    git clone https://github.com/luthor91/gameEngine2d.git
    cd gameEngine2d
    ```

3. Build the project:

    ```sh
    make ainstall
    ```

## Running Test Codes

After building the project, you can run the test codes. Note that test codes are available only for Linux and Arch:

- **Window Test**: 

    ```sh
    make lt_window
    ```
    This code will only display a very ugly windows with a simple background

- **Animation Test**: 

    ```sh
    make lt_animation
    ```
    This code will display a single black box going through multiple locations.

- **Sprites Test**: 

    ```sh
    make lt_sprites
    ```
    This code will display multiple images.

  
- **Interface Test**: 

    ```sh
    make lt_interface
    ```
    This code will display some UI elements such as button, widget, image and input fields.

## Usage

To use the game engine in your C project, link against the library and include the necessary headers.
