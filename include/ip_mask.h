#ifndef IP_MASK_H
#define IP_MASK_H

#include "ip_address.h"

/**
 * @brief Presentation of star sign
 *
 */
#define IP_MASK_STAR 0xFF

/**
 * @brief Struct that contains devided IP address.
    Address is divided into 4 bytes, where each byte is divided into MSB and LSB part.
    MSB part contain 4 most signecifient bits
    LSB part conatain 4 lest signecifinet bits
    / address[0] - 1st_addres_MSB /
    / address[1] - 1st_addres_LSB /
    / address[2] - 2nd_addres_MSB /
    / address[3] - 2nd_addres_LSB /
    / address[4] - 3rd_addres_MSB /
    / address[5] - 3rd_addres_LSB /
    / address[6] - 4th_addres_MSB /
    / address[7] - 4th_addres_LSB /
 */
typedef struct {
    uint8_t address[8];
} ip_mask_t;

/**
 * @brief IP mask init default
 *
 */
#define IP_MASK_INIT_DEFAULT() { \
    .address = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} \
} \

/**
 * @brief Load ip mask
 *
 * @param ip pointer to mask struct
 * @param ip_string pointer to string containing mask
 * @param ip_len length of string mask
 * @return true success
 * @return false invalid mask format
 */
bool ip_mask_load(ip_mask_t *ip, char *ip_string, size_t ip_len);

/**
 * @brief Concatenate two mask - perform operator & on two mask
 *
 * @param mask_to mask to store result
 * @param mask_from mask to concatenate with mask_to
 * @return true
 * @return false masks do not have intersection
 */
bool ip_mask_concatenate(ip_mask_t *mask_to, ip_mask_t *mask_from);

/**
 * @brief Check that address fit the mask
 *
 * @param mask mask
 * @param address ip address
 * @return true address fit the mask
 * @return false addres does not fit the mask
 */
bool ip_mask_check_address(ip_mask_t *mask, ip_address_t *address);

#endif
