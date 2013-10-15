/////////////////////////////////////////////////////////////////////////////
// Name:        _wxPalette.i
// Purpose:     SWIG interface defs for wxPalette
//
// Author:      Robin Dunn
//
// Created:     7-July-1997
// RCS-ID:      $Id: _palette.i 49161 2007-10-15 20:02:51Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

MustHaveApp(wxPalette);

class wxPalette : public wxGDIObject {
public:
    //wxPalette(int n, const unsigned char *red, const unsigned char *green, const unsigned char *blue);
    %extend {
        wxPalette(const wxArrayInt& red, const wxArrayInt& green, const wxArrayInt& blue)
        {
            wxPalette* self = new wxPalette();
            int count = red.Count();

            wxCHECK_MSG( count == green.Count() && count == blue.Count(),
                         self,
                         wxT("Palette list lengths must be equal"));

            int idx;
            unsigned char* ra = new unsigned char[count];
            unsigned char* ga = new unsigned char[count];
            unsigned char* ba = new unsigned char[count];
            for (idx=0; idx<count; idx++)
            {
                int rv = red.Item(idx);
                int gv = green.Item(idx);
                int bv = blue.Item(idx);
                wxCHECK_MSG( rv >=0 && rv <=255 &&
                             gv >=0 && gv <=255 &&
                             bv >=0 && bv <=255,
                             self,
                             wxT("Palette values must be in the range 0..255"));
                ra[idx] = (unsigned char)rv;
                ga[idx] = (unsigned char)gv;
                ba[idx] = (unsigned char)bv;
            }
            self->Create(count, ra, ga, ba);
            delete [] ra;
            delete [] ga;
            delete [] ba;

            return self;
        }
    }
    ~wxPalette();

    int GetPixel(byte red, byte green, byte blue);
    
    DocDeclA(
        bool, GetRGB(int pixel, byte* OUTPUT, byte* OUTPUT, byte* OUTPUT),
        "GetRGB(self, int pixel) -> (success, R,G,B)");

    int GetColoursCount() const;
    bool IsOk();
    %pythoncode { Ok = IsOk }

    %pythoncode { def __nonzero__(self): return self.IsOk() }

    %property(ColoursCount, GetColoursCount, doc="See `GetColoursCount`");
};



//---------------------------------------------------------------------------
