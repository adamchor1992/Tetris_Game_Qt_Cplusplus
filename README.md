# Tetris
C++ implementation of classic Tetris game using Qt 6.2.3 library.

**Windows and Linux executables are provided.**

See screenshot.jpg for quick glance at game window.

# Tests
Unit tested using Google Test 1.11.0

# How to run on Windows
Run\
**executable_windows/Tetris.exe**

# How to run on Linux
Run\
**executable_linux/Tetris.sh**

# How to run using Docker (on Linux host)
Run\
**./Tetris.sh**

This requires running Docker service. It builds and runs Docker image based on provided dockerfile. The image is based on my prebuilt image "adamchor/ubuntu-image-for-qt-gui" which is available on my Docker Hub. It is actually an Ubuntu image with preinstalled libraries required for running Qt GUI applications on Linux.

**Warning**\
Due to the fact that this is a GUI application, the Docker container needs to acquire access to host's display. In this case it is done by adding "local:docker" to xhost access control to enable Docker connection to X Server.
