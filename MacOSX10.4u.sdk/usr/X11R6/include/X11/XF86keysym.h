/* $XFree86: xc/include/XF86keysym.h,v 1.17 2003/02/14 22:02:26 dawes Exp $ */

/*
 * XFree86 vendor specific keysyms.
 *
 * The XFree86 keysym range is 0x10080001 - 0x1008FFFF.
 *
 * When adding new entries, the xc/lib/XKeysymDB file should also be
 * updated to make the new entries visible to Xlib.
 */

/*
 * ModeLock
 *
 * This one is old, and not really used any more since XKB offers this
 * functionality.
 */

#define XF86XK_ModeLock		0x1008FF01	/* Mode Switch Lock */

/*
 * Note, 0x1008FF02 - 0x1008FF0F are free and should be used for misc new
 * keysyms that don't fit into any of the groups below.
 *
 * 0x1008FF64, 0x1008FF6F, 0x1008FF71, 0x1008FF83 are no longer used,
 * and should be used first for new keysyms.
 *
 * Check in keysymdef.h for generic symbols before adding new XFree86-specific
 * symbols here.
 */


/*
 * Keys found on some "Internet" keyboards.
 */
#define XF86XK_Standby		0x1008FF10
#define XF86XK_AudioLowerVolume	0x1008FF11
#define XF86XK_AudioMute	0x1008FF12
#define XF86XK_AudioRaiseVolume	0x1008FF13
#define XF86XK_AudioPlay	0x1008FF14
#define XF86XK_AudioStop	0x1008FF15
#define XF86XK_AudioPrev	0x1008FF16
#define XF86XK_AudioNext	0x1008FF17
#define XF86XK_HomePage		0x1008FF18
#define XF86XK_Mail		0x1008FF19
#define XF86XK_Start		0x1008FF1A
#define XF86XK_Search		0x1008FF1B
#define XF86XK_AudioRecord	0x1008FF1C

/* These are sometimes found on PDA's (e.g. Palm, PocketPC or elsewhere) */
#define XF86XK_Calculator	0x1008FF1D
#define XF86XK_Memo		0x1008FF1E
#define XF86XK_ToDoList		0x1008FF1F
#define XF86XK_Calendar		0x1008FF20
#define XF86XK_PowerDown	0x1008FF21
#define XF86XK_ContrastAdjust	0x1008FF22
#define XF86XK_RockerUp		0x1008FF23
#define XF86XK_RockerDown	0x1008FF24
#define XF86XK_RockerEnter	0x1008FF25

/* Some more "Internet" keyboard symbols */
#define XF86XK_Back		0x1008FF26
#define XF86XK_Forward		0x1008FF27
#define XF86XK_Stop		0x1008FF28
#define XF86XK_Refresh		0x1008FF29
#define XF86XK_PowerOff		0x1008FF2A
#define XF86XK_WakeUp		0x1008FF2B
#define XF86XK_Eject            0x1008FF2C
#define XF86XK_ScreenSaver      0x1008FF2D
#define XF86XK_WWW              0x1008FF2E
#define XF86XK_Sleep            0x1008FF2F
#define XF86XK_Favorites	0x1008FF30
#define XF86XK_AudioPause	0x1008FF31
#define XF86XK_AudioMedia	0x1008FF32
#define XF86XK_MyComputer	0x1008FF33
#define XF86XK_VendorHome	0x1008FF34
#define XF86XK_LightBulb	0x1008FF35
#define XF86XK_Shop		0x1008FF36
#define XF86XK_History		0x1008FF37
#define XF86XK_OpenURL		0x1008FF38
#define XF86XK_AddFavorite	0x1008FF39
#define XF86XK_HotLinks		0x1008FF3A
#define XF86XK_BrightnessAdjust	0x1008FF3B
#define XF86XK_Finance		0x1008FF3C
#define XF86XK_Community	0x1008FF3D
#define XF86XK_AudioRewind	0x1008FF3E
#define XF86XK_XF86BackForward	0x1008FF3F
#define XF86XK_Launch0		0x1008FF40
#define XF86XK_Launch1		0x1008FF41
#define XF86XK_Launch2		0x1008FF42
#define XF86XK_Launch3		0x1008FF43
#define XF86XK_Launch4		0x1008FF44
#define XF86XK_Launch5		0x1008FF45
#define XF86XK_Launch6		0x1008FF46
#define XF86XK_Launch7		0x1008FF47
#define XF86XK_Launch8		0x1008FF48
#define XF86XK_Launch9		0x1008FF49
#define XF86XK_LaunchA		0x1008FF4A
#define XF86XK_LaunchB		0x1008FF4B
#define XF86XK_LaunchC		0x1008FF4C
#define XF86XK_LaunchD		0x1008FF4D
#define XF86XK_LaunchE		0x1008FF4E
#define XF86XK_LaunchF		0x1008FF4F

#define XF86XK_ApplicationLeft	0x1008FF50
#define XF86XK_ApplicationRight	0x1008FF51
#define XF86XK_Book		0x1008FF52
#define XF86XK_CD		0x1008FF53
#define XF86XK_Calculater	0x1008FF54
#define XF86XK_Clear		0x1008FF55
#define XF86XK_Close		0x1008FF56
#define XF86XK_Copy		0x1008FF57
#define XF86XK_Cut		0x1008FF58
#define XF86XK_Display		0x1008FF59
#define XF86XK_DOS		0x1008FF5A
#define XF86XK_Documents	0x1008FF5B
#define XF86XK_Excel		0x1008FF5C
#define XF86XK_Explorer		0x1008FF5D
#define XF86XK_Game		0x1008FF5E
#define XF86XK_Go		0x1008FF5F
#define XF86XK_iTouch		0x1008FF60
#define XF86XK_LogOff		0x1008FF61
#define XF86XK_Market		0x1008FF62
#define XF86XK_Meeting		0x1008FF63
#define XF86XK_MenuKB		0x1008FF65
#define XF86XK_MenuPB		0x1008FF66
#define XF86XK_MySites		0x1008FF67
#define XF86XK_New		0x1008FF68
#define XF86XK_News		0x1008FF69
#define XF86XK_OfficeHome	0x1008FF6A
#define XF86XK_Open		0x1008FF6B
#define XF86XK_Option		0x1008FF6C
#define XF86XK_Paste		0x1008FF6D
#define XF86XK_Phone		0x1008FF6E
#define XF86XK_Q		0x1008FF70
#define XF86XK_Reply		0x1008FF72
#define XF86XK_Reload		0x1008FF73
#define XF86XK_RotateWindows	0x1008FF74
#define XF86XK_RotationPB	0x1008FF75
#define XF86XK_RotationKB	0x1008FF76
#define XF86XK_Save		0x1008FF77
#define XF86XK_ScrollUp		0x1008FF78
#define XF86XK_ScrollDown	0x1008FF79
#define XF86XK_ScrollClick	0x1008FF7A
#define XF86XK_Send		0x1008FF7B
#define XF86XK_Spell		0x1008FF7C
#define XF86XK_SplitScreen	0x1008FF7D
#define XF86XK_Support		0x1008FF7E
#define XF86XK_TaskPane		0x1008FF7F
#define XF86XK_Terminal		0x1008FF80
#define XF86XK_Tools		0x1008FF81
#define XF86XK_Travel		0x1008FF82
#define XF86XK_UserPB		0x1008FF84
#define XF86XK_User1KB		0x1008FF85
#define XF86XK_User2KB		0x1008FF86
#define XF86XK_Video		0x1008FF87
#define XF86XK_WheelButton	0x1008FF88
#define XF86XK_Word		0x1008FF89
#define XF86XK_Xfer		0x1008FF8A
#define XF86XK_ZoomIn		0x1008FF8B
#define XF86XK_ZoomOut		0x1008FF8C

#define XF86XK_Away		0x1008FF8D
#define XF86XK_Messenger	0x1008FF8E
#define XF86XK_WebCam		0x1008FF8F
#define XF86XK_MailForward	0x1008FF90
#define XF86XK_Pictures		0x1008FF91
#define XF86XK_Music		0x1008FF92

/* Keys for special action keys (hot keys) */
#define XF86XK_Switch_VT_1	0x1008FE01
#define XF86XK_Switch_VT_2	0x1008FE02
#define XF86XK_Switch_VT_3	0x1008FE03
#define XF86XK_Switch_VT_4	0x1008FE04
#define XF86XK_Switch_VT_5	0x1008FE05
#define XF86XK_Switch_VT_6	0x1008FE06
#define XF86XK_Switch_VT_7	0x1008FE07
#define XF86XK_Switch_VT_8	0x1008FE08
#define XF86XK_Switch_VT_9	0x1008FE09
#define XF86XK_Switch_VT_10	0x1008FE0A
#define XF86XK_Switch_VT_11	0x1008FE0B
#define XF86XK_Switch_VT_12	0x1008FE0C

#define XF86XK_Ungrab		0x1008FE20
#define XF86XK_ClearGrab	0x1008FE21
#define XF86XK_Next_VMode	0x1008FE22
#define XF86XK_Prev_VMode	0x1008FE23

