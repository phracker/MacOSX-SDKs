///////////////////////////////////////////////////////////////////////////////
// Name:        wx/iosfwrap.h
// Purpose:     includes the correct stream-related forward declarations
// Author:      Jan van Dijk <jan@etpmod.phys.tue.nl>
// Modified by:
// Created:     18.12.2002
// RCS-ID:      $Id: iosfwrap.h,v 1.7 2005/04/12 21:06:03 ABX Exp $
// Copyright:   wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#if wxUSE_STD_IOSTREAM

#if wxUSE_IOSTREAMH
    // There is no pre-ANSI iosfwd header so we include the full declarations.
#   include <iostream.h>
#else
#   include <iosfwd>
#endif

#ifdef __WXMSW__
#   include "wx/msw/winundef.h"
#endif

#endif // wxUSE_STD_IOSTREAM

