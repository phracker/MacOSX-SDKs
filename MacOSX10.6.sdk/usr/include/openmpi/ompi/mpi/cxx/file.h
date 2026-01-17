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
// Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
// $COPYRIGHT$
// 
// Additional copyrights may follow
// 
// $HEADER$
//

class File {
#if 0 /* OMPI_ENABLE_MPI_PROFILING */
  //  friend class P;

#endif
  friend class MPI::Comm; //so I can access pmpi_file data member in comm.cc
  friend class MPI::Request; //and also from request.cc

public:
#if 0 /* OMPI_ENABLE_MPI_PROFILING */

  // construction / destruction
  File() { }
  virtual ~File() { }


  // copy / assignment
  File(const File& data) : pmpi_file(data.pmpi_file) { }

  File(MPI_File i) : pmpi_file(i) { }

  File& operator=(const File& data) {
    pmpi_file = data.pmpi_file; return *this; }

  // comparison, don't need for file

  // inter-language operability
  File& operator= (const MPI_File &i) {
    pmpi_file = i; return *this; }
  operator MPI_File () const { return pmpi_file; }
  //  operator MPI_File* () const { return pmpi_file; }
  operator const PMPI::File&() const { return pmpi_file; }

#else

  File() { }
  // copy
  File(const File& data) : mpi_file(data.mpi_file) { }

  File(MPI_File i) : mpi_file(i) { }
	
  virtual ~File() { }

  File& operator=(const File& data) {
    mpi_file = data.mpi_file; return *this; }

  // comparison, don't need for file

  // inter-language operability
  File& operator= (const MPI_File &i) {
    mpi_file = i; return *this; }
  operator MPI_File () const { return mpi_file; }
  //  operator MPI_File* () const { return (MPI_File*)&mpi_file; }

#endif

  // from the I/o chapter of MPI - 2 

  void Close();

  static void Delete(const char* filename, const MPI::Info& info);

  int Get_amode() const;

  bool Get_atomicity() const;

  MPI::Offset Get_byte_offset(const MPI::Offset disp) const;

  MPI::Group Get_group() const;

  MPI::Info Get_info() const;

  MPI::Offset Get_position() const;

  MPI::Offset Get_position_shared() const;

  MPI::Offset Get_size() const;

  MPI::Aint Get_type_extent(const MPI::Datatype& datatype) const;

  void Get_view(MPI::Offset& disp, MPI::Datatype& etype, 
		MPI::Datatype& filetype, char* datarep) const;

  MPI::Request Iread(void* buf, int count, 
		     const MPI::Datatype& datatype);
  
  MPI::Request Iread_at(MPI::Offset offset, void* buf, int count, 
			const MPI::Datatype& datatype);
  
  MPI::Request Iread_shared(void* buf, int count,
			    const MPI::Datatype& datatype);

  MPI::Request Iwrite(const void* buf, int count,
		       const MPI::Datatype& datatype);

  MPI::Request Iwrite_at(MPI::Offset offset, const void* buf, 
			 int count,  const MPI::Datatype& datatype);

  MPI::Request Iwrite_shared(const void* buf, int count,
			      const MPI::Datatype& datatype);

  static MPI::File Open(const MPI::Intracomm& comm,
			const char* filename, int amode,
			const MPI::Info& info);

  void Preallocate(MPI::Offset size);

  void Read(void* buf, int count, const MPI::Datatype& datatype);

  void Read(void* buf, int count, const MPI::Datatype& datatype,
	    MPI::Status& status);

  void Read_all(void* buf, int count, const MPI::Datatype& datatype);

  void Read_all(void* buf, int count, const MPI::Datatype& datatype,
		MPI::Status& status);

  void Read_all_begin(void* buf, int count,
		      const MPI::Datatype& datatype);

  void Read_all_end(void* buf);

  void Read_all_end(void* buf, MPI::Status& status);

  void Read_at(MPI::Offset offset, 
	       void* buf, int count,  const MPI::Datatype& datatype);

  void Read_at(MPI::Offset offset, void* buf, int count,
	       const MPI::Datatype& datatype, MPI::Status& status);

  void Read_at_all(MPI::Offset offset, void* buf, int count, 
		   const MPI::Datatype& datatype);
  
  void Read_at_all(MPI::Offset offset, void* buf, int count,
		   const MPI::Datatype& datatype, MPI::Status& status);

  void Read_at_all_begin(MPI::Offset offset, void* buf, int count,
			 const MPI::Datatype& datatype);
  
  void Read_at_all_end(void* buf);

  void Read_at_all_end(void* buf, MPI::Status& status);

  void Read_ordered(void* buf, int count,
		    const MPI::Datatype& datatype);

  void Read_ordered(void* buf, int count,
		    const MPI::Datatype& datatype,
		    MPI::Status& status);

  void Read_ordered_begin(void* buf, int count,
			  const MPI::Datatype& datatype);

  void Read_ordered_end(void* buf);

  void Read_ordered_end(void* buf, MPI::Status& status);

  void Read_shared(void* buf, int count,
		   const MPI::Datatype& datatype);

  void Read_shared(void* buf, int count,
		   const MPI::Datatype& datatype, MPI::Status& status);

  void Seek(MPI::Offset offset, int whence);

  void Seek_shared(MPI::Offset offset, int whence);

  void Set_atomicity(bool flag);

  void Set_info(const MPI::Info& info);

  void Set_size(MPI::Offset size);

  void Set_view(MPI::Offset disp,  const MPI::Datatype& etype,
		const MPI::Datatype& filetype, const char* datarep,
		const MPI::Info& info);

  void Sync();

  void Write(const void* buf, int count,
	      const MPI::Datatype& datatype);

  void Write(const void* buf, int count,
	      const MPI::Datatype& datatype, MPI::Status& status);

  void Write_all(const void* buf, int count,
		  const MPI::Datatype& datatype);

  void Write_all(const void* buf, int count,
		  const MPI::Datatype& datatype, MPI::Status& status);

  void Write_all_begin(const void* buf, int count,
			const MPI::Datatype& datatype);

  void Write_all_end(const void* buf);

  void Write_all_end(const void* buf, MPI::Status& status);

  void Write_at(MPI::Offset offset,  const void* buf, int count,
		const MPI::Datatype& datatype);

  void Write_at(MPI::Offset offset,  const void* buf, int count,
		const MPI::Datatype& datatype, MPI::Status& status);

  void Write_at_all(MPI::Offset offset,  const void* buf, int count,
		    const MPI::Datatype& datatype);

  void Write_at_all(MPI::Offset offset,  const void* buf, int count,
		    const MPI::Datatype& datatype,
  			     MPI::Status& status);

  void Write_at_all_begin(MPI::Offset offset, const void* buf,
			  int count,  const MPI::Datatype& datatype);

  void Write_at_all_end(const void* buf);

  void Write_at_all_end(const void* buf, MPI::Status& status);

  void Write_ordered(const void* buf, int count,
		      const MPI::Datatype& datatype);

  void Write_ordered(const void* buf, int count,
		      const MPI::Datatype& datatype, MPI::Status& status);

  void Write_ordered_begin(const void* buf, int count, 
			    const MPI::Datatype& datatype);

  void Write_ordered_end(const void* buf);

  void Write_ordered_end(const void* buf, MPI::Status& status);

  void Write_shared(const void* buf, int count,
		     const MPI::Datatype& datatype);

  void Write_shared(const void* buf, int count,
		     const MPI::Datatype& datatype, MPI::Status& status);
  
  void Call_errhandler(int errorcode) const;

  typedef void Errhandler_fn(MPI::File &, int *, ... );

  static MPI::Errhandler Create_errhandler(Errhandler_fn* function); 

  MPI::Errhandler Get_errhandler() const;
  
  void Set_errhandler(const MPI::Errhandler& errhandler);
    
protected:
#if 0 /* OMPI_ENABLE_MPI_PROFILING */
      PMPI::File pmpi_file;

#else
  MPI_File mpi_file;

#endif

public:
  Errhandler* my_errhandler;

  typedef ::std::map<MPI_File, File*> mpi_file_map_t;
  static mpi_file_map_t mpi_file_map;
};

