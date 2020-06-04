rm tp;
nasm -f elf32 helloworld.s -o helloworld.o;
nasm -f elf32 mulSIMD.s -o mulSIMD.o;
nasm -f elf32 multiply.s -o multiply.o;
gcc -m32 main.c lectorBmp.c filtros.c helloworld.o mulSIMD.o multiply.o -o tp;
./tp;
