
# Memcheck-Shim
This project is meant to emulate the behaviour of Valgrind, while remaining light weight, minorly impacting executable runtime. My  project leak checks an executable by intercepting library calls to new and delete implemented in libstdc++, then using this information to track memory consumption.
This shim is build to run on Linux based operating systems (tested on Ubuntu 18.0.4) using the c++17 standard. My shim does not and will not support Windows.
## Setup
- clone git repository
- change to root project directory and run make
- install shared objects into _____

## Details
**What this project will do:**
- Determine memory leaks in a program indicating size, base address, and order
- Show memory request timeline for the program lifetime
 
**What this project will not do:**
 - Provide line numbers and code snippets for detected memory leaks
 - detect memory leaks in C programs / programs utilizing C style memory management functions or memory allocation system calls like mmap

**Comparison With Valgrind**
- Valgrind uses JIT translation of the executable, instrumenting it on the fly
	- This instrumentation allows Valgrind to use debug symbols providing code snippets and line numbers, as well as stack frame snapshots
- The implementation in this project is far simpler and consequently far more light weight 
- I implement a shim oveloading the new and delete operators provided by the standard library, then I force this shim to be linked first so that the overloads take effect
	- The shim then makes calls to a second shared library to record the memory request, and on program completion this library dumps the recorded memory requests

## License


## Future Improvements
-Allow for the data collector to persist the allocation timeline to a swap file should the time line begin to eat up too much memory
-Allow for additional options to be passed via posix message queue

