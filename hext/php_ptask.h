/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1.2.1.2.1 2008/02/07 19:39:50 iliaa Exp $ */

#ifndef PHP_PTASK_H
#define PHP_PTASK_H 1

#ifdef ZTS
  #include "TSRM.h"
#endif
#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
/*
#include "TSRM/TSRM.h"
#include "php_output.h"
#include "php_main.h"
#include "SAPI.h"
#include "zend_API.h"
#include "zend_variables.h"
#include "php_globals.h"
#include "ext/standard/head.h"
#include "php_variables.h"
#include "zend_interfaces.h"
*/
#ifdef ZTS
#define PTASK_G(v) TSRMG(ptask_globals_id, zend_ptask_globals *, v)
#else
#define PTASK_G(v) (ptask_globals.v)
#endif

#define PHP_PTASK_WORLD_VERSION "1.0"
#define PHP_PTASK_WORLD_EXTNAME "ptask"


PHP_MINIT_FUNCTION(ptask);
PHP_MSHUTDOWN_FUNCTION(ptask);
PHP_RINIT_FUNCTION(ptask);
PHP_RSHUTDOWN_FUNCTION(ptask);
PHP_MINFO_FUNCTION(ptask);

PHP_FUNCTION(ptask_create);
PHP_FUNCTION(ptask_run);
PHP_FUNCTION(ptask_yield);
PHP_FUNCTION(ptask_exit);
PHP_FUNCTION(ptask_net_listen);
PHP_FUNCTION(ptask_net_accept);
PHP_FUNCTION(ptask_net_recv);
PHP_FUNCTION(ptask_net_send);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(ptask)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(ptask)
*/

/* In every utility function you add that needs to use variables 
   in php_ptask_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PTASK_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

extern zend_module_entry ptask_module_entry;
#define phpext_ptask_ptr &ptask_module_entry
#endif	/* PHP_PTASK_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
