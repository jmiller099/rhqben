/* Copyright (c) 2017, Computer History Museum All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below) provided that the following conditions are met:  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following    disclaimer in the documentation and/or other materials provided with the distribution.  * Neither the name of Computer History Museum nor the names of its contributors may be used to endorse or promote products    derived from this software without specific prior written permission. NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */#ifdef DIAL#include "dial.h"/* Dial telephone number */#define FILE_NUM 123#pragma segment DIAL#define kPauseSeconds 2/************************************************************************ * prototypes ************************************************************************/void DialSpeaker(StringPtr number);void DialModem(StringPtr number);/************************************************************************ * Dial - dial a telephone number through speaker or modem ************************************************************************/void Dial(StringPtr number, short mode){	if (!*number) return;	//	nothing to dial		if (!mode)		mode = PrefIsSet(PREF_DIAL_MODE) ? kDialModem : kDialSpeaker;	switch (mode)	{		case kDialSpeaker:	DialSpeaker(number); break;		case kDialModem:	DialModem(number); break;	}}/************************************************************************ * DialSpeaker - dial telephone number through speaker ************************************************************************/void DialSpeaker(StringPtr number){	short	i;		for(i=1;i<=*number;i++)	{		char	c=number[i];		long	finalTicks;		short	soundID;		soundID = 0;		switch (c)		{			case '0':			case '1':			case '2':			case '3':			case '4':			case '5':			case '6':			case '7':			case '8':			case '9':				soundID = DIAL_0_SND + c - '0'; break;			case '*':				soundID = DIAL_STAR_SND; break;			case '#':				soundID = DIAL_POUND_SND; break;				break;						case ',':				// pause on comma				Delay(kPauseSeconds*60, &finalTicks);				break;				}				if (soundID)		{					// dial this digit			Handle	hSound;								if (hSound = GetResource('snd ',soundID))			{				SndPlay(nil,hSound,false);				ReleaseResource(hSound);			}		}	}}/************************************************************************ * DialModem - dial telephone number through modem ************************************************************************/void DialModem(StringPtr number){}#endif