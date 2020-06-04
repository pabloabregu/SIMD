rm tp;
nasm -f elf32 helloworld.s -o helloworld.o;
nasm -f elf32 mulSIMD.s -o mulSIMD.o
gcc -m32 main.c lectorBmp.c filtros.c mulSIMD.o  helloworld.o -o tp;
./tp;
