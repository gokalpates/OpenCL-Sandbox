#pragma once

#include "Utils.h"

cl_uint get_platform_count()
{
    cl_uint platform_count = 0u;
    clGetPlatformIDs(0, NULL, &platform_count);
    return platform_count;
}

void get_platform_info(cl_platform_id platform, int platform_index)
{
    cl_char* return_buffer = NULL;
    size_t return_size = 0u;

    printf("--------Platform %d-------- \n", platform_index);

    clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetPlatformInfo(platform, CL_PLATFORM_NAME, return_size, return_buffer, NULL);
    printf("Platform name: %s\n", return_buffer);
    free(return_buffer);

    clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, return_size, return_buffer, NULL);
    printf("Platform vendor: %s\n", return_buffer);
    free(return_buffer);

    clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetPlatformInfo(platform, CL_PLATFORM_VERSION, return_size, return_buffer, NULL);
    printf("Platform version: %s\n", return_buffer);
    free(return_buffer);

    clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, return_size, return_buffer, NULL);
    printf("Platform profile: %s\n", return_buffer);
    free(return_buffer);

    clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, return_size, return_buffer, NULL);
    printf("Platform's supported extensions: %s\n", return_buffer);
    free(return_buffer);
}

void get_all_platforms_info(cl_platform_id* platforms, int platform_count)
{
    for (int i = 0; i < platform_count; i++)
    {
        get_platform_info(platforms[i], i);
    }
}

cl_uint get_device_count(cl_platform_id platform)
{
    cl_uint device_count = 0u;
    cl_uint err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &device_count);
    return device_count;
}

cl_uint get_device_count_based_type(cl_platform_id platform, cl_device_info type)
{
    cl_uint device_count = 0u;
    cl_uint err = clGetDeviceIDs(platform, type, 0, NULL, &device_count);
    return device_count;;
}

void get_device_info(cl_device_id device, int device_index)
{
    cl_char* return_buffer = NULL;
    size_t return_size = 0u;

    printf("----Device %d---- \n", device_index);

    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetDeviceInfo(device, CL_DEVICE_NAME, return_size, return_buffer, NULL);
    printf("Device name: %s\n", return_buffer);
    free(return_buffer);

    clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, return_size, return_buffer, NULL);
    printf("Device vendor: %s\n", return_buffer);
    free(return_buffer);

    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &return_size);
    return_buffer = (cl_char*)malloc(return_size);
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, return_size, return_buffer, NULL);
    printf("Device's supported extensions: %s\n", return_buffer);
    free(return_buffer);
}

void get_all_devices_info(cl_device_id* devices, int device_count)
{
    for (int i = 0; i < device_count; i++)
    {
        get_device_info(devices[i], i);
    }
}

char* get_source_from_file(char* source_file)
{
    FILE* file_stream = NULL;
    
    char* program_buffer = NULL;
    size_t program_size = 0u;

    file_stream = fopen(source_file, "rb");

    fseek(file_stream, 0, SEEK_END);
    program_size = ftell(file_stream);
    rewind(file_stream);

    program_buffer = (char*)malloc(program_size + 1);
    program_buffer[program_size] = '\0';
    
    fread(program_buffer, sizeof(char), program_size, file_stream);

    fclose(file_stream);

    return program_buffer;
}
