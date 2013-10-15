/*
 * Copyright © 2009 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _XI2_H_
#define _XI2_H_

/* Indices into the versions[] array (XExtInt.c). Used as a index to
 * retrieve the minimum version of XI from _XiCheckExtInit.
 * For indices 0 to 6 see XI.h */
#ifndef Dont_Check /* defined in XI.h */
#define Dont_Check                              0
#endif
#define XInput_2_0                              7


#define XI_2_Major                              2
#define XI_2_Minor                              0

/* Property event flags */
#define XIPropertyDeleted                       0
#define XIPropertyCreated                       1
#define XIPropertyModified                      2

/* Enter/Leave and Focus In/Out modes */
#define XINotifyNormal                          0
#define XINotifyGrab                            1
#define XINotifyUngrab                          2
#define XINotifyWhileGrabbed                    3
#define XINotifyPassiveGrab                     4
#define XINotifyPassiveUngrab                   5

/* Enter/Leave and focus In/out detail */
#define XINotifyAncestor                        0
#define XINotifyVirtual                         1
#define XINotifyInferior                        2
#define XINotifyNonlinear                       3
#define XINotifyNonlinearVirtual                4
#define XINotifyPointer                         5
#define XINotifyPointerRoot                     6
#define XINotifyDetailNone                      7

/* Passive grab types */
#define XIGrabtypeButton                        0
#define XIGrabtypeKeycode                       1
#define XIGrabtypeEnter                         2
#define XIGrabtypeFocusIn                       3

/* Passive grab modifier */
#define XIAnyModifier                           (1U << 31)
#define XIAnyButton                             0
#define XIAnyKeycode                            0

/* XIAllowEvents event-modes */
#define XIAsyncDevice                           0
#define XISyncDevice                            1
#define XIReplayDevice                          2
#define XIAsyncPairedDevice                     3
#define XIAsyncPair                             4
#define XISyncPair                              5

/* DeviceChangedEvent change reasons */
#define XISlaveSwitch                           1
#define XIDeviceChange                          2

/* Hierarchy flags */
#define XIMasterAdded                           (1 << 0)
#define XIMasterRemoved                         (1 << 1)
#define XISlaveAdded                            (1 << 2)
#define XISlaveRemoved                          (1 << 3)
#define XISlaveAttached                         (1 << 4)
#define XISlaveDetached                         (1 << 5)
#define XIDeviceEnabled                         (1 << 6)
#define XIDeviceDisabled                        (1 << 7)

/* ChangeHierarchy constants */
#define XIAddMaster                             1
#define XIRemoveMaster                          2
#define XIAttachSlave                           3
#define XIDetachSlave                           4

#define XIAttachToMaster                        1
#define XIFloating                              2

/* Valuator modes */
#define XIModeRelative                          0
#define XIModeAbsolute                          1

/* Device types */
#define XIMasterPointer                         1
#define XIMasterKeyboard                        2
#define XISlavePointer                          3
#define XISlaveKeyboard                         4
#define XIFloatingSlave                         5

/* Device classes */
#define XIKeyClass                              0
#define XIButtonClass                           1
#define XIValuatorClass                         2

/* Device event flags (common) */
/* Device event flags (key events only) */
#define XIKeyRepeat                             (1 << 16)
/* Device event flags (pointer events only) */

/* XI2 event mask macros */
#define XISetMask(ptr, event)   (((unsigned char*)(ptr))[(event)>>3] |=  (1 << ((event) & 7)))
#define XIClearMask(ptr, event) (((unsigned char*)(ptr))[(event)>>3] &= ~(1 << ((event) & 7)))
#define XIMaskIsSet(ptr, event) (((unsigned char*)(ptr))[(event)>>3] &   (1 << ((event) & 7)))
#define XIMaskLen(event)        (((event + 7) >> 3))

/* Fake device ID's for event selection */
#define XIAllDevices                            0
#define XIAllMasterDevices                      1

/* Event types */
#define XI_DeviceChanged                 1
#define XI_KeyPress                      2
#define XI_KeyRelease                    3
#define XI_ButtonPress                   4
#define XI_ButtonRelease                 5
#define XI_Motion                        6
#define XI_Enter                         7
#define XI_Leave                         8
#define XI_FocusIn                       9
#define XI_FocusOut                      10
#define XI_HierarchyChanged              11
#define XI_PropertyEvent                 12
#define XI_RawKeyPress                   13
#define XI_RawKeyRelease                 14
#define XI_RawButtonPress                15
#define XI_RawButtonRelease              16
#define XI_RawMotion                     17
#define XI_LASTEVENT                     XI_RawMotion
/* NOTE: XI2LASTEVENT in xserver/include/inputstr.h must be the same value
 * as XI_LASTEVENT if the server is supposed to handle masks etc. for this
 * type of event. */

/* Event masks.
 * Note: the protocol spec defines a mask to be of (1 << type). Clients are
 * free to create masks by bitshifting instead of using these defines.
 */
#define XI_DeviceChangedMask             (1 << XI_DeviceChanged)
#define XI_KeyPressMask                  (1 << XI_KeyPress)
#define XI_KeyReleaseMask                (1 << XI_KeyRelease)
#define XI_ButtonPressMask               (1 << XI_ButtonPress)
#define XI_ButtonReleaseMask             (1 << XI_ButtonRelease)
#define XI_MotionMask                    (1 << XI_Motion)
#define XI_EnterMask                     (1 << XI_Enter)
#define XI_LeaveMask                     (1 << XI_Leave)
#define XI_FocusInMask                   (1 << XI_FocusIn)
#define XI_FocusOutMask                  (1 << XI_FocusOut)
#define XI_HierarchyChangedMask          (1 << XI_HierarchyChanged)
#define XI_PropertyEventMask             (1 << XI_PropertyEvent)
#define XI_RawKeyPressMask               (1 << XI_RawKeyPress)
#define XI_RawKeyReleaseMask             (1 << XI_RawKeyRelease)
#define XI_RawButtonPressMask            (1 << XI_RawButtonPress)
#define XI_RawButtonReleaseMask          (1 << XI_RawButtonRelease)
#define XI_RawMotionMask                 (1 << XI_RawMotion)

#endif /* _XI2_H_ */
