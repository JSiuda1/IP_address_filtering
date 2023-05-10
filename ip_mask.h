#ifndef IP_MASK_H
#define IP_MASK_H

#include "ip_address.h"

#define IP_MASK_STAR 0xFF

/**
 * @brief Struct which contain devieded ip addres.
 * Addres is devided in 4 bytes, where each bite is devided into MSB and LSB part
 * MSB part contain 4 most signecifient bits
 * LSB part conatain 4 lest signecifinet bits
 * address[0] - 1st_addres_MSB
 * address[1] - 1st_addres_LSB
 * address[2] - 2nd_addres_MSB
 * address[3] - 2nd_addres_LSB
 * address[4] - 3rd_addres_MSB
 * address[5] - 3rd_addres_LSB
 * address[6] - 4th_addres_MSB
 * address[7] - 4th_addres_LSB
 */
typedef struct {
    uint8_t address[8];
} ip_mask_t;

#define IP_MASK_INIT_DEFAULT() { \
    .address = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} \
} \

bool ip_mask_load(ip_mask_t *ip, char *ip_string, size_t ip_len);
void ip_mask_concatenate(ip_mask_t *mask_to, ip_mask_t *mask_from);
bool ip_mask_check_address(ip_mask_t *mask, ip_address_t *address);

#endif