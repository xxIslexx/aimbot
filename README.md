> **Educational purposes only.**
>
> **Do not use this project to cheat in online games, bypass anti-cheat systems, or violate any Terms of Service.**

## Overview

This project is an Internal Aimbot for Counter-Strike 2. Unlike external tools, this project is designed to be injected directly into the game's process, allowing for high-performance, real-time interaction with the engine's internal memory.

The repository serves as a practical study case for:
- Internal Memory Hooking: Exploring how a DLL executes code within the host process (cs2.exe) to access protected data structures.
- Source 2 Entity Forensics: Navigating the EntityList and GameSceneNode from the inside to retrieve precise coordinates.
- Internal Bone Extraction: Accessing the m_modelState and bone array directly from the game's heap to calculate aim targets.
- Applied FPS Math: Implementing 3D trigonometry (Pitch/Yaw calculations) based on the local player's view position and the target's bone location.

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
