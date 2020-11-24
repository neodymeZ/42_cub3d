# 42_cub3d

A simple raycasting experiment

*NB: Code is dense due to 42 styling rules (25 lines per function, 5 functions per file, etc).*

## Description

This project demonstrates how a Wolfenstein 3D era raycasting technique allows to build a pseudo-3D environment.

It uses [libft](https://github.com/neodymeZ/42_libft) and [minilibx](https://github.com/pbondoer/MinilibX) libraries (included).

The algorithmic design is based on this tutorial: https://lodev.org/cgtutor/raycasting.html

<img src="demo.gif"/>

## Usage
### To install
```
git clone <repo> <dir>
cd <dir>
make
./cub3d <map>
```

### Controls

<kbd>W</kbd> or <kbd>↑</kbd> - move forward

<kbd>S</kbd> or <kbd>↓</kbd> - move backward

<kbd>A</kbd> - shift left (strafe)

<kbd>D</kbd> - shift right (strafe)

<kbd>←</kbd> - rotate view to the left

<kbd>→</kbd> - rotate view to the right

<kbd>M</kbd> - toggle mouse look

<kbd>L</kbd> - toggle lights (distance-related shadow effect)

<kbd>Esc</kbd> - quit Cub3D

### Maps
Cub3D application loads a map, specified as its argument. Simple maps are included in the `/maps` folder.

Map file should have a `.cub` extension.

Configuration is made by editing several fields on the beginning of the map file:
1. `R` - screen resolution;
2. `NO, SO, WE, EA` - define paths to the north, south, west and east walls 'textures, respectively;
3. `S` - defines a path to the sprite texture;
4. `FT, CT, ST` - define paths to the floor texture and ceiling or sky texture (if CT is specified, it overrides ST);
5. `F, C` - define floor and ceiling colors (in RGB), if no textures are specified.

After the configuration, the map is drawn in the file using the following notation:
1. `N, S, W, E` - define the player location and orientation (only 1 per map is allowed);
2. `0` - define an empty space within the map;
3. `1` - define a wall;
4. `2` - define a sprite;
5. `space` - define an empty space outside the map.

The map could be of any shape, not necessarily rectangular. However, it needs to be completely surrounded with walls - i.e. no `0` cell could be a neighbor of `space`.

If `--save` flag is specified, a BMP screenshot of the first frame is saved to the application folder.
