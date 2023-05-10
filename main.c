#include <stdio.h>
#include "ip_mask.h"

bool load_ip_mask_from_file(ip_mask_t *mask, char *file_path);
bool load_and_check_addresses(ip_mask_t *mask, char *file_path);
void print_address_decimal(ip_address_t *ip);
void print_address_hex(ip_address_t *ip);
void print_mask(ip_mask_t *mask);

int main(int argc, char ** argv) {
    printf("Hello world!\n");

    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return -1;
    }

    ip_mask_t address_mask = IP_MASK_INIT_DEFAULT();
    if (load_ip_mask_from_file(&address_mask, argv[2]) == false) {
        return -1;
    }

    print_mask(&address_mask);

    if (load_and_check_addresses(&address_mask, argv[1]) == false) {
        return -1;
    }

    return 0;
}

bool load_ip_mask_from_file(ip_mask_t *mask, char *file_path) {
    FILE* mask_list_file;
    mask_list_file = fopen(file_path, "r");
    if (mask_list_file == NULL) {
        printf("Unable to open mask list file\n");
        return false;
    }

    char line[25];
    ip_mask_t temp_mask;
    while (fgets(line, sizeof(line), mask_list_file)) {
        ip_mask_load(&temp_mask, line);
        printf("Mask -> ");
        print_mask(&temp_mask);
        ip_mask_concatenate(mask, &temp_mask);
    }

    fclose(mask_list_file);

    return true;
}

bool load_and_check_addresses(ip_mask_t *mask, char *file_path) {
    FILE* address_list_file;
    address_list_file = fopen(file_path, "r");
    if (address_list_file == NULL) {
        printf("Unable to open address list file\n");
        return false;
    }

    char line[25];
    ip_address_t address;
    while(fgets(line, sizeof(line), address_list_file)) {
        ip_address_load_binary(&address, line);

        if (ip_mask_check_address(mask, &address) == true) {
            printf("Address -> ");
            print_address_hex(&address);
        }
    }

    fclose(address_list_file);

    return true;
}

void print_address_decimal(ip_address_t *ip) {
    printf("%d.%d.%d.%d\n", ip->address[0], ip->address[1], ip->address[2], ip->address[3]);
}

void print_address_hex(ip_address_t *ip) {
    printf("%02X:%02X:%02X:%02X\n",
                ip->address[0], ip->address[1], ip->address[2], ip->address[3]);
}

void print_mask(ip_mask_t *mask) {
    uint8_t temp;
    for (int i = 0; i < 8; ++i) {
        temp = mask->address[i];
        if (temp == IP_MASK_STAR) {
            printf("*");
        } else {
            printf("%X", temp);
        }

        if (i % 2 == 1 && i < 7) {
            printf(":");
        }
    }

    printf("\n");
}

// int main(int argc, char ** argv) {
//     printf("Hello world!\n");

//     if (argc != 3) {
//         printf("Invalid number of arguments\n");
//         return -1;
//     }

//     FILE* mask_list_file;
//     mask_list_file = fopen(argv[2], "r");
//     if (mask_list_file == NULL) {
//         printf("Unable to open mask list file\n");
//         return -1;
//     }

//     char line[25];
//     ip_address_info_t address_mask = IP_ADDRESS_INIT_DEFAULT();
//     ip_address_info_t temp_mask;
//     while (fgets(line, sizeof(line), mask_list_file)) {
//         ip_address_load_hex(&temp_mask, line);
//         printf("      Mask -> ");
//         ip_address_print(&temp_mask);
//         ip_addres_operator_and(&address_mask, &temp_mask);
//     }
//     printf("Final mask -> ");
//     ip_address_print(&address_mask);
//     fclose(mask_list_file);

//     FILE* address_list_file;
//     address_list_file = fopen(argv[1], "r");
//     if (address_list_file == NULL) {
//         printf("Unable to open address list file\n");
//         return -1;
//     }

//     ip_address_info_t address;
//     while(fgets(line, sizeof(line), address_list_file)) {
//         ip_address_load_binary(&address, line);
        
//         if (ip_address_equal(&address, &address_mask) == true) {
//             printf("   Address -> ");
//             ip_address_print(&address);
//         }
//     } 
//     fclose(mask_list_file);
    
//     return 0;
// }