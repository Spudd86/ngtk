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

#define NGTK_IN_RANGE(val,min,max) ((min) <= (val) && (val) <= (max))
#define NGTK_BIT_MASK(bit) (1 << ((bit)-1))

#define NGTK_FIELD_OFFSET(field,type) ((int)(&(((type*)NULL)->field)))

#define NGTK_LONG_MACRO_BEGIN do {
#define NGTK_LONG_MACRO_END   } while (FALSE)

#define NGTK_MACRO_DO_NOTHING() NGTK_LONG_MACRO_BEGIN NGTK_LONG_MACRO_END

#ifndef NGTK_OPTIMIZE
#define ngtk_assert(expr) assert(expr)
#else
#define ngtk_assert(expr) NGTK_MACRO_DO_NOTHING ()
#endif

#define ngtk_assert_not_reached() assert (FALSE)
#endif
