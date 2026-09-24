#!/bin/bash

cd test_utils && rm -r ./venv && cd ../ && echo -e "\033[0;32mvenv limpio\033[0m"

cd src/ej1 && make clean && cd ../../ && echo -e "\033[0;32mDirectorio del EJ1 limpio\033[0m"

cd src/ej2 && make clean && cd ../../ && echo -e "\033[0;32mDirectorio del EJ2 limpio\033[0m"

cd src/ej3 && make clean && cd ../../ && echo -e "\033[0;32mDirectorio del EJ3 limpio\033[0m"
