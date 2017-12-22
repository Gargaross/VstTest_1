// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef DLLTEST1_EXPORTS
#define DLLTEST1_API __declspec(dllexport)
#else
#define DLLTEST1_API __declspec(dllimport)
#endif

extern "C" DLLTEST1_API int add_int(
	const int a, const int b);
