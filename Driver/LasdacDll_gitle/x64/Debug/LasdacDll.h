#pragma once
// LasdacDll.h

#include "LasdacStructs.h"

#ifdef LASDACDLL_EXPORTS
#define LASDACDLL_API __declspec(dllexport) 
#else
#define LASDACDLL_API __declspec(dllimport) 
#endif

LASDACDLL_API int send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, struct Point *punkter);
LASDACDLL_API void print_test();

