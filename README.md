# IP_address_filtering

## Build project
```
cd build
cmake -S ..
make
```

## Run project in normal mode
```
cd build
./IP_address_filtering ../address_list.txt ../mask_list.txt
```

## Run project in debug mode - prints logs about unwanted actions
```
cd build
./IP_address_filtering_debug ../address_list.txt ../mask_list.txt
```

## Run ip addresses and masks generator
[...] - optional arguments
```
python3 address_generator.py [number_of_addresses] [number_of_masks]
```