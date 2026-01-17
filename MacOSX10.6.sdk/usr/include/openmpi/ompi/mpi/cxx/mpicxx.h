// -*- c++ -*-
// 
// Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
//                         University Research and Technology
//                         Corporation.  All rights reserved.
// Copyright (c) 2004-2005 The University of Tennessee and The University
//                         of Tennessee Research Foundation.  All rights
//                         reserved.
// Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
//                         University of Stuttgart.  All rights reserved.
// Copyright (c) 2004-2005 The Regents of the University of California.
//                         All rights reserved.
// Copyright (c) 2006-2007 Cisco Systems, Inc.  All rights reserved.
// $COPYRIGHT$
// 
// Additional copyrights may follow
// 
// $HEADER$
//

#ifndef MPIPP_H
#define MPIPP_H

// 
// Let's ensure that we're really in C++, and some errant programmer
// hasn't included <mpicxx.h> just "for completeness"
//

#if defined(__cplusplus) || defined(c_plusplus) 

// do not include ompi_config.h.  it will smash free() as a symbol
#include <mpi.h>

// we include all this here so that we escape the silly namespacing issues
#include <map>
#include <utility>

#include <stdarg.h>

#if !defined(OMPI_IGNORE_CXX_SEEK) & OMPI_WANT_MPI_CXX_SEEK
// We need to include the header files that define SEEK_* or use them
// in ways that require them to be #defines so that if the user
// includes them later, the double inclusion logic in the headers will
// prevent trouble from occuring.

// include so that we can smash SEEK_* properly
#include <stdio.h>
// include because on Linux, there is one place that assumes SEEK_* is
// a #define (it's used in an enum).
#include <iostream>

// smash SEEK_* #defines
#ifdef SEEK_SET
#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#endif

// make globally scoped constants to replace smashed #defines
extern const int SEEK_SET;
extern const int SEEK_CUR;
extern const int SEEK_END;
#endif

// forward declare so that we can still do inlining
struct opal_mutex_t;

// See lengthy explanation in intercepts.cc about this function.
extern "C" void
ompi_mpi_cxx_op_intercept(void *invec, void *outvec, int *len, 
                          MPI_Datatype *datatype, MPI_User_function *fn);

extern "C" void
ompi_mpi_cxx_comm_errhandler_intercept(MPI_Comm * mpi_comm, int * err, ...);
extern "C" void
ompi_mpi_cxx_win_errhandler_intercept(MPI_Win * mpi_comm, int * err, ...);
extern "C" void
ompi_mpi_cxx_file_errhandler_intercept(MPI_File * mpi_comm, int * err, ...);


//used for attr intercept functions
enum CommType { eIntracomm, eIntercomm, eCartcomm, eGraphcomm};

extern "C" int
ompi_mpi_cxx_comm_copy_attr_intercept(MPI_Comm oldcomm, int keyval, 
                                      void *extra_state, void *attribute_val_in, 
                                      void *attribute_val_out, int *flag,
                                      MPI_Comm newcomm);
extern "C" int
ompi_mpi_cxx_comm_delete_attr_intercept(MPI_Comm comm, int keyval, 
                                        void *attribute_val, void *extra_state);

extern "C" int
ompi_mpi_cxx_type_copy_attr_intercept(MPI_Datatype oldtype, int keyval, 
                                      void *extra_state, void *attribute_val_in, 
                                      void *attribute_val_out, int *flag);
extern "C" int
ompi_mpi_cxx_type_delete_attr_intercept(MPI_Datatype type, int keyval, 
                                        void *attribute_val, void *extra_state);

extern "C" int
ompi_mpi_cxx_win_copy_attr_intercept(MPI_Win oldwin, int keyval, 
                                      void *extra_state, void *attribute_val_in, 
                                      void *attribute_val_out, int *flag);
extern "C" int
ompi_mpi_cxx_win_delete_attr_intercept(MPI_Win win, int keyval, 
                                        void *attribute_val, void *extra_state);



//
// MPI generalized request intercepts
//

extern "C" int 
ompi_mpi_cxx_grequest_query_fn_intercept(void *state, MPI_Status *status);
extern "C" int 
ompi_mpi_cxx_grequest_free_fn_intercept(void *state);
extern "C" int 
ompi_mpi_cxx_grequest_cancel_fn_intercept(void *state, int canceled);

/**
 * Windows bool type is not any kind of integer. Special care should
 * be taken in order to cast it correctly.
 */
#if defined(WIN32) || defined(_WIN32) || defined(WIN64)
#define OPAL_INT_TO_BOOL(VALUE)  ((VALUE) != 0 ? true : false)
#else
#define OPAL_INT_TO_BOOL(VALUE)  ((bool)(VALUE))
#endif  /* defined(WIN32) || defined(_WIN32) || defined(WIN64) */

#if 0 /* OMPI_ENABLE_MPI_PROFILING */
#include "ompi/mpi/cxx/pmpicxx.h"
#endif

namespace MPI {

#if ! OMPI_HAVE_CXX_EXCEPTION_SUPPORT
	OMPI_DECLSPEC extern int mpi_errno;
#endif

  class Comm_Null;
  class Comm;
  class Intracomm;
  class Intercomm;
  class Graphcomm;
  class Cartcomm;
  class Datatype;
  class Errhandler;
  class Group;
  class Op;
  class Request;
  class Grequest;
  class Status;
  class Info;
  class Win;
  class File;

  typedef MPI_Aint Aint;
  typedef MPI_Offset Offset;

#ifdef OMPI_BUILDING_CXX_BINDINGS_LIBRARY
#include "ompi/mpi/cxx/constants.h"
#include "ompi/mpi/cxx/functions.h"
#include "ompi/mpi/cxx/datatype.h"
#else
#include "openmpi/ompi/mpi/cxx/constants.h"
#include "openmpi/ompi/mpi/cxx/functions.h"
#include "openmpi/ompi/mpi/cxx/datatype.h"
#endif

  typedef void User_function(const void* invec, void* inoutvec, int len,
			     const Datatype& datatype);

    /* Prevent needing a -I${prefix}/include/openmpi, as it seems to
       really annoy peope that don't use the wrapper compilers and is
       no longer worth the fight of getting right... */
#ifdef OMPI_BUILDING_CXX_BINDINGS_LIBRARY
#include "ompi/mpi/cxx/exception.h"
#include "ompi/mpi/cxx/op.h"
#include "ompi/mpi/cxx/status.h"
#include "ompi/mpi/cxx/request.h"   //includes class Prequest
#include "ompi/mpi/cxx/group.h" 
#include "ompi/mpi/cxx/comm.h"
#include "ompi/mpi/cxx/win.h"
#include "ompi/mpi/cxx/file.h"
#include "ompi/mpi/cxx/errhandler.h"
#include "ompi/mpi/cxx/intracomm.h"
#include "ompi/mpi/cxx/topology.h"  //includes Cartcomm and Graphcomm
#include "ompi/mpi/cxx/intercomm.h"
#include "ompi/mpi/cxx/info.h"
#else
#include "openmpi/ompi/mpi/cxx/exception.h"
#include "openmpi/ompi/mpi/cxx/op.h"
#include "openmpi/ompi/mpi/cxx/status.h"
#include "openmpi/ompi/mpi/cxx/request.h"   //includes class Prequest
#include "openmpi/ompi/mpi/cxx/group.h" 
#include "openmpi/ompi/mpi/cxx/comm.h"
#include "openmpi/ompi/mpi/cxx/win.h"
#include "openmpi/ompi/mpi/cxx/file.h"
#include "openmpi/ompi/mpi/cxx/errhandler.h"
#include "openmpi/ompi/mpi/cxx/intracomm.h"
#include "openmpi/ompi/mpi/cxx/topology.h"  //includes Cartcomm and Graphcomm
#include "openmpi/ompi/mpi/cxx/intercomm.h"
#include "openmpi/ompi/mpi/cxx/info.h"
#endif

    extern opal_mutex_t *mpi_map_mutex;
}

#if 0 /* OMPI_ENABLE_MPI_PROFILING */
#include "ompi/mpi/cxx/pop_inln.h"
#include "ompi/mpi/cxx/pgroup_inln.h"
#include "ompi/mpi/cxx/pstatus_inln.h"
#include "ompi/mpi/cxx/prequest_inln.h"
#endif

//
// These are the "real" functions, whether prototyping is enabled
// or not. These functions are assigned to either the MPI::XXX class
// or the PMPI::XXX class based on the value of the macro MPI
// which is set in mpi2cxx_config.h.
// If prototyping is enabled, there is a top layer that calls these
// PMPI functions, and this top layer is in the XXX.cc files.
//

/* see note above... */
#ifdef OMPI_BUILDING_CXX_BINDINGS_LIBRARY
#include "ompi/mpi/cxx/datatype_inln.h"
#include "ompi/mpi/cxx/functions_inln.h"
#include "ompi/mpi/cxx/request_inln.h"
#include "ompi/mpi/cxx/comm_inln.h"
#include "ompi/mpi/cxx/intracomm_inln.h"
#include "ompi/mpi/cxx/topology_inln.h"
#include "ompi/mpi/cxx/intercomm_inln.h"
#include "ompi/mpi/cxx/group_inln.h"
#include "ompi/mpi/cxx/op_inln.h"
#include "ompi/mpi/cxx/errhandler_inln.h"
#include "ompi/mpi/cxx/status_inln.h"
#include "ompi/mpi/cxx/info_inln.h"
#include "ompi/mpi/cxx/win_inln.h"
#include "ompi/mpi/cxx/file_inln.h"
#else
#include "openmpi/ompi/mpi/cxx/datatype_inln.h"
#include "openmpi/ompi/mpi/cxx/functions_inln.h"
#include "openmpi/ompi/mpi/cxx/request_inln.h"
#include "openmpi/ompi/mpi/cxx/comm_inln.h"
#include "openmpi/ompi/mpi/cxx/intracomm_inln.h"
#include "openmpi/ompi/mpi/cxx/topology_inln.h"
#include "openmpi/ompi/mpi/cxx/intercomm_inln.h"
#include "openmpi/ompi/mpi/cxx/group_inln.h"
#include "openmpi/ompi/mpi/cxx/op_inln.h"
#include "openmpi/ompi/mpi/cxx/errhandler_inln.h"
#include "openmpi/ompi/mpi/cxx/status_inln.h"
#include "openmpi/ompi/mpi/cxx/info_inln.h"
#include "openmpi/ompi/mpi/cxx/win_inln.h"
#include "openmpi/ompi/mpi/cxx/file_inln.h"
#endif

#endif // #if defined(__cplusplus) || defined(c_plusplus) 
#endif // #ifndef MPIPP_H_
