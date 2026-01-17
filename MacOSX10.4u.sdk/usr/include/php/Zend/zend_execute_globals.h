/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2003 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        | 
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/


#ifndef ZEND_EXECUTE_GLOBALS_H
#define ZEND_EXECUTE_GLOBALS_H

#include "zend_compile.h"
#include "zend_hash.h"
#include "zend_variables.h"
#include "zend_operators.h"

typedef union _temp_variable {
	zval tmp_var;
	struct {
		zval **ptr_ptr;
		zval *ptr;
		zend_bool fcall_returned_reference;
	} var;
	struct {
		zval tmp_var; /* a dummy */

		union {
			struct {
				zval *str;
				int offset;
			} str_offset;
			zend_property_reference overloaded_element;
		} data;
			
		unsigned char type;
	} EA;
} temp_variable;

typedef struct _object_info {
	zval *ptr;
} object_info;

typedef struct _zend_execute_data {
	zend_op *opline;
	zend_function_state function_state;
	zend_function *fbc; /* Function Being Called */
	zend_class_entry *ce; 
	object_info object;
	temp_variable *Ts;
	zend_bool original_in_execution;
	zend_op_array *op_array;
	struct  _zend_execute_data *prev_execute_data;
} zend_execute_data;

#define EX(element) execute_data.element

#endif
