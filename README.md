# Pomodoro

This project is an implementation of a [pomodoro](https://en.wikipedia.org/wiki/Pomodoro_Technique).
For now, the focus is on making a simple terminal application.

## Features

- [X] Aternate automatically between "Work" and "Break" periods.
- [X] Emit a sound at the end/start of a new period.
- [X] Implements a pomodoro class with the same behavior as the one described on [Wikipedia](https://en.wikipedia.org/wiki/Pomodoro_Technique)
- [X] Make one period update the same line on the terminal to avoid flooding it.

## Compilation

This projects uses cmake as a build system manager, and conan as a package manager.
Here is the command to generate the executable.

```shell
mkdir build
cd build
cmake ..
cmake --build --config [Debug | Release]
```

## Credits

The sounds in the resources have been made by [Eric Matyas](www.soundimage.org)
