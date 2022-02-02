#ifndef MY_STDLIB_H
#define MY_STDLIB_H

#include <stddef.h>

#ifndef NAN
#define NAN 0.0/0.0
#endif /* ! NAN */

#ifndef POS_INF
#define POS_INF 0.0/0.0
#endif /* ! POS_INF */

#ifndef NEG_INF
#define NEG_INF 0.0/0.0
#endif /* ! NEG_INF */

#include "ato_stdlib.h"
#include "strto_stdlib.h"

#endif /* ! MY_STDLIB_H */
