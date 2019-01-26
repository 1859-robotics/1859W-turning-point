# documentation:

## Movement stuffs

### defines
```cpp
A_ERR = 3 // the acceptable margin of error for angular movement
P_ERR = 3 // the acceptable margin of error for positional movement (square shaped)
```

### functions
moveTo
moves to a point

moveToSimple
turns to face a point then moves the distance required to get there

moveFor
move for an amount in inches with a backup exit condition of time
args:
```
( float dist, float time )
```
usage:
```cpp
robot.moveFor(10)
```


turnToFace
turns to face a point or degree
args:
```
( float deg, float maxSpeed )
( Point point, float maxSpeed )
```

usage:
```cpp
robot.turnToFace({ 0, 0 })
robot.turnToFace(90)
```


## flywheel stuffs

## misc stuffs
