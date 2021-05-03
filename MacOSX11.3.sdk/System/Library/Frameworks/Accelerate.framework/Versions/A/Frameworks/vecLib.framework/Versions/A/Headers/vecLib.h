/*
     File:       vecLib/vecLib.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-760.100
 
     Copyright:  Copyright (c) 2000-2021 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECLIB__
#define __VECLIB__


#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

#ifndef __VBASICOPS__
#include <vecLib/vBasicOps.h>
#endif

#ifndef __VBIGNUM__
#include <vecLib/vBigNum.h>
#endif

#ifndef __VECTOROPS__
#include <vecLib/vectorOps.h>
#endif

#ifndef __VFP__
#include <vecLib/vfp.h>
#endif

#ifndef __VDSP__
#include <vecLib/vDSP.h>
#endif

#if defined __ppc__ || defined __i386__
#ifndef __VDSP_TRANSLATE__
#include <vecLib/vDSP_translate.h>
#endif
#endif

#ifndef CBLAS_H	
#include <vecLib/cblas.h>
#endif

#ifndef __CLAPACK_H
#include <vecLib/clapack.h>
#endif

#ifndef __LINEAR_ALGEBRA_PUBLIC_HEADER__
#include <vecLib/LinearAlgebra/LinearAlgebra.h>
#endif

#ifndef __SPARSE_HEADER__
#include <vecLib/Sparse/Sparse.h>
#include <vecLib/Sparse/Solve.h>
#endif

#ifndef __QUADRATURE_PUBLIC_HEADER__
#include <vecLib/Quadrature/Quadrature.h>
#endif // __QUADRATURE_PUBLIC_HEADER__

#ifndef __BNNS_HEADER__
#include <vecLib/BNNS/bnns.h>
#endif // __BNNS_HEADER__

#ifndef __VFORCE_H
#include <vecLib/vForce.h>
#endif

#endif /* __VECLIB__ */
