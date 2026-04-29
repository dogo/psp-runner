# psp-runner

Runner is a small side-scrolling runner game for the PlayStation Portable.
It uses PSPSDK with OSLib.

## Features

- Splash screen with fade transition
- Auto-running player with jump controls
- Parallax-style scrolling background
- Randomly spaced stone obstacles
- Collision-based game over flow
- MP3 background music
- Basic Memory Stick ranking/save scaffolding

## Requirements

- PSPSDK available in `PATH`
- OSLib installed for the PSP toolchain
- `make`

You can verify the PSP toolchain with:

```sh
psp-config --pspsdk-path
```

## Build

Build from the project directory:

```sh
cd "PSP Project"
make
```

The build produces:

- `EBOOT.PBP`
- `Runner.elf`
- `Runner.prx`
- `PARAM.SFO`
- object files under `Src/`

These generated files are ignored by git.

## Running on PSP or Emulator

Copy the built game folder to the PSP memory stick, keeping the resource
directory next to the EBOOT:

```text
PSP/GAME/Runner/
  EBOOT.PBP
  Res/
    anykeylogo.png
    background.png
    crystal.png
    ground.png
    runner.png
    spikes.png
    stone.png
    stump.png
    test.mp3
```

The game loads assets from `/Res/...`, so missing or misplaced resources will
trigger an OSLib fatal error at startup.

## Controls

- `Cross`: jump
- `Start`: pause or resume

The runner accelerates automatically. The game ends when the runner collides
with a stone.

## Project Layout

```text
PSP Project/
  Include/       Header files
  Src/           Game source files
  Src/util/      Drawing helpers
  Res/           Runtime assets loaded by the game
  Makefile       PSPSDK build definition
  ICON0.PNG      EBOOT icon
```

Important source files:

- `Src/Main.cpp`: PSP module setup and main loop
- `Src/ScreenManager.cpp`: screen switching
- `Src/AnykeyScreen.cpp`: startup splash screen
- `Src/GameScreen.cpp`: gameplay loop, drawing, pause, game over
- `Src/Runner.cpp`: player movement, jump, animation
- `Src/Obstacles.cpp`: obstacle generation and collision
- `Src/Ranking.cpp`: save/load scaffolding

## Clean Build Artifacts

Use the PSPSDK make target:

```sh
cd "PSP Project"
make clean
```

If needed, remove the packaged output as well:

```sh
rm -f EBOOT.PBP PARAM.SFO Runner.elf Runner.prx
```
