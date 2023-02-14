#include <ulog.h>
#include <libpomp.h>

int main(){
    ULOGI("Hello %s\n", pomp_event_str(POMP_EVENT_CONNECTED));

    return 0;
}
