/* dbivport.h

	Provides macros that enable greater portability between DBI versions.

	This file should be *copied* and included in driver distributions
	and #included into the source, after #include DBIXS.h

	New driver releases should include an updated copy of dbivport.h
	from the most recent DBI release.
*/

#ifndef DBI_VPORT_H
#define DBI_VPORT_H

#ifndef DBIh_SET_ERR_CHAR
/* Emulate DBIh_SET_ERR_CHAR
	Only uses the err_i, errstr and state parameters.
*/
#define DBIh_SET_ERR_CHAR(h, imp_xxh, err_c, err_i, errstr, state, method) \
        sv_setiv(DBIc_ERR(imp_xxh), err_i); \
        (state) ? (void)sv_setpv(DBIc_STATE(imp_xxh), state) : (void)SvOK_off(DBIc_STATE(imp_xxh)); \
        sv_setpv(DBIc_ERRSTR(imp_xxh), errstr)
#endif

#ifndef DBIcf_Executed
#define DBIcf_Executed    0x080000
#endif

#ifndef DBIc_TRACE_LEVEL_MASK
#define DBIc_TRACE_LEVEL_MASK   0x0000000F
#define DBIc_TRACE_FLAGS_MASK   0xFFFFFF00
#define DBIc_TRACE_SETTINGS(imp) (DBIc_DBISTATE(imp)->debug)
#define DBIc_TRACE_LEVEL(imp)   (DBIc_TRACE_SETTINGS(imp) & DBIc_TRACE_LEVEL_MASK)
#define DBIc_TRACE_FLAGS(imp)   (DBIc_TRACE_SETTINGS(imp) & DBIc_TRACE_FLAGS_MASK)
/* DBIc_TRACE_MATCHES - true if s1 'matches' s2  (c.f. trace_msg())
   DBIc_TRACE_MATCHES(foo, DBIc_TRACE_SETTINGS(imp))
*/
#define DBIc_TRACE_MATCHES(s1, s2)      \
        (  ((s1 & DBIc_TRACE_LEVEL_MASK) >= (s2 & DBIc_TRACE_LEVEL_MASK)) \
        || ((s1 & DBIc_TRACE_FLAGS_MASK)  & (s2 & DBIc_TRACE_FLAGS_MASK)) )
/* DBIc_TRACE - true if flags match & DBI level>=flaglevel, or if DBI level>level
   DBIc_TRACE(imp,         0, 0, 4) = if level >= 4
   DBIc_TRACE(imp, DBDtf_FOO, 2, 4) = if tracing DBDtf_FOO & level>=2 or level>=4
   DBIc_TRACE(imp, DBDtf_FOO, 2, 0) = as above but never trace just due to level
*/
#define DBIc_TRACE(imp, flags, flaglevel, level)        \
        (  (flags && (DBIc_TRACE_FLAGS(imp) & flags) && (DBIc_TRACE_LEVEL(imp) >= flaglevel)) \
        || (level && DBIc_TRACE_LEVEL(imp) >= level) )
#endif


#endif /* !DBI_VPORT_H */
