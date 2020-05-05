/*
* Author: davidpeet8
* 
*
*
* IMPLEMENTATIONS WE WILL REPLACE
* [ Throwing ]:   void* operator new (std::size_t);
* [ No Throw ]:   void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) noexcept;
* [ Placement ]:  void* operator new (std::size_t size, void* ptr) noexcept
*
* [ Throwing ]:   void *operator new[] (std::size_t size);
* [ No Throw ]:   void *operator new[] (std::size_t size, const std::nothrow_t& nothrow_value) noexcept;
* [ Placement ]:  void *operator new[] (std::size_t size, void *ptr) noexcept;
*
* [ Normal ]:             void operator delete (void *ptr) noexcept;
* [ No Throw ]:           void operator delete (void *ptr, const std::nothrow_T& nothrow_constant) noexcept;
* [ Placement ]:          void operator delete (void *ptr, void *voidptr2) noexcept;
* [ With Size ]:          void operator delete (void *ptr, std::size_t size) noexcept;
* [ No Throw & Size ]:    void operator delete (void *ptr, std::size_t size, const std::nothrow_t& nothrow_constant) noexcept;
*
* 
* Notes: 
* 	1) nothrow constant --> does not mean will not fail, just will not throw when it does
* 		- means new will return nullptr on fail instead of throwing
* 	2) invocations of different news
* 		new MyClass
*		new (std::nothrow) MyClass --> constructs new object but returns nullptr if alloc fails
* 		new (pointer to existant obj) MyClass --> constructs new object at pointer
*	3) This shim implementation is far different than Valgrind, which instruments the executable on the fly 
* 	   and runs it in a virtual CPU allowing for more advanced diagnostic info like memory leak line numbers
* 	4) Placement Implementations will not need to be replaced at all, the memory consumption before and after will be the same anyway
*/

// Two Implementations could be followed here - reimplement the new and delete overloads, or try to obtain pointers to the initial definitions
// I am Choosing to reimplment the overloads
// Portability would be garbage if I used function pointer implementation
// 	- 'new' and 'delete' are not symbols in the <new> header, their symbols have already been mangled into assembly lables 
//	- Ex. _Zwnm is the symbol to use to retrieve a pointer to new using dlsym() but this is likely compiler specific
// 

// -----------------------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <new>

// Force internal linkage on methods that shouldn't clutter global namespace
namespace 
{
	void dumpMemory() 
	{
		printf("Dumping memory contents:\n");
		// Call the library implementing the storage of memory
	}

	// Note that this is called on lib load, so given that this shim uses LD_PRELOAD, onLoad will be called before main is run
	// - stdout does not exist yet, among other things
	__attribute__((constructor)) 
	void onLoad() 
	{
		// Get configuration from the posix messge queue that was set up by the cli

		// Set up program exit handler - printing data
		std::atexit(dumpMemory);
	}
}

// ----------------------------- NEW -----------------------------------

void *operator new(size_t size)
{
	printf("Hit shim impl of throwing new\n");
	void * retaddr = malloc(size);
	if (retaddr == nullptr) 
	{
		throw std::bad_alloc();
	}
	// request succeeded, we have size and starting address of allocated virtual memory
	// Call to store this information
	return retaddr;
}

// Return nullptr on fail - default behavior of malloc
void *operator new(size_t size, const std::nothrow_t& nothrow) noexcept 
{
	printf("Hit shim impl of nothrow new\n");
	return malloc(size);
}

// ---------------------------- NEW [] --------------------------------

void *operator new[](size_t size)
{
	printf("Hit shim impl of throwing new[]\n");
	return ::operator new(size);
}

void *operator new[](size_t size, const std::nothrow_t& nothrow) noexcept
{
	printf("Hit shim impl of nothrow new[]\n");
	return ::operator new(size, nothrow);
}

// ---------------------------- DELETE --------------------------------

void operator delete(void *ptr) noexcept
{
	printf("Hit shim impl of normal delete\n");
	free(ptr);
}

void operator delete(void *ptr, const std::nothrow_t& nothrow) noexcept
{
	printf("Hit shim impl of nothrow delete\n");
	::operator delete(ptr);
}

void operator delete(void *ptr, size_t size) noexcept
{
	printf("Hit shim impl of sized delete\n");
	::operator delete(ptr);
}

void operator delete(void *ptr, size_t size, const std::nothrow_t& nothrow) noexcept
{
	printf("Hit shim impl of sized nothrow delete\n");
	::operator delete(ptr, nothrow);
}


// -------------------------- DELETE [] ------------------------------

void operator delete[](void *ptr) noexcept
{
	printf("Hit shim impl of normal delete[]\n");
	::operator delete(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t& nothrow) noexcept
{
	printf("Hit shim impl of nothrow delete[]\n");
	::operator delete[](ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
	printf("Hit shim impl of sized delete[]\n");
	::operator delete(ptr, size);
}

void operator delete[](void *ptr, size_t size, const std::nothrow_t& nothrow) noexcept
{
	printf("Hit shim impl of sized nothrow delete[]\n");
	::operator delete(ptr, size, nothrow);
}


