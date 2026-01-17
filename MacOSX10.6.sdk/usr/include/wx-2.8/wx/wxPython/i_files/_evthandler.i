/////////////////////////////////////////////////////////////////////////////
// Name:        _evthandler.i
// Purpose:     SWIG interface for wxEventHandler
//
// Author:      Robin Dunn
//
// Created:     9-Aug-2003
// RCS-ID:      $Id: _evthandler.i 51607 2008-02-08 19:21:48Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%newgroup

// wxEvtHandler: the base class for all objects handling wxWindows events
class wxEvtHandler : public wxObject {
public:
    // turn off this typemap
    %typemap(out) wxEvtHandler*;    

    %pythonAppend wxEvtHandler         "self._setOORInfo(self)"
    wxEvtHandler();

    // Turn it back on again
    %typemap(out) wxEvtHandler* { $result = wxPyMake_wxObject($1, $owner); }

    wxEvtHandler* GetNextHandler();
    wxEvtHandler* GetPreviousHandler();
    void SetNextHandler(wxEvtHandler* handler);
    void SetPreviousHandler(wxEvtHandler* handler);

    bool GetEvtHandlerEnabled();
    void SetEvtHandlerEnabled(bool enabled);


    // process an event right now
    bool ProcessEvent(wxEvent& event);

    // add an event to be processed later
    void AddPendingEvent(wxEvent& event);

    // process all pending events
    void ProcessPendingEvents();

    %extend {
        // Dynamic association of a member function handler with the event handler
        void Connect( int id, int lastId, int eventType, PyObject* func) {
            if (PyCallable_Check(func)) {
                self->Connect(id, lastId, eventType,
                          (wxObjectEventFunction) &wxPyCallback::EventThunker,
                          new wxPyCallback(func));
            }
            else if (func == Py_None) {
                self->Disconnect(id, lastId, eventType,
                                 (wxObjectEventFunction)
                                 &wxPyCallback::EventThunker);
            }
            else {
                wxPyBLOCK_THREADS(
                    PyErr_SetString(PyExc_TypeError, "Expected callable object or None."));
            }
        }

        bool Disconnect(int id, int lastId = -1,
                        wxEventType eventType = wxEVT_NULL) {
            return self->Disconnect(id, lastId, eventType,
                                   (wxObjectEventFunction)
                                    &wxPyCallback::EventThunker);
        }
    }

    %pythonAppend _setOORInfo   "args[0].this.own(False)";
    %extend {
        void _setOORInfo(PyObject* _self, bool incref=true) {
            if (_self && _self != Py_None) {
                self->SetClientObject(new wxPyOORClientData(_self, incref));
            }
            else {
                wxPyOORClientData* data = (wxPyOORClientData*)self->GetClientObject();
                if (data) {
                    self->SetClientObject(NULL);  // This will delete it too
                }
            }
        }
    }

    %pythoncode {
        def Bind(self, event, handler, source=None, id=wx.ID_ANY, id2=wx.ID_ANY):
            """
            Bind an event to an event handler.

            :param event: One of the EVT_* objects that specifies the
                          type of event to bind,

            :param handler: A callable object to be invoked when the
                          event is delivered to self.  Pass None to
                          disconnect an event handler.

            :param source: Sometimes the event originates from a
                          different window than self, but you still
                          want to catch it in self.  (For example, a
                          button event delivered to a frame.)  By
                          passing the source of the event, the event
                          handling system is able to differentiate
                          between the same event type from different
                          controls.

            :param id: Used to spcify the event source by ID instead
                       of instance.

            :param id2: Used when it is desirable to bind a handler
                          to a range of IDs, such as with EVT_MENU_RANGE.
            """
            if source is not None:
                id  = source.GetId()
            event.Bind(self, id, id2, handler)              

        def Unbind(self, event, source=None, id=wx.ID_ANY, id2=wx.ID_ANY):
            """
            Disconnects the event handler binding for event from self.
            Returns True if successful.
            """
            if source is not None:
                id  = source.GetId()
            return event.Unbind(self, id, id2)              
    }

    %property(EvtHandlerEnabled, GetEvtHandlerEnabled, SetEvtHandlerEnabled, doc="See `GetEvtHandlerEnabled` and `SetEvtHandlerEnabled`");
    %property(NextHandler, GetNextHandler, SetNextHandler, doc="See `GetNextHandler` and `SetNextHandler`");
    %property(PreviousHandler, GetPreviousHandler, SetPreviousHandler, doc="See `GetPreviousHandler` and `SetPreviousHandler`");
    
};

//---------------------------------------------------------------------------
// A class derived from wxEvtHandler that allows the ProcessEvent method to be
// overridden in Python.

%{ // The Python-aware C++ class
class wxPyEvtHandler : public wxEvtHandler
{
    DECLARE_DYNAMIC_CLASS(wxPyEvtHandler)
public:
    wxPyEvtHandler() : wxEvtHandler() {}

    virtual bool ProcessEvent(wxEvent& event)
    {
        bool found;
        bool rval;
        wxString className = event.GetClassInfo()->GetClassName();

        wxPyBlock_t blocked = wxPyBeginBlockThreads();
        if ((found = wxPyCBH_findCallback(m_myInst, "ProcessEvent"))) {
            PyObject* arg = wxPyConstructObject((void*)&event, className);
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(O)",arg));
            Py_DECREF(arg);
        }
        wxPyEndBlockThreads(blocked);        
        if (! found)
            rval = wxEvtHandler::ProcessEvent(event);
        return rval;
    }
    
    PYPRIVATE;
};

IMPLEMENT_DYNAMIC_CLASS(wxPyEvtHandler, wxEvtHandler)
%}



// Let SWIG see this class too
DocStr(wxPyEvtHandler,
"The wx.PyEvtHandler class can be used to intercept calls to the
`ProcessEvent` method.  Simply derive a new class from this one,
override ProcessEvent, and then push an instance of the class onto the
event handler chain for a window using `wx.Window.PushEventHandler`.", "");
class wxPyEvtHandler : public wxEvtHandler
{
public:
    %pythonAppend wxPyEvtHandler   "self._setOORInfo(self);" setCallbackInfo(PyEvtHandler)
    wxPyEvtHandler();

    void _setCallbackInfo(PyObject* self, PyObject* _class);    
    
    DocDeclStr(
        virtual bool , ProcessEvent(wxEvent& event),
        "Override this method to intercept the events being sent to the window.
The default implementation searches the event tables and calls event
handler functions if matching event bindings are found.", "");
};

//---------------------------------------------------------------------------
