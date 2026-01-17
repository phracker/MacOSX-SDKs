/////////////////////////////////////////////////////////////////////////////
// Name:        _richtextprint
// Purpose:     RichTextCtrl printing classes
//
// Author:      Robin Dunn
//
// Created:     7-July-2008
// RCS-ID:      $Id: $
// Copyright:   (c) 2008 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

%{
#include <wx/richtext/richtextprint.h>
%}

//---------------------------------------------------------------------------
%newgroup


enum { wxRICHTEXT_PRINT_MAX_PAGES }; 

// Header/footer page identifiers
enum wxRichTextOddEvenPage {
    wxRICHTEXT_PAGE_ODD,
    wxRICHTEXT_PAGE_EVEN,
    wxRICHTEXT_PAGE_ALL
};

// Header/footer text locations
enum wxRichTextPageLocation {
    wxRICHTEXT_PAGE_LEFT,
    wxRICHTEXT_PAGE_CENTRE,
    wxRICHTEXT_PAGE_RIGHT
};




/*!
 * wxRichTextPrintout
 */

class wxRichTextPrintout : public wxPrintout
{
public:
    wxRichTextPrintout(const wxString& title = wxT("Printout"));
    virtual ~wxRichTextPrintout();

    /// The buffer to print
    void SetRichTextBuffer(wxRichTextBuffer* buffer);
    wxRichTextBuffer* GetRichTextBuffer() const;

    /// Set/get header/footer data
    void SetHeaderFooterData(const wxRichTextHeaderFooterData& data);
    const wxRichTextHeaderFooterData& GetHeaderFooterData() const;

    /// Sets margins in 10ths of millimetre. Defaults to 1 inch for margins.
    void SetMargins(int top = 252, int bottom = 252, int left = 252, int right = 252);

    /// Calculate scaling and rectangles, setting the device context scaling
    void CalculateScaling(wxDC* dc, wxRect& textRect, wxRect& headerRect, wxRect& footerRect);

//     // wxPrintout virtual functions
//     virtual bool OnPrintPage(int page);
//     virtual bool HasPage(int page);
//     virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);
//     virtual bool OnBeginDocument(int startPage, int endPage);
//     virtual void OnPreparePrinting();

};


/*
 *! wxRichTextPrinting
 * A simple interface to perform wxRichTextBuffer printing.
 */

class wxRichTextPrinting : public wxObject
{
public:
    wxRichTextPrinting(const wxString& name = wxT("Printing"),
                       wxWindow *parentWindow = NULL);
    virtual ~wxRichTextPrinting();

    /// Preview the file or buffer
    bool PreviewFile(const wxString& richTextFile);
    bool PreviewBuffer(const wxRichTextBuffer& buffer);

    /// Print the file or buffer
    bool PrintFile(const wxString& richTextFile);
    bool PrintBuffer(const wxRichTextBuffer& buffer);

    /// Shows page setup dialog
    void PageSetup();

    /// Set/get header/footer data
    void SetHeaderFooterData(const wxRichTextHeaderFooterData& data);
    const wxRichTextHeaderFooterData& GetHeaderFooterData() const;

    /// Set/get header text, e.g. wxRICHTEXT_PAGE_ODD, wxRICHTEXT_PAGE_LEFT
    void SetHeaderText(const wxString& text,
                       wxRichTextOddEvenPage page = wxRICHTEXT_PAGE_ALL,
                       wxRichTextPageLocation location = wxRICHTEXT_PAGE_CENTRE);
    wxString GetHeaderText(wxRichTextOddEvenPage page = wxRICHTEXT_PAGE_EVEN,
                           wxRichTextPageLocation location = wxRICHTEXT_PAGE_CENTRE) const;

    /// Set/get footer text, e.g. wxRICHTEXT_PAGE_ODD, wxRICHTEXT_PAGE_LEFT
    void SetFooterText(const wxString& text,
                       wxRichTextOddEvenPage page = wxRICHTEXT_PAGE_ALL,
                       wxRichTextPageLocation location = wxRICHTEXT_PAGE_CENTRE);
    wxString GetFooterText(wxRichTextOddEvenPage page = wxRICHTEXT_PAGE_EVEN,
                           wxRichTextPageLocation location = wxRICHTEXT_PAGE_CENTRE) const;

    /// Show header/footer on first page, or not
    void SetShowOnFirstPage(bool show);

    /// Set the font
    void SetHeaderFooterFont(const wxFont& font);

    /// Set the colour
    void SetHeaderFooterTextColour(const wxColour& font);

    /// Get print and page setup data
    wxPrintData *GetPrintData();
    wxPageSetupDialogData *GetPageSetupData();

    /// Set print and page setup data
    void SetPrintData(const wxPrintData& printData);
    void SetPageSetupData(const wxPageSetupData& pageSetupData);

    /// Set the rich text buffer pointer, deleting the existing object if present
    void SetRichTextBufferPreview(wxRichTextBuffer* buf);
    wxRichTextBuffer* GetRichTextBufferPreview() const;

    void SetRichTextBufferPrinting(wxRichTextBuffer* buf);
    wxRichTextBuffer* GetRichTextBufferPrinting() const;

    /// Set/get the parent window
    void SetParentWindow(wxWindow* parent);
    wxWindow* GetParentWindow() const;

    /// Set/get the title
    void SetTitle(const wxString& title);
    const wxString& GetTitle() const;

    /// Set/get the preview rect
    void SetPreviewRect(const wxRect& rect);
    const wxRect& GetPreviewRect() const;

};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
