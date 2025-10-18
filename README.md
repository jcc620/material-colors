# Material Colors

## About
This project was built to fix a specific need; determining the colors used by 
Omarchy's micro-fork of Chromium for the frame and active tab when the theme 
color is set.

## Installation
This project requires the CMake utility to build. The install script will fetch
dependencies, build the project and copy the executable to `~/.local/bin`.

## Usage
```bash
$ material-colors (primary|secondary) <red> <green> <blue>
```

The red, green and blue values must be integers in the range 0-255. The primary
color corresponds to the 