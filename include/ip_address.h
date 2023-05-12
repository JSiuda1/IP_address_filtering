#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t address[4];
} ip_address_t;

#define IP_ADDRESS_INIT_DEFAULT() { \
    .address = {0, 0, 0, 0} \
} \

/**
 * @brief Load decimal form ip address
 *
 * @param ip pointer to ip struct
 * @param ip_string pointer to decimal form ip string, should contain null terminator
 * @return true success
 * @return false unable to load ip address
 */
bool ip_address_load_binary(ip_address_t *ip, char *ip_string);

#endif
