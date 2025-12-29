#pragma once
#include "Player.h"
#include "LocalPlayer.h"
#include <iostream>

Player* GetClosestEnemy()
{
    LocalPlayer* localPlayer = LocalPlayer::Get();

    float closestDistance = 1000000.f;
    int closestDistanceIndex = -1;

    for (int i = 1; i < 64; i++)
    {
        Player* currentPlayer = Player::GetPlayer(i);

        if (!currentPlayer || (uintptr_t)currentPlayer == (uintptr_t)localPlayer)
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
        LocalPlayer::Get()->AimAt(closestEnemy->GetBonePos(8));
    }
}