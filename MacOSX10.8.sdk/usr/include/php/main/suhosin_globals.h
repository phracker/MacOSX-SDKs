/*
   +----------------------------------------------------------------------+
   | Suhosin-Patch for PHP                                                |
   +----------------------------------------------------------------------+
   | Copyright (c) 2004-2009 Stefan Esser                                 |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Stefan Esser <stefan.esser@sektioneins.de>                   |
   +----------------------------------------------------------------------+
 */

#ifndef SUHOSIN_GLOBALS_H
#define SUHOSIN_GLOBALS_H

typedef struct _suhosin_patch_globals suhosin_patch_globals_struct;

#ifdef ZTS
# define SPG(v) TSRMG(suhosin_patch_globals_id, suhosin_patch_globals_struct *, v)
extern int suhosin_patch_globals_id;
#else
# define SPG(v) (suhosin_patch_globals.v)
extern struct _suhosin_patch_globals suhosin_patch_globals;
#endif


struct _suhosin_patch_globals {
	/* logging */
	int log_syslog;
	int log_syslog_facility;
	int log_syslog_priority;
	int log_sapi;
	int log_script;
	int log_phpscript;
	char *log_scriptname;
	char *log_phpscriptname;
	zend_bool log_phpscript_is_safe;
	zend_bool log_use_x_forwarded_for;
	
	/* memory manager canary protection */
	unsigned int canary_1;
	unsigned int canary_2;
	unsigned int canary_3;
	unsigned int dummy;
};


#endif /* SUHOSIN_GLOBALS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
