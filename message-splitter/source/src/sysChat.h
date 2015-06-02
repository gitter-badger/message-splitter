/*
 *
 * @File: sysChat.h
 * @Project: C++ Framework for SA-MP
 * @Author: Rancho
 * @Description: Chat system for Lipstick - MP
 *
 */

#ifndef __SYSCHAT_H
#define __SYSCHAT_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

namespace sysChat {

	void	fixSendClientMessage ( int playerid, int color, const char * szMessage, char * szInitialColour = NULL );
	void	fixSendClientMessageToAll ( int color, const char * szMessage , char * szInitialColour = NULL );
	
	
} /* namespace sysChat */

#endif /* __SYSCHAT_H */
