/* ===EmacsMode: -*- Mode: C; tab-width:4; c-basic-offset: 4; -*- === */
/* ===FileName: ===
   Copyright (c) 1998 Takuya SHIOZAKI, All Rights reserved.
   Copyright (c) 1998 Go Watanabe, All rights reserved.
   Copyright (c) 1999 Mutsumi ISHIKAWA, All rights reserved.
   Copyright (c) 1999 Nozomi YTOW, All rights reserved.
   Copyright (c) 1998,1999 X-TrueType Server Project, All rights reserved. 

===Notice
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGE.

   Major Release ID: X-TrueType Server Version 1.3 [Aoi MATSUBARA Release 3]

Notice===
 */
/* $XFree86: xc/extras/X-TrueType/xttcconvP.h,v 1.8 2001/08/01 00:44:33 tsi Exp $ */

#ifndef _XTTCCONVP_H_
#define _XTTCCONVP_H_ 1

#include <X11/Xdefs.h>

/*************************************
  Data Types
 */

/*
  Charset Selection Hints Struct
    --- To keep backward compatibility,
        you should not change the sequence of the elements.
        You should only add new elements to the tail of the struct.
 */
typedef struct {
    char const *charsetStdName;   /* e.g. "iso8859", "jisx0208" .... */
    char const *charsetYear;      /* e.g. "1983" of "jisx0208.1983" */
    char const *charsetEncoding;  /* e.g. "1" of "iso8859-1"  */
    TT_Face hFace;
    int numberOfCharMaps;
    SRefPropRecValList *refListPropRecVal;
                                  /* user property */
} CharSetSelectionHints;


/*
  relation between Charset Name and info.
 */
typedef struct {
    char const *charsetStdName;   /* e.g. "iso8859", "jisx0208" .... */
    char const *charsetYear;      /* e.g. "1983" of "jisx0208.1983" */
    char const *charsetEncoding;  /* e.g. "1" of "iso8859-1"  */
    int magicNumber;              /* serial number of char set */
    CharSetInfo charSetInfo;      /* char set info */
} CharSetRelation;


/* Module Entry Pointer */
typedef 
Bool /* isFound */
(*mod_entrypoint_ptr_t)(CharSetSelectionHints const *charSetHints,
                        CodeConverterInfo *refCodeConverterInfo /* result */,
                        int *refMapID /* result */);

/*
  relation between charset and mapID
 */

enum {
    EPlfmUnicode = 0,
    EPlfmApple   = 1,
    EPlfmISO     = 2,
    EPlfmMS      = 3,
    EPlfmAny     = -1
};
enum {
    EEncUnicodeAny    = -1,
    EEncAppleRoman    =  0,
    EEncAppleJapanese =  1,
    EEncAppleCenteuro = 29,
    EEncAppleCyrillic =  7,
    EEncISOASCII      =  0,
    EEncISO10646      =  1,
    EEncISO8859_1     =  2,
    EEncMSSymbol      =  0,
    EEncMSUnicode     =  1,
    EEncMSShiftJIS    =  2,
    EEncMSBig5WGL4    =  3,
    EEncMSGB2312      =  4,
    EEncMSWansung     =  5,
    EEncAny           = -1
};
typedef struct {
    int magicNumber;
    int platform, encoding;
    ft_code_converter_ptr_t ptrCodeConverter;
    void (*callback)(CharSetSelectionHints const *charSetHints,
                     CodeConverterInfo *refCodeConverterInfo /* result */,
                     int *refMapID /* result */);
} MapIDRelation;


/*************************************
  Code convert function templates
 */

/* 1 octet charset to unicode */
#define CODE_CONV_ONE_OCTET_TO_UCS2(funcName, tableName,\
                                    begin, end,\
                                    altChar)\
ft_char_code_t /* result charCodeDst */\
funcName(ft_char_code_t codeSrc)\
{\
    ucs2_t codeDst;\
\
    if (codeSrc>=begin && codeSrc<=end)\
        codeDst = tableName[codeSrc-begin];\
    else\
        codeDst = altChar;\
\
    return codeDst;\
}

#define CODE_CONV_ONE_OCTET_TO_UCS2_ALL(funcName, tableName)\
ft_char_code_t /* result charCodeDst */\
funcName(ft_char_code_t codeSrc)\
{\
    return tableName[codeSrc];\
}

/* 2 octet charset to unicode */
#define CODE_CONV_TWO_OCTET_TO_UCS2(funcName, tableName,\
                                    beginHigh, endHigh,\
                                    beginLow, endLow,\
                                    altChar)\
ft_char_code_t /* result charCodeDst */\
funcName(ft_char_code_t codeSrc)\
{\
    ucs2_t codeDst;\
    int high = codeSrc >> 8;\
    int low  = codeSrc & 0xff;\
\
    if (high>=beginHigh && high<=endHigh && low>=beginLow && low<=endLow)\
        codeDst =\
            tableName[(high-beginHigh)*(endLow-beginLow+1)+(low-beginLow)];\
    else\
        codeDst = altChar;\
\
    return codeDst;\
}


/* iso8859-* to unicode or apple roman */
#define CODE_CONV_ISO8859_TO_UCS2(funcName, tableName, altChar)\
ft_char_code_t /* result charCodeDst */\
funcName(ft_char_code_t codeSrc)\
{\
    ucs2_t codeDst = 0;\
\
    if (codeSrc>=0xa0)\
        codeDst = tableName[codeSrc-0xa0];\
    else if (codeSrc<0x80)\
        codeDst = codeSrc;\
\
    return codeDst;\
}


/*************************************
  Code convert functions
 */

#define CODECONV_TEMPLATE(funcName)\
ft_char_code_t /* result charCodeDst */\
funcName(ft_char_code_t codeSrc)


/********************************************
  Module Entry Point Function Template
 */

#define ENTRYFUNC_PROTO_TEMPLATE(funcName) \
Bool /* isFound */\
funcName(CharSetSelectionHints const *charSetHints,\
         CodeConverterInfo *refCodeConverterInfo /* result */,\
         int *refMapID /* result */)

#define ENTRYFUNC_TEMPLATE(funcName) \
ENTRYFUNC_PROTO_TEMPLATE(funcName); \
CCONV_MODULE_SETUP \
ENTRYFUNC_PROTO_TEMPLATE(funcName) \

#define STD_ENTRYFUNC_TEMPLATE(funcName) \
ENTRYFUNC_TEMPLATE(funcName) \
{\
    return codeconv_search_map_id(charSetHints,\
                                  charSetRelations,\
                                  mapIDRelations,\
                                  refCodeConverterInfo,\
                                  refMapID);\
}


/*************************************
  callback function template
 */

#define CODECONV_CALLBACK_TEMPLATE(funcName)\
void funcName(CharSetSelectionHints const *charSetHints,\
              CodeConverterInfo *refCodeConverterInfo /* result */,\
              int *refMapID /* result */)


/********************************************
  Private Functions
 */

/* search charset info from relationship table */
Bool /* isFound */
codeconv_search_charset(CharSetRelation const *charSetRelations,
                        char const *charsetStdName,
                        char const *charsetYear,
                        char const *charsetEncoding,
                        int *refMagicNumber /* result */,
                        CharSetInfo const **refRefCharSetInfo /* result */);

/* search map ID */
Bool /* isFound */
codeconv_search_map_id(CharSetSelectionHints const *charSetHints,
                       CharSetRelation const *refCharSetRelations,
                       MapIDRelation const *refMapIDRelations,
                       CodeConverterInfo *refCodeConverterInfo /* result */,
                       int *refMapID /* result */);


#endif /* !def _XTTCCONVP_H_ */


#ifdef FONTMODULE
/* for New Designed XFree86 font module */

/*
 * This is moved to xttcommon.h because it needs to be included before
 * "xf86_ansic.h"
 */
#if 0
#include "xf86Module.h"
#endif
#include "xttversion.h"
#include "cconvversion.h"

/* end of New Designed XFree86 font module */
#else
/* dlopen module */

#define CCONV_MODULE_SETUP

#endif


/* end of file */
