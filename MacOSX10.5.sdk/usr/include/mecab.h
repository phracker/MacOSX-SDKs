/*
  MeCab -- Yet Another Part-of-Speech and Morphological Analyzer

  $Id: mecab.h,v 1.2 2007/04/08 11:08:40 guo1 Exp $;

  Copyright(C) 2001-2006 Taku Kudo <taku@chasen.org>
  Copyright(C) 2004-2006 Nippon Telegraph and Telephone Corporation
*/
#ifndef MECAB_MECAB_H
#define MECAB_MECAB_H

/* C/C++ common data structures  */
struct mecab_dictionary_info_t {
  const char                     *filename;
  const char                     *charset;
  unsigned int                    size;
  int                             type;
  unsigned int                    lsize;
  unsigned int                    rsize;
  unsigned short                  version;
  struct mecab_dictionary_info_t *next;
};

struct mecab_path_t {
  struct mecab_node_t* rnode;
  struct mecab_path_t* rnext;
  struct mecab_node_t* lnode;
  struct mecab_path_t* lnext;
  int                  cost;
  float                prob;
};

struct mecab_learner_path_t {
  struct mecab_learner_node_t*  rnode;
  struct mecab_learner_path_t*  rnext;
  struct mecab_learner_node_t*  lnode;
  struct mecab_learner_path_t*  lnext;
  double                        cost;
  const int                     *fvector;
};

struct mecab_node_t {
  struct mecab_node_t  *prev;
  struct mecab_node_t  *next;
  struct mecab_node_t  *enext;
  struct mecab_node_t  *bnext;
  struct mecab_path_t  *rpath;
  struct mecab_path_t  *lpath;
  struct mecab_node_t **begin_node_list;
  struct mecab_node_t **end_node_list;
  const char           *surface;
  const char           *feature;
  unsigned int          id;
  unsigned short        length; /* length of morph */
  unsigned short        rlength; /* real length of morph(include white space before the morph) */
  unsigned short        rcAttr;
  unsigned short        lcAttr;
  unsigned short        posid;
  unsigned char         char_type;
  unsigned char         stat;
  unsigned char         isbest;
  unsigned int          sentence_length; /* it is avaialbe only when BOS node */
  float                 alpha;
  float                 beta;
  float                 prob;
  short                 wcost;
  long                  cost;
};

/* almost the same as mecab_node_t.
   used only for cost estimation */
struct mecab_learner_node_t {
  struct mecab_learner_node_t *prev;
  struct mecab_learner_node_t *next;
  struct mecab_learner_node_t *enext;
  struct mecab_learner_node_t *bnext;
  struct mecab_learner_path_t *rpath;
  struct mecab_learner_path_t *lpath;
  struct mecab_learner_node_t *anext;
  const char                  *surface;
  const char                  *feature;
  unsigned int                 id;
  unsigned short               length;
  unsigned short               rlength;
  unsigned short               rcAttr;
  unsigned short               lcAttr;
  unsigned short               posid;
  unsigned char                char_type;
  unsigned char                stat;
  unsigned char                isbest;
  double                       alpha;
  double                       beta;
  short                        wcost2;
  double                       wcost;
  double                       cost;
  const int                    *fvector;
};

#define MECAB_NOR_NODE  0
#define MECAB_UNK_NODE  1
#define MECAB_BOS_NODE  2
#define MECAB_EOS_NODE  3

#define MECAB_USR_DIC   1
#define MECAB_SYS_DIC   0
#define MECAB_UNK_DIC   2

/* C interface  */
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <windows.h>
#  ifdef DLL_EXPORT
#    define MECAB_DLL_EXTERN  __declspec(dllexport)
#  else
#    define MECAB_DLL_EXTERN  __declspec(dllimport)
#  endif
#endif

#ifndef MECAB_DLL_EXTERN
#  define MECAB_DLL_EXTERN extern
#endif

  typedef struct mecab_t                 mecab_t;
  typedef struct mecab_dictionary_info_t mecab_dictionary_info_t;
  typedef struct mecab_node_t            mecab_node_t;
  typedef struct mecab_learner_node_t    mecab_learner_node_t;
  typedef struct mecab_path_t            mecab_path_t;
  typedef struct mecab_learner_path_t    mecab_learner_path_t;

#ifndef SWIG
  /* C interface */
  MECAB_DLL_EXTERN int           mecab_do (int argc, char **argv);
  MECAB_DLL_EXTERN mecab_t*      mecab_new(int argc, char **argv);
  MECAB_DLL_EXTERN mecab_t*      mecab_new2(const char *arg);
  MECAB_DLL_EXTERN const char*   mecab_version();
  MECAB_DLL_EXTERN const char*   mecab_strerror(mecab_t *mecab);
  MECAB_DLL_EXTERN void          mecab_destroy(mecab_t *mecab);
  MECAB_DLL_EXTERN const char*   mecab_sparse_tostr(mecab_t *mecab, const char *str);
  MECAB_DLL_EXTERN const char*   mecab_sparse_tostr2(mecab_t *mecab, const char *str, size_t len);
  MECAB_DLL_EXTERN char*         mecab_sparse_tostr3(mecab_t *mecab, const char *str, size_t len,
                                                     char *ostr, size_t olen);
  MECAB_DLL_EXTERN const mecab_node_t* mecab_sparse_tonode(mecab_t *mecab, const char*);
  MECAB_DLL_EXTERN const mecab_node_t* mecab_sparse_tonode2(mecab_t *mecab, const char*, size_t);
  MECAB_DLL_EXTERN const char*   mecab_nbest_sparse_tostr(mecab_t *mecab, size_t N, const char *str);
  MECAB_DLL_EXTERN const char*   mecab_nbest_sparse_tostr2(mecab_t *mecab, size_t N,
                                                           const char *str, size_t len);
  MECAB_DLL_EXTERN char*         mecab_nbest_sparse_tostr3(mecab_t *mecab, size_t N,
                                                           const char *str, size_t len,
                                                           char *ostr, size_t olen);
  MECAB_DLL_EXTERN int           mecab_nbest_init(mecab_t *mecab, const char *str);
  MECAB_DLL_EXTERN int           mecab_nbest_init2(mecab_t *mecab, const char *str, size_t len);
  MECAB_DLL_EXTERN const char*   mecab_nbest_next_tostr(mecab_t *mecab);
  MECAB_DLL_EXTERN char*         mecab_nbest_next_tostr2(mecab_t *mecab, char *ostr, size_t olen);
  MECAB_DLL_EXTERN const mecab_node_t* mecab_nbest_next_tonode(mecab_t *mecab);
  MECAB_DLL_EXTERN const char*   mecab_format_node(mecab_t *mecab, const mecab_node_t *node);
  MECAB_DLL_EXTERN const mecab_dictionary_info_t* mecab_dictionary_info(mecab_t *mecab);
  MECAB_DLL_EXTERN int           mecab_dict_index(int argc, char **argv);
  MECAB_DLL_EXTERN int           mecab_dict_gen(int argc, char **argv);
  MECAB_DLL_EXTERN int           mecab_cost_train(int argc, char **argv);
  MECAB_DLL_EXTERN int           mecab_system_eval(int argc, char **argv);
  MECAB_DLL_EXTERN int           mecab_test_gen(int argc, char **argv);
#endif

#ifdef __cplusplus
}
#endif

/* C++ interface */
#ifdef __cplusplus

namespace MeCab {
  typedef struct mecab_dictionary_info_t DictionaryInfo;
  typedef struct mecab_path_t            Path;
  typedef struct mecab_node_t            Node;
  typedef struct mecab_learner_path_t    LearnerPath;
  typedef struct mecab_learner_node_t    LearnerNode;

  class Tagger {
  public:

#ifndef SWIG
    virtual const char* parse(const char *str, size_t len, char *ostr, size_t olen) = 0;
    virtual const char* parse(const char *str, size_t len)                          = 0;
    virtual const Node* parseToNode(const char *str, size_t len)                    = 0;
    virtual const char* parseNBest(size_t N, const char *str, size_t len)           = 0;
    virtual bool  parseNBestInit(const char *str, size_t len)                       = 0;
#endif

    virtual const char* parse(const char *str)                = 0;
    virtual const Node* parseToNode(const char *str)          = 0;
    virtual const char* parseNBest(size_t N, const char *str) = 0;
    virtual bool  parseNBestInit(const char *str)             = 0;
    virtual const Node* nextNode()                            = 0;
    virtual const char* next()                                = 0;
    virtual const char* formatNode(const Node *node)          = 0;

#ifndef SWIG
    virtual const char* next(char *ostr , size_t olen)                        = 0;
    virtual const char* parseNBest(size_t N, const char *str,
                                   size_t len, char *ostr, size_t olen)       = 0;
    virtual const char* formatNode(const Node *node, char *ostr, size_t olen) = 0;
#endif

    virtual const DictionaryInfo* dictionary_info() const = 0;

    virtual const char* what() = 0;

    virtual ~Tagger() {}

#ifndef SIWG
    static Tagger* create(int argc, char **argv);
    static Tagger* create(const char *arg);
#endif

    static const char *version();
  };

  /* factory method */
  MECAB_DLL_EXTERN Tagger *createTagger(int argc, char **argv);
  MECAB_DLL_EXTERN Tagger *createTagger(const char *arg);
  MECAB_DLL_EXTERN const char* getTaggerError();
}

#endif
#endif
