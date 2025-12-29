#pragma once

#include <iostream>
#include <cstdint>
#include <Windows.h>

#include "pch.h"
#include "Player.h"
#include "LocalPlayer.h"
#include "Vector3.h"
#include <thread>



Player* GetClosestEnemy()
{
    LocalPlayer* localPlayer = LocalPlayer::Get();

    float closestDistance = 1000000.f;
    int closestDistanceIndex = -1;

    for (int i = 1; i < 11; i++)
    {
        Player* currentPlayer = Player::GetPlayer(i);

        if (!currentPlayer || !(*(uintptr_t*)currentPlayer) || (uintptr_t)currentPlayer == (uintptr_t)localPlayer)
            continue;

        if (*currentPlayer->GetTeam() == *localPlayer->GetTeam())
            continue;
        
        if (*currentPlayer->GetHealth() < 1 || *localPlayer->GetHealth() < 1)
            continue;

        float currentDistance = localPlayer->GetDistance(currentPlayer->GetOrigin());

        if (currentDistance < closestDistance)
        {
            closestDistance = currentDistance;
            closestDistanceIndex = i;
        }
    }

    if (closestDistanceIndex == -1)
        return nullptr;

    return Player::GetPlayer(closestDistanceIndex);
}

void Run()
{
    Player* closestEnemy = GetClosestEnemy();
    if (closestEnemy)
    {
        LocalPlayer::Get()->AimAt(closestEnemy->GetBonePos(6));
    }
}

DWORD WINAPI OnDllAttach(PVOID base)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("GH_Aimbot_Tutorial - Debug");
    while (!(GetAsyncKeyState(VK_DELETE) & 0x8000))
    {
        if (GetAsyncKeyState(0x33) & 0x8000)
        {
            while (!(GetAsyncKeyState(0x34) & 0x8000))
            {
                Run();
                Sleep(1);
            }
        }
    }
    MessageBoxA(nullptr, "[AIMBOT] DELETE", "AIMBOT", MB_OK | MB_ICONINFORMATION);
    FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
}

VOID WINAPI OnDllDetach()
{
#ifdef _DEBUG
    fclose((FILE*)stdin);
    fclose((FILE*)stdout);

    HWND hConsoleWnd = GetConsoleWindow();
    FreeConsole();
    PostMessage(hConsoleWnd, WM_CLOSE, 0, 0);
#endif
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, NULL, NULL);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        OnDllDetach();
    }

    return TRUE;
}

