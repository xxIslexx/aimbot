#include "pch.h"
#include "LocalPlayer.h"
#include "./offsets/all_offsets.hpp"
#include "iostream"
#include "Windows.h"
#include "Player.h"
#include "Vector3.h"
#include <iostream>

using namespace cs2_dumper::schemas::client_dll::CBasePlayerController;
using namespace cs2_dumper::schemas::client_dll::CGameSceneNode;
using namespace cs2_dumper::schemas::client_dll::C_BaseEntity;
using namespace cs2_dumper::schemas::client_dll::C_BaseModelEntity;
using namespace cs2_dumper::schemas::client_dll::CSkeletonInstance;
using namespace cs2_dumper::schemas::client_dll::CCSPlayerController;
using namespace cs2_dumper::schemas::client_dll::C_BasePlayerPawn;
using namespace cs2_dumper::offsets::client_dll;

Player* Player::GetPlayer(int index)
{
    
    static uint64_t moduleBase = (uint64_t)(GetModuleHandleA("client.dll")); //ou GetModuleHandle(L"client.dll")
    uint64_t entityList = *(uint64_t*)(moduleBase + dwEntityList);                                // index → C_CSPlayerController (team, name, handle) 
    uint64_t listEntity = *(uint64_t*)(entityList + (0x8 * ((index & 0x7FFF) >> 9) + 0x10));      // handle → C_CSPlayerPawn(origin, health, angles, etc.)
    uint64_t entityController = *(uint64_t*)(listEntity + (0x70 * (index & 0x1FF)));
    uint32_t PawnHandle = *(uint32_t*)(entityController + m_hPlayerPawn);
    uint64_t PawnEntry = *(uint64_t*)(entityList + (0x8 * ((PawnHandle & 0x7FFF) >> 9) + 0x10));
    uint64_t Pawn = *(uint64_t*)(PawnEntry + (0x70 * (PawnHandle & 0x1FF)));

    //int team = *(int*)(Pawn + m_iTeamNum);
    std::cout << "LOCALPLAYER EXEC : " << index << std::endl;

    //return (Player*)Pawn;
    return (Player*)(PawnEntry + (0x70 * (PawnHandle & 0x1FF)));
}

/*
int* Player::GetMaxPlayer()
{
    static uint32_t moduleBase = (uint32_t)GetModuleHandleA("engine.dll");
    return (int*)((uint32_t)moduleBase + dwClientState + dwClientState_MaxPlayer);
}
*/

Vector3* Player::GetOrigin()
{
    std::cout << "ORIGIN : " << (Vector3*)(*(uintptr_t*)this + m_vecOrigin) << std::endl;
    //return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
    return (Vector3*)(*(uintptr_t*)this + m_vOldOrigin);
}

Vector3* Player::GetViewOffset()
{
    return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
}

Vector3* Player::GetBonePos(int boneID)
{
    std::cout << "GETBONESPOS " << std::endl;

    uint64_t gameSceneNode = *(uint64_t*)(*(uint64_t*)this + m_pGameSceneNode);
    uint64_t modelState = gameSceneNode + m_modelState;
    uint64_t boneMatrix = *(uint64_t*)(modelState + 0x80);

    return (Vector3*)(boneMatrix + (boneID * 0x20));

    /*
    static Vector3 bonePos;
    bonePos.x = *(float*)(boneMatrix + 0x20 * boneID + 0x0C);
    bonePos.y = *(float*)(boneMatrix + 0x20 * boneID + 0x1C);
    bonePos.z = *(float*)(boneMatrix + 0x20 * boneID + 0x2C);
    return &bonePos;
    */
}

int* Player::GetHealth()
{
    std::cout << "HEALTH : " << *(int*)(*(uint64_t*)this + m_iHealth) << std::endl;
    return (int*)(*(uint64_t*)this + m_iHealth);
}

int* Player::GetTeam()
{
    std::cout << "TEAM : " << *(int*)(*(uint64_t*)this + m_iTeamNum) << std::endl;
    return (int*)(*(uint64_t*)this + m_iTeamNum);
}
