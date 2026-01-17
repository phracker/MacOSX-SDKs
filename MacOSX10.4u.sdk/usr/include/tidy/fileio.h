#ifndef __FILEIO_H__
#define __FILEIO_H__

/** @file fileio.h - does standard C I/O

  Implementation of a FILE* based TidyInputSource and 
  TidyOutputSink.

  (c) 1998-2003 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

  CVS Info:
    $Author: rbraun $ 
    $Date: 2004/05/04 20:05:14 $ 
    $Revision: 1.1.1.1 $ 
*/

#include "buffio.h"
#ifdef __cplusplus
extern "C" {
#endif

/** Allocate and initialize file input source */
void initFileSource( TidyInputSource* source, FILE* fp );

/** Free file input source */
void freeFileSource( TidyInputSource* source, Bool closeIt );

/** Initialize file output sink */
void initFileSink( TidyOutputSink* sink, FILE* fp );

/* Needed for internal declarations */
void filesink_putByte( ulong sinkData, byte bv );

#ifdef __cplusplus
}
#endif
#endif /* __FILEIO_H__ */
