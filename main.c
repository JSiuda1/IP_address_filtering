#include <stdio.h>
#include "ip_address.h"

int main(int argc, char ** argv) {
    printf("Hello world!\n");

    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return -1;
    }

    FILE* mask_list_file;
    mask_list_file = fopen(argv[2], "r");
    if (mask_list_file == NULL) {
        printf("Unable to open mask list file\n");
        return -1;
    }

    char line[25];
    ip_address_info_t address_mask = IP_ADDRESS_INIT_DEFAULT();
    ip_address_info_t temp_mask;
    while (fgets(line, sizeof(line), mask_list_file)) {
        ip_address_load_hex(&temp_mask, line);
        printf("      Mask -> ");
        ip_address_print(&temp_mask);
        ip_addres_operator_and(&address_mask, &temp_mask);
    }
    printf("Final mask -> ");
    ip_address_print(&address_mask);
    fclose(mask_list_file);

    FILE* address_list_file;
    address_list_file = fopen(argv[1], "r");
    if (address_list_file == NULL) {
        printf("Unable to open address list file\n");
        return -1;
    }

    ip_address_info_t address;
    while(fgets(line, sizeof(line), address_list_file)) {
        ip_address_load_binary(&address, line);
        
        if (ip_address_equal(&address, &address_mask) == true) {
            printf("   Address -> ");
            ip_address_print(&address);
        }
    } 
    fclose(mask_list_file);
    
    return 0;
}