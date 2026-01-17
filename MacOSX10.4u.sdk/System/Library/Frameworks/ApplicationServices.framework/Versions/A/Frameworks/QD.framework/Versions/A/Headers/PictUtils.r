/*
     File:       PictUtils.r
 
     Contains:   Picture Utilities Interfaces.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 1990-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __PICTUTILS_R__
#define __PICTUTILS_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif


/*----------------------------PICT • Quickdraw Picture----------------------------------*/
/*
 PICT_RezTemplateVersion:
       0 - PICT opcodes as hex values              <-- default
        1 - PICT opcodes dissasembled       
       2 - PICT opcodes dissasembled supports extended HeaderOp        
*/
#ifndef __PICT_R__
#define __PICT_R__

#ifndef PICT_RezTemplateVersion
 #ifdef oldPICTCompatible                        /* grandfather in use of “oldPICTCompatible” */
        #if oldPICTCompatible
          #define PICT_RezTemplateVersion 1
      #else
          #define PICT_RezTemplateVersion 2
      #endif
 #else
      #define PICT_RezTemplateVersion 1
  #endif
#endif

type 'PICT' {
#if PICT_RezTemplateVersion == 0
    unsigned integer;                                       /* Length               */
    rect;                                                   /* Frame                */
    hex string;                                             /* Data                 */
#else
    startOfPict:
        unsigned integer = (endOfPict - startOfPict) >> 3;
        Rect;                                   /* Bounds of picture */
        switch {
            case VersionOne:
                key integer = $1101;
                array OpCodes {
                    switch {
                        case NOP:
                            key byte = $00;

                        case ClipRgn:
                            key byte = $01;
    ClipRgnStart:           integer = (ClipRgnEnd[$$ArrayIndex(OpCodes)] - ClipRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(ClipRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    ClipRgnEnd:
                        case BkPat:
                            key byte = $02;
                            hex string [8];

                        case TxFont:
                            key byte = $03;
                            integer;            /* font */

                        case TxFace:
                            key byte = $04;
                            unsigned hex byte;  /* text face */

                        case TxMode:
                            key byte = $05;
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;
                        case SpExtra:
                            key byte = $06;
                            unsigned hex longint;

                        case PnSize:
                            key byte = $07;
                            Point;

                        case PnMode:
                            key byte = $08;
                            unsigned hex integer;

                        case PnPat:
                            key byte = $09;
                            hex string [8];

                        case ThePat:
                            key byte = $0A;
                            hex string [8];

                        case OvSize:
                            key byte = $0B;
                            Point;

                        case Origin:
                            key byte = $0C;
                            integer;            /* dh */
                            integer;            /* dv */

                        case TxSize:
                            key byte = $0D;
                            integer;

                        case FgColor:
                            key byte = $0E;
                            longint;

                        case BkColor:
                            key byte = $0F;
                            longint;

                        case TxRatio:
                            key byte = $10;
                            Point;              /* numer */
                            Point;              /* denom */

                        case PicVersion:
                            key byte = $11;
                            byte;

                        case Line:
                            key byte = $20;
                            Point;              /* pnLoc */
                            Point;              /* newPt */

                        case LineFrom:
                            key byte = $21;
                            Point;              /* newPt */

                        case ShortLine:
                            key byte = $22;
                            Point;              /* pnLoc */
                            byte;               /* dh */
                            byte;               /* dv */

                        case ShortLineFrom:
                            key byte = $23;
                            byte;               /* dh */
                            byte;               /* dv */

                        case LongText:
                            key byte = $28;
                            Point;              /* txLoc */
                            pstring;

                        case dhText:
                            key byte = $29;
                            byte;               /* dh */
                            pstring;

                        case dvText:
                            key byte = $2A;
                            byte;               /* dvh */
                            pstring;

                        case dhdvText:
                            key byte = $2B;
                            byte;               /* dh */
                            byte;               /* dv */
                            pstring;

                        case FrameRect:
                            key byte = $30;
                            Rect;

                        case PaintRect:
                            key byte = $31;
                            Rect;
                        case EraseRect:
                            key byte = $32;
                            Rect;

                        case InvertRect:
                            key byte = $33;
                            Rect;

                        case FillRect:
                            key byte = $34;
                            Rect;

                        case FrameSameRect:
                            key byte = $38;

                        case PaintSameRect:
                            key byte = $39;

                        case EraseSameRect:
                            key byte = $3A;

                        case InvertSameRect:
                            key byte = $3B;

                        case FillSameRect:
                            key byte = $3C;

                        case FrameRRect:
                            key byte = $40;
                            Rect;

                        case PaintRRect:
                            key byte = $41;
                            Rect;

                        case EraseRRect:
                            key byte = $42;
                            Rect;

                        case InvertRRect:
                            key byte = $43;
                            Rect;

                        case FillRRect:
                            key byte = $44;
                            Rect;

                        case FrameSameRRect:
                            key byte = $48;

                        case PaintSameRRect:
                            key byte = $49;

                        case EraseSameRRect:
                            key byte = $4A;

                        case InvertSameRRect:
                            key byte = $4B;

                        case FillSameRRect:
                            key byte = $4C;

                        case FrameOval:
                            key byte = $50;
                            Rect;

                        case PaintOval:
                            key byte = $51;
                            Rect;

                        case EraseOval:
                            key byte = $52;
                            Rect;

                        case InvertOval:
                            key byte = $53;
                            Rect;

                        case FillOval:
                            key byte = $54;
                            Rect;

                        case FrameSameOval:
                            key byte = $58;

                        case PaintSameOval:
                            key byte = $59;

                        case EraseSameOval:
                            key byte = $5A;

                        case InvertSameOval:
                            key byte = $5B;

                        case FillSameOval:
                            key byte = $5C;
                        case FrameArc:
                            key byte = $60;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case PaintArc:
                            key byte = $61;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case EraseArc:
                            key byte = $62;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case InvertArc:
                            key byte = $63;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FillArc:
                            key byte = $64;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FrameSameArc:
                            key byte = $68;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case PaintSameArc:
                            key byte = $69;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case EraseSameArc:
                            key byte = $6A;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case InvertSameArc:
                            key byte = $6B;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FillSameArc:
                            key byte = $6C;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FramePoly:
                            key byte = $70;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };
                        case PaintPoly:
                            key byte = $71;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case ErasePoly:
                            key byte = $72;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case InvertPoly:
                            key byte = $73;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case FillPoly:
                            key byte = $74;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case FrameSamePoly:
                            key byte = $78;

                        case PaintSamePoly:
                            key byte = $79;

                        case EraseSamePoly:
                            key byte = $7A;

                        case InvertSamePoly:
                            key byte = $7B;

                        case FillSamePoly:
                            key byte = $7C;
                        case FrameRgn:
                            key byte = $80;
    FrameRgnStart:          integer = (FrameRgnEnd[$$ArrayIndex(OpCodes)] - FrameRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(FrameRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    FrameRgnEnd:
                        case PaintRgn:
                            key byte = $81;
    PaintRgnStart:          integer = (PaintRgnEnd[$$ArrayIndex(OpCodes)] - PaintRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(PaintRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    PaintRgnEnd:
                        case EraseRgn:
                            key byte = $82;
    EraseRgnStart:          integer = (EraseRgnEnd[$$ArrayIndex(OpCodes)] - EraseRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(EraseRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    EraseRgnEnd:
                        case InvertRgn:
                            key byte = $83;
    InvertRgnStart:         integer = (InvertRgnEnd[$$ArrayIndex(OpCodes)] - InvertRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(InvertRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    InvertRgnEnd:
                        case FillRgn:
                            key byte = $84;
    FillRgnStart:           integer = (FillRgnEnd[$$ArrayIndex(OpCodes)] - FillRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(FillRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    FillRgnEnd:
                        case FrameSameRgn:
                            key byte = $88;

                        case PaintSameRgn:
                            key byte = $89;

                        case EraseSameRgn:
                            key byte = $8A;

                        case InvertSameRgn:
                            key byte = $8B;

                        case FillSameRgn:
                            key byte = $8C;

                        case BitsRect:
                            key byte = $90;
    BitsRectRowBytes:       integer;                    /* row bytes */
    BitsRectBounds:         Rect;                       /* bounds */
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;
                            hex string [($$BitField(BitsRectBounds[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(BitsRectBounds[$$ArrayIndex(OpCodes)],0,16))
                                        * $$Word(BitsRectRowBytes[$$ArrayIndex(OpCodes)])];

                        case BitsRgn:
                            key byte = $91;
    BitsRgnRowBytes:        integer;                    /* row bytes */
    BitsRgnBounds:          Rect;                       /* bounds */
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;
    BitsRgnStart:           integer = (BitsRgnEnd[$$ArrayIndex(OpCodes)] - BitsRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(BitsRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    BitsRgnEnd:
                            hex string [($$BitField(BitsRgnBounds[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(BitsRgnBounds[$$ArrayIndex(OpCodes)],0,16))
                                        * $$Word(BitsRgnRowBytes[$$ArrayIndex(OpCodes)])];
                        case PackBitsRect:
                            key byte = $98;
    PackBitsRectRowBytes:   integer;                    /* row bytes */
    PackBitsRectBounds:     Rect;                       /* bounds */
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;
    PackBitsBits:           hex string [$$PackedSize(PackBitsBits[$$ArrayIndex(OpCodes)],
                                        $$Word(PackBitsRectRowBytes[$$ArrayIndex(OpCodes)]),
                                        ($$BitField(PackBitsRectBounds[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(PackBitsRectBounds[$$ArrayIndex(OpCodes)],0,16)))];
                        case PackBitsRgn:
                            key byte = $99;
    PackBitsRgnRowBytes:    integer;                    /* row bytes */
    PackBitsRgnBounds:      Rect;                       /* bounds */
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;
    PackBitsRgnStart:       integer = (PackBitsRgnEnd[$$ArrayIndex(OpCodes)] - PackBitsRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(PackBitsRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    PackBitsRgnEnd:         hex string [$$PackedSize(PackBitsRgnEnd[$$ArrayIndex(OpCodes)],
                                        $$Word(PackBitsRgnRowBytes[$$ArrayIndex(OpCodes)]),
                                        ($$BitField(PackBitsRgnBounds[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(PackBitsRgnBounds[$$ArrayIndex(OpCodes)],0,16)))];

                        case ShortComment:
                            key byte = $A0;
                            integer;            /* kind */

                        case LongComment:
                            key byte = $A1;
                            integer;            /* kind */
    LongCommentStart:       integer = (LongCommentEnd[$$ArrayIndex(OpCodes)] - LongCommentStart[$$ArrayIndex(OpCodes)] - 16) >> 3;
                            hex string [$$Word(LongCommentStart[$$ArrayIndex(OpCodes)])];
    LongCommentEnd:
                    };
                };
                byte = $FF;     /* End of picture */
            case VersionTwo:
                key longint = $001102ff;        /* Version op + version */
                array OpCodes {
                    switch {
                        case Clip:
                            key integer = $0001;
    ClipStart:              integer = (ClipEnd[$$ArrayIndex(OpCodes)] - ClipStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(ClipStart[$$ArrayIndex(OpCodes)]) - 10];
    ClipEnd:
                        case BkPat:
                            key integer = $0002;
                            hex string [8];

                        case TxFont:
                            key integer = $0003;
                            integer;            /* font */

                        case TxFace:
                            key integer = $0004;
                            unsigned hex byte;  /* text face */

                        case TxMode:
                            key integer = $0005;
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic;

                        case SpExtra:
                            key integer = $0006;
                            unsigned hex longint;

                        case PnSize:
                            key integer = $0007;
                            Point;

                        case PnMode:
                            key integer = $0008;
                            unsigned hex integer;

                        case PnPat:
                            key integer = $0009;
                            hex string [8];

                        case FillPat:
                            key integer = $000A;
                            hex string [8];

                        case OvSize:
                            key integer = $000B;
                            Point;

                        case Origin:
                            key integer = $000C;
                            integer;            /* dh */
                            integer;            /* dv */

                        case TxSize:
                            key integer = $000D;
                            integer;

                        case FgColor:
                            key integer = $000E;
                            longint;

                        case BkColor:
                            key integer = $000F;
                            longint;

                        case TxRatio:
                            key integer = $0010;
                            Point;              /* numer */
                            Point;              /* denom */

                        case Version:
                            key integer = $0011;
                            byte;
                        case BkPixPat:
                            key integer = $0012;
                            switch {
                                case newPattern:
                                    key integer = 1;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                                    unsigned bitstring[2] = 0;                              /* Must be 0            */
    BkPixPatpMapRowBytes:           unsigned bitstring[13];                                 /* Offset to next row   */
    BkPixPatBounds:                 rect;                                                   /* Bitmap bounds        */
                                    integer;                                                /* pixMap vers number   */
                                    integer unpacked;                                       /* Packing format       */
                                    unsigned longint;                                       /* Size of pixel data   */
                                    unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                                    unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                                    integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                                    integer;                                                /* # bits in pixel      */
                                    integer;                                                /* # components in pixel*/
                                    integer;                                                /* # bits per field     */
                                    unsigned longint;                                       /* Offset to next plane */
                                    unsigned longint;                                       /* Offset to color table*/
                                    fill long;                                              /* Reserved             */
                                    /* Color Table */
                                    unsigned hex longint;                                   /* ctSeed               */
                                    integer;                                                /* ctFlags              */
                                    integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                                    wide array ColorSpec {
                                            integer;                                        /* value                */
                                            unsigned integer;                               /* RGB: red             */
                                            unsigned integer;                               /*      green           */
                                            unsigned integer;                               /*      blue            */
                                    };
                                    /* If rowBytes < 8 then data is unpacked,
                                       if >= 8, then data is packed */
    BkPixPatBits:                   hex string [($$BitField(BkPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) < 8) *
                                                $$BitField(BkPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) +
                                                ($$BitField(BkPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) >= 8) *
                                                $$PackedSize(BkPixPatBits[$$ArrayIndex(OpCodes)],
                                                $$BitField(BkPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                                ($$BitField(BkPixPatBounds[$$ArrayIndex(OpCodes)],32,16)
                                                - $$BitField(BkPixPatBounds[$$ArrayIndex(OpCodes)],0,16)))];

                                case ditherPattern:
                                    key integer = 2;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned integer;       /* RGB: red             */
                                    unsigned integer;       /*      green           */
                                    unsigned integer;       /*      blue            */
                            };
                        case PnPixPat:
                            key integer = $0013;
                            switch {
                                case newPattern:
                                    key integer = 1;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                                    unsigned bitstring[2] = 0;                              /* Must be 0            */
    PnPixPatpMapRowBytes:           unsigned bitstring[13];                                 /* Offset to next row   */
    PnPixPatBounds:                 rect;                                                   /* Bitmap bounds        */
                                    integer;                                                /* pixMap vers number   */
                                    integer unpacked;                                       /* Packing format       */
                                    unsigned longint;                                       /* Size of pixel data   */
                                    unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                                    unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                                    integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                                    integer;                                                /* # bits in pixel      */
                                    integer;                                                /* # components in pixel*/
                                    integer;                                                /* # bits per field     */
                                    unsigned longint;                                       /* Offset to next plane */
                                    unsigned longint;                                       /* Offset to color table*/
                                    fill long;                                              /* Reserved             */
                                    /* Color Table */
                                    unsigned hex longint;                                   /* ctSeed               */
                                    integer;                                                /* ctFlags              */
                                    integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                                    wide array ColorSpec {
                                            integer;                                        /* value                */
                                            unsigned integer;                               /* RGB: red             */
                                            unsigned integer;                               /*      green           */
                                            unsigned integer;                               /*      blue            */
                                    };
                                    /* If rowBytes < 8 then data is unpacked,
                                       if >= 8, then data is packed */
    PnPixPatBits:                   hex string [($$BitField(PnPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) < 8) *
                                                $$BitField(PnPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) +
                                                ($$BitField(PnPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) >= 8) *
                                                $$PackedSize(PnPixPatBits[$$ArrayIndex(OpCodes)],
                                                $$BitField(PnPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                                ($$BitField(PnPixPatBounds[$$ArrayIndex(OpCodes)],32,16)
                                                - $$BitField(PnPixPatBounds[$$ArrayIndex(OpCodes)],0,16)))];
                                case ditherPattern:
                                    key integer = 2;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned integer;       /* RGB: red             */
                                    unsigned integer;       /*      green           */
                                    unsigned integer;       /*      blue            */
                            };

                        case FillPixPat:
                            key integer = $0014;
                            switch {
                                case newPattern:
                                    key integer = 1;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                                    unsigned bitstring[2] = 0;                              /* Must be 0            */
    FillPixPatpMapRowBytes:         unsigned bitstring[13];                                 /* Offset to next row   */
    FillPixPatBounds:                   rect;                                                   /* Bitmap bounds        */
                                    integer;                                                /* pixMap vers number   */
                                    integer unpacked;                                       /* Packing format       */
                                    unsigned longint;                                       /* Size of pixel data   */
                                    unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                                    unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                                    integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                                    integer;                                                /* # bits in pixel      */
                                    integer;                                                /* # components in pixel*/
                                    integer;                                                /* # bits per field     */
                                    unsigned longint;                                       /* Offset to next plane */
                                    unsigned longint;                                       /* Offset to color table*/
                                    fill long;                                              /* Reserved             */
                                    /* Color Table */
                                    unsigned hex longint;                                   /* ctSeed               */
                                    integer;                                                /* ctFlags              */
                                    integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                                    wide array ColorSpec {
                                            integer;                                        /* value                */
                                            unsigned integer;                               /* RGB: red             */
                                            unsigned integer;                               /*      green           */
                                            unsigned integer;                               /*      blue            */
                                    };
                                    /* If rowBytes < 8 then data is unpacked,
                                       if >= 8, then data is packed */
    FillPixPatBits:                 hex string [($$BitField(FillPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) < 8) *
                                                $$BitField(FillPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) +
                                                ($$BitField(FillPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) >= 8) *
                                                $$PackedSize(FillPixPatBits[$$ArrayIndex(OpCodes)],
                                                $$BitField(FillPixPatpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                                ($$BitField(FillPixPatBounds[$$ArrayIndex(OpCodes)],32,16)
                                                - $$BitField(FillPixPatBounds[$$ArrayIndex(OpCodes)],0,16)))];
                                case ditherPattern:
                                    key integer = 2;
                                    hex string [8];         /* old-style pattern    */
                                    unsigned integer;       /* RGB: red             */
                                    unsigned integer;       /*      green           */
                                    unsigned integer;       /*      blue            */
                            };

                        case PnLocHFrac:
                            key integer = $0015;
                            unsigned hex integer;

                        case ChExtra:
                            key integer = $0016;
                            integer;                        /* extra for each character */

                        case AppleReserved0017:
                            key integer = $0017;

                        case AppleReserved0018:
                            key integer = $0018;

                        case AppleReserved0019:
                            key integer = $0019;

                        case RGBFgCol:
                            key integer = $001A;
                            unsigned integer;       /* RGB: red             */
                            unsigned integer;       /*      green           */
                            unsigned integer;       /*      blue            */

                        case RGBBkCol:
                            key integer = $001B;
                            unsigned integer;       /* RGB: red             */
                            unsigned integer;       /*      green           */
                            unsigned integer;       /*      blue            */

                        case HiliteMode:
                            key integer = $001C;

                        case HiliteColor:
                            key integer = $001D;
                            unsigned integer;       /* RGB: red             */
                            unsigned integer;       /*      green           */
                            unsigned integer;       /*      blue            */

                        case DefHilite:
                            key integer = $001E;

                        case OpColor:
                            key integer = $001F;
                            unsigned integer;       /* RGB: red             */
                            unsigned integer;       /*      green           */
                            unsigned integer;       /*      blue            */

                        case Line:
                            key integer = $0020;
                            Point;                  /* pnLoc */
                            Point;                  /* newPt */

                        case LineFrom:
                            key integer = $0021;
                            Point;                  /* newPt */

                        case ShortLine:
                            key integer = $0022;
                            Point;                  /* pnLoc */
                            byte;                   /* dh */
                            byte;                   /* dv */

                        case ShortLineFrom:
                            key integer = $0023;
                            byte;                   /* dh */
                            byte;                   /* dv */
                        case AppleReserved0024:
                            key integer = $0024;
                AR24:       unsigned integer = (AR24End[$$ArrayIndex(Opcodes)] - AR24[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR24[$$ArrayIndex(Opcodes)])];
                AR24End:

                        case AppleReserved0025:
                            key integer = $0025;
                AR25:       unsigned integer = (AR25End[$$ArrayIndex(Opcodes)] - AR25[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR25[$$ArrayIndex(Opcodes)])];
                AR25End:

                        case AppleReserved0026:
                            key integer = $0026;
                AR26:       unsigned integer = (AR26End[$$ArrayIndex(Opcodes)] - AR26[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR26[$$ArrayIndex(Opcodes)])];
                AR26End:

                        case AppleReserved0027:
                            key integer = $0027;
                AR27:       unsigned integer = (AR27End[$$ArrayIndex(Opcodes)] - AR27[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR27[$$ArrayIndex(Opcodes)])];
                AR27End:

                        case LongText:
                            key integer = $0028;
                            Point;              /* TxLoc */
                            pstring;            /* text */

                        case DHText:
                            key integer = $0029;
                            byte;               /* dh */
                            pstring;            /* text */

                        case DVText:
                            key integer = $002A;
                            byte;               /* dv */
                            pstring;            /* text */

                        case DHDVText:
                            key integer = $002B;
                            byte;               /* dh */
                            byte;               /* dv */
                            pstring;            /* text */

                        case FontName:
                            key integer = $002C;
                FontNameBegin:  unsigned integer = (FontNameEnd[$$ArrayIndex(Opcodes)] - FontNameBegin[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            integer;            /* Old font ID */
                            pstring;            /* Font name */
                FontNameEnd:

                        case LineJustify:
                            key integer = $002D;
                            unsigned integer = 8;
                            longint;            /* Inter-character spacing */
                            longint;            /* Total extra space for justification */

                        case AppleReserved002E:
                            key integer = $002E;
                AR2E:       unsigned integer = (AR2EEnd[$$ArrayIndex(Opcodes)] - AR2E[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR2E[$$ArrayIndex(Opcodes)])];
                AR2EEnd:

                        case AppleReserved002F:
                            key integer = $002F;
                AR2F:       unsigned integer = (AR2FEnd[$$ArrayIndex(Opcodes)] - AR2F[$$ArrayIndex(Opcodes)]) / 8 - 2;
                            hex string [$$Word(AR2F[$$ArrayIndex(Opcodes)])];
                AR2FEnd:

                        case FrameRect:
                            key integer = $0030;
                            Rect;

                        case PaintRect:
                            key integer = $0031;
                            Rect;

                        case EraseRect:
                            key integer = $0032;
                            Rect;

                        case InvertRect:
                            key integer = $0033;
                            Rect;

                        case FillRect:
                            key integer = $0034;
                            Rect;

                        case AppleReserved0035:
                            key integer = $0035;
                            Rect;

                        case AppleReserved0036:
                            key integer = $0036;
                            Rect;

                        case AppleReserved0037:
                            key integer = $0037;
                            Rect;
                        case FrameSameRect:
                            key integer = $0038;

                        case PaintSameRect:
                            key integer = $0039;

                        case EraseSameRect:
                            key integer = $003A;

                        case InvertSameRect:
                            key integer = $003B;

                        case FillSameRect:
                            key integer = $003C;

                        case AppleReserved003D:
                            key integer = $003D;

                        case AppleReserved003E:
                            key integer = $003E;

                        case AppleReserved003F:
                            key integer = $003F;

                        case FrameRRect:
                            key integer = $0040;
                            Rect;

                        case PaintRRect:
                            key integer = $0041;
                            Rect;

                        case EraseRRect:
                            key integer = $0042;
                            Rect;

                        case InvertRRect:
                            key integer = $0043;
                            Rect;

                        case FillRRect:
                            key integer = $0044;
                            Rect;

                        case AppleReserved0045:
                            key integer = $0045;
                            Rect;

                        case AppleReserved0046:
                            key integer = $0046;
                            Rect;

                        case AppleReserved0047:
                            key integer = $0047;
                            Rect;

                        case FrameSameRRect:
                            key integer = $0048;

                        case PaintSameRRect:
                            key integer = $0049;

                        case EraseSameRRect:
                            key integer = $004A;

                        case InvertSameRRect:
                            key integer = $004B;

                        case FillSameRRect:
                            key integer = $004C;

                        case AppleReserved004D:
                            key integer = $004D;

                        case AppleReserved004E:
                            key integer = $004E;

                        case AppleReserved004F:
                            key integer = $004F;

                        case FrameOval:
                            key integer = $0050;
                            Rect;

                        case PaintOval:
                            key integer = $0051;
                            Rect;

                        case EraseOval:
                            key integer = $0052;
                            Rect;

                        case InvertOval:
                            key integer = $0053;
                            Rect;

                        case FillOval:
                            key integer = $0054;
                            Rect;

                        case AppleReserved0055:
                            key integer = $0055;
                            Rect;

                        case AppleReserved0056:
                            key integer = $0056;
                            Rect;

                        case AppleReserved0057:
                            key integer = $0057;
                            Rect;
                        case FrameSameOval:
                            key integer = $0058;

                        case PaintSameOval:
                            key integer = $0059;

                        case EraseSameOval:
                            key integer = $005A;

                        case InvertSameOval:
                            key integer = $005B;

                        case FillSameOval:
                            key integer = $005C;

                        case AppleReserved005D:
                            key integer = $005D;

                        case AppleReserved005E:
                            key integer = $005E;

                        case FrameArc:
                            key integer = $0060;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case PaintArc:
                            key integer = $0061;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case EraseArc:
                            key integer = $0062;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case InvertArc:
                            key integer = $0063;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FillArc:
                            key integer = $0064;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved0065:
                            key integer = $0065;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved0066:
                            key integer = $0066;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved0067:
                            key integer = $0067;
                            Rect;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FrameSameArc:
                            key integer = $0068;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case PaintSameArc:
                            key integer = $0069;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case EraseSameArc:
                            key integer = $006A;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case InvertSameArc:
                            key integer = $006B;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case FillSameArc:
                            key integer = $006C;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved006D:
                            key integer = $006D;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved006E:
                            key integer = $006E;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */

                        case AppleReserved006F:
                            key integer = $006F;
                            integer;                /* startAngle */
                            integer;                /* arcAngle */
                        case FramePoly:
                            key integer = $0070;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case PaintPoly:
                            key integer = $0071;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case ErasePoly:
                            key integer = $0072;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case InvertPoly:
                            key integer = $0073;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case FillPoly:
                            key integer = $0074;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case AppleReserved0075:
                            key integer = $0075;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case AppleReserved0076:
                            key integer = $0076;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case AppleReserved0077:
                            key integer = $0077;
                            integer = $$CountOf(PolyPoints) * 4 + 10;
                            Rect;                   /* enclosing rectangle */
                            wide array PolyPoints { Point; };

                        case FrameSamePoly:
                            key integer = $0078;

                        case PaintSamePoly:
                            key integer = $0079;

                        case EraseSamePoly:
                            key integer = $007A;

                        case InvertSamePoly:
                            key integer = $007B;

                        case FillSamePoly:
                            key integer = $007C;

                        case AppleReserved007D:
                            key integer = $007D;

                        case AppleReserved007E:
                            key integer = $007E;

                        case AppleReserved007F:
                            key integer = $007F;
                        case FrameRgn:
                            key integer = $0080;
    FrameRgnStart2:         integer = (FrameRgnEnd2[$$ArrayIndex(OpCodes)] - FrameRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(FrameRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    FrameRgnEnd2:
                        case PaintRgn:
                            key integer = $0081;
    PaintRgnStart2:         integer = (PaintRgnEnd2[$$ArrayIndex(OpCodes)] - PaintRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(PaintRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    PaintRgnEnd2:
                        case EraseRgn:
                            key integer = $0082;
    EraseRgnStart2:         integer = (EraseRgnEnd2[$$ArrayIndex(OpCodes)] - EraseRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(EraseRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    EraseRgnEnd2:
                        case InvertRgn:
                            key integer = $0083;
    InvertRgnStart2:        integer = (InvertRgnEnd2[$$ArrayIndex(OpCodes)] - InvertRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(InvertRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    InvertRgnEnd2:
                        case FillRgn:
                            key integer = $0084;
    FillRgnStart2:          integer = (FillRgnEnd2[$$ArrayIndex(OpCodes)] - FillRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(FillRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    FillRgnEnd2:
                        case AppleReserved0085:
                            key integer = $0085;
    AppleReserved0085Start:integer = (AppleReserved0085End[$$ArrayIndex(OpCodes)] - AppleReserved0085Start[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(AppleReserved0085Start[$$ArrayIndex(OpCodes)]) - 10];
    AppleReserved0085End:
                        case AppleReserved0086:
                            key integer = $0086;
    AppleReserved0086Start: integer = (AppleReserved0086End[$$ArrayIndex(OpCodes)] - AppleReserved0086Start[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(AppleReserved0086Start[$$ArrayIndex(OpCodes)]) - 10];
    AppleReserved0086End:
                        case AppleReserved0087:
                            key integer = $0087;
    AppleReserved0087Start: integer = (AppleReserved0087End[$$ArrayIndex(OpCodes)] - AppleReserved0087Start[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(AppleReserved0087Start[$$ArrayIndex(OpCodes)]) - 10];
    AppleReserved0087End:
                        case FrameSameRgn:
                            key integer = $0088;

                        case PaintSameRgn:
                            key integer = $0089;

                        case EraseSameRgn:
                            key integer = $008A;

                        case InvertSameRgn:
                            key integer = $008B;

                        case FillSameRgn:
                            key integer = $008C;

                        case AppleReserved008D:
                            key integer = $008D;

                        case AppleReserved008E:
                            key integer = $008E;

                        case AppleReserved008F:
                            key integer = $008F;

                        case BitsRect:
                            key integer = $0090;
                            unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                              /* Must be 0            */
    BitsRectpMapRowBytes:   unsigned bitstring[13];                                 /* Offset to next row   */
    BitsRectBounds2:        rect;                                                   /* Bitmap bounds        */
                            integer;                                                /* pixMap vers number   */
                            integer unpacked;                                       /* Packing format       */
                            unsigned longint;                                       /* Size of pixel data   */
                            unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                            integer;                                                /* # bits in pixel      */
                            integer;                                                /* # components in pixel*/
                            integer;                                                /* # bits per field     */
                            unsigned longint;                                       /* Offset to next plane */
                            unsigned longint;                                       /* Offset to color table*/
                            fill long;                                              /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                   /* ctSeed               */
                            integer;                                                /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                        /* value                */
                                    unsigned integer;                               /* RGB: red             */
                                    unsigned integer;                               /*      green           */
                                    unsigned integer;                               /*      blue            */
                            };
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    BitsRectBits:           hex string [$$BitField(BitsRectpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) *
                                        ($$BitField(BitsRectBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(BitsRectBounds2[$$ArrayIndex(OpCodes)],0,16))];

                        case BitsRgn:
                            key integer = $0091;
                            unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                              /* Must be 0            */
    BitsRgnpMapRowBytes:    unsigned bitstring[13];                                 /* Offset to next row   */
    BitsRgnBounds2:         rect;                                                   /* Bitmap bounds        */
                            integer;                                                /* pixMap vers number   */
                            integer unpacked;                                       /* Packing format       */
                            unsigned longint;                                       /* Size of pixel data   */
                            unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                            integer;                                                /* # bits in pixel      */
                            integer;                                                /* # components in pixel*/
                            integer;                                                /* # bits per field     */
                            unsigned longint;                                       /* Offset to next plane */
                            unsigned longint;                                       /* Offset to color table*/
                            fill long;                                              /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                   /* ctSeed               */
                            integer;                                                /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                        /* value                */
                                    unsigned integer;                               /* RGB: red             */
                                    unsigned integer;                               /*      green           */
                                    unsigned integer;                               /*      blue            */
                            };
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    BitsRgnStart2:          integer = (BitsRgnEnd2[$$ArrayIndex(OpCodes)] - BitsRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(BitsRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    BitsRgnEnd2:            hex string [$$PackedSize(BitsRgnEnd2[$$ArrayIndex(OpCodes)],
                                        $$BitField(BitsRgnpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                        ($$BitField(BitsRgnBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(BitsRgnBounds2[$$ArrayIndex(OpCodes)],0,16)))];

                        case AppleReserved0092:
                            key integer = $0092;
    AppleReserved0092Start: unsigned integer = (AppleReserved0092End[$$ArrayIndex(OpCodes)] - AppleReserved0092Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0092Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0092End:
                        case AppleReserved0093:
                            key integer = $0093;
    AppleReserved0093Start: unsigned integer = (AppleReserved0093End[$$ArrayIndex(OpCodes)] - AppleReserved0093Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0093Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0093End:
                        case AppleReserved0094:
                            key integer = $0094;
    AppleReserved0094Start: unsigned integer = (AppleReserved0094End[$$ArrayIndex(OpCodes)] - AppleReserved0094Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0094Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0094End:
                        case AppleReserved0095:
                            key integer = $0095;
    AppleReserved0095Start: unsigned integer = (AppleReserved0095End[$$ArrayIndex(OpCodes)] - AppleReserved0095Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0095Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0095End:
                        case AppleReserved0096:
                            key integer = $0096;
    AppleReserved0096Start: unsigned integer = (AppleReserved0096End[$$ArrayIndex(OpCodes)] - AppleReserved0096Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0096Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0096End:
                        case AppleReserved0097:
                            key integer = $0097;
    AppleReserved0097Start: unsigned integer = (AppleReserved0097End[$$ArrayIndex(OpCodes)] - AppleReserved0097Start[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved0097Start[$$ArrayIndex(OpCodes)])];
    AppleReserved0097End:
                        case PackBitsRect:
                            key integer = $0098;
                            unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                              /* Must be 0            */
    PackBitsRectpMapRowBytes:unsigned bitstring[13];                                    /* Offset to next row   */
    PackBitsRectBounds2:    rect;                                                   /* Bitmap bounds        */
                            integer;                                                /* pixMap vers number   */
                            integer unpacked;                                       /* Packing format       */
                            unsigned longint;                                       /* Size of pixel data   */
                            unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                            integer;                                                /* # bits in pixel      */
                            integer;                                                /* # components in pixel*/
                            integer;                                                /* # bits per field     */
                            unsigned longint;                                       /* Offset to next plane */
                            unsigned longint;                                       /* Offset to color table*/
                            fill long;                                              /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                   /* ctSeed               */
                            integer;                                                /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                        /* value                */
                                    unsigned integer;                               /* RGB: red             */
                                    unsigned integer;                               /*      green           */
                                    unsigned integer;                               /*      blue            */
                            };
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    PackBitsRectBits:       hex string [$$PackedSize(PackBitsRectBits[$$ArrayIndex(OpCodes)],
                                        $$BitField(PackBitsRectpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                        ($$BitField(PackBitsRectBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(PackBitsRectBounds2[$$ArrayIndex(OpCodes)],0,16)))];
                        case PackBitsRgn:
                            key integer = $0099;
                            unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                              /* Must be 0            */
    PackBitsRgnpMapRowBytes:unsigned bitstring[13];                                 /* Offset to next row   */
    PackBitsRgnBounds2: rect;                                                       /* Bitmap bounds        */
                            integer;                                                /* pixMap vers number   */
                            integer unpacked;                                       /* Packing format       */
                            unsigned longint;                                       /* Size of pixel data   */
                            unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                            integer;                                                /* # bits in pixel      */
                            integer;                                                /* # components in pixel*/
                            integer;                                                /* # bits per field     */
                            unsigned longint;                                       /* Offset to next plane */
                            unsigned longint;                                       /* Offset to color table*/
                            fill long;                                              /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                   /* ctSeed               */
                            integer;                                                /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                        /* value                */
                                    unsigned integer;                               /* RGB: red             */
                                    unsigned integer;                               /*      green           */
                                    unsigned integer;                               /*      blue            */
                            };
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    PackBitsRgnStart2:      integer = (PackBitsRgnEnd2[$$ArrayIndex(OpCodes)] - PackBitsRgnStart2[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;               /* region’s enclosing rect */
                            hex string [$$Word(PackBitsRgnStart2[$$ArrayIndex(OpCodes)]) - 10];
    PackBitsRgnEnd2:        hex string [$$PackedSize(PackBitsRgnEnd2[$$ArrayIndex(OpCodes)],
                                        $$BitField(PackBitsRgnpMapRowBytes[$$ArrayIndex(OpCodes)],0,13),
                                        ($$BitField(PackBitsRgnBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(PackBitsRgnBounds2[$$ArrayIndex(OpCodes)],0,16)))];

                        case DirectBitsRect:
                            key integer = $009A;
    DirectBitsRectStart:    unsigned integer = (DirectBitsRectEnd[$$ArrayIndex(OpCodes)] - DirectBitsRectStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            unsigned bitstring[1] = 1;                              /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                              /* Must be 0            */
    DirectBitsRectpMapRowBytes: unsigned bitstring[13];                                 /* Offset to next row   */
    DirectBitsRectBounds2:      rect;                                                   /* Bitmap bounds        */
                            integer;                                                /* pixMap vers number   */
                            integer unpacked;                                       /* Packing format       */
                            unsigned longint;                                       /* Size of pixel data   */
                            unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
                            integer;                                                /* # bits in pixel      */
                            integer;                                                /* # components in pixel*/
                            integer;                                                /* # bits per field     */
                            unsigned longint;                                       /* Offset to next plane */
                            unsigned longint;                                       /* Offset to color table*/
                            fill long;                                              /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                   /* ctSeed               */
                            integer;                                                /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                        /* value                */
                                    unsigned integer;                               /* RGB: red             */
                                    unsigned integer;                               /*      green           */
                                    unsigned integer;                               /*      blue            */
                            };
                            Rect;                       /* srcRect */
                            Rect;                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    DirectBitsRectBits:     hex string [$$BitField(DirectBitsRectpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) *
                                        ($$BitField(DirectBitsRectBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(DirectBitsRectBounds2[$$ArrayIndex(OpCodes)],0,16))];
    DirectBitsRectEnd:
                        case DirectBitsRgn:
                            key integer = $009B;
    DirectBitsRgnStart: unsigned integer = (DirectBitsRgnEnd[$$ArrayIndex(OpCodes)] - DirectBitsRgnStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            unsigned bitstring[1] = 1;                                  /* New pixMap flag      */
                            unsigned bitstring[2] = 0;                                  /* Must be 0            */
    DirectBitsRgnpMapRowBytes:  unsigned bitstring[13];                                 /* Offset to next row   */
    DirectBitsRgnBounds2:       rect;                                                   /* Bitmap bounds        */
                            integer;                                                    /* pixMap vers number   */
                            integer unpacked;                                           /* Packing format       */
                            unsigned longint;                                           /* Size of pixel data   */
                            unsigned hex longint;                                       /* h. resolution (ppi) (fixed) */
                            unsigned hex longint;                                       /* v. resolution (ppi) (fixed) */
                            integer         chunky, chunkyPlanar, planar;               /* Pixel storage format */
                            integer;                                                    /* # bits in pixel      */
                            integer;                                                    /* # components in pixel*/
                            integer;                                                    /* # bits per field     */
                            unsigned longint;                                           /* Offset to next plane */
                            unsigned longint;                                           /* Offset to color table*/
                            fill long;                                                  /* Reserved             */
                            /* Color Table */
                            unsigned hex longint;                                       /* ctSeed               */
                            integer;                                                    /* ctFlags              */
                            integer = $$Countof(ColorSpec) - 1;                         /* ctSize               */
                            wide array ColorSpec {
                                    integer;                                            /* value                */
                                    unsigned integer;                                   /* RGB: red             */
                                    unsigned integer;                                   /*      green           */
                                    unsigned integer;                                   /*      blue            */
                            };
                            Rect;                                                       /* srcRect */
                            Rect;                                                       /* destRect */
                            integer     srcCopy, srcOr, srcXor, srcBic, /* mode */
                                        notSrcCopy, notSrcOr, notSrcXor, notSrcBic, 
                                        patCopy, patOr, patXor, patBic,
                                        notPatCopy, notPatOr, notPatXor, notPatBic,
                                        blend = 32, addPin, addOver, subPin,
                                        adMax = 37, subOver, adMin;
    DirectBitsMaskRgnStart: integer = (DirectBitsMaskRgnEnd[$$ArrayIndex(OpCodes)] - DirectBitsMaskRgnStart[$$ArrayIndex(OpCodes)]) >> 3;
                            Rect;                                                   /* region’s enclosing rect */
                            hex string [$$Word(DirectBitsMaskRgnStart[$$ArrayIndex(OpCodes)]) - 10];
    DirectBitsMaskRgnEnd:
    DirectBitsRgnBits:      hex string [$$BitField(DirectBitsRgnpMapRowBytes[$$ArrayIndex(OpCodes)],0,13) *
                                        ($$BitField(DirectBitsRgnBounds2[$$ArrayIndex(OpCodes)],32,16)
                                        - $$BitField(DirectBitsRgnBounds2[$$ArrayIndex(OpCodes)],0,16))];
    DirectBitsRgnEnd:

                        case AppleReserved009C:
                            key integer = $009C;
    AppleReserved009CStart: unsigned integer = (AppleReserved009CEnd[$$ArrayIndex(OpCodes)] - AppleReserved009CStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved009CStart[$$ArrayIndex(OpCodes)])];
    AppleReserved009CEnd:
                        case AppleReserved009D:
                            key integer = $009D;
    AppleReserved009DStart: unsigned integer = (AppleReserved009DEnd[$$ArrayIndex(OpCodes)] - AppleReserved009DStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved009DStart[$$ArrayIndex(OpCodes)])];
    AppleReserved009DEnd:
                        case AppleReserved009E:
                            key integer = $009E;
    AppleReserved009EStart: unsigned integer = (AppleReserved009EEnd[$$ArrayIndex(OpCodes)] - AppleReserved009EStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved009EStart[$$ArrayIndex(OpCodes)])];
    AppleReserved009EEnd:
                        case AppleReserved009F:
                            key integer = $009F;
    AppleReserved009FStart: unsigned integer = (AppleReserved009FEnd[$$ArrayIndex(OpCodes)] - AppleReserved009FStart[$$ArrayIndex(OpCodes)]) >> 3 - 2;
                            hex string [$$Word(AppleReserved009FStart[$$ArrayIndex(OpCodes)])];
    AppleReserved009FEnd:
                        case ShortComment:
                            key integer = $00A0;
                            integer;                            /* comment kind */
                        case LongComment:
                            key integer = $00A1;
                            integer;                            /* comment kind */
    LongCommentStart2:      integer = (LongCommentEnd2[$$ArrayIndex(OpCodes)] - LongCommentStart2[$$ArrayIndex(OpCodes)] - 16) >> 3;
                            hex string [$$Word(LongCommentStart2[$$ArrayIndex(OpCodes)])];
    LongCommentEnd2:
                        case OpEndPic:
                            key integer = $00FF;

                        case HeaderOp:
                            key integer = $0C00;
#if PICT_RezTemplateVersion == 1
                            longint Version2 = -1;
                            /* Fixed point bounding box */
                            unsigned hex longint;
                            unsigned hex longint;
                            unsigned hex longint;
                            unsigned hex longint;
                            longint Version2 = -1;                  /* Reserved */
#else
                            switch  {
                                case StandardVersion2:
                                    key integer = -1;
                                    integer = -1;
                                    unsigned hex longint;
                                    unsigned hex longint;
                                    unsigned hex longint;
                                    unsigned hex longint;
                                    fill long;                      /* Reserved */
                                case ExtendedVersion2:
                                    key integer = -2;
                                    fill word;
                                    unsigned hex longint;           /* hRes */
                                    unsigned hex longint;           /* vRes */
                                    Rect;                           /* SrcRect */
                                    fill long;                      /* Reserved */
                            };
#endif
                    };
                    align word;
                };
        };
    endOfPict:
#endif
};

#endif __PICT_R__


#endif /* __PICTUTILS_R__ */

