/*
 *
 * 		@File: slm.inc
 *		@Author: Rancho
 * 		@Description: slm class
 *
 */

#if defined _slm_included
  #endinput
#endif
#define _slm_included
#pragma library SendLongMessage

native SendLongMessage ( playerid, color, msg[] );
native SendLongMessageToAll ( color, msg[] );