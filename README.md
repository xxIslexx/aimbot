> **Educational purposes only.**
>
> **Do not use this project to cheat in online games, bypass anti-cheat systems, or violate any Terms of Service.**

## Overview

...

## Project Structure

```bash
aimbot/
├── offsets/            # Updated game offsets (m_pGameSceneNode, dwEntityList, etc.)
├── LocalPlayer.cpp/h   # Local player specific logic (Origin, ViewOffset, AimAt)
├── Player.cpp/h        # General entity management (Bone Matrix, Health, Team)
├── Vector3.h           # 3D Math structure (x, y, z)
└── dllmain.cpp         # DLL entry point and main execution loop
```

## Build instructions (Visual Studio)

1. Open `aimbot.sln` in Visual Studio.
2. Select a configuration (Debug/Release) and platform (x64).
3. Build the solution.

If you run into include errors, ensure:
- The solution is opened from the repository root
- The `offsets/` folder exists with the latest .hpp offsets files
- Your include paths are correct for your setup

## Credits

- **Guided Hacking** — BDKPlayer : for educational content explaining FPS math concepts (e.g., `CalcAngle`) and general learning resources (link : https://www.youtube.com/watch?v=sDd8aBCCBbA).
- **a2x** — credited for community tooling/resources commonly referenced in offset dumping/data extraction discussions.

## Disclaimer

This code is provided **as-is** for educational and research purposes only.  
You are responsible for complying with laws, software licenses, and game Terms of Service.  
The maintainers do not condone cheating, disruption, or bypassing protections in any form.
