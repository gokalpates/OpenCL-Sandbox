#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else  
#include <CL/cl.h>
#endif

cl_uint get_platform_count();
void get_platform_info(cl_platform_id platform, int platform_index);
void get_all_platforms_info(cl_platform_id* platforms, int platform_count);

cl_uint get_device_count(cl_platform_id platform);
cl_uint get_device_count_based_type(cl_platform_id platform, cl_device_info type);
void get_device_info(cl_device_id device, int device_index);
void get_all_devices_info(cl_device_id* devices, int device_count);

char* get_source_from_file(char* source_file);
