/*
	File:		afpHLMount.h

	Contains:	High level url based access to the AppleShare Client

	Copyright:	(c) 2000 - 2010 by Apple Inc., all rights reserved.	
*/

#ifdef __cplusplus
extern "C" {
#endif

/* Options bit definitions	*/	
#define		kAFPUseExistingMountBit		0
#define		kAFPNoNewMountBit			1
#define		kAFPMountPointProvidedBit	2
#define		kAFPForceNewSessionBit		3
#define		kAFPAutomountedBit			4
#define		kAFPNoNotify				5
#define		kAFPDontBrowse				6
#define		kAFPMountAllVols			7
#define		kAFPSupressKeychainBit		8
#define		kAFPAllowUNCHIBit			9
#define		kAFPSoftMountBit			12
#define		kAFPAllowSelfConnection		13

/*
    if no bits are set and the volume is already mounted we return afpAlreadyMounted (-5062)
    if kUseExistingMount is set and the volume is already mounted we return noErr
    if kNoNewMount is set and the volume is mounted we return noErr
    if kNoNewMount is set and the volume is not already mounted we return nsvErr (-35)
    
    if kAFPMountPointProvidedBit is set then the volume is mounted on the mount point passed in.
    if kAFPForceNewSessionBit is set, then we will not check for existing sessions during mounting.


*/

struct mountinfo {
	short	length;
	OSType	media;
	short	flags;
	char	media_specific[0];
};

typedef struct mountinfo mountinfo;

int	afp_LLMount(const char* inFullURL, const char* inMountDir, size_t inMaxPath, char* outMountPoint, UInt32 inOptions);

int 	afp_LLMountAuth(const char *inTargetURL, const char *inMountDir, 
						size_t inMaxPath, char *outMountPoint, const char* inAuthDomain,
						const char *inUserName, const char *inUAMName,
						void *authenticator, size_t authenticatorlength,
						UInt32 inOptions);

int	afp_getMountURL(const char* inMountPoint, size_t inMaxURL, char* outMountURL, UInt32 inOptions);

int 	afp_GetURLFromURLRemountInfo(const mountinfo *inRemountinfo, size_t inMaxURLlength, char *outComplete_URL, UInt32 inOptions);

int	afp_getmountinfosize(const char* inMountPoint, size_t* outSize, UInt32 inOptions);

int	afp_getmountinfo(const char* inMountPoint, size_t inMountInfoMaxSize, mountinfo* outMountInfo, UInt32 inOptions);

#ifdef __cplusplus		
};
#endif

