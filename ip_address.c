#include "ip_address.h"
#include <stdio.h>
#include <memory.h>

static inline uint8_t convert_char_to_hex(char hex) {
    if (hex > 0x40 && hex < 0x47) {
        return hex - 0x37;
    } else {
        return hex - 0x30;
    }
}

bool ip_address_load_hex(ip_address_info_t *ip, char *ip_string) {
    uint8_t digit;
    memset(ip->address, 0, sizeof(ip->address));
    for (int i = 0; i < 8; ++i) {
        digit = *ip_string++;
        if (digit == '*') {
            ip->address[i*2] = 0xFF;
        } else {
            ip->address[i*2] = convert_char_to_hex(digit);
        }
        digit = *ip_string++;
        if (digit == '*') {
            ip->address[i*2 + 1] = 0xFF;
        } else {
            ip->address[i*2 + 1] = convert_char_to_hex(digit);
        }
        ip_string++;
    }
}

bool ip_address_load_binary(ip_address_info_t *ip, char *ip_string) {
    uint8_t bytes[4];
    if (sscanf(ip_string, "%hhd.%hhd.%hhd.%hhd", &bytes[0], &bytes[1], &bytes[2], &bytes[3]) != 4) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        ip->address[i*2] = bytes[i] >> 4;
        ip->address[i*2 + 1] = bytes[i] & 0x0F;
    }

    return true;
}

void ip_addres_operator_and(ip_address_info_t *var1, ip_address_info_t *var2) {
    for (int i = 0; i < 8; ++i) {
        var1->address[i] &= var2->address[i];
    }
}

bool ip_address_equal(ip_address_info_t *var1, ip_address_info_t *var2) {
    for (int i = 0; i < 8; ++i) {
        if (var1->address[i] != 0xFF && var2->address[i] != 0xFF) {
            if (var1->address[i] != var2->address[i]) {
                return false;
            }
        }
    }

    return true;
}


void ip_address_print_dec(ip_address_info_t *ip) {
    int temp = 0;
    for (int i = 0; i < 4; ++i) {
        if (ip->address[i*2] == 0xff || ip->address[i*2 + 1] == 0xff){
            printf("%c.", '*');
        } else {
            temp = ip->address[i*2] << 4;
            temp |= ip->address[i*2 + 1];
            printf("%d.", temp);
        }
    }
}

void ip_address_print(ip_address_info_t *ip) {
    for (int i = 0; i < 8; ++i) {
        printf("0x%02x\t", ip->address[i]);
    }

    ip_address_print_dec(ip);
    printf("\n");
}