#include "pch.h"
#include "LocalPlayer.h"
#include "./offsets/all_offsets.hpp"
#include "iostream"
#include "Windows.h"
#include "Vector3.h"
#include <iostream>
#include "math.h"

using namespace cs2_dumper::schemas::client_dll::CBasePlayerController;
using namespace cs2_dumper::schemas::client_dll::CGameSceneNode;
using namespace cs2_dumper::schemas::client_dll::C_BaseEntity;
using namespace cs2_dumper::schemas::client_dll::C_BaseModelEntity;
using namespace cs2_dumper::schemas::client_dll::C_CSPlayerPawn;
using namespace cs2_dumper::offsets::client_dll;
using namespace cs2_dumper::schemas::client_dll::C_BasePlayerPawn;
using namespace cs2_dumper::schemas::client_dll::CSkeletonInstance;
using namespace cs2_dumper::schemas::client_dll::CCSPlayerController;



LocalPlayer* LocalPlayer::Get()
{
    /*
	static uintptr_t clientModule = (uintptr_t)(GetModuleHandle(L"client.dll"));
	static uintptr_t localPlayer = *(uintptr_t*)(clientModule + dwLocalPlayerPawn);

    std::cout << "LOCAL PLAYER : " << localPlayer << std::endl;
	return (LocalPlayer*)localPlayer;
    */
    
    static uint64_t clientModule = (uint64_t)(GetModuleHandle(L"client.dll"));
    static LocalPlayer* localPlayer = (LocalPlayer*)(clientModule + dwLocalPlayerPawn);
	std::cout << "LOCAL PLAYER : " << localPlayer << std::endl;

    return localPlayer;
    
}

Vector3* LocalPlayer::GetOrigin()
{
    std::cout << "LOCALPLAYER ORIGIN : " << (Vector3*)(*(uintptr_t*)this + m_vOldOrigin) << std::endl;
    //return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
    return (Vector3*)(*(uintptr_t*)this + m_vOldOrigin);
}

Vector3* LocalPlayer::GetViewOffset()
{
    return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
}

int* LocalPlayer::GetHealth()
{
    std::cout << "LOCALPLAYER HEALTH : " << *(int*)(*(uint64_t*)this + m_iHealth) << std::endl;
    return (int*)(*(uint64_t*)this + m_iHealth);
}

int* LocalPlayer::GetTeam()
{
    std::cout << "LOCAL PLAYER TEAM : " << *(int*)(*(uint64_t*)this + m_iTeamNum) << std::endl;
    return (int*)(*(uint64_t*)this + m_iTeamNum);
}

float LocalPlayer::GetDistance(Vector3* other)
{
    Vector3* myPos = GetOrigin();
    Vector3 delta = Vector3(other->x - myPos->x, other->y - myPos->y, other->z - myPos->z);
    std::cout << "Ma Pos: " << myPos->x << ", " << myPos->y << std::endl;

    std::cout << "DISTANCE AVEC JOUEUR LE PLUS PROCHE : " << sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) << std::endl;

    return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

double PI = 3.141592653589;

void LocalPlayer::AimAt(Vector3* target)
{
    static uint64_t clientModule = (uint64_t)GetModuleHandleA("client.dll");
    static Vector3* viewAngles = (Vector3*)(clientModule + dwViewAngles);

    Vector3 origin = *GetOrigin();
    Vector3 viewOffset = *GetViewOffset();
    Vector3* myPos = &(origin + viewOffset);

    std::cout << "[DEBUG] myPos->x : " << myPos->x << " | myPos->y : " << myPos->y << " | myPos->z : " << myPos->z << std::endl;
    std::cout << "[DEBUG] target->x : " << target->x << " | target->y : " << target->y << " | target->z : " << target->z << std::endl;
    std::cout << "[DEBUG VISER] x : " << target->x - myPos->x << " | y : " << target->y - myPos->y << " | z : " << target->z - myPos->z << std::endl;

    Vector3 deltaVec = { target->x - myPos->x, target->y - myPos->y, target->z - myPos->z };
    float deltaVecLength = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z);

    float pitch = -asin(deltaVec.z / deltaVecLength) * (180 / PI);
    float yaw = atan2(deltaVec.y, deltaVec.x) * (180 / PI);

    if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
    {
        viewAngles->x = pitch;
        viewAngles->y = yaw;
    }
   
}
