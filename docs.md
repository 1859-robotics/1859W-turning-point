# documentation:

## Movement stuffs

### defines
```cpp
A_ERR = 3 // the acceptable margin of error for angular movement
P_ERR = 3 // the acceptable margin of error for positional movement (square shaped)
```

### functions
moveTo
moves to a point with an optional PID configuration, error bounds, and exit time (in ms)
args:
```
( Point target, float err, PIDConfig tPID, PIDConfig rPID, float exit = 5000 )
( Point target, PIDConfig tPID, PIDConfig rPID, float exit = 5000 )
( Point target, float err, float exit = 5000 )
```
usage:
```cpp
robot.moveTo({ 12, 8 }, { 10, 0, 0.2 }, { 0.1, 0, 0.01 });
robot.moveTo({ 48, 9 }, 2, 1000);
robot.moveTo({ 48, 9 }, 1, { 10, 0, 0.2 }, { 0.1, 0, 0.01 });
```

moveAlong


moveToSimple
turns to face a point then moves the distance required to get there
don't use this

moveFor
move for an amount in inches with a backup exit condition of time (in ms)
args:
```
( float dist, float time = 5000 )
```
usage:
```cpp
robot.moveFor(10);
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
robot.turnToFace({ 0, 0 });
robot.turnToFace(90);
```


## flywheel stuffs

## misc stuffs
