/**
 * \file DynamicLibrary.cpp
 * \brief
 *
 * Cross-platform dynamic link libraries (.dll/.so)
 *
 * \version 1.0.0
 * \date 13/03/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#include "DynamicLibrary.h"

#if defined(_WIN32)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

bool ldr::DynamicLibrary::load(const char* fileName)
{
#if defined(_WIN32)
	handle_ = (void*)::LoadLibrary(fileName);
#else
	handle_ = dlopen(fileName, RTLD_LAZY);

	const char* errStr = dlerror();

	if (errStr != nullptr) {
		printf("Failed to load %s (%s)\n", fileName, errStr);
		handle_ = nullptr;
	}
#endif
	return handle_ != nullptr;
}

ldr::DynamicLibrary::~DynamicLibrary()
{
	if (handle_) {
#if defined(_WIN32)
		FreeLibrary((HMODULE)handle_);
#else
		dlclose(handle_);
#endif
	}
}

void* ldr::DynamicLibrary::getProcAddress(const char* procName) const
{
#if defined(_WIN32)
	FARPROC proc = ::GetProcAddress((HMODULE)handle_, procName);

	return (void*)(proc);
#else
	void* proc = dlsym(handle_, procName);

	const char* errStr = dlerror();

	return errStr == nullptr ? proc : nullptr;
#endif
}
