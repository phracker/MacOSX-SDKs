/*
     File:       CarbonCore/HFSVolumes.h
 
     Contains:   On-disk data structures for HFS and HFS Plus volumes.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1984-2006 by Apple Computer, Inc.  All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HFSVOLUMES__
#define __HFSVOLUMES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __FINDER__
#include <CarbonCore/Finder.h>
#endif


#include <hfs/hfs_format.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/* CatalogNodeID is used to track catalog objects */
typedef UInt32                          HFSCatalogNodeID;


#endif /* __HFSVOLUMES__ */

