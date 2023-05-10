#include <memory.h>
#include <stdio.h>
#include "ip_mask.h"

#define CHECK_IS_UPPERCASE_HEX(x) x > 0x40 && x < 0x47
#define CHECK_IS_LOWERCASE_HEX(x) x > 0x60 && x < 0x67
#define CHECK_IS_NUMBER(x) x > 0x2f && x < 0x3A

bool convert_char_to_hex(char in, uint8_t *out) {
    if (CHECK_IS_LOWERCASE_HEX(in)) {
        *out = in - 0x57;
    } else if (CHECK_IS_UPPERCASE_HEX(in)) {
        *out = in - 0x37;
    } else if (CHECK_IS_NUMBER(in)) {
        *out = in - 0x30;
    } else {
        return false;
    }

    return true;
}

bool ip_mask_load(ip_mask_t *ip, char *ip_string) {
    uint8_t digit;
    memset(ip->address, 0, sizeof(ip->address));

    for (int i = 0; i < 8; ++i) {
        if (*ip_string == '.') {
            i--;
            ip_string++;
            continue;
        }

        if (*ip_string == '*') {
            digit = IP_MASK_STAR;
        } else {
            if (convert_char_to_hex(*(ip_string), &digit) == false) {
                return false;
            }
        }

        ip->address[i] = digit;
        ip_string++;
    }

    return true;
}

void ip_mask_concatenate(ip_mask_t *mask_to, ip_mask_t *mask_from) {
    for (int i = 0; i < sizeof(mask_to->address); ++i) {
        mask_to->address[i] &= mask_from->address[i];
    }
}

bool ip_mask_check_address(ip_mask_t *mask, ip_address_t *address) {
    for (int i = 0; i < sizeof(address->address); ++i) {
        if (mask->address[i * 2] != IP_MASK_STAR) {
            if (mask->address[i * 2] != (address->address[i] >> 4)) {
                return false;
            }
        }

        if (mask->address[i * 2 + 1] != IP_MASK_STAR) {
            if (mask->address[i * 2 + 1] != (address->address[i] & 0x0F)) {
                return false;
            }
        }
    }

    return true;
}