# documentation:

## Movement stuffs

### defines
```cpp
A_ERR = 3 // the acceptable margin of error for angular movement
P_ERR = 3 // the acceptable margin of error for positional movement (square shaped)
```

### functions
moveTo
moves to a point with an optional PID configuration and error bounds
args:
```
( Point target, float err, PIDConfig tPID, PIDConfig rPID )
( Point target, PIDConfig tPID, PIDConfig rPID )
( Point target, float err)
```
usage:
```cpp
robot.moveTo({ 12, 8 }, { 10, 0, 0.2 }, { 0.1, 0, 0.01 });
robot.moveTo({ 48, 9 }, 2);
robot.moveTo({ 48, 9 }, 1, { 10, 0, 0.2 }, { 0.1, 0, 0.01 });
```

moveToSimple
turns to face a point then moves the distance required to get there
don't use this

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
