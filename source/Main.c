#define PROGRAM_FILE "kernels/matvec.cl"
#define KERNEL_FUNC "matvec_mult"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <Windows.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else  
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>
#endif

#include "Utils.h"

int main() {

    cl_platform_id* platforms = NULL;
    cl_uint platform_count = get_platform_count();

    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platform_count);
    clGetPlatformIDs(platform_count, platforms, NULL);

    cl_device_id* devices = NULL;
    cl_uint device_count = get_device_count(platforms[0]);

    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * device_count);
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, device_count, devices, NULL);
    
    cl_int error;
    cl_context context = clCreateContext(NULL, device_count, devices, NULL, NULL, &error);
    if (error < 0)
    {
        printf("ERROR: Could not create context.\n");
    }

    char* program_source = get_source_from_file("kernels/blank.cl");
    size_t program_size = strlen(program_source);

    cl_program program = clCreateProgramWithSource(context, 1, &program_source, &program_size, &error);
    if (error < 0)
    {
        printf("ERROR: Could not create program.\n");
    }
    free(program_source);

    error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (error < 0)
    {
        printf("ERROR: Build failed.\n");

        size_t log_size = 0u;
        char* program_log = NULL;

        clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        program_log = (char*)calloc(log_size + 1, sizeof(char));
        clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
        printf("%s\n", program_log);

        free(program_log);
    }

    cl_kernel kernel = clCreateKernel(program, "blank", &error);
    if (error < 0)
    {
        printf("ERROR: Could not create kernel.\n");
    }

    cl_queue_properties command_queue_properties[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, 0 };
    cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, devices[0], command_queue_properties, &error);
    if (error < 0)
    {
        printf("ERROR: Could not create command queue.\n");
    }

    size_t work_units_per_kernel = 1;
    error = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &work_units_per_kernel, NULL, 0, NULL, NULL);
    if (error < 0)
    {
        printf("ERROR: Could not enqueue command queue.\n");
    }

    clReleaseCommandQueue(command_queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
    free(devices);
    free(platforms);
    return 0;
}

