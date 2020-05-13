

# MCheck
MCheck is a streamlined memory leak checker similar to Valgrind. This project leak checks an executable by intercepting library calls to new and delete implemented in libstdc++. The intercepted calls then use the contextual information to track heap memory consumption.
This shim is built to run on Linux based operating systems only (tested on Ubuntu 18.0.4) using the C++17 standard. This shim does not and will not support Windows due to lack of POSIX compliance.

## Setup
1) Clone git repository
2) Change to root project directory and run make
3) If not already done, install shared objects `libmcheck.so` and `libmcheckstorage.so` into `~/mylibs`
4) Add the executable `mcheck` to your `$PATH` environment variable either by moving it to a location in your path or by appending to your path
5) Run the leak checker on an executable via `mcheck <exe to check path>`

## Details
**MCheck Options:**
- `-v` option indicates to use verbose realtime logging

**What this project will do:**
- Determine memory leaks in a program indicating size, and base address
- Show memory allocation timeline for the program
 
**What this project will not do:**
 - Provide line numbers and code snippets for detected memory leaks
 - Detect memory leaks in C programs / programs utilizing C style memory management functions or memory allocation system calls like mmap or brk
 	- Leak checking for C style memory management may be added in a future update, but does not work at the moment

**Comparison With Valgrind**
- Valgrind uses JIT translation of the executable, instrumenting the executable on the fly
	- Instrumentation allows Valgrind to use debug symbols to provide code snippets and line numbers, as well as stack frame snapshots for any leaks found
- This project implements a shim oveloading the new and delete operators provided by the standard library. There is no translation or instrumentation of the client executable resulting in a far smaller performance cost

## Future Improvements
- Allow for the data collector to persist the allocation timeline to a swap file if the time line begins to hog memory as this may cause memory thrashing / constant state of paging
- Allow for additional options to be passed via POSIX message queue
- Shim C style memory mangement methods (malloc, calloc, realloc, free, etc)
- Look into possible ways of tracking / overloading memory allocation system calls (mmap, brk, etc)

