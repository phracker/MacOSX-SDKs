/* ===EmacsMode: -*- Mode: C; tab-width:4; c-basic-offset: 4; -*- === */
/* ===FileName: ===
   Copyright (c) 1998 Takuya SHIOZAKI, All Rights reserved.
   Copyright (c) 1998 Go Watanabe, All rights reserved. 
   Copyright (c) 1998 X-TrueType Server Project, All rights reserved. 

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

#ifndef _XTTCCONV_H_
#define _XTTCCONV_H_ (1)

#include "xttcap.h"

/*************************************
  Data Types
 */

#if 0
typedef unsigned short one_octet_t;
typedef unsigned short two_octet_t;
#endif
typedef unsigned short ft_char_code_t;
typedef ft_char_code_t ucs2_t;
typedef ft_char_code_t (*ft_code_converter_ptr_t)(ft_char_code_t idx);
typedef void *ft_module_handle_t;


/*
  Charset Information Struct
    --- To keep backward compatibility,
        you should not change the sequence of the elements.
        you should only add new elements to the tail of the struct.
 */
typedef struct {
    int firstCol;
    int lastCol;
    int firstRow;
    int lastRow;
    int defaultCh;
} CharSetInfo;


/*
  Code Converter Information Struct
 */
typedef struct TagCodeConverterInfo {
    CharSetInfo const *refCharSetInfo;
    ft_module_handle_t   handleModule;
    ft_code_converter_ptr_t ptrCodeConverter;
    void (*destructor)(struct TagCodeConverterInfo *codeConverterInfo);
    void *work;
} CodeConverterInfo;


/************************************
  Prototypes
 */

/* search code converter */
Bool /* isFound */
codeconv_search_code_converter(char const *charSetName,
                               TT_Face hFace, int numberOfCharMaps,
                               SRefPropRecValList *refListPropRecVal,
                               CodeConverterInfo *
                                   refCodeConverterInfo /*result*/,
                               int *refMapID /*result*/);

/* free code converter */
void
codeconv_free_code_converter(CodeConverterInfo *refCodeConverterInfo);

/* null code converter */
ft_char_code_t /* result charCodeDst */
null_code_converter(ft_char_code_t charCodeSrc);


#endif /* !def _XTTCCONV_H_ */


/* end of file */
