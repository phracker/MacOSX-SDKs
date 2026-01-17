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
// Copyright (c) 2007      Cisco Systems, Inc.  All rights reserved.
// $COPYRIGHT$
// 
// Additional copyrights may follow
// 
// $HEADER$
//
 
//
// Point-to-Point
//

inline void
MPI::Comm::Send(const void *buf, int count, 
		const MPI::Datatype & datatype, int dest, int tag) const
{
  (void)MPI_Send(const_cast<void *>(buf), count, datatype, dest, tag, mpi_comm);
}

inline void
MPI::Comm::Recv(void *buf, int count, const MPI::Datatype & datatype,
		int source, int tag, MPI::Status & status) const
{
  (void)MPI_Recv(buf, count, datatype, source, tag, mpi_comm, &status.mpi_status);
}

inline void
MPI::Comm::Recv(void *buf, int count, const MPI::Datatype & datatype,
				    int source, int tag) const
{
  (void)MPI_Recv(buf, count, datatype, source, 
		 tag, mpi_comm, MPI_STATUS_IGNORE);
}

inline void
MPI::Comm::Bsend(const void *buf, int count,
		 const MPI::Datatype & datatype, int dest, int tag) const
{
  (void)MPI_Bsend(const_cast<void *>(buf), count, datatype, 
		  dest, tag, mpi_comm);
}

inline void
MPI::Comm::Ssend(const void *buf, int count, 
		 const MPI::Datatype & datatype, int dest, int tag) const 
{
  (void)MPI_Ssend(const_cast<void *>(buf), count,  datatype, dest, 
		  tag, mpi_comm);
}

inline void
MPI::Comm::Rsend(const void *buf, int count,
		 const MPI::Datatype & datatype, int dest, int tag) const
{
  (void)MPI_Rsend(const_cast<void *>(buf), count, datatype, 
		  dest, tag, mpi_comm);
}

inline MPI::Request
MPI::Comm::Isend(const void *buf, int count,
		 const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request;
  (void)MPI_Isend(const_cast<void *>(buf), count, datatype, 
		  dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Request
MPI::Comm::Ibsend(const void *buf, int count,
		  const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request;    
  (void)MPI_Ibsend(const_cast<void *>(buf), count, datatype, 
		   dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Request
MPI::Comm::Issend(const void *buf, int count,
		  const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request;        
  (void)MPI_Issend(const_cast<void *>(buf), count, datatype,
		   dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Request
MPI::Comm::Irsend(const void *buf, int count,
		  const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request;
  (void)MPI_Irsend(const_cast<void *>(buf), count, datatype, 
		   dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Request
MPI::Comm::Irecv(void *buf, int count,
		 const MPI::Datatype & datatype, int source, int tag) const
{
  MPI_Request request;
  (void)MPI_Irecv(buf, count, datatype, source, 
		  tag, mpi_comm, &request);
  return request;
}


inline bool
MPI::Comm::Iprobe(int source, int tag, MPI::Status & status) const
{
  int t;
  (void)MPI_Iprobe(source, tag, mpi_comm, &t, &status.mpi_status);
  return OPAL_INT_TO_BOOL(t);
}
  
inline bool
MPI::Comm::Iprobe(int source, int tag) const
{
  int t;
  (void)MPI_Iprobe(source, tag, mpi_comm, &t, MPI_STATUS_IGNORE);
  return OPAL_INT_TO_BOOL(t);
}

inline void
MPI::Comm::Probe(int source, int tag, MPI::Status & status) const
{
  (void)MPI_Probe(source, tag, mpi_comm, &status.mpi_status);
}

inline void
MPI::Comm::Probe(int source, int tag) const
{
  (void)MPI_Probe(source, tag, mpi_comm, MPI_STATUS_IGNORE);
}

inline MPI::Prequest
MPI::Comm::Send_init(const void *buf, int count,
		     const MPI::Datatype & datatype, int dest, int tag) const
{ 
  MPI_Request request;
  (void)MPI_Send_init(const_cast<void *>(buf), count, datatype, 
		      dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Prequest
MPI::Comm::Bsend_init(const void *buf, int count,
		      const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request; 
  (void)MPI_Bsend_init(const_cast<void *>(buf), count, datatype, 
		       dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Prequest
MPI::Comm::Ssend_init(const void *buf, int count,
		      const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request; 
  (void)MPI_Ssend_init(const_cast<void *>(buf), count, datatype,
		       dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Prequest
MPI::Comm::Rsend_init(const void *buf, int count,
		      const MPI::Datatype & datatype, int dest, int tag) const
{
  MPI_Request request; 
  (void)MPI_Rsend_init(const_cast<void *>(buf), count,  datatype,
		       dest, tag, mpi_comm, &request);
  return request;
}

inline MPI::Prequest
MPI::Comm::Recv_init(void *buf, int count,
		     const MPI::Datatype & datatype, int source, int tag) const
{
  MPI_Request request; 
  (void)MPI_Recv_init(buf, count, datatype, source, 
		      tag, mpi_comm, &request);
  return request;
}

inline void
MPI::Comm::Sendrecv(const void *sendbuf, int sendcount,
		    const MPI::Datatype & sendtype, int dest, int sendtag, 
		    void *recvbuf, int recvcount, 
		    const MPI::Datatype & recvtype, int source,
		    int recvtag, MPI::Status & status) const
{
  (void)MPI_Sendrecv(const_cast<void *>(sendbuf), sendcount, 
		     sendtype,
		     dest, sendtag, recvbuf, recvcount, 
		     recvtype, 
		     source, recvtag, mpi_comm, &status.mpi_status);
}

inline void
MPI::Comm::Sendrecv(const void *sendbuf, int sendcount,
		    const MPI::Datatype & sendtype, int dest, int sendtag, 
		    void *recvbuf, int recvcount, 
		    const MPI::Datatype & recvtype, int source,
		    int recvtag) const
{
  (void)MPI_Sendrecv(const_cast<void *>(sendbuf), sendcount, 
		     sendtype,
		     dest, sendtag, recvbuf, recvcount, 
		     recvtype, 
		     source, recvtag, mpi_comm, MPI_STATUS_IGNORE);
}

inline void
MPI::Comm::Sendrecv_replace(void *buf, int count,
			    const MPI::Datatype & datatype, int dest, 
			    int sendtag, int source,
			    int recvtag, MPI::Status & status) const 
{
  (void)MPI_Sendrecv_replace(buf, count, datatype, dest,
			     sendtag, source, recvtag, mpi_comm,
			     &status.mpi_status);
}

inline void
MPI::Comm::Sendrecv_replace(void *buf, int count,
			    const MPI::Datatype & datatype, int dest, 
			    int sendtag, int source,
			    int recvtag) const 
{
  (void)MPI_Sendrecv_replace(buf, count, datatype, dest,
			     sendtag, source, recvtag, mpi_comm,
			     MPI_STATUS_IGNORE);
}

//
// Groups, Contexts, and Communicators
//

inline MPI::Group
MPI::Comm::Get_group() const 
{
  MPI_Group group;
  (void)MPI_Comm_group(mpi_comm, &group);
  return group;
}
  
inline int
MPI::Comm::Get_size() const 
{
  int size;
  (void)MPI_Comm_size (mpi_comm, &size);
  return size;
}
  
inline int
MPI::Comm::Get_rank() const 
{
  int rank;
  (void)MPI_Comm_rank (mpi_comm, &rank);
  return rank;
}
  
inline int
MPI::Comm::Compare(const MPI::Comm & comm1,
		   const MPI::Comm & comm2)
{
  int result;
  (void)MPI_Comm_compare(comm1, comm2, &result);
  return result;
}

inline void
MPI::Comm::Free(void) 
{
    (void)MPI_Comm_free(&mpi_comm);
}

inline bool
MPI::Comm::Is_inter() const
{
  int t;
  (void)MPI_Comm_test_inter(mpi_comm, &t);
  return OPAL_INT_TO_BOOL(t);
}


//
// Collective Communication
//

inline void
MPI::Comm::Barrier() const
{
    (void)MPI_Barrier(mpi_comm);
}

inline void
MPI::Comm::Bcast(void *buffer, int count, 
                 const MPI::Datatype& datatype, int root) const
{ 
    (void)MPI_Bcast(buffer, count, datatype, root, mpi_comm);
}

inline void
MPI::Comm::Gather(const void *sendbuf, int sendcount, 
                  const MPI::Datatype & sendtype, 
                  void *recvbuf, int recvcount, 
                  const MPI::Datatype & recvtype, int root) const
{
    (void)MPI_Gather(const_cast<void *>(sendbuf), sendcount, sendtype,
                     recvbuf, recvcount, recvtype, root, mpi_comm);
}

inline void
MPI::Comm::Gatherv(const void *sendbuf, int sendcount, 
                   const MPI::Datatype & sendtype, void *recvbuf, 
                   const int recvcounts[], const int displs[], 
                   const MPI::Datatype & recvtype, int root) const
{
    (void)MPI_Gatherv(const_cast<void *>(sendbuf), sendcount,  sendtype,
                      recvbuf, const_cast<int *>(recvcounts),
                      const_cast<int *>(displs), 
                      recvtype, root, mpi_comm);
}

inline void
MPI::Comm::Scatter(const void *sendbuf, int sendcount, 
                   const MPI::Datatype & sendtype, 
                   void *recvbuf, int recvcount, 
                   const MPI::Datatype & recvtype, int root) const
{ 
    (void)MPI_Scatter(const_cast<void *>(sendbuf), sendcount, sendtype,
                      recvbuf, recvcount, recvtype, root, mpi_comm);
}

inline void
MPI::Comm::Scatterv(const void *sendbuf, const int sendcounts[], 
                    const int displs[], const MPI::Datatype & sendtype,
                    void *recvbuf, int recvcount, 
                    const MPI::Datatype & recvtype, int root) const
{
    (void)MPI_Scatterv(const_cast<void *>(sendbuf),
                       const_cast<int *>(sendcounts), 
                       const_cast<int *>(displs), sendtype, 
                       recvbuf, recvcount, recvtype, 
                       root, mpi_comm);
}

inline void
MPI::Comm::Allgather(const void *sendbuf, int sendcount, 
                     const MPI::Datatype & sendtype, void *recvbuf, 
                     int recvcount, const MPI::Datatype & recvtype) const 
{
    (void)MPI_Allgather(const_cast<void *>(sendbuf), sendcount, 
                        sendtype, recvbuf, recvcount,
                        recvtype, mpi_comm);
}

inline void
MPI::Comm::Allgatherv(const void *sendbuf, int sendcount, 
                      const MPI::Datatype & sendtype, void *recvbuf, 
                      const int recvcounts[], const int displs[],
                      const MPI::Datatype & recvtype) const
{
    (void)MPI_Allgatherv(const_cast<void *>(sendbuf), sendcount, 
                         sendtype, recvbuf, 
                         const_cast<int *>(recvcounts),
                         const_cast<int *>(displs), 
                         recvtype, mpi_comm);
}

inline void
MPI::Comm::Alltoall(const void *sendbuf, int sendcount, 
                    const MPI::Datatype & sendtype, void *recvbuf, 
                    int recvcount, const MPI::Datatype & recvtype) const
{
    (void)MPI_Alltoall(const_cast<void *>(sendbuf), sendcount,
                       sendtype, recvbuf, recvcount,
                       recvtype, mpi_comm);
}

inline void
MPI::Comm::Alltoallv(const void *sendbuf, const int sendcounts[], 
                     const int sdispls[], const MPI::Datatype & sendtype, 
                     void *recvbuf, const int recvcounts[], 
                     const int rdispls[], 
                     const MPI::Datatype & recvtype) const 
{
    (void)MPI_Alltoallv(const_cast<void *>(sendbuf), 
                        const_cast<int *>(sendcounts), 
			const_cast<int *>(sdispls), sendtype, recvbuf, 
			const_cast<int *>(recvcounts), 
                        const_cast<int *>(rdispls), 
			recvtype,mpi_comm);
}

inline void
MPI::Comm::Alltoallw(const void *sendbuf, const int sendcounts[],
                     const int sdispls[], const MPI::Datatype sendtypes[],
                     void *recvbuf, const int recvcounts[],
                     const int rdispls[], 
                     const MPI::Datatype recvtypes[]) const
{
    const int comm_size = Get_size();
    MPI_Datatype *const data_type_tbl = new MPI_Datatype [2*comm_size];
    
    // This must be done because MPI::Datatype arrays cannot be
    // converted directly into MPI_Datatype arrays.  
    for (int i_rank=0; i_rank < comm_size; i_rank++) {
        data_type_tbl[i_rank] = sendtypes[i_rank];
        data_type_tbl[i_rank + comm_size] = recvtypes[i_rank];
    }
    
    (void)MPI_Alltoallw(const_cast<void *>(sendbuf), 
                        const_cast<int *>(sendcounts),
                        const_cast<int *>(sdispls),
                        data_type_tbl, recvbuf,
                        const_cast<int *>(recvcounts), 
                        const_cast<int *>(rdispls),
                        &data_type_tbl[comm_size], mpi_comm);
    
    delete[] data_type_tbl;
}

inline void
MPI::Comm::Reduce(const void *sendbuf, void *recvbuf, int count, 
                  const MPI::Datatype & datatype, const MPI::Op& op, 
                  int root) const
{
    (void)MPI_Reduce(const_cast<void *>(sendbuf), recvbuf, count, datatype, op, root, mpi_comm);
}

inline void
MPI::Comm::Allreduce(const void *sendbuf, void *recvbuf, int count,
                     const MPI::Datatype & datatype, const MPI::Op& op) const
{
    (void)MPI_Allreduce (const_cast<void *>(sendbuf), recvbuf, count, datatype,  op, mpi_comm);
}

inline void
MPI::Comm::Reduce_scatter(const void *sendbuf, void *recvbuf, 
                          int recvcounts[], 
                          const MPI::Datatype & datatype, 
                          const MPI::Op& op) const
{
    (void)MPI_Reduce_scatter(const_cast<void *>(sendbuf), recvbuf, recvcounts,
                             datatype, op, mpi_comm);
}

//
// Process Creation and Managemnt
//

inline void
MPI::Comm::Disconnect()
{
  (void) MPI_Comm_disconnect(&mpi_comm);
}


inline MPI::Intercomm
MPI::Comm::Get_parent()
{
  MPI_Comm parent;
  MPI_Comm_get_parent(&parent);
  return parent;
}


inline MPI::Intercomm
MPI::Comm::Join(const int fd) 
{
  MPI_Comm newcomm;
  (void) MPI_Comm_join((int) fd, &newcomm);
  return newcomm;
}

//
// External Interfaces
//

inline void
MPI::Comm::Get_name(char* comm_name, int& resultlen) const
{
  (void) MPI_Comm_get_name(mpi_comm, comm_name, &resultlen);
}

inline void
MPI::Comm::Set_name(const char* comm_name) 
{
  (void) MPI_Comm_set_name(mpi_comm, const_cast<char *>(comm_name));
}
  
//
//Process Topologies
//

inline int
MPI::Comm::Get_topology() const 
{
  int status;
  (void)MPI_Topo_test(mpi_comm, &status);
  return status;
}
  
//
// Environmental Inquiry
//

inline void
MPI::Comm::Abort(int errorcode) 
{
  (void)MPI_Abort(mpi_comm, errorcode);
}

//
//  These C++ bindings are for MPI-2.
//  The MPI-1.2 functions called below are all
//  going to be deprecated and replaced in MPI-2.
//

inline MPI::Errhandler
MPI::Comm::Get_errhandler() const
{
  return *my_errhandler;
}

inline MPI::Errhandler
MPI::Comm::Create_errhandler(MPI::Comm::_MPI2CPP_ERRHANDLERFN_* function)
{
  MPI_Errhandler errhandler;
  // $%%@#%# AIX/POE 2.3.0.0 makes us put in this cast here
  (void)MPI_Comm_create_errhandler((MPI_Handler_function*) ompi_mpi_cxx_comm_errhandler_intercept, 
			      &errhandler);
  MPI::Errhandler temp(errhandler);
  temp.comm_handler_fn = (void(*)(MPI::Comm&, int*, ...))function;
  return temp;
}

// 1) original Create_keyval that takes the first 2 arguments as C++
//    functions
inline int
MPI::Comm::Create_keyval(MPI::Comm::Copy_attr_function* comm_copy_attr_fn,
                         MPI::Comm::Delete_attr_function* comm_delete_attr_fn, 
                         void* extra_state)
{
    // Back-end function does the heavy lifting
    return do_create_keyval(NULL, NULL, 
                            comm_copy_attr_fn, comm_delete_attr_fn,
                            extra_state);
}

// 2) overload Create_keyval to take the first 2 arguments as C
//    functions
inline int
MPI::Comm::Create_keyval(MPI_Comm_copy_attr_function* comm_copy_attr_fn,
                         MPI_Comm_delete_attr_function* comm_delete_attr_fn, 
                         void* extra_state)
{
    // Back-end function does the heavy lifting
    return do_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn,
                            NULL, NULL,
                            extra_state);
}

// 3) overload Create_keyval to take the first 2 arguments as C++ & C
//    functions
inline int
MPI::Comm::Create_keyval(MPI::Comm::Copy_attr_function* comm_copy_attr_fn,
                         MPI_Comm_delete_attr_function* comm_delete_attr_fn,
                         void* extra_state)
{
    // Back-end function does the heavy lifting
    return do_create_keyval(NULL, comm_delete_attr_fn,
                            comm_copy_attr_fn, NULL,
                            extra_state);
}

// 4) overload Create_keyval to take the first 2 arguments as C & C++
//    functions
inline int
MPI::Comm::Create_keyval(MPI_Comm_copy_attr_function* comm_copy_attr_fn,
                         MPI::Comm::Delete_attr_function* comm_delete_attr_fn,
                         void* extra_state)
{
    // Back-end function does the heavy lifting
    return do_create_keyval(comm_copy_attr_fn, NULL,
                            NULL, comm_delete_attr_fn,
                            extra_state);
}

inline void
MPI::Comm::Free_keyval(int& comm_keyval)
{
    (void) MPI_Keyval_free(&comm_keyval);
}

inline void
MPI::Comm::Set_attr(int comm_keyval, const void* attribute_val) const
{
    (void)MPI_Attr_put(mpi_comm, comm_keyval, (void*) attribute_val);
}

inline bool
MPI::Comm::Get_attr(int comm_keyval, void* attribute_val) const
{
  int flag;
  (void)MPI_Attr_get(mpi_comm, comm_keyval, attribute_val, &flag);
  return OPAL_INT_TO_BOOL(flag);
}

inline void
MPI::Comm::Delete_attr(int comm_keyval)
{
  (void)MPI_Attr_delete(mpi_comm, comm_keyval);
}

inline int
MPI::Comm::NULL_COPY_FN(const MPI::Comm& oldcomm, int comm_keyval,
			       void* extra_state, void* attribute_val_in,
			       void* attribute_val_out, bool& flag)
{
#if SIZEOF_BOOL != SIZEOF_INT
  int f = (int)flag;
  int ret;
  if (MPI_NULL_COPY_FN != 0) {

    // Portland pgCC 5.0-2 has a bug that we have to workaround here.
    // MPI_NULL_COPY_FN is actually a #define for ((MPI_Copy_function
    // *) 0).  If we try to invoke it, such as:
    //   ret = MPI_NULL_COPY_FN(...);
    // the preprocessor will resolve this to:
    //   ret = ((MPI_Copy_function *) 0)(...);
    // which should be fine.  But unfortunately, pgCC 5.0-2 makes this
    // into a real symbol that will refuse to link.  The workaround is
    // to assign this into a temp variable and then invoke through the
    // function pointer.  This shouldn't be necessary.  :-(

    MPI_Copy_function *stupid_compiler = MPI_NULL_COPY_FN;
    ret = stupid_compiler(oldcomm, comm_keyval, extra_state, attribute_val_in,
                          attribute_val_out, &f);
    flag = OPAL_INT_TO_BOOL(f);
  } else {
    ret = MPI_SUCCESS;
    flag = true;
  }
  return ret;
#else
  if (MPI_NULL_COPY_FN != 0) {

    // See note above.

    MPI_Copy_function *stupid_compiler = MPI_NULL_COPY_FN;
    return stupid_compiler(oldcomm, comm_keyval, extra_state, 
                           attribute_val_in, attribute_val_out, (int*)&flag);
  } else
    return MPI_SUCCESS;
#endif
}

inline int
MPI::Comm::DUP_FN(const MPI::Comm& oldcomm, int comm_keyval,
			 void* extra_state, void* attribute_val_in,
			 void* attribute_val_out, bool& flag)
{
#if SIZEOF_BOOL != SIZEOF_INT
  int f = (int)flag;
  int ret;
  ret = MPI_DUP_FN(oldcomm, comm_keyval, extra_state, attribute_val_in,
		   attribute_val_out, &f);
  flag = OPAL_INT_TO_BOOL(f);
  return ret;
#else
  return MPI_DUP_FN(oldcomm, comm_keyval, extra_state, attribute_val_in,
		    attribute_val_out, (int*)&flag);
#endif
}

inline int
MPI::Comm::NULL_DELETE_FN(MPI::Comm& comm, int comm_keyval, void* attribute_val,
				 void* extra_state)
{
  if (MPI_NULL_DELETE_FN != 0) {

    // See note in MPI_NULL_COPY_FN.

    MPI_Delete_function *stupid_compiler = MPI_NULL_DELETE_FN;
    return stupid_compiler(comm, comm_keyval, attribute_val, extra_state);
  } else
    return MPI_SUCCESS;
}

