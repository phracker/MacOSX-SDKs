/*
 *  IO80211WorkLoop.h
 *  Family
 *
 *  Created by Pete on 5/31/06.
 *  Copyright 2006 Apple Computer, Inc. All rights reserved.
 *
 */

#include <IOKit/IOWorkLoop.h>

class IO80211WorkLoop : public IOWorkLoop
{
	OSDeclareDefaultStructors( IO80211WorkLoop )
	
public:

	static IO80211WorkLoop * workLoop();
	
	virtual bool init();
	virtual void free();
	
	virtual bool releaseGateLock();
	virtual void retakeGateLock();
	
private:
	
	UInt32 _lockDepth;
	IOLock * _releaseGateLock;
};