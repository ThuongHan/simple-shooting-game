# VirusGame

A simple game build using the SDL2 graphics library. Use
the cursor keys to move to escape/kill the viruses.

![Alt text](VirusGame.png)

## Install

### Linux/Mac:

Using the package manager on your system to install:

    cmake
    git
    libsdl2-dev
    libsdl2-gfx-dev

For example for Ubuntu use:

    sudo apt install cmake git libsdl2-dev libsdl2-gfx-dev

For a Mac probably something like (run 'brew search sdl2' to see which are available):

    brew install cmake git sdl2 sdl2_gfx

Then:

    git clone https://bterwijn@bitbucket.org/bterwijn/virusgame.git
    cd virusgame/src
    mkdir build
    cd build
    cmake ..
    make
    ./VirusGame

### Windows:

Install [git](https://git-scm.com/download/win) and clone
[VirusGame](https://bitbucket.org/bterwijn/virusgame/src/master).

Install [Visual Studio Studio Community
2022](https://visualstudio.microsoft.com/) and in the Visual Studio
Installer install Worksload "Desktop development with C++" (includes
CMake).

Install the SDL2 graphics library use
[vcpkg](https://github.com/Microsoft/vcpkg) by using:

    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    .\vcpkg.exe integrate install
    .\vcpkg.exe install sdl2
    .\vcpkg.exe install sdl2-gfx --triplet x64-windows

Then in Visual Studio Studio Community 2019 open the virusgame/src
folder and build the project (F7) and run it (F5).

## Documentation

For documentation see the
[list of classes](http://sbt.science.uva.nl/bterwijn/virusgame/doc/html/annotated.html "Doxygen documentation")

## Authors

Bas Terwijn <<b.terwijn@uva.nl>>
...

## Description of extension by student

My extension ...

# 1. Shooting Mechanism

The player can shoot bullets in the direction the are facing and also there is a cooling system so that we shoot approximately 3 bullets per second.

# 2. Scoring System

- Destroying a normal virus gives +1 points
- Destroying a BigVirus gives +2 points
- Colliding with a virus decreases score - collision with BigVirus : -2 points - collosion with virus : -1 points
  The score is displayed on the screen (top left), and the game ends when:
- player wins if score > 20
- player losses if score < 0

# 3. BigVirus (new unit type, implemented in BigVirus.h)

A new virus is added:

- Bigger and slower than normal viruses
- Has 5 hp (5 bullets to kill it)
- Gain 2 points when killed

BigVirus is derived from Virus

# 4. Collision System

- Bullets damage or destroy viruses if distances are close
- BigVirus requires 5 hits but gives you 2 points to the score
- Player also lose points when colliding with viruses (lose 1 if normal viurs and lose 2 points when colliding with BigVirus)


-- Note: the game always starts with a score of 10. From there it can go up or down.
## Description of decisions related to SOLID principles by student

My code structure ...
