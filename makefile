# nmake makefile
# 
# Tools used:
#  Compile::Resource Compiler
#  Compile::GNU C
#  Make: nmake
all : bitcat2.exe

bitcat2.exe : bitcat2.obj bitcat2.def
	gcc -Zomf bitcat2.obj bitcat2.def -o bitcat2.exe

bitcat2.obj : bitcat2.c bitcat2.h
	gcc -Wall -Zomf -c -O2 bitcat2.c -o bitcat2.obj

clean :
	rm -rf *exe *RES *obj