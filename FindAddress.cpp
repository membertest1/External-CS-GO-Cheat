#include "FindAddress.h"

bool			FindAddress::isgetaddress = false;
DWORD		    FindAddress::dwLocalPlayer = NULL,
FindAddress::dwEntityList = NULL,
FindAddress::dwForceJump = NULL,
FindAddress::dwGlowObjectManager = NULL,
FindAddress::localPlayer = NULL,
FindAddress::dwClientState = NULL,
FindAddress::dwPrecacheInfo;
MODULEENTRY32   FindAddress::client,
				FindAddress::engine;

bool FindAddress::Prepare()
{
	if (!isgetaddress)
	{
		client = getModule(getProcess("csgo.exe"), "client.dll");
		engine = getModule(getProcess("csgo.exe"), "engine.dll");
		/*dwLocalPlayer*/ {
			dwLocalPlayer = FindPattern::FindPattern((DWORD)client.modBaseAddr, (DWORD)client.modBaseSize, (PBYTE)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", "000????00????000000000").Base;
			{
				dwLocalPlayer = readMem<DWORD>(dwLocalPlayer + 0x3);
				dwLocalPlayer -= (DWORD)client.modBaseAddr;
				dwLocalPlayer += 0x4;
			}
		}
		/*dwEntityList*/ {
			dwEntityList = FindPattern::FindPattern((DWORD)client.modBaseAddr, (DWORD)client.modBaseSize, (PBYTE)"\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "0????00000????00").Base;
			{
				dwEntityList = readMem<DWORD>(dwEntityList + 0x1);
				dwEntityList -= (DWORD)client.modBaseAddr;
			}
		}
		/*dwForceJump*/ {
			dwForceJump = FindPattern::FindPattern((DWORD)client.modBaseAddr, (DWORD)client.modBaseSize, (PBYTE)("\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02"), "00????0000000").Base;
			if (dwForceJump)
			{
				dwForceJump = readMem<DWORD>(dwForceJump + 0x2);
				dwForceJump -= (DWORD)client.modBaseAddr;
			}
		}
		/*dwGlowObjectManager*/ {
			dwGlowObjectManager = FindPattern::FindPattern((DWORD)client.modBaseAddr, (DWORD)client.modBaseSize, (PBYTE)("\x5E\x5D\xC2\x00\x00\x83\xE9\x40\xE9\x00\x00\x00\x00\xA1\x00\x00\x00\x00"), "000??0000????0????").Base;
			if (dwGlowObjectManager)
			{
				dwGlowObjectManager = readMem<DWORD>(dwGlowObjectManager + 0xE);
				dwGlowObjectManager -= (DWORD)client.modBaseAddr;
				dwGlowObjectManager += 0x4;
			}
			
		}
		/*dwClientState*/{
			dwClientState = FindPattern::FindPattern((DWORD)engine.modBaseAddr, (DWORD)engine.modBaseSize, (PBYTE)("\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0"), "0????000?0?0000").Base;
			if (dwClientState)
			{
				dwClientState = readMem<DWORD>(dwClientState + 0x1);
				dwClientState -= (DWORD)engine.modBaseAddr;
			}
		}
		/*dwPrecacheInfo*/{
			dwPrecacheInfo = FindPattern::FindPattern((DWORD)engine.modBaseAddr, (DWORD)engine.modBaseSize, (PBYTE)("\x3B\x81\x00\x00\x00\x00\x75\x11\x8B\x45\x00\x83\xF8\x00"), "00????0000?00?").Base;
			if (dwPrecacheInfo)
			{
				dwPrecacheInfo = readMem<DWORD>(dwPrecacheInfo + 0x2);
			}
		}
		isgetaddress = true;
	}
	localPlayer = readMem<DWORD>((DWORD)client.modBaseAddr + dwLocalPlayer);
	return 0;
}
