#ifndef __HOOK_OP_CHECK_H__
#define __HOOK_OP_CHECK_H__

#include "perl.h"

START_EXTERN_C

typedef UV hook_op_check_id;

typedef OP *(*hook_op_check_cb) (pTHX_ OP *, void *);
hook_op_check_id hook_op_check (opcode type, hook_op_check_cb cb, void *user_data);
void *hook_op_check_remove (opcode type, hook_op_check_id id);

END_EXTERN_C

#endif
