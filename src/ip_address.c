#include "ip_address.h"
#include <stdio.h>
#include <memory.h>

bool ip_address_load_binary(ip_address_t *ip, char *ip_string) {
    if (sscanf(ip_string, "%hhu.%hhu.%hhu.%hhu",
                &ip->address[0], &ip->address[1], &ip->address[2], &ip->address[3]) != 4) {
        return false;
    }

    return true;
}
