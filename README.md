# vgc
A minimal Garbage Collector for ANSI-C, C99, C11

## Vulture Garbage Collector
A small, minimal automatic memory management system (Garbage Collector).  Currently, it is a simple [Reference Counting][0] implementation based a [blog post][1] by Skeeto/Chris Wells and it is contained in a single header file.  It can be used in ANSI C, C99, C11.  In C99 and C11, it defaults to a thread-safe implementation.  My eventual plans are to
* Add benchmarking tests
* Make it more generic
* Make it so it compiles on less ANSI compatible compilers and 16-bit DOS compilers ([Dunfield Micro-C][2], [Borland C/C++][3], [Borland TurboC/C++][4], [OpenWatcom 1.9][5]/[V2][6])
* Optimize it for better cache locality
* Optimize it's memory use (currently 2 pointers per Object, 8 bytes (32-bit) or 16-bits (64-bit)
* Make mark, sweep, scavenge automagical with [RAII/cleanup vars][7]/[auto-destructors][8]
* Optimize with [MRU Cache Replacement Policies][9] in mind

## Setting up your environment
* In RHEL 7 (and Fedora, CentOS),
* Enable `server-optional-rpms` repo.
* `# subscription-manager repos --enable rhel-7-server-optional-rpms`
* Install `kernel-headers`, `glibc-static`, `gcc`, `g++`, `binutils`, `git`, `make`
* `# yum install kernel-headers glibc-static gcc g++ binutils git make`

## Building
In the original forlder, try:
* `make test`
* `make runtest`
* `make install`
* `make DESTDIR=/usr/local install`, or simply, `make install`
* You can also do `make uninstall`

## References
* [Unified Theory of Garbage Collection][10]
* [Reference Counting][0]
* [Skeeto/Chris Wells' Reference Counting Implementation][1]
* [Dunfield Micro-C for DOS][2]
* [Borland C/C++][3]
* [Turbo C/C++ for DOS][4]
* [OpenWatcom v1.9][5]
* [OpenWatcom V2 at Github][6]
* [RAII, Reference Counting, and cleanup vars][7]
* [cleanup vars and destructors][8]
* [MRU Cache Replacement Policy][9]
* [Cache Simulator written in HTML/JS][11]

[0]: https://en.wikipedia.org/wiki/Reference_counting
[1]: http://nullprogram.com/blog/2015/02/17/
[2]: http://www.classiccmp.org/dunfield/dos/index.htm
[3]: https://en.wikipedia.org/wiki/Borland_C%2B%2B
[4]: https://en.wikipedia.org/wiki/Turbo_C%2B%2B
[5]: http://openwatcom.org/
[6]: https://github.com/open-watcom/open-watcom-v2
[7]: https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization#Reference_counting
[8]: https://en.wikipedia.org/wiki/Destructor_(computer_programming)#In_C_with_GCC_extensions
[9]: https://en.wikipedia.org/wiki/Cache_replacement_policies#Most_Recently_Used_.28MRU.29
[10]: http://www.cs.virginia.edu/~cs415/reading/bacon-garbage.pdf
[11]: https://github.com/lpsantil/CacheSimulator
