# DEV-SAMPLES-PM-BitCat
Bitmap demonstration for PM sample. Source code in C language.

LICENSE
===============
* The 3-Clause BSD License.

COMPILE TOOLS
===============
* ArcaOS	- Version 5.0.6
* RC 		- Version 4.00.011 Oct 10 2000
* gcc		- gcc (GCC) 9.2.0 20190812 (OS/2 RPM build 9.2.0-5.oc00)

* nmake		- Version 4.00.001 Oct  4 2001
or
* make 		- Version 3.81 k2 (2017-11-10)

REQUIREMENTS
===============
* yum install gcc libc-devel binutils kbuild-make

COMPILE INSTRUCTIONS
===============
This version of this sample was modified to compile on ArcaOS with GCC 9 compiler. 
1) Remember to have correct OS/2 toolkit header files your path. For GCC the correct ones are the included on the "libc-devel", not the ones from the OS/2 Toolkit.
2) Run "make" or "make 2>&1 |tee make.out" to get the log file.

HISTORY
===============
* 1.02 - 2022-04-10
- Improved source code comments.

* 1.01 - 2022-04-10
- Changes for gcc compiler

* 1.0 - 1990
- Original version

TROUBLESHOOT
===============
The compile produce will run by just executing "nmake" (or "make") on the directory. If you want to save the log file you can run it as "nmake 2>&1 |tee make.out". The log will be saved into the "make.out" file. 

AUTHORS
===============
* Martin Iturbide
* Dave Yeo
* Charles Petzold

LINKS
===============
* 
