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
#define ULOGE_ERRNO
#define ULOG_PRI
#define ULOG_PRI_VA
#define ULOG_DEBUG 0
#define ULOG_INFO 0
#define ULOG_ERR 3
#define ULOG_CRIT 2
#define ULOG_WARN 1
#define ULOG_UNLIKELY 0

#endif //_PARROT_ULOG_