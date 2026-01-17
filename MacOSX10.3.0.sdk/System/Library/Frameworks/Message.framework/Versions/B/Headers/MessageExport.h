/*
 *	Message  --  MessageExport.h
 *
 *	Copyright (c) 1999, Apple Computer, Inc.
 *	All rights reserved.
 *
 */

#if !defined(__MESSAGE_EXPORT__)
#define __MESSAGE_EXPORT__ 1


#if defined(macintosh)

    #undef MESSAGE_EXPORT
    #if defined(__MWERKS__)
        #define MESSAGE_EXPORT __declspec(export) extern
    #endif

#endif

#if !defined(MESSAGE_EXPORT)
    #define MESSAGE_EXPORT extern
#endif

#if !defined(MESSAGE_IMPORT)
    #define MESSAGE_IMPORT extern
#endif



#endif /* ! __MESSAGE_EXPORT__ */


