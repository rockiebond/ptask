/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/ext/extension.h"
#include <task.h>

namespace HPHP {

struct ptask_ctx {
    char *func;
    const Array& arg;
};

void ptask_thread_fn(void *arg)
{
    struct ptask_ctx *ctx = arg;
    zval fname, retval;
    zval *params[1];

    ZVAL_STRING(&fname, ctx->func, 0); /* create new function name zval */

    params[0] = ctx->arg;

    call_user_function(EG(function_table), NULL, &fname,
        &retval, 1, params TSRMLS_CC);

    /* free all memory */
    Z_DELREF_PP(&(ctx->arg));
    if (Z_REFCOUNT_PP(&(ctx->arg)) == 0) {
        zval_dtor(ctx->arg);
    }
    efree(ctx->func);
    efree(ctx);
}

int64_t HHVM_FUNCTION(example_sum, int64_t a, int64_t b) {
  return a + b;
}

bool HHVM_FUNCTION(ptask_create, const String& func, const Array& arg) {
    char  *fname;
    int    flen;
    zval  *arg;
    struct ptask_ctx *ctx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz",
        &fname, &flen, &arg) == FAILURE)
    {
        RETURN_FALSE;
    }

    /* create task context */
    ctx = emalloc(sizeof(struct ptask_ctx));

    /* copy function name */
    ctx->func = emalloc(flen + 1);
    memcpy(ctx->func, fname, flen);
    ctx->func[flen] = '\0';

    ctx->arg = arg;

    Z_ADDREF_PP(&arg); /* arg->refcount++ */

    taskcreate(ptask_thread_fn, (void *)ctx, PTASK_STACK_SIZE);

    RETURN_TRUE;
}

static class ExampleExtension : public Extension {
 public:
  ExampleExtension() : Extension("example") {}
  virtual void moduleInit() {
    HHVM_FE(example_sum);
    HHVM_FE(ptask_create);
    loadSystemlib();
  }
} s_example_extension;

HHVM_GET_MODULE(example)

} // namespace HPHP
