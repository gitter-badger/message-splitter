/*
 *
 * @File: iFramework.cpp
 * @Project: C++ Framework for SA-MP
 * @Author: Ahmet Hakan Karaaslan <iHakan4s@gmail.com>
 *
 */

#include "main.h"
#include "sysChat.h"
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"



PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

extern void *pAMXFunctions;



PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	sampgdk::Unload();
}


cell AMX_NATIVE_CALL SendLongMessage ( AMX * amx, cell * params ) {
	
	int playerid = params[1];
	int color = params[2];
	char * longText = NULL;
	
	amx_StrParam(amx, params[3], longText);
	
	if ( longText != NULL ) {
		sysChat::fixSendClientMessage ( playerid, color, longText);
	}
}

cell AMX_NATIVE_CALL SendLongMessageToAll ( AMX * amx, cell * params ) {
	int color = params[1];
	char * longText = NULL;
	
	amx_StrParam(amx, params[2], longText);
	
	if ( longText != NULL ) {
		sysChat::fixSendClientMessageToAll ( color, longText);
	}
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SendLongMessage", SendLongMessage },
	{ "SendLongMessageToAll", SendLongMessageToAll },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}

