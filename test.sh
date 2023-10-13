#Copyright 2019-2023 Kai D. Gonzalez

#--- valgrind
gcc test.c -o test string.c
clear
valgrind --leak-check=full -s ./test
read -n 1 -s -r -p "Press any key to continue . . ."
rm ./test

#--- testing with gcc

gcc test.c -o test string.c -Wno-implicit-int -fsanitize=address -g -O3
clear
printf "gcc outputs:\n";
./test
rm test

sleep 2;


#--- testing with tcc
tcc test.c -o test string.c
clear
printf "tcc outputs:\n";
./test
rm test

sleep 2
