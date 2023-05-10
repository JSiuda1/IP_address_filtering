#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include <stdint.h>
#include <stdbool.h>

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
} ip_address_info_t;

#define IP_ADDRESS_INIT_DEFAULT() { \
    .address = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} \
} \

bool ip_address_load_hex(ip_address_info_t *ip, char *ip_string);
bool ip_address_load_binary(ip_address_info_t *ip, char *ip_string);
void ip_addres_operator_and(ip_address_info_t *var1, ip_address_info_t *var2);
bool ip_address_equal(ip_address_info_t *var1, ip_address_info_t *var2);
void ip_address_print(ip_address_info_t *ip);
void ip_address_print_dec(ip_address_info_t *ip);
#endif