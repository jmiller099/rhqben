/* Copyright (c) 2017, Computer History Museum All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below) provided that the following conditions are met:  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following    disclaimer in the documentation and/or other materials provided with the distribution.  * Neither the name of Computer History Museum nor the names of its contributors may be used to endorse or promote products    derived from this software without specific prior written permission. NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. *//*	Code taken from Tech Note 1145*/#include "MachOWrapper.h"/* Ripped off from:	"/System/Library/Frameworks/SystemConfiguration.framework/Versions/A/Headers/SCNetwork.h" 	Boolean SCNetworkCheckReachabilityByName (	const char *nodename,	SCNetworkConnectionFlags	*flags	);*/	typedef enum {	kSCNetworkFlagsTransientConnection	=  1<<0,	kSCNetworkFlagsReachable			=  1<<1,	kSCNetworkFlagsConnectionRequired	=  1<<2,	kSCNetworkFlagsConnectionAutomatic	=  1<<3,	kSCNetworkFlagsInterventionRequired	=  1<<4,} SCNetworkConnectionFlags;Boolean CHostUnreachableByPPP ( char *serverName ) {	Boolean result;//	SCNetworkConnectionFlags flags;//	IMPORTANT://	To work with CodeWarrior you should set the//	"enums are always int" option, which the CWPro8//	Mach-O stationery fails to do.//	assert(sizeof(SCNetworkConnectionFlags) == sizeof(int));//	Marshall sez: We'll just pass an int!	int flags;	static MachOWrapper<Boolean (*)(const char *, int * )>		SCNetworkCheckReachabilityByName ( CFSTR ( "SystemConfiguration.framework" ), CFSTR ( "SCNetworkCheckReachabilityByName" ));	result = false;	if ( SCNetworkCheckReachabilityByName.IsValid ())		if ( SCNetworkCheckReachabilityByName ( serverName, &flags )) {			result = (flags & kSCNetworkFlagsConnectionRequired)!=0;			}	return result;	}	UInt32 SwapQDTextFlags ( UInt32 flags ) {	static MachOWrapper<UInt32 (*)( UInt32 )>		QDSwapTextFlags ( CFSTR ( "CoreFoundation.framework" ), CFSTR ( "SwapQDTextFlags" ));	if ( QDSwapTextFlags.IsValid ())		 return QDSwapTextFlags ( flags );	return kQDDontChangeFlags;	}extern "C" Boolean OnBatteriesX ( void );Boolean OnBatteriesX () {	Boolean retVal = false;//	These are the functions that we need//	They (and the constants below) are taken from <IOKit/ps/IOPowerSources.h>	static MachOWrapper<CFTypeRef (*) (void)>IOPSCopyPowerSourcesInfo ( CFSTR ( "IOKit.framework" ), CFSTR ( "IOPSCopyPowerSourcesInfo" ));	static MachOWrapper<CFArrayRef (*) (CFTypeRef)>IOPSCopyPowerSourcesList ( CFSTR ( "IOKit.framework" ), CFSTR ( "IOPSCopyPowerSourcesList" ));	static MachOWrapper<CFDictionaryRef (*) (CFTypeRef, CFTypeRef)>IOPSGetPowerSourceDescription ( CFSTR ( "IOKit.framework" ), CFSTR ( "IOPSGetPowerSourceDescription" ));//	From <IOKit/ps/IOPSKeys.h>	#define kIOPSACPowerValue              "AC Power"	#define kIOPSBatteryPowerValue         "Battery Power"//	Type CFString, value is kIOPSACPowerValue or kIOPSBatteryPowerValue	#define kIOPSPowerSourceStateKey       "Power Source State"//	Fail-Safe: If we can't get any power info, we're not on battery	if ( IOPSCopyPowerSourcesInfo.IsValid ()) {	    CFTypeRef		psInfo = IOPSCopyPowerSourcesInfo ();	    CFArrayRef		psList = IOPSCopyPowerSourcesList ( psInfo );	    CFDictionaryRef	one_ps;	    CFStringRef		state;	    int				count;		int				anyPower = -1;	// tri-state			    count = CFArrayGetCount ( psList );	    for ( int i = 0; i < count; ++i ) {			one_ps = IOPSGetPowerSourceDescription ( psInfo, CFArrayGetValueAtIndex ( psList, i ));			if ( NULL == one_ps )				break;			state = (CFStringRef) CFDictionaryGetValue ( one_ps, CFSTR ( kIOPSPowerSourceStateKey ));		//	If any of the power sources are on AC, then we're not on battery			if ( CFEqual ( state, CFSTR ( kIOPSACPowerValue ))) {				anyPower = 1;				break;				}			anyPower = 0;			}	    CFRelease ( psList );	    CFRelease ( psInfo );	//	If we found any power sources, then return the settings		if ( anyPower != -1 )			retVal = anyPower == 0;		}			return retVal;	}