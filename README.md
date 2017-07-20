vgc
===

Vulture Garbage Collector - Is a small automatic memory management system (Garbage Collector).  Currently, it is a simple [Reference Counting][0] implementation based a [blog post][1] by Skeeto/Chris Wells and it is contained in a single header file.  It can be used in ANSI C, C99, C11.  In C99 and C11, it defaults to a thread-safe implementation.  My eventual plans are to
* Add benchmarking tests
* Make it more generic
* Make it so it compiles on less ANSI compatible compilers and 16-bit DOS compilers ([Dunfield MicroC][2], [Borland C/C++][3], [Borland TurboC/C++][4], [OpenWatcom 1.9][5]/[2.0][6])
* Optimize it for better cache locality
* Optimize it's memory use (currently 2 pointers per Object, 8 bytes (32-bit) or 16-bits (64-bit)
* Make mark, sweep, scavenge automagical with [RAII][7]/[auto-destructors][8]

Setting up your environment
===
* In RHEL 7 (and Fedora, CentOS),
** Enable `server-optional-rpms` repo.
*** `# subscription-manager repos --enable rhel-7-server-optional-rpms`
** Install `kernel-headers`, `glibc-static`, `gcc`, `g++`, `binutils`, `git`, `make`
*** `# yum install kernel-headers glibc-static gcc g++ binutils git make`



[0]: 
