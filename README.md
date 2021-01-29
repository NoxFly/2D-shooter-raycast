# 2D-Shooter-Raycast

The configuration is set up for Linux environment.

## Execution

On console :

```bash
./run.sh
```

It applies last changes by doing `make` then it executes the generated executable (on `bin/debug/raycast.exe`).

If you want to execute debug version :

```bash
./run.sh -d
```

If, doing the `./run.sh`, the code seems to not be actualizing, do `make clean` then `./run.sh` again, to clear object files.


## Structure

All `.o` files are on the `build/` folder.

All `.h` files are on the `include/` folder.

All `.cpp` files are on the `src/` folder.


Executables `.exe` are either  on `bin/debug/` or `bin/release` folders depending on the execution you want.

```
Main
  | win_prop: the configuration of the window
  | Scene
    | Input
      | manage all user's input binding the window of the scene
    | Player
      | position, direction, speed, ...
      | Ray(s)
        | player's position, player's heading, angle offset, length ...
    | Wall(s)
      | position, size, ...
    
```

## Process for the raycasting

```
On each frames:
  
  wallBorders = Recovering every wall's border on a vector

  For each rays:
    For each walls:
      pt = intersection's point between the ray and the wall
      min = get the minimum of the intersection's points between the walls and the ray
    
    if there's any interection's point:
      ray's size = closest intersection point (min)
    else:
      ray's size = ray's length
```

Maybe there's more efficient...