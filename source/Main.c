#define _CRT_SECURE_NO_WARNINGS
#define PROGRAM_FILE "kernels/matvec.cl"
#define KERNEL_FUNC "matvec_mult"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else  
#include <CL/cl.h>
#endif

#include "Utils.h"

int main() {

    cl_platform_id* platforms = NULL;
    cl_uint platform_count = get_platform_count();

    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platform_count);
    clGetPlatformIDs(platform_count, platforms, NULL);
    get_all_platforms_info(platforms, platform_count);

    cl_device_id* devices = NULL;
    cl_uint device_count = get_device_count(platforms[0]);

    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * device_count);
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, device_count, devices, NULL);
    get_all_devices_info(devices,device_count);

    cl_int error;
    cl_context context = clCreateContext(NULL, device_count, devices, NULL, NULL, &error);
    if (error < 0)
    {
        printf("ERROR: Could not create context.\n");
    }


    clReleaseContext(context);

    free(devices);
    free(platforms);
    return 0;
}

