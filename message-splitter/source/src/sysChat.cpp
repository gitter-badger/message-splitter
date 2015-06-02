/*
 *
 * @File: sysChat.cpp
 * @Project: C++ Framework for SA-MP
 * @Author: Rancho
 * @Description:  Chat system for Lipstick - MP
 *
 */
 
#include "main.h"
#include "sysChat.h"

#define MAX_LINE_LENGTH ( 136 )
#define MAX_LINE_ALPHACHAR_LENGTH ( 70 ) // Maximum number of alphanumeric character.
#define MAX_CHECK_LINE_LENGTH ( 100 ) 


namespace sysChat {
	
	void	fixSendClientMessage ( int playerid, int color, const char * szMessage, char * szInitialColour ) {
		unsigned int 	uiMessageLen = strlen(szMessage);
		static char szBuffer [MAX_LINE_LENGTH + 1]; /* assuming every single character colour coded, static allocated, will not cause huge performance losts. */

		if ( uiMessageLen < MAX_CHECK_LINE_LENGTH ) { /* will increase performance */
			if ( szInitialColour != NULL ) {
				snprintf(szBuffer, sizeof(szBuffer) , "%s%s", szInitialColour, szMessage );
			} else {
				snprintf(szBuffer, sizeof(szBuffer) , "%s", szMessage );
			}
			SendClientMessage(playerid, color, szBuffer);
			return;
		}
		
		unsigned int 	uiLen = 0, uiIndex = 0, uiBufferIndex = 0, uiColourBufferIndex = 0,
						uiAlphaLen = 0;
		unsigned int 	uiSpaceIndex = 0, uiSpaceBufferIndex = 0;
		
		unsigned int 	uiColour = 0;
		unsigned int 	uiCapturedColour = 0;
		

		char szColour[16];
		memset ( &szColour, '\0', sizeof(szColour) ); /* clear szColour */
		char szColourBuffer[16];
		char uiData;
		
		if ( szInitialColour != NULL ) {
			snprintf(szBuffer, sizeof(szColourBuffer) , "%s", szInitialColour );
			uiBufferIndex = 8;
			uiLen = 8;
		}
		
		for (; (uiData = szMessage[uiIndex]) != '\0'; ) {
			
			switch ( uiData ) {
				case ' ':
					if ( uiColour > 0 ) {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
						
						if ( uiLen < MAX_LINE_LENGTH && uiAlphaLen < MAX_LINE_ALPHACHAR_LENGTH ) {
							uiSpaceIndex = uiIndex;
							uiSpaceBufferIndex = uiBufferIndex;
						}
						
					} else {
						++uiLen;
						++uiAlphaLen;
						uiSpaceIndex = uiIndex;
						uiSpaceBufferIndex = uiBufferIndex;
						
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '{':
					if ( uiColour == 0 ) {
						++uiColour;
						szColourBuffer[uiColourBufferIndex++] = uiData;
					} else {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '}':
					if ( uiColour > 0 ) {
						if (++uiColour == 8) {
							szColourBuffer[uiColourBufferIndex++] = uiData;
							szColourBuffer[uiColourBufferIndex++] = '\0';
							snprintf(szColour, sizeof(szColour), "%s", szColourBuffer);
							++uiCapturedColour;
						} else {
							uiAlphaLen += uiColour;
						}
					} else {
						uiLen += 1;
						uiAlphaLen += 1;
					}
					uiLen += uiColour;
					uiColour = 0;
					uiColourBufferIndex = 0;
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				case 'a': case 'A': case 'b': case 'B':	case 'c': case 'C': case 'd': case 'D': case 'f': case 'F': case 'e': case 'E':
					if ( uiColour > 0 ) {
						++uiColour;
						szColourBuffer[uiColourBufferIndex++] = uiData;
					} else {
						++uiLen;
						++uiAlphaLen;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				default:
					if ( uiColour > 0 ) {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
					} else {
						++uiLen;
						++uiAlphaLen;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;						
			}
			
			if ( uiColour >= 8 ) { /* uiColour cannot be equal to 8 here, because it should be closed '}' */
				uiLen += uiColour;
				uiColour = 0;
			}
			
			if ( uiLen >= MAX_LINE_LENGTH  || uiAlphaLen >= MAX_LINE_ALPHACHAR_LENGTH ) {
				if ( uiSpaceBufferIndex == 0 ) {
					uiSpaceBufferIndex = uiBufferIndex;
				} else {
					++uiSpaceIndex;
				}
				

				szBuffer[uiSpaceBufferIndex] = '\0';
				
				
				SendClientMessage ( playerid, color, szBuffer );
				szMessage += uiSpaceIndex;
				if ( uiCapturedColour > 0 ) {
					sysChat::fixSendClientMessage ( playerid, color, szMessage, szColour );
				} else {
					sysChat::fixSendClientMessage ( playerid, color, szMessage, szInitialColour );
				}
				return;
			}
			
			_inc_index:
				++uiIndex;
		}

		if ( uiSpaceBufferIndex == 0 ) {
			uiSpaceBufferIndex = uiBufferIndex;
		}

		szBuffer[uiSpaceBufferIndex] = '\0';
		SendClientMessage ( playerid, color, szBuffer );
	}
	
	void	fixSendClientMessageToAll ( int color, const char * szMessage, char * szInitialColour ) {
		unsigned int 	uiMessageLen = strlen(szMessage);
		static char szBuffer [MAX_LINE_LENGTH + 1]; /* assuming every single character colour coded, static allocated, will not cause huge performance losts. */
		
		if ( uiMessageLen < MAX_CHECK_LINE_LENGTH ) { /* will increase performance */
			if ( szInitialColour != NULL ) {
				snprintf(szBuffer, sizeof(szBuffer) , "%s%s", szInitialColour, szMessage );
			} else {
				snprintf(szBuffer, sizeof(szBuffer) , "%s", szMessage );
			}
			SendClientMessageToAll(color, szBuffer);
			return;
		}
		
		unsigned int 	uiLen = 0, uiIndex = 0, uiBufferIndex = 0, uiColourBufferIndex = 0,
						uiAlphaLen = 0;
		unsigned int 	uiSpaceIndex = 0, uiSpaceBufferIndex = 0;
		
		unsigned int 	uiColour = 0;
		unsigned int 	uiCapturedColour = 0;
		
		char szColour[16];
		memset ( &szColour, '\0', sizeof(szColour) ); /* clear szColour */
		char szColourBuffer[16];
		char uiData;
		
		
		if ( szInitialColour != NULL ) {
			snprintf(szBuffer, sizeof(szColourBuffer) , "%s", szInitialColour );
			uiBufferIndex = 8;
			uiLen = 8;
		}
		
		for (; (uiData = szMessage[uiIndex]) != '\0'; ) {
			
			switch ( uiData ) {
				case ' ':
					if ( uiColour > 0 ) {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
						
						if ( uiLen < MAX_LINE_LENGTH && uiAlphaLen < MAX_LINE_ALPHACHAR_LENGTH ) {
							uiSpaceIndex = uiIndex;
							uiSpaceBufferIndex = uiBufferIndex;
						}
						
					} else {
						++uiLen;
						++uiAlphaLen;
						uiSpaceIndex = uiIndex;
						uiSpaceBufferIndex = uiBufferIndex;
						
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '{':
					if ( uiColour == 0 ) {
						++uiColour;
						szColourBuffer[uiColourBufferIndex++] = uiData;
					} else {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '}':
					if ( uiColour > 0 ) {
						if (++uiColour == 8) {
							szColourBuffer[uiColourBufferIndex++] = uiData;
							szColourBuffer[uiColourBufferIndex++] = '\0';
							snprintf(szColour, sizeof(szColour), "%s", szColourBuffer);
							++uiCapturedColour;
						} else {
							uiAlphaLen += uiColour;
						}
					} else {
						uiLen += 1;
						uiAlphaLen += 1;
					}
					uiLen += uiColour;
					uiColour = 0;
					uiColourBufferIndex = 0;
					szBuffer[uiBufferIndex++] = uiData;
				break;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				case 'a': case 'A': case 'b': case 'B':	case 'c': case 'C': case 'd': case 'D': case 'f': case 'F': case 'e': case 'E':
					if ( uiColour > 0 ) {
						++uiColour;
						szColourBuffer[uiColourBufferIndex++] = uiData;
					} else {
						++uiLen;
						++uiAlphaLen;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;
				default:
					if ( uiColour > 0 ) {
						uiLen += uiColour + 1;
						uiAlphaLen += uiColour + 1;
						uiColour = 0;
						uiColourBufferIndex = 0;
					} else {
						++uiLen;
						++uiAlphaLen;
					}
					szBuffer[uiBufferIndex++] = uiData;
				break;						
			}
			
			if ( uiColour >= 8 ) { /* uiColour cannot be equal to 8 here, because it should be closed '}' */
				uiLen += uiColour;
				uiColour = 0;
			}
			
			if ( uiLen >= MAX_LINE_LENGTH  || uiAlphaLen >= MAX_LINE_ALPHACHAR_LENGTH ) {
				if ( uiSpaceBufferIndex == 0 ) {
					uiSpaceBufferIndex = uiBufferIndex;
				} else {
					++uiSpaceIndex;
				}
				

				szBuffer[uiSpaceBufferIndex] = '\0';
				
				
				SendClientMessageToAll ( color, szBuffer );
				szMessage += uiSpaceIndex;
				if ( uiCapturedColour > 0 ) {
					sysChat::fixSendClientMessageToAll ( color, szMessage, szColour );
				} else {
					sysChat::fixSendClientMessageToAll ( color, szMessage, szInitialColour );
				}
				return;
			}
			
			_inc_index:
				++uiIndex;
		}

		if ( uiSpaceBufferIndex == 0 ) {
			uiSpaceBufferIndex = uiBufferIndex;
		}

		szBuffer[uiSpaceBufferIndex] = '\0';
		SendClientMessageToAll ( color, szBuffer );
	}
					
} /* namespace sysChat */
