# rbxfpsunlocker-osx - UI [![License](https://img.shields.io/badge/License-GPL3.0-green.svg)](https://github.com/lanylow/rbxfpsunlocker-osx/blob/main/LICENSE) ![OS](https://img.shields.io/badge/OS-macOS-green.svg) [![Github All Releases](https://img.shields.io/github/downloads/lanylow/rbxfpsunlocker-osx/total.svg)]()

The first Roblox FPS unlocker for macOS. This UI branch is the first major update to the FPS unlocker. This has been tested and working both on Intel-based Macs and on M1 Macs using Rosetta 2. This update features a new user interface, along with features such as scanning for Roblox and automatically setting the FPS cap. If you want a lighter command line interface then go to the [main](https://github.com/lanylow/rbxfpsunlocker-osx/tree/main) branch.

## Disclaimers

**Use at your own risk**, this is new and still in-development, however this uses the same computational/theoretical method as [axstin](https://github.com/axstin/)'s [rbxfpsunlocker](https://github.com/axstin/rbxfpsunlocker) which has been cleared by Roblox as safe to use.

**UPDATE (27/10/22):** Roblox recently announced their purchasing of anti-cheat company Byfron Technologies who currently develop anti-cheat for games like Fortnite, Apex Legends and more. After observing what has happened to these games internally, the changes made will stop the unlocker from working and may issue _false_ bans, which is something we want to avoid. **From here on out we want to issue a clear and bold warning to users of rbxfpsunlocker-osx, that if you use this tool you are at risk of being falsely banned. By using rbxfpsunlocker-osx we are **not** responsible for false positive bans. You are susceptible to being banned permanently on account and/or hardware levels, without warning. In the case that you are banned it is up to Roblox to revert your ban, not us. We cannot guarantee that Roblox will unban you.** Upon detection of false positive bans or the introduction of any anti-cheat code we will try to update this GitHub page as soon as possible.

Please note that this is a FPS _unlocker_ and not a FPS _booster_ and if your frame rate is the same or below 60 FPS, then your machine is not powerful enough to run Roblox at more than 60 FPS. Heavy usage of system resources may occur because of the higher frame rate.

## Setup

_Note: you must have `sudo` permissions in order to do the steps below. If you do not have `sudo` permissions, either change your account or add yourself to the sudoers file._

**By continuing you have read the disclaimers above and understand the risks associated with using rbxfpsunlocker-osx.**

1. Download the latest release from here: https://github.com/lanylow/rbxfpsunlocker-osx/releases.
2. Open the .dmg file and drag and drop the FPS unlocker to your Applications folder.
3. If you want, you can drag the application into your Launchpad on your Dock.
4. Double click the `rbxfpsunlocker-osx` file in your Applications folder.
5. You will see it instantly close and open again with a prompt from `osascript` to enter your password. **Enter your password into the prompt or else the FPS Unlocker will not open.**
6. After the password prompt, you will see a menu bar item appear. Click it for more details.

## Compiling (advanced)

1. Open Terminal and clone the repository and change directory.

```
git clone -b ui https://github.com/lanylow/rbxfpsunlocker-osx/ && cd rbxfpsunlocker-osx
```

2. Compile in Xcode by pressing Command+B.

Feel free to contribute and improve this project by making pull requests!

## Credits

- @fjij - For bringing the idea to our attention
- @lanylow - For the base unlocker
- @SeizureSaladd - For coding and maintaining the UI
