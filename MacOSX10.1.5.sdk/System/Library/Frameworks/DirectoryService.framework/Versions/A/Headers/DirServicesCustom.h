/*
	File:		DirServicesCustom.h

	Contains:	xxx put contents here xxx

	Copyright:	© 1998-2000 by Apple Computer, Inc., all rights reserved.

	NOT_FOR_OPEN_SOURCE <to be reevaluated at a later time>
*/


#ifndef __DirServicesCustom_h__
#define __DirServicesCustom_h__	1

// App
#include "DirServicesTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------
// register custom allocate/deallocate routines MacOS 8.x Applications Only
tDirStatus	dsRegisterCustomMemory		(	tDirReference		inDirReference,
											fpCustomAllocate	inCustomAllocate,
											fpCustomDeAllocate	inCustomDeAllocate,
											tClientData			inClientData		);
	
tDirStatus	dsGetCustomAllocate			(	tDirReference		inDirReference,
											fpCustomAllocate	*outCustomAllocate,
											fpCustomDeAllocate	*outCustomDeAllocate,
											tClientData			*outClientData		);

tDirStatus	dsUnRegisterCustomMemory	(	tDirReference		inDirReference,
											fpCustomAllocate	inCustomAllocate,
											fpCustomDeAllocate	inCustomDeAllocate,
											tClientData			inClientData		);

//------------------------------------------------------------
// register custom thread routines MacOS 8.x Applications Only
tDirStatus	dsRegisterCustomThread		(	tDirReference			inDirReference,
											fpCustomThreadBlock		inCustomBlock,
											fpCustomThreadUnBlock	inCustomUnBlock,
											fpCustomThreadYield		inCustomYield,
											tClientData				inClientData	);

tDirStatus	dsGetCustomThread			(	tDirReference			inDirReference,
											fpCustomThreadBlock		*outCustomBlock,
											fpCustomThreadUnBlock	*outCustomUnBlock,
											fpCustomThreadYield		*outCustomYield,
											tClientData				*outClientData	);

tDirStatus	dsUnRegisterCustomThread	(	tDirReference			inDirReference,
											fpCustomThreadBlock		inCustomBlock,
											fpCustomThreadUnBlock	inCustomUnBlock,
											fpCustomThreadYield		inCustomYield,
											tClientData				inClientData	);

#ifdef __cplusplus
}
#endif

#endif
