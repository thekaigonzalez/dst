#Copyright 2019-2023 Kai D. Gonzalez

gcc test.c -o test string.c -Wno-implicit-int
clear
./test
rm test
