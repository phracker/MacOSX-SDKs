/////////////////////////////////////////////////////////////////////////////
// Name:        _axbase.i
// Purpose:     SWIG interface for a wxWindow that virtualizes MSWTranslateMessage
//
// Author:      Robin Dunn
//
// Created:     6-Jun-2008
// RCS-ID:      $Id: $
// Copyright:   (c) 2008 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module



//---------------------------------------------------------------------------
#ifdef __WXMSW__
%newgroup
// a wxWindow class that can forward the MSWTranslateMessage virtual to
// Python.  This is intended only for use in the wxSMW port and only as the
// base class for a new ActiveX wrapper, so we'll use a private name.

%{
class wxPyAxBaseWindow : public wxWindow
{
    DECLARE_DYNAMIC_CLASS(wxPyAxBaseWindow)

public:
    wxPyAxBaseWindow(wxWindow* parent, const wxWindowID id=-1,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxString& name = wxPyPanelNameStr)
    : wxWindow(parent, id, pos, size, style, name) {}
    
    wxPyAxBaseWindow() : wxWindow() {}


    virtual bool MSWTranslateMessage(WXMSG* msg)
    {
        // To make the python interface easier we'll just pass the msg pointer
        // as a long
        bool rval;
        bool found;
        wxPyBlock_t blocked = wxPyBeginBlockThreads();                          
        if ((found = wxPyCBH_findCallback(m_myInst, "MSWTranslateMessage"))) {
            rval = wxPyCBH_callCallback(m_myInst,
                                        Py_BuildValue("(i)", (long)msg));
        }
        wxPyEndBlockThreads(blocked);
        if (! found)
            rval = wxWindow::MSWTranslateMessage(msg);
        return rval;
    }

    PYPRIVATE;
};

IMPLEMENT_DYNAMIC_CLASS(wxPyAxBaseWindow, wxWindow);
%}


MustHaveApp(wxPyAxBaseWindow);

class wxPyAxBaseWindow : public wxWindow
{
public:
    %pythonAppend wxPyAxBaseWindow   "self._setOORInfo(self);" setCallbackInfo(PyAxBaseWindow)
    %pythonAppend wxPyAxBaseWindow() ""

    wxPyAxBaseWindow(wxWindow* parent, const wxWindowID id=-1,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxString& name = wxPyPanelNameStr);

    %RenameCtor(PrePyAxBaseWindow, wxPyAxBaseWindow());

    void _setCallbackInfo(PyObject* self, PyObject* _class);

    %extend {
        bool MSWTranslateMessage(long msg)
        {
            return self->MSWTranslateMessage((WXMSG*)msg);
        }
    }
};



MustHaveApp(wxWindow_FromHWND);

// Note this is similar to another function in _window.i, keep them in sync.
%inline %{
    wxPyAxBaseWindow* wxPyAxBaseWindow_FromHWND(wxWindow* parent, unsigned long _hWnd)
    {
        WXHWND hWnd = (WXHWND)_hWnd;
        wxPyAxBaseWindow* win = new wxPyAxBaseWindow;
        if (parent)
            parent->AddChild(win);
        win->SetEventHandler(win);
        win->SetHWND(hWnd);
        win->SubclassWin(hWnd);
        win->AdoptAttributesFromHWND();
        win->SetupColours();
        return win;
    }
%}

#endif
//---------------------------------------------------------------------------
