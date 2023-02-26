#include <Windows.h>

namespace GeneralInfo::Addresses
{
	//PlayerControl Instance Base And Member Methods
	const DWORD base = (DWORD)GetModuleHandleA("GameAssembly.dll");
	const unsigned long PlayerControlBase = base + 0x020024B0;
	const unsigned long CmdCheckColor = base + 0x5FABE0;
	const unsigned long CmdCheckName = base + 0x5FAD40;
	const unsigned long RpcCompleteTask = base + 0x5FFC20;
	const unsigned long RpcPlayAnimation = base + 0x5FFD70;
	const unsigned long RpcSetColor = base + 0x600450;
	const unsigned long RpcSetHat = base + 0x6004F0;
	const unsigned long RpcSetName = base + 0x600730;
	const unsigned long RpcSetPet = base + 0x6007D0;
	const unsigned long RpcSetScanner = base + 0x600910;
	const unsigned long RpcSetSkin = base + 0x600A20;
	const unsigned long FixedUpdateAddress = base + 0x5FB7A0;

	//ShipStatus Instance Base And Member Methods
	const unsigned long ShipStatusBase = base + 0x01FD25C0;
	const unsigned long RpcCloseDoorsOfType = base + 0x407720;
	const unsigned long RpcRepairSystem = base + 0x4077D0;
}