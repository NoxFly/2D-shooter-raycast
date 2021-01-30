# 2D-Shooter-Raycast

## Execution

On console :

```bash
./run.sh # for release mode, same as ./run.sh -r
./run.sh -d # for debug version
```

## Usage

You can move forward with key `Z`, backward with `S`, turn left with `Q` and turn right with `D`.

You also can mouse down and move it, so you'll drag and drop the player.

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