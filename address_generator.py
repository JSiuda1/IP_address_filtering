import random

ip_byte_max = 255
ip_byte_min = 0

def generate_ip_address() -> list:
    return [random.randint(ip_byte_min, ip_byte_max + 1) for i in range(4)]

# def generate_ip_mask() -> list:


with open("address_list.txt", "+w") as address_file:
    for i in range(500000):
        ip_string = "{}.{}.{}.{}\n".format(*generate_ip_address())
        address_file.write(ip_string)