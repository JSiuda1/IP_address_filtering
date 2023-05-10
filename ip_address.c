#include "ip_address.h"
#include <stdio.h>
#include <memory.h>

bool ip_address_load_binary(ip_address_t *ip, char *ip_string) {
    uint8_t bytes[4];
    if (sscanf(ip_string, "%hhd.%hhd.%hhd.%hhd",
                &ip->address[0], &ip->address[1], &ip->address[2], &ip->address[3]) != 4) {
        return false;
    }

    return true;
}

// void ip_addres_operator_and(ip_address_info_t *var1, ip_address_info_t *var2) {
//     for (int i = 0; i < 8; ++i) {
//         var1->address[i] &= var2->address[i];
//     }
// }

// bool ip_address_equal(ip_address_info_t *var1, ip_address_info_t *var2) {
//     for (int i = 0; i < 8; ++i) {
//         if (var1->address[i] != 0xFF && var2->address[i] != 0xFF) {
//             if (var1->address[i] != var2->address[i]) {
//                 return false;
//             }
//         }
//     }

//     return true;
// }


// void ip_address_print_dec(ip_address_info_t *ip) {
//     int temp = 0;
//     for (int i = 0; i < 4; ++i) {
//         if (ip->address[i*2] == 0xff || ip->address[i*2 + 1] == 0xff){
//             printf("%c.", '*');
//         } else {
//             temp = ip->address[i*2] << 4;
//             temp |= ip->address[i*2 + 1];
//             printf("%d.", temp);
//         }
//     }
// }

// void ip_address_print(ip_address_info_t *ip) {
//     for (int i = 0; i < 8; ++i) {
//         printf("0x%02x\t", ip->address[i]);
//     }

//     ip_address_print_dec(ip);
//     printf("\n");
// }