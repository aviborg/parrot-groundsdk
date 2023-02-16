#ifndef _PARROT_ULOG_
#define _PARROT_ULOG_
#include <stdio.h>

#define ULOG_DECLARE_TAG(name)

#define ULOGC(...) printf(__VA_ARGS__)
#define ULOGE(...) printf(__VA_ARGS__)
#define ULOGW(...) printf(__VA_ARGS__)
#define ULOGN(...) printf(__VA_ARGS__)
#define ULOGI(...) printf(__VA_ARGS__)
#define ULOGD(...) printf(__VA_ARGS__)

#define ULOG_ERRNO
#define ULOG_ERRNO_RETURN_ERR_IF
#define ULOG_ERRNO_RETURN_VAL_IF
#define ULOG_ERRNO_RETURN_IF

#endif //_PARROT_ULOG_