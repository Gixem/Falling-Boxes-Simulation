# Falling Boxes Simulation

This project is a simple game where the player can shoot bullets to interact with falling boxes. The simulation is created using the ICBYTES library and features basic collision detection, animation, and keyboard handling.

## Features

- **Collision Detection**: 
  - **Left Collision**: When a bullet hits the left side of a box, the box is moved to the top-right corner.
  - **Right Collision**: When a bullet hits the right side of a box, the box is moved to the top-left corner.
  - **Center Collision**: When a bullet hits the center of a box, the box disappears.
- **Keyboard Controls**: Fire bullets by pressing the Space key.
- **Object Animation**: Boxes fall from the top of the screen and reappear at random horizontal positions after reaching the bottom.

## Project Structure

- **Box Struct**: Defines each box's position and visibility.
- **Functions**:
  - `InitializeObjects()`: Initializes positions and visibility for boxes and bullets.
  - `FireBullet()`: Launches bullets from a fixed position when the Space key is pressed.
  - `MoveBullets()`: Updates bullet positions and checks for collisions with boxes.
  - `HandleBulletBoxCollision()`: Handles specific reactions to collisions based on the side of the box that the bullet hits.
  - `AnimateBoxes()`: Continuously moves boxes downward and resets their position when they leave the screen.
  - `GameLoop()`: Main loop that controls the game's logic, rendering, and frame rate.
  - `KlavyeyeBasinca(int k)`: Detects the Space key press for bullet firing.
  - `ICGUI_main()`: Sets up the main GUI, including buttons and the game display.

## How to Run

1. **Requirements**: Install the ICBYTES library and configure your environment to include it.
2. **Build and Run**: Compile and run the program in an environment that supports the required libraries.

## Acknowledgments
- Created as part of a project utilizing the ICBYTES library for GUI and event handling.
