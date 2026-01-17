/*
 * "$Id: help-index.h 8881 2009-11-17 21:38:38Z mike $"
 *
 *   Online help index definitions for CUPS.
 *
 *   Copyright 2007-2011 by Apple Inc.
 *   Copyright 1997-2007 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 */

#ifndef _CUPS_HELP_INDEX_H_
#  define _CUPS_HELP_INDEX_H_

/*
 * Include necessary headers...
 */

#  include <cups/array.h>


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Data structures...
 */

typedef struct help_word_s		/**** Help word structure... ****/
{
  int		count;			/* Number of occurrences */
  char		*text;			/* Word text */
} help_word_t;

typedef struct help_node_s		/**** Help node structure... ****/
{
  char		*filename;		/* Filename, relative to help dir */
  char		*section;		/* Section name (NULL if none) */
  char		*anchor;		/* Anchor name (NULL if none) */
  char		*text;			/* Text in anchor */
  cups_array_t	*words;			/* Words after this node */
  time_t	mtime;			/* Last modification time */
  off_t		offset;			/* Offset in file */
  size_t	length;			/* Length in bytes */
  int		score;			/* Search score */
} help_node_t;

typedef struct help_index_s		/**** Help index structure ****/
{
  int		search;			/* 1 = search index, 0 = normal */
  cups_array_t	*nodes;			/* Nodes sorted by filename */
  cups_array_t	*sorted;		/* Nodes sorted by score + text */
} help_index_t;


/*
 * Functions...
 */

extern void		helpDeleteIndex(help_index_t *hi);
extern help_node_t	*helpFindNode(help_index_t *hi, const char *filename,
			              const char *anchor);
extern help_index_t	*helpLoadIndex(const char *hifile, const char *directory);
extern int		helpSaveIndex(help_index_t *hi, const char *hifile);
extern help_index_t	*helpSearchIndex(help_index_t *hi, const char *query,
			                 const char *section,
					 const char *filename);


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_HELP_INDEX_H_ */

/*
 * End of "$Id: help-index.h 8881 2009-11-17 21:38:38Z mike $".
 */
