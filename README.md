# rbxfpsunlocker-osx [![GitHub license](https://img.shields.io/github/license/lanylow/rbxfpsunlocker-osx?color=informational)](https://github.com/lanylow/rbxfpsunlocker-osx/blob/main/LICENSE) [![Github All Releases](https://img.shields.io/github/downloads/lanylow/rbxfpsunlocker-osx/total.svg?color=informational)]() [![Discord](https://img.shields.io/badge/chat-discord-informational)](https://discord.gg/MrtJvV5tKv)

The first Roblox FPS unlocker for macOS. This program works only on both Intel and Apple Silicon Macs.

## Setup


If you don't want to set your own custom FPS cap, you can use the following command to do it automatically:
```
curl -f https://raw.githubusercontent.com/lanylow/rbxfpsunlocker-osx/script/install_fps_unlocker | sh
```
Otherwise, you can follow the steps below:

1. Download the script using `curl -LO https://raw.githubusercontent.com/lanylow/rbxfpsunlocker-osx/script/install_fps_unlocker`
2. Make the script executable using `chmod +x ./install_fps_unlocker`
3. Run the script and set your custom FPS cap using `./install_fps_unlocker (custom FPS cap number goes here)`

After executing the script, you should see a confirmation that the unlocker was installed.

*Note: You must run the command again when Roblox updates.*

*Note: if you're using macOS Ventura or newer and your display doesn't support more than 60 Hz **you won't see the effect of this program**. Please don't create issues asking about this. A workaround or fix will **NEVER** be made.*

*Note: This experimental version of rbxfpsunlocker-osx might ask you for your contacts, or reminders, or calendar, or photos. **If it does, click "Don't Allow" or "Cancel".** Don't worry, this is normal behavior with `find` looking in your Full User directory, and is not trying to steal your information.*

## Credits
 
 - [lanylow](https://github.com/lanylow) - for coding this script and older versions of the unlocker
 - [SeizureSaladd](https://github.com/SeizureSaladd) - for testing the code of older versions
 - [fjij](https://github.com/fjij) - for bringing the idea to my attention
