/*
 Name:        wx/gsockmac.h
 Purpose:     GSocket base header
 Author:      Stefan Csomor
 Modified by:
 Created:
 Copyright:   (c) Stefan Csomor
 RCS-ID:      $Id: gsockmac.h 33948 2005-05-04 18:57:50Z JS $
 Licence:     wxWindows Licence
*/

#ifdef __WXMAC_CLASSIC__
#include "wx/mac/classic/gsockmac.h"
#else
#include "wx/mac/carbon/gsockmac.h"
#endif