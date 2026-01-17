/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_panel.h
// Purpose:     XML resource handler for wxPanel
// Author:      Vaclav Slavik
// Created:     2000/03/05
// RCS-ID:      $Id: xh_panel.h,v 1.8 2006/10/03 14:53:32 VZ Exp $
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_PANEL_H_
#define _WX_XH_PANEL_H_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC

class WXDLLIMPEXP_XRC wxPanelXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxPanelXmlHandler)

public:
    wxPanelXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif // wxUSE_XRC

#endif // _WX_XH_PANEL_H_
