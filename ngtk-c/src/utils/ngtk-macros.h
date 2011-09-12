#ifndef __NGtk_macros_h__
#define __NGtk_macros_h__

#include <assert.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (! FALSE)
#endif

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#define NGTK_BIT_MASK(bit) (1 << ((bit)-1))

#define NGTK_FIELD_OFFSET(field,type) ((int)(&(((type*)NULL)->field)))

#define NGTK_LONG_MACRO_BEGIN do
#define NGTK_LONG_MACRO_END   while(FALSE);

#ifndef NGTK_OPTIMIZE
#define ngtk_assert(expr) assert(expr)
#else
#define ngtk_assert(expr) NGTK_LONG_MACRO_BEGIN if (FALSE && (expr)) { } NGTK_LONG_MACRO_END
#endif

#endif