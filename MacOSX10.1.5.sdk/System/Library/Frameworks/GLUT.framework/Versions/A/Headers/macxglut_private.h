
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


/* *** supported build switches *** */

#define	__APPLE__						1		// must be set
//#define	VERBOSE						0		// normal debug output level
//#define	VERBOSE1						0		// GLUTVisual matching subsystem debug output


#import <AppKit/AppKit.h>
# import <OpenGL/gl.h>
# import <OpenGL/glu.h>
#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <stdarg.h>
#import <sys/time.h>

#import "macxglut_utilities.h"

#define	GLUT_PERIODIC_DELAY	0.14
#define	kGLUTPeriodicDelay  0.0
#define kGLUTPeriodicPeriod 0.00001 // .001msec

	/* many greetings from Windows ! */
#ifndef APIENTRY
#define APIENTRY
#endif

@class GLUTAppDelegate, GLUTView, GLUTMenu;

/* *** types *** */

typedef void	(*GLUTKeyboardCallback)(unsigned char key, int x, int y);
typedef void	(*GLUTMouseCallback)(int button, int state, int x, int y);
typedef void	(*GLUTMotionCallback)(int x, int y);
typedef void	(*GLUTVisibilityCallback)(int state);
typedef void	(*GLUTEntryCallback)(int state);
typedef void	(*GLUTWindowStatusCallback)(int state);
typedef void	(*GLUTSpecialCallback)(int key, int x, int y);
typedef void	(*GLUTDisplayCallback)(void);
typedef void	(*GLUTReshapeCallback)(int width, int height);
typedef void	(*GLUTMenuCallback)(int value);
typedef void	(*GLUTMenuStatusCallback)(int state, int x, int y);
typedef void	(*GLUTSpaceballMotionCallback)(int x, int y, int z);
typedef void	(*GLUTSpaceballRotateCallback)(int x, int y, int z);
typedef void	(*GLUTSpaceballButtonCallback)(int button, int state);
typedef void	(*GLUTButtonBoxCallback)(int button, int state);
typedef void	(*GLUTDialCallback)(int dial, int value);
typedef void	(*GLUTTabletMotionCallback)(int x, int y);
typedef void	(*GLUTTabletButtonCallback)(int button, int state, int x, int y);
typedef void	(*GLUTJoystickCallback)(unsigned int buttonMask, int x, int y, int z);
typedef void	(*GLUTIdleCallback)(void);
typedef void	(*GLUTTimerCallback)(int value);


/* *** globals *** */

extern GLUTAppDelegate *						__glutAppDel;
extern int						__glutArgc;
extern char **					__glutArgv;
extern char *					__glutGeometry;
extern int						__glutScreenHeight;
extern int						__glutScreenWidth;
extern BOOL						__glutIconic;
extern BOOL						__glutDebug;
extern unsigned int				__glutDisplayMode;
extern NSOpenGLPixelFormat *	__glutPixelFormat;
extern int						__glutInitWidth;
extern int						__glutInitHeight;
extern int						__glutInitX;
extern int						__glutInitY;
extern NSMapTable *				__glutViewList;				/* list of GLUT top-level & sub- windows */
extern GLUTView *				__glutCurrentView;
extern int						__glutGameModeWindow;
extern NSMapTable *				__glutMenuList;
extern GLUTMenu *				__glutCurrentMenu;
extern GLUTMenuStatusCallback	__glutMenuStatusCallback;
extern GLUTIdleCallback			__glutIdleCallback;
extern BOOL				__glutInDrawingCallback;
extern GLUTTimerCallback		__glutTimerCallback;
extern int						__glutTimerValue;
extern BOOL						__glutFinishedInitialization;
extern NSTimeInterval			__glutPeriodicEventDelay;
extern int						__glutWindowUniqueID;
extern int						__glutMenuUniqueID;
extern BOOL						__glutMenuMode;
extern BOOL						__glutGameMode;
extern NSTimer *				__glutPeriodicObject;
extern BOOL						__glutEmulateMultiButtonMouse;
extern NSTimeInterval			__glutStartupTime;

enum {
	kGLUTEventViewUpdate,
	kGLUTEventViewRedisplay,
};


/* *** macros *** */

#define	FailNil(x)	if((x) == nil) goto _failed

#define	FWLocalizedString(key)	[[NSBundle bundleForClass: [GLUTApplication class]] localizedStringForKey: (key) value: nil table: nil]
