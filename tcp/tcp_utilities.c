#include "tcp_utilities.h"

void error(const char *msg) {
    perror(msg);
    exit(1);
}
