/////////////////////////////////////////////////////////////////////////////
// Name:        _pywindows.i
// Purpose:     SWIG interface for wxPyControl, See also _pywindows.i
//
// Author:      Robin Dunn
//
// Created:     2-June-1998
// RCS-ID:      $Id: _pycontrol.i 54192 2008-06-13 17:21:58Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%newgroup



//---------------------------------------------------------------------------

%{ // C++ version of Python aware wxControl
class wxPyControl : public wxControl
{
    DECLARE_DYNAMIC_CLASS(wxPyControl)
public:
    wxPyControl() : wxControl() {}
    wxPyControl(wxWindow* parent, const wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator=wxDefaultValidator,
                const wxString& name = wxPyControlNameStr)
        : wxControl(parent, id, pos, size, style, validator, name) {}


    bool DoEraseBackground(wxDC* dc) {
#ifdef __WXMSW__
        return wxWindow::DoEraseBackground(dc->GetHDC());
#else
        dc->SetBackground(wxBrush(GetBackgroundColour()));
        dc->Clear();
        return true;
#endif
    }

    DEC_PYCALLBACK_VOID_INT4(DoMoveWindow);
    DEC_PYCALLBACK_VOID_INT5(DoSetSize);
    DEC_PYCALLBACK_VOID_INTINT(DoSetClientSize);
    DEC_PYCALLBACK_VOID_INTINT(DoSetVirtualSize);

    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetSize);
    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetClientSize);
    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetPosition);
    DEC_PYCALLBACK_POINT_const(GetClientAreaOrigin);

    DEC_PYCALLBACK_SIZE_const(DoGetVirtualSize);
    DEC_PYCALLBACK_SIZE_const(DoGetBestSize);

    DEC_PYCALLBACK__(InitDialog);
    DEC_PYCALLBACK_BOOL_(TransferDataFromWindow);
    DEC_PYCALLBACK_BOOL_(TransferDataToWindow);
    DEC_PYCALLBACK_BOOL_(Validate);

    DEC_PYCALLBACK_BOOL_const(AcceptsFocus);
    DEC_PYCALLBACK_BOOL_const(AcceptsFocusFromKeyboard);
    DEC_PYCALLBACK_SIZE_const(GetMaxSize);

    DEC_PYCALLBACK_VOID_WXWINBASE(AddChild);
    DEC_PYCALLBACK_VOID_WXWINBASE(RemoveChild);

    DEC_PYCALLBACK_BOOL_const(ShouldInheritColours);
    DEC_PYCALLBACK_VIZATTR_(GetDefaultAttributes);
    
    DEC_PYCALLBACK_BOOL_(HasTransparentBackground);

    DEC_PYCALLBACK_VOID_(OnInternalIdle);

    PYPRIVATE;
};

IMPLEMENT_DYNAMIC_CLASS(wxPyControl, wxControl);

IMP_PYCALLBACK_VOID_INT4(wxPyControl, wxControl, DoMoveWindow);
IMP_PYCALLBACK_VOID_INT5(wxPyControl, wxControl, DoSetSize);
IMP_PYCALLBACK_VOID_INTINT(wxPyControl, wxControl, DoSetClientSize);
IMP_PYCALLBACK_VOID_INTINT(wxPyControl, wxControl, DoSetVirtualSize);

IMP_PYCALLBACK_VOID_INTPINTP_const(wxPyControl, wxControl, DoGetSize);
IMP_PYCALLBACK_VOID_INTPINTP_const(wxPyControl, wxControl, DoGetClientSize);
IMP_PYCALLBACK_VOID_INTPINTP_const(wxPyControl, wxControl, DoGetPosition);
IMP_PYCALLBACK_POINT_const(wxPyControl, wxControl, GetClientAreaOrigin);

IMP_PYCALLBACK_SIZE_const(wxPyControl, wxControl, DoGetVirtualSize);
IMP_PYCALLBACK_SIZE_const(wxPyControl, wxControl, DoGetBestSize);

IMP_PYCALLBACK__(wxPyControl, wxControl, InitDialog);
IMP_PYCALLBACK_BOOL_(wxPyControl, wxControl, TransferDataFromWindow);
IMP_PYCALLBACK_BOOL_(wxPyControl, wxControl, TransferDataToWindow);
IMP_PYCALLBACK_BOOL_(wxPyControl, wxControl, Validate);

IMP_PYCALLBACK_BOOL_const(wxPyControl, wxControl, AcceptsFocus);
IMP_PYCALLBACK_BOOL_const(wxPyControl, wxControl, AcceptsFocusFromKeyboard);
IMP_PYCALLBACK_SIZE_const(wxPyControl, wxControl, GetMaxSize);

IMP_PYCALLBACK_VOID_WXWINBASE(wxPyControl, wxControl, AddChild);
IMP_PYCALLBACK_VOID_WXWINBASE(wxPyControl, wxControl, RemoveChild);

IMP_PYCALLBACK_BOOL_const(wxPyControl, wxControl, ShouldInheritColours);
IMP_PYCALLBACK_VIZATTR_(wxPyControl, wxControl, GetDefaultAttributes);

IMP_PYCALLBACK_BOOL_(wxPyControl, wxControl, HasTransparentBackground);

IMP_PYCALLBACK_VOID_(wxPyControl, wxControl, OnInternalIdle);

%}

// And now the one for SWIG to see
MustHaveApp(wxPyControl);
class wxPyControl : public wxControl
{
public:
    %pythonAppend wxPyControl         "self._setOORInfo(self);"  setCallbackInfo(PyControl)
    %pythonAppend wxPyControl()       ""

    wxPyControl(wxWindow* parent, const wxWindowID id=-1,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator=wxDefaultValidator,
                const wxString& name = wxPyControlNameStr);

    %RenameCtor(PrePyControl,  wxPyControl());
    
    void _setCallbackInfo(PyObject* self, PyObject* _class);

    %pythoncode { SetBestSize = wx.Window.SetInitialSize }
    bool DoEraseBackground(wxDC* dc);
    
    void DoMoveWindow(int x, int y, int width, int height);
    void DoSetSize(int x, int y, int width, int height,
                        int sizeFlags = wxSIZE_AUTO);
    void DoSetClientSize(int width, int height);
    void DoSetVirtualSize( int x, int y );

    DocDeclA(
        void, DoGetSize( int *OUTPUT, int *OUTPUT ) const,
        "DoGetSize() -> (width, height)");
    DocDeclA(
        void, DoGetClientSize( int *OUTPUT, int *OUTPUT ) const,
        "DoGetClientSize() -> (width, height)");
    DocDeclA(
        void, DoGetPosition( int *OUTPUT, int *OUTPUT ) const,
        "DoGetPosition() -> (x,y)");

    wxSize DoGetVirtualSize() const;
    wxSize DoGetBestSize() const;

    void InitDialog();
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    bool Validate();

    bool AcceptsFocus() const;
    bool AcceptsFocusFromKeyboard() const;
    wxSize GetMaxSize() const;

    void AddChild(wxWindow* child);
    void RemoveChild(wxWindow* child);

    bool ShouldInheritColours() const;
    wxVisualAttributes GetDefaultAttributes();

    void OnInternalIdle();

    %MAKE_BASE_FUNC(PyControl, DoMoveWindow);
    %MAKE_BASE_FUNC(PyControl, DoSetSize);
    %MAKE_BASE_FUNC(PyControl, DoSetClientSize);
    %MAKE_BASE_FUNC(PyControl, DoSetVirtualSize);
    %MAKE_BASE_FUNC(PyControl, DoGetSize);
    %MAKE_BASE_FUNC(PyControl, DoGetClientSize);
    %MAKE_BASE_FUNC(PyControl, DoGetPosition);
    %MAKE_BASE_FUNC(PyControl, DoGetVirtualSize);
    %MAKE_BASE_FUNC(PyControl, DoGetBestSize);
    %MAKE_BASE_FUNC(PyControl, InitDialog);
    %MAKE_BASE_FUNC(PyControl, TransferDataToWindow);
    %MAKE_BASE_FUNC(PyControl, TransferDataFromWindow);
    %MAKE_BASE_FUNC(PyControl, Validate);
    %MAKE_BASE_FUNC(PyControl, AcceptsFocus);
    %MAKE_BASE_FUNC(PyControl, AcceptsFocusFromKeyboard);
    %MAKE_BASE_FUNC(PyControl, GetMaxSize);
    %MAKE_BASE_FUNC(PyControl, AddChild);
    %MAKE_BASE_FUNC(PyControl, RemoveChild);
    %MAKE_BASE_FUNC(PyControl, ShouldInheritColours);
    %MAKE_BASE_FUNC(PyControl, GetDefaultAttributes);
    %MAKE_BASE_FUNC(PyControl, OnInternalIdle);

};


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
