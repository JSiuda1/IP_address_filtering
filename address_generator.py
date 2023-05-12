import sys
import random

ip_byte_max = 255
ip_byte_min = 0

def generate_ip_address() -> list:
    return [random.randint(ip_byte_min, ip_byte_max + 1) for i in range(4)]



def generate_ip_mask() -> list:
    mask_characters = [str(i) for i in range(0, 10)]
    mask_characters = mask_characters + ["a", "b", "c", "d" ,"e" ,"f"]
    mask_characters = mask_characters + ["*" for i in range(0, 100)]
    return [mask_characters[random.randint(0, len(mask_characters) - 1)] for i in range(8)]

def gererate_and_write_addreses():
    with open("address_list.txt", "+w") as address_file:
        for i in range(number_of_addresses):
            ip_string = "{}.{}.{}.{}\n".format(*generate_ip_address())
            address_file.write(ip_string)

def generate_and_write_masks():
    with open("mask_list.txt", "+w") as mask_file:
        for i in range(number_of_masks):
            ip_string = "{}{}.{}{}.{}{}.{}{}\n".format(*generate_ip_mask())
            mask_file.write(ip_string)

if __name__ == "__main__":
    number_of_addresses = 100_000
    number_of_masks = 5

    if (len(sys.argv) != 1):
        number_of_addresses = int(sys.argv[1])
        number_of_masks = int(sys.argv[2])

    print("Generating {} addresses and {} masks".format(number_of_addresses, number_of_masks))

    if number_of_addresses != 0:
        gererate_and_write_addreses()

    if number_of_masks != 0:
        generate_and_write_masks()

    print("Done")
