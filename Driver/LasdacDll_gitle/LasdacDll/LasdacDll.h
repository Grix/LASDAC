#pragma once
// LasdacDll.h

//#include "LasdacStructs.h"
#include <windows.h>
#include "libusb.h"

#ifdef LASDACDLL_EXPORTS
#define LASDACDLL_API __declspec(dllexport)
#define LASDACDLL_API extern "C" __declspec (dllexport)
#else
#define LASDACDLL_API __declspec(dllimport) 
#endif

LASDACDLL_API void print_test2();
LASDACDLL_API int open_device();
LASDACDLL_API int send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, uint8_t *punkter);
LASDACDLL_API int close_device();

/*namespace LasdacFuncs
{
	class MyLasdacFuncs
	{
		public: 
		static LASDACDLL_API struct Point
			{
				UINT16 X;
				UINT16 Y;
				UINT8  R;
				UINT8  G;
				UINT8  B;
				UINT8  I;
			};
		static LASDACDLL_API void open_device();
		static LASDACDLL_API void send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, Point *punkter);
		static LASDACDLL_API void close_device();
		static LASDACDLL_API void print_test();
		

	};
}*/