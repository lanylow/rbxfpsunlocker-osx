# rbxfpsunlocker-osx [![License](https://img.shields.io/badge/License-GPL3.0-green.svg)](https://github.com/lanylow/rbxfpsunlocker-osx/blob/main/LICENSE) ![OS](https://img.shields.io/badge/OS-macOS-green.svg)

The first Roblox FPS unlocker for macOS. This is a very simple and unpolished FPS unlocker with more updates to come. This has been tested and working both on Intel-based machines and under Rosetta 2 on M1.

## Usage

1. Download the latest release from https://github.com/lanylow/rbxfpsunlocker-osx/releases.
2. Extract `rbxfpsunlocker.zip` by double clicking on it, if it wasn't extracted automatically.
3. Locate `rbxfpsunlocker` in Finder in your Downloads and right click and press `Get Info`.
4. Copy all text after where it says `Where:`.
5. Open Terminal and write the following command. Replace the `<path>` with the copied path from Finder.

```
cd <path>
```

6. Using the `cd` command, you should now be in your Downloads folder or wherever else your FPS unlocker file may be.
7. In the same Terminal window, run the following command. `<cap>` may be replaced with whatever framerate is desired, e.g. 90, 120, 144, etc. If no framerate is supplied it will automatically be set to 120.

```
sudo ./rbxfpsunlocker <cap>
```

8. Enjoy those smooth frames but on macOS now

A more user friendly setup will soon be released with a video tutorial.

## Compiling (advanced)

1. Open Terminal and clone the repository and change directory.

```
git clone https://github.com/lanylow/rbxfpsunlocker-osx/ && cd rbxfpsunlocker-osx
```

2. Compile. This will fail if you don't have [Xcode Developer tools](https://mac.install.guide/commandlinetools/index.html) installed.

```
make
```

3. Launch the unlocker

```
sudo ./rbxfpsunlocker <cap>
```

## Disclaimer

**Use at your own risk**, this is new and still in-development, however this uses the same computational/theoretical method as [axstin](https://github.com/axstin/)'s [rbxfpsunlocker](https://github.com/axstin/rbxfpsunlocker) which has been cleared by Roblox as safe to use.

Please note that this is a FPS *unlocker* and not a FPS *booster* and if your frame rate is the same or below 60 FPS, then your machine is not powerful enough to run Roblox at more than 60 FPS. Heavy usage of system resources may occur because of the higher frame rate.

## Credits

@fjij - For bringing the idea to our attention

@lanylow - For reverse engineering and coding the unlocker

@SeizureSaladd - For testing the code and coding the front-end
