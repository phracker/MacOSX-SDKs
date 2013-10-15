///////////////////////////////////////////////////////////////////////////////
// Name:        wx/ioswrap.h
// Purpose:     includes the correct iostream headers for current compiler
// Author:      Vadim Zeitlin
// Modified by:
// Created:     03.02.99
// RCS-ID:      $Id: ioswrap.h,v 1.8 2004/05/23 20:50:23 JS Exp $
// Copyright:   (c) 1998 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#if wxUSE_STD_IOSTREAM

#if wxUSE_IOSTREAMH
#   include <iostream.h>
#else
#   include <iostream>
#endif

#endif
  // wxUSE_STD_IOSTREAM

