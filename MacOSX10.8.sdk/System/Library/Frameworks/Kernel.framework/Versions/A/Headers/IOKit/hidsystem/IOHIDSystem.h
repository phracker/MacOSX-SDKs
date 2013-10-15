/*
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2009 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * EventDriver.h - Exported Interface Event Driver object.
 *
 *		The EventDriver is a pseudo-device driver.
 *
 * HISTORY
 * 19 Mar 1992    Mike Paquette at NeXT
 *      Created. 
 * 4  Aug 1993	  Erik Kay at NeXT
 *	API cleanup
 */

#ifndef	_IOHIDSYSTEM_H
#define _IOHIDSYSTEM_H

#include <TargetConditionals.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOService.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/pwr_mgt/IOPM.h>
#if TARGET_OS_EMBEDDED
class IOGraphicsDevice;
#else
#include <IOKit/graphics/IOGraphicsDevice.h>
#endif
#include <IOKit/hidsystem/IOHIDevice.h>
#include <IOKit/hidsystem/IOHIDShared.h>
#include <IOKit/hidsystem/IOHIDTypes.h>
#include <IOKit/hidsystem/IOLLEvent.h>
#include <IOKit/IODataQueue.h>
#include <IOKit/hidsystem/ev_keymap.h>		/* For NX_NUM_SCANNED_SPECIALKEYS */

           
// The following messages should be unique across the entire system
#ifndef sub_iokit_hidsystem
#define sub_iokit_hidsystem                     err_sub(14)
#endif

#define kIOHIDSystem508MouseClickMessage        iokit_family_msg(sub_iokit_hidsystem, 1)
#define kIOHIDSystemDeviceSeizeRequestMessage	iokit_family_msg(sub_iokit_hidsystem, 2)
#define kIOHIDSystem508SpecialKeyDownMessage    iokit_family_msg(sub_iokit_hidsystem, 3)
// 4 is used by IOHIDSecurePrompt
#define kIOHIDSystemActivityTickle              iokit_family_msg(sub_iokit_hidsystem, 5)


class IOHIDKeyboardDevice;
class IOHIDPointingDevice;
class IOHIDEvent;
class IOFixedPoint64;

class IOHIDSystem : public IOService
{
	OSDeclareDefaultStructors(IOHIDSystem);

	friend class IOHIDUserClient;
	friend class IOHIDParamUserClient;
	friend class IOHIDEventSystemUserClient;

private:
	IOWorkLoop *		workLoop;
	IOTimerEventSource *  	timerES;
	IOTimerEventSource *  	vblES;
        IOInterruptEventSource * eventConsumerES;
        IOInterruptEventSource * keyboardEQES;
        IOCommandGate *		cmdGate;
	IOUserClient *		serverConnect;
	IOUserClient *		paramConnect;
        IONotifier *		eventPublishNotify;
        IONotifier *		eventTerminateNotify;
        IONotifier *		publishNotify;
        IONotifier *		terminateNotify;
        
        OSArray *		ioHIDevices;
    OSSet             * touchEventPosters;

	// Ports on which we hold send rights
	mach_port_t	eventPort;	// Send msg here when event queue
					// goes non-empty
    mach_port_t stackShotPort;
	mach_port_t	_specialKeyPort[NX_NUM_SCANNED_SPECIALKEYS]; // Special key msgs
	void		*eventMsg;	// Msg to be sent to Window Server.
	void		*stackShotMsg;	// Msg to be sent to Stack Shot.

	// Shared memory area information
    IOBufferMemoryDescriptor * globalMemory;
	uintptr_t	shmem_addr;	// kernel address of shared memory
	vm_size_t	shmem_size;	// size of shared memory
    
	// Pointers to structures which occupy the shared memory area.
	volatile void	*evs;		// Pointer to private driver shmem
	volatile EvGlobals *evg;	// Pointer to EvGlobals (shmem)
	// Internal variables related to the shared memory area
	int		lleqSize;	// # of entries in low-level queue
                        // FIXME: why is this ivar lleqSize an ivar? {Dan]

	// Screens list
	vm_size_t	evScreenSize;	// Byte size of evScreen array
	void		*evScreen;	// array of screens known to driver
	volatile void	*lastShmemPtr;	// Pointer used to index thru shmem
					// while assigning shared areas to
					// drivers.
	int		screens;	// running total of allocated screens
	UInt32		cursorScreens;	// bit mask of screens with cursor present
        UInt32		cursorPinScreen;// a screen to pin against
	IOGBounds		cursorPin;	// Range to which cursor is pinned
					// while on this screen.
	IOGBounds		workSpace;	// IOGBounds of full workspace.
	// Event Status state - This includes things like event timestamps,
	// time til screen dim, and related things manipulated through the
	// Event Status API.
	//
    struct ExpansionData;
    union {
        struct {
            IOGPoint	for_spacing_only[2];
        }               reserved;
        ExpansionData   *_privateData;
    }; // Anon union
    
    IOGPoint	clickLoc;       // location of last mouse click
    IOGPoint    clickSpaceThresh;// max mouse delta to be a doubleclick
    
	int	clickState;	// Current click state

	bool evOpenCalled;	// Has the driver been opened?
	bool evInitialized;	// Has the first-open-only initialization run?
    bool evStateChanging;   // Is the event system state changing.
	bool eventsOpen;	// Boolean: has evmmap been called yet?
	bool cursorStarted;	// periodic events running?
	bool cursorEnabled;	// cursor positioning ok?
	bool cursorCoupled;	// cursor positioning on pointer moves ok?
	bool cursorPinned;	// cursor positioning on pointer moves ok?

	short leftENum;		// Unique ID for last left down event
	short rightENum;	// Unique ID for last right down event
	
	// The periodic event mechanism timestamps and state
	// are recorded here.
	AbsoluteTime thisPeriodicRun;
        AbsoluteTime periodicEventDelta;// Time between periodic events
                                        // todo: make infinite
        AbsoluteTime clickTime;		// Timestamps used to determine doubleclicks
        AbsoluteTime clickTimeThresh;

        AbsoluteTime waitSustain;	// Sustain time before removing cursor
        AbsoluteTime waitSusTime;	// Sustain counter
        AbsoluteTime waitFrameRate;	// Ticks per wait cursor frame
        AbsoluteTime waitFrameTime;	// Wait cursor frame timer

        AbsoluteTime lastRelativeEventTime;	// Used to post mouse events once per frame
        AbsoluteTime lastRelativeMoveTime;
        AbsoluteTime lastEventTime;
        AbsoluteTime lastUndimEvent;
    SInt32  reserved2[4];
    //SInt32 postDeltaX, accumDX;
    //SInt32 postDeltaY, accumDY;

	// Flags used in scheduling periodic event callbacks
	bool		needSetCursorPosition;
	bool		needToKickEventConsumer;
        
        IOService *	displayManager;	// points to display manager
        IOPMPowerFlags	displayState;
        
        IOService *	rootDomain;
        AbsoluteTime	rootDomainStateChangeDeadline;
        AbsoluteTime    displayStateChangeDeadline;
        AbsoluteTime    displaySleepWakeupDeadline;
        bool  displaySleepDrivenByPM;
        
        OSDictionary *  savedParameters;	// keep user settings
        
        const char *    registryName;		// cache our name
        UInt32		maxWaitCursorFrame;	// animation frames
	UInt32		firstWaitCursorFrame;	//
        
        int		cachedEventFlags;
        OSArray *  cachedButtonStates;
        
        OSArray * systemInfo;
        
        IOHIDPointingDevice * _hidPointingDevice;
        IOHIDKeyboardDevice * _hidKeyboardDevice;

        /* The consumed keys array stores key codes for which a key down event
         * has been consumed and a corresponding key up event must be consumed
         * when it arrives.
         */
        OSArray * consumedKeys;
        
    OSObject * lastSender;
    
        UInt32 scrollZoomMask;
        
    bool setParamPropertiesInProgress;
    
    OSSet * dataQueueSet;
        
private:
    void vblEvent(void);
    UInt8 getSubtypeForSender(OSObject * sender);
    void updateMouseEventForSender(OSObject * sender, NXEventData * evData);
    void updateMouseMoveEventForSender(OSObject * sender, NXEventData * evData);
    void updateScrollEventForSender(OSObject * sender, NXEventData * evData);
    static void _vblEvent(OSObject *self, IOTimerEventSource *sender);

  inline short getUniqueEventNum();

  virtual IOReturn powerStateDidChangeTo( IOPMPowerFlags, unsigned long, IOService * );
  static IOReturn powerStateHandler( void *target, void *refCon,
               UInt32 messageType, IOService *service, void *messageArgument, vm_size_t argSize );
 /* Resets */
    void    _resetMouseParameters();
    void    _setScrollCountParameters(OSDictionary *newSettings = NULL);

  /* Initialize the shared memory area */
  void     initShmem(bool clean);
  /* Dispatch low level events through shared memory to the WindowServer */
  void postEvent(       int        what,
          /* at */      IOFixedPoint64 *       location,
          /* atTime */  AbsoluteTime  ts,
          /* withData */NXEventData * myData,
          /* sender */  OSObject *    sender   = 0,
          /* pid */     UInt32        extPID   = 0,
          /* processKEQ*/bool          processKEQ = true);
  /* Dispatch mechanisms for screen state changes */
  void evDispatch(
            /* command */ EvCmd evcmd);
  /* Dispatch mechanism for special key press */
  void evSpecialKeyMsg(unsigned key,
               /* direction */ unsigned dir,
               /* flags */     unsigned f,
               /* level */     unsigned l);
  /* Message the event consumer to process posted events */
  void kickEventConsumer();
  void sendStackShotMessage(UInt32 flavor);
  
  OSDictionary * createFilteredParamPropertiesForService(IOService * service, OSDictionary * dict);

  static void _periodicEvents(IOHIDSystem * self,
                              IOTimerEventSource *timer);

  static void doSpecialKeyMsg(IOHIDSystem * self,
					struct evioSpecialKeyMsg *msg);
  static void doKickEventConsumer(IOHIDSystem * self);

  static void doProcessKeyboardEQ(IOHIDSystem * self);
  static void processKeyboardEQ(IOHIDSystem * self, AbsoluteTime * deadline = 0);
 
  static bool genericNotificationHandler( void * target, 
				void * ref, IOService * newService, IONotifier * notifier );
                
  static bool handlePublishNotification( void * target, IOService * newService );

  static bool handleTerminateNotification( void * target, IOService * service );

  static void makeNumberParamProperty( OSDictionary * dict, const char * key,
                            unsigned long long number, unsigned int bits );

  static void makeInt32ArrayParamProperty( OSDictionary * dict, const char * key,
                            UInt32 * array, unsigned int count );

/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOHIDSystem(Input) category;
 *   the declarations have now been merged directly into this class.
 *
 * Exported Interface Event Driver object input services.
 */

private:
  // Schedule next periodic run based on current event system state.
  void scheduleNextPeriodicEvent();
  // Message invoked to run periodic events.  This method runs in the workloop.
  void periodicEvents(IOTimerEventSource *timer);
  // Start the cursor running.
  bool startCursor();
  // Repin cursor location.
  bool resetCursor();
  // Wait Cursor machinery.
  void showWaitCursor();
  void hideWaitCursor();
  void animateWaitCursor();
  void changeCursor(int frame);
  // Return screen number a point lies on.
  int  pointToScreen(IOGPoint * p);

  inline void showCursor();
  inline void hideCursor();
  inline void moveCursor();
  // Claim ownership of event sources.
  void attachDefaultEventSources();
  // Give up ownership of event sources.
  void detachEventSources();
  bool registerEventSource(IOService * source);

  // Set abs cursor position.
  void setCursorPosition(IOGPoint * newLoc, bool external, OSObject * sender=0);
  void _setButtonState(int buttons,
                       /* atTime */ AbsoluteTime ts,
                       OSObject * sender);
  void _setCursorPosition(bool external = false, bool proximityChange = false, OSObject * sender=0);

  static bool _idleTimeSerializerCallback(void * target, void * ref, OSSerialize *s);

  void _postMouseMoveEvent(int		what,
                           AbsoluteTime	theClock,
                           OSObject *	sender);
  void createParameters( void );

/* END HISTORICAL NOTE */

public:
  static IOHIDSystem * instance();     /* Return the current instance of the */
				       /* EventDriver, or 0 if none. */
  static void scaleLocationToCurrentScreen(IOGPoint *location, IOGBounds *bounds);

  virtual bool init(OSDictionary * properties = 0);
  virtual IOHIDSystem * probe(IOService *    provider,
                              SInt32 * score);
  virtual bool start(IOService * provider);
  virtual IOReturn message(UInt32 type, IOService * provider,
				void * argument);
  virtual void free();
  virtual bool attach( IOService * provider );
  virtual void detach( IOService * provider );

  virtual IOWorkLoop *getWorkLoop() const;

  virtual IOReturn evOpen(void);
  virtual IOReturn evClose(void);

  virtual IOReturn  setProperties( OSObject * properties );
  virtual IOReturn  setParamProperties(OSDictionary * dict);

  /* Create the shared memory area */
  virtual IOReturn createShmem(void*,void*,void*,void*,void*,void*);

  /* register the IODataQueue for the new user events */
  virtual IOReturn registerEventQueue(IODataQueue * queue);

  /* Unregister the IODataQueue for the new user events */
  virtual IOReturn unregisterEventQueue(IODataQueue * queue);

  /* Set the port for event available notify msg */
  virtual void     setEventPort(mach_port_t port);

  /* Set if display sleep is driven by IOPMrootDomain */
  void setDisplaySleepDrivenByPM(bool val);
private:
    static IOReturn doSetEventPort(IOHIDSystem *self, void *port_void, void *arg1, void *arg2, void *arg3);
    void            setEventPortGated(mach_port_t port);
public:

  /* Set the port for the special key keypress msg */
  virtual IOReturn setSpecialKeyPort(
                     /* keyFlavor */ int         special_key,
                     /* keyPort */   mach_port_t key_port);
  virtual mach_port_t specialKeyPort(int special_key);


  virtual IOReturn newUserClient(task_t         owningTask,
                 /* withToken */ void *         security_id,
                 /* ofType */    UInt32         type,
                 /* withProps*/  OSDictionary *  properties,
                 /* client */    IOUserClient ** handler);

/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOHIPointingEvents protocol;
 *   the declarations have now been merged directly into this class.
 */

public: 
  /* Mouse event reporting */
  virtual void relativePointerEvent(int        buttons,
                       /* deltaX */ int        dx,
                       /* deltaY */ int        dy,
                       /* atTime */ AbsoluteTime ts);

  /* Tablet event reporting */
  virtual void absolutePointerEvent(int        buttons,
                 /* at */           IOGPoint *    newLoc,
                 /* withBounds */   IOGBounds *bounds,
                 /* inProximity */  bool       proximity,
                 /* withPressure */ int        pressure,
                 /* withAngle */    int        stylusAngle,
                 /* atTime */       AbsoluteTime ts);

  /* Mouse scroll wheel event reporting */
  virtual void scrollWheelEvent(short deltaAxis1,
                                short deltaAxis2,
                                short deltaAxis3,
                                AbsoluteTime ts);
  

  virtual void tabletEvent(NXEventData *tabletData,
                           AbsoluteTime ts);

  virtual void proximityEvent(NXEventData *proximityData,
                              AbsoluteTime ts);

/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOHIKeyboardEvents protocol;
 *   the declarations have now been merged directly into this class.
 */

public:
  virtual void keyboardEvent(unsigned   eventType,
      /* flags */            unsigned   flags,
      /* keyCode */          unsigned   key,
      /* charCode */         unsigned   charCode,
      /* charSet */          unsigned   charSet,
      /* originalCharCode */ unsigned   origCharCode,
      /* originalCharSet */  unsigned   origCharSet,
      /* keyboardType */     unsigned   keyboardType,
      /* repeat */           bool       repeat,
      /* atTime */           AbsoluteTime ts);

  virtual void keyboardSpecialEvent(   unsigned   eventType,
                    /* flags */        unsigned   flags,
                    /* keyCode  */     unsigned   key,
                    /* specialty */    unsigned   flavor,
                    /* guid */ 	       UInt64     guid,
                    /* repeat */       bool       repeat,
                    /* atTime */       AbsoluteTime ts);

  virtual void updateEventFlags(unsigned flags);  /* Does not generate events */




private:

  /*
   * statics for upstream callouts
   */

  void _scaleLocationToCurrentScreen(IOFixedPoint64 &location, IOGBounds *bounds);

  static void _relativePointerEvent(IOHIDSystem * self,
				    int        buttons,
                       /* deltaX */ int        dx,
                       /* deltaY */ int        dy,
                       /* atTime */ AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);

  /* Tablet event reporting */
  static void _absolutePointerEvent(IOHIDSystem * self,
				    int        buttons,
                 /* at */           IOGPoint *    newLoc,
                 /* withBounds */   IOGBounds *bounds,
                 /* inProximity */  bool       proximity,
                 /* withPressure */ int        pressure,
                 /* withAngle */    int        stylusAngle,
                 /* atTime */       AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);

  /* Mouse scroll wheel event reporting */
  static void _scrollWheelEvent(    IOHIDSystem *self,
                                    short      deltaAxis1,
                                    short      deltaAxis2,
                                    short      deltaAxis3,
                                    IOFixed    fixedDelta1,
                                    IOFixed    fixedDelta2,
                                    IOFixed    fixedDelta3,
                                    SInt32  pointDeltaAxis1,
                                    SInt32  pointDeltaAxis2,
                                    SInt32  pointDeltaAxis3,
                                    UInt32  options,
                                    AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);

  static void _tabletEvent(         IOHIDSystem *self,
                                    NXEventData *tabletData,
                                    AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);

  static void _proximityEvent(      IOHIDSystem *self,
                                    NXEventData *proximityData,
                                    AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);

  static void _keyboardEvent(       IOHIDSystem * self,
                                    unsigned   eventType,
            /* flags */             unsigned   flags,
            /* keyCode */           unsigned   key,
            /* charCode */          unsigned   charCode,
            /* charSet */           unsigned   charSet,
            /* originalCharCode */  unsigned   origCharCode,
            /* originalCharSet */   unsigned   origCharSet,
            /* keyboardType */      unsigned   keyboardType,
            /* repeat */            bool       repeat,
            /* atTime */            AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);
            
  static void _keyboardSpecialEvent(IOHIDSystem * self,
                                    unsigned   eventType,
                /* flags */         unsigned   flags,
                /* keyCode  */      unsigned   key,
                /* specialty */     unsigned   flavor,
                /* guid */          UInt64     guid,
                /* repeat */        bool       repeat,
                /* atTime */        AbsoluteTime ts,
                                    OSObject * sender,
                                    void *     refcon);
                
  static void _updateEventFlags(    IOHIDSystem * self,
                                    unsigned   flags,
                                    OSObject * sender,
                                    void *     refcon);  /* Does not generate events */


/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOUserClient protocol;
 *   the declarations have now been merged directly into this class.
 */

public:

  virtual IOReturn setEventsEnable(void*,void*,void*,void*,void*,void*);
  virtual IOReturn setCursorEnable(void*,void*,void*,void*,void*,void*);
  virtual IOReturn extPostEvent(void*,void*,void*,void*,void*,void*);
  virtual IOReturn extSetMouseLocation(void*,void*,void*,void*,void*,void*);
  virtual IOReturn extGetButtonEventNum(void*,void*,void*,void*,void*,void*);
  IOReturn extSetBounds( IOGBounds * bounds );
    IOReturn extGetModifierLockState(void*,void*,void*,void*,void*,void*);
    IOReturn extSetModifierLockState(void*,void*,void*,void*,void*,void*);
    IOReturn extRegisterVirtualDisplay(void*,void*,void*,void*,void*,void*);
    IOReturn extUnregisterVirtualDisplay(void*,void*,void*,void*,void*,void*);
    IOReturn extSetVirtualDisplayBounds(void*,void*,void*,void*,void*,void*);

/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOScreenRegistration protocol;
 *   the declarations have now been merged directly into this class.
 *
 * Methods exported by the EventDriver for display systems.
 *
 *	The screenRegister protocol is used by frame buffer drivers to register
 *	themselves with the Event Driver.  These methods are called in response
 *	to an _IOGetParameterInIntArray() call with "IO_Framebuffer_Register" or
 *	"IO_Framebuffer_Unregister".
 */

public:
  virtual int registerScreen(IOGraphicsDevice * instance,
        /* bounds */         IOGBounds * bp,
        /* virtual bounds */ IOGBounds * vbp);
private:
    static IOReturn doRegisterScreen(IOHIDSystem *self, IOGraphicsDevice *io_gd, IOGBounds *bp, IOGBounds * vbp, void *arg3);
    IOReturn        registerScreenGated(IOGraphicsDevice *io_gd, IOGBounds *bp, IOGBounds * vbp, SInt32 *index);
public:
    

  virtual void unregisterScreen(int index);
    
/*
 * HISTORICAL NOTE:
 *   The following methods were part of the IOWorkspaceBounds protocol;
 *   the declarations have now been merged directly into this class.
 *
 * Absolute position input devices and some specialized output devices
 * may need to know the bounding rectangle for all attached displays.
 * The following method returns a IOGBounds* for the workspace.  Please note
 * that the bounds are kept as signed values, and that on a multi-display
 * system the minx and miny values may very well be negative.
 */

public:
  virtual IOGBounds * workspaceBounds();

/* END HISTORICAL NOTES */

private:
void relativePointerEvent(          int        buttons,
                 /* deltaX */       int        dx,
                 /* deltaY */       int        dy,
                 /* atTime */       AbsoluteTime ts,
                 /* senderID */     OSObject * sender);

  /* Tablet event reporting */
void absolutePointerEvent(          int        buttons,
                 /* at */           IOGPoint *    newLoc,
                 /* withBounds */   IOGBounds *bounds,
                 /* inProximity */  bool       proximity,
                 /* withPressure */ int        pressure,
                 /* withAngle */    int        stylusAngle,
                 /* atTime */       AbsoluteTime ts,
                 /* senderID */     OSObject * sender);

  /* Mouse scroll wheel event reporting */
void scrollWheelEvent(	        short 	       deltaAxis1,
                                short          deltaAxis2,
                                short          deltaAxis3,
                                IOFixed        fixedDelta1,
                                IOFixed        fixedDelta2,
                                IOFixed        fixedDelta3,
                                SInt32         pointDeltaAxis1,
                                SInt32         pointDeltaAxis2,
                                SInt32         pointDeltaAxis3,
                                UInt32         options,
                                AbsoluteTime   ts,
                                OSObject *     sender);

void tabletEvent(	NXEventData * tabletData,
                                AbsoluteTime ts,
                                OSObject * sender);

void proximityEvent(	NXEventData * proximityData,
                                AbsoluteTime ts,
                                OSObject * sender);

void keyboardEvent(unsigned   eventType,
      /* flags */            unsigned   flags,
      /* keyCode */          unsigned   key,
      /* charCode */         unsigned   charCode,
      /* charSet */          unsigned   charSet,
      /* originalCharCode */ unsigned   origCharCode,
      /* originalCharSet */  unsigned   origCharSet,
      /* keyboardType */     unsigned   keyboardType,
      /* repeat */           bool       repeat,
      /* atTime */           AbsoluteTime ts,
      /* sender */           OSObject * sender);

void keyboardSpecialEvent(   unsigned   eventType,
      /* flags */        unsigned   flags,
      /* keyCode  */     unsigned   key,
      /* specialty */    unsigned   flavor,
      /* guid */         UInt64     guid,
      /* repeat */       bool       repeat,
      /* atTime */       AbsoluteTime ts,
      /* sender */       OSObject * sender);

void updateEventFlags(unsigned flags, OSObject * sender);

bool addConsumedKey(unsigned key);
bool removeConsumedKey(unsigned key);

/*
 * COMMAND GATE COMPATIBILITY:
 *   The following method is part of the work needed to make IOHIDSystem
 *   compatible with IOCommandGate.  The use of IOCommandQueue has been
 *   deprecated, thus requiring this move.  This should allow for less
 *   context switching as all actions formerly run on the I/O Workloop
 *   thread, will now be run on the caller thread.  The static methods
 *   will be called from cmdGate->runAction and returns the appropriate 
 *   non-static helper method.  Arguments are stored in the void* array, 
 *   args, and are passed through.   Since we are returning in the static
 *   function, gcc3 should translate that to one instruction, thus 
 *   minimizing cost.
 */ 

static	IOReturn	doEvClose (IOHIDSystem *self);
        IOReturn	evCloseGated (void);
        
static	IOReturn	doSetEventsEnablePre (IOHIDSystem *self, void *p1);
        IOReturn	setEventsEnablePreGated (void *p1);

static	IOReturn	doSetEventsEnablePost (IOHIDSystem *self, void *p1);
        IOReturn	setEventsEnablePostGated (void *p1);
        
static	IOReturn	doUnregisterScreen (IOHIDSystem *self, void * arg0, void *arg1);
        IOReturn	unregisterScreenGated (int index, bool internal);

static	IOReturn	doSetDisplayBounds (IOHIDSystem *self, void * arg0, void * arg1);
        IOReturn	setDisplayBoundsGated (UInt32 index, IOGBounds *bounds);
    
static	IOReturn	doCreateShmem (IOHIDSystem *self, void * arg0);
        IOReturn	createShmemGated (void * p1);

static	IOReturn	doRegisterEventQueue (IOHIDSystem *self, void * arg0);
        IOReturn	registerEventQueueGated (void * p1);

static	IOReturn	doUnregisterEventQueue (IOHIDSystem *self, void * arg0);
        IOReturn	unregisterEventQueueGated (void * p1);

static	IOReturn	doRelativePointerEvent (IOHIDSystem *self, void * args);
        void		relativePointerEventGated(int buttons, 
                                                    int dx, 
                                                    int dy, 
                                                    AbsoluteTime ts,
                                                    OSObject * sender);

static	IOReturn	doAbsolutePointerEvent (IOHIDSystem *self, void * args);        
        void 		absolutePointerEventGated (int buttons,
                                                    IOGPoint *    newLoc,
                                                    IOGBounds *bounds,
                                                    bool       proximity,
                                                    int        pressure,
                                                    int        stylusAngle,
                                                    AbsoluteTime ts,
                                                    OSObject * sender);

static	IOReturn	doScrollWheelEvent(IOHIDSystem *self, void * args);        
        void		scrollWheelEventGated (short deltaAxis1,
                                                short deltaAxis2,
                                                short deltaAxis3,
                                               IOFixed  fixedDelta1,
                                               IOFixed  fixedDelta2,
                                               IOFixed  fixedDelta3,
                                               SInt32   pointDeltaAxis1,
                                               SInt32   pointDeltaAxis2,
                                               SInt32   pointDeltaAxis3,
                                               UInt32   options,
                                                AbsoluteTime ts,
                                                OSObject * sender);

static	IOReturn	doTabletEvent (IOHIDSystem *self, void * arg0, void * arg1, void * arg2);        
        void		tabletEventGated (	NXEventData *tabletData, 
                                                AbsoluteTime ts, 
                                                OSObject * sender);

static	IOReturn	doProximityEvent (IOHIDSystem *self, void * arg0, void * arg1, void * arg2);        
        void		proximityEventGated (	NXEventData *proximityData, 
                                                AbsoluteTime ts, 
                                                OSObject * sender);

static	IOReturn	doKeyboardEvent (IOHIDSystem *self, void * args);        
        void		keyboardEventGated (unsigned   eventType,
                                            unsigned   flags,
                                            unsigned   key,
                                            unsigned   charCode,
                                            unsigned   charSet,
                                            unsigned   origCharCode,
                                            unsigned   origCharSet,
                                            unsigned   keyboardType,
                                            bool       repeat,
                                            AbsoluteTime ts,
                                            OSObject * sender);

static	IOReturn	doKeyboardSpecialEvent (IOHIDSystem *self, void * args);        
        void		keyboardSpecialEventGated (   
                                            unsigned   eventType,
                                            unsigned   flags,
                                            unsigned   key,
                                            unsigned   flavor,
                                            UInt64     guid,
                                            bool       repeat,
                                            AbsoluteTime ts,
                                            OSObject * sender);

static	IOReturn	doUpdateEventFlags (IOHIDSystem *self, void * args);        
        void		updateEventFlagsGated (unsigned flags, OSObject * sender);

static	IOReturn	doNewUserClient (IOHIDSystem *self, void * args);        
        IOReturn 	newUserClientGated (task_t owningTask,
                                            void * security_id,
                                            UInt32 type,
                                            OSDictionary *  properties,
                                            IOUserClient ** handler);

static	IOReturn	doSetCursorEnable (IOHIDSystem *self, void * arg0);        
        IOReturn	setCursorEnableGated (void * p1);

static	IOReturn	doExtPostEvent(IOHIDSystem *self, void * arg0, void * arg1, void * arg2, void * arg3);        
        IOReturn	extPostEventGated (void * p1, void * p2, void * p3);

static	IOReturn	doExtSetMouseLocation (IOHIDSystem *self, void * args);        
        IOReturn	extSetMouseLocationGated (void * args);

static	IOReturn	doExtGetButtonEventNum (IOHIDSystem *self, void * arg0, void * arg1);        
        IOReturn	extGetButtonEventNumGated (void * p1, void * p2);

static	IOReturn	doSetParamPropertiesPre (IOHIDSystem *self, void * arg0, void * arg1);        
        IOReturn	setParamPropertiesPreGated (OSDictionary * dict, OSIterator ** pOpenIter);

static	IOReturn	doSetParamPropertiesPost (IOHIDSystem *self, void * arg0);        
        IOReturn	setParamPropertiesPostGated (OSDictionary * dict);
        
static	IOReturn	doExtGetToggleState (IOHIDSystem *self, void *p1, void *p2);        
static	IOReturn	doExtSetToggleState (IOHIDSystem *self, void *p1, void *p2);        
        IOReturn    getCapsLockState(unsigned int *state_O);
        IOReturn    setCapsLockState(unsigned int state_I);
        IOReturn    getNumLockState(unsigned int *state_O);
        IOReturn    setNumLockState(unsigned int state_I);

/* END COMMAND GATE COMPATIBILITY */

public:
    virtual void setStackShotPort(mach_port_t port);
    
    virtual UInt32 eventFlags();
    
    virtual void dispatchEvent(IOHIDEvent *event, IOOptionBits options=0);

};

#endif /* !_IOHIDSYSTEM_H */
