#include <stdio.h>
#include <string.h>
#include "ip_mask.h"

/**
 * @brief Load and concatenate masks from a file
 *
 * @param mask pointer to store concatenate mask
 * @param file_path path to masks file
 * @return true success
 * @return false unable to open file or read from file
 */
bool load_ip_mask_from_file(ip_mask_t *mask, char *file_path);

/**
 * @brief Load ip addresses from file and check witch fit the mask,
 *  this function also print result to standatd output
 *
 * @param mask ip mask
 * @param file_path path to addresses file
 * @return true success
 * @return false unable to open filer or read from file
 */
bool load_and_check_addresses(ip_mask_t *mask, char *file_path);

/**
 * @brief Print addres to standard otuput in decimal form
 *
 * @param ip pointer to ip
 */
void print_address_decimal(ip_address_t *ip);

/**
 * @brief Print addres to standard otuput in hex form
 *
 * @param ip pointer to ip
 */
void print_address_hex(ip_address_t *ip);


/**
 * @brief Print mask to standard otuput in hex form
 *
 * @param ip pointer to ip
 */
void print_mask(ip_mask_t *mask);


int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return -1;
    }

    ip_mask_t address_mask = IP_MASK_INIT_DEFAULT();
    if (load_ip_mask_from_file(&address_mask, argv[2]) == false) {
        return -1;
    }

#ifdef DEBUG
    printf("Mask -> ");
    print_mask(&address_mask);
#endif

    if (load_and_check_addresses(&address_mask, argv[1]) == false) {
        return -1;
    }

    return 0;
}

bool load_ip_mask_from_file(ip_mask_t *mask, char *file_path) {
    FILE* mask_list_file;
    mask_list_file = fopen(file_path, "r");
    if (mask_list_file == NULL) {
        perror("Unable to open mask list file");
        return false;
    }

    char line[25];
    ip_mask_t temp_mask;
    while (fgets(line, sizeof(line), mask_list_file)) {
        if (ip_mask_load(&temp_mask, line, strlen(line)) == false) {
#ifdef DEBUG
            printf("Invalid mask format -> %s\n", line);
#endif
        }

        if (ip_mask_concatenate(mask, &temp_mask) == false) {
#ifdef DEBUG
            printf("Masks does not have intescetion, loaded mask-> %s", line);
#endif
        }
    }

    fclose(mask_list_file);

    return true;
}

bool load_and_check_addresses(ip_mask_t *mask, char *file_path) {
    FILE* address_list_file;
    address_list_file = fopen(file_path, "r");
    if (address_list_file == NULL) {
        perror("Unable to open address list file");
        return false;
    }

    char line[25];
    ip_address_t address;
    while(fgets(line, sizeof(line), address_list_file)) {
        if (ip_address_load_binary(&address, line) == false) {
#ifdef DEBUG
            printf("Invalid address format -> %s", line);
#endif
        }

        if (ip_mask_check_address(mask, &address) == true) {
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
