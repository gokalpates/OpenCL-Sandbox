#include <stdio.h>
#include <CL/cl.h>

#define PROGRAM_FILE "kernels/matvec_mult"
#define KERNEL_FUNC "matvec_mult"

#define MAX_ALLOWED_PLATFORM 16

int main()
{
    cl_platform_id platform[MAX_ALLOWED_PLATFORM];
    cl_device_id device;
    cl_context context;
    cl_program program;
    cl_kernel kernel;
    cl_mem mat_buffer, vec_buffer, res_buffer;
    cl_command_queue queue;

    cl_int i, error;

    FILE* program_source_file;
    char* program_source, program_log;
    size_t program_size, log_size;
    size_t work_units_per_kernel;

    float mat[16], vec[4], result[4];
    float correct[4] = { 0.f };

    //CPU computations.
    //Initialize matrix data.
    for (int i = 0; i < 16; i++)
    {
        mat[i] = i * 2.f;
    }

    //Initialize vector data.
    for (int i = 0; i < 4; i++)
    {
        vec[i] = i * 3.f;
    }

    //Calculate correct result.
    for (int i = 0; i < 4; i++)
    {
        correct[0] += mat[i] * vec[i];
        correct[1] += mat[i + 4] * vec[i];
        correct[2] += mat[i + 8] * vec[i];
        correct[3] += mat[i + 12] * vec[i];
    }

    cl_uint platform_count;
    
    clGetPlatformIDs(MAX_ALLOWED_PLATFORM, platform, &platform_count);

    printf("%d", platform_count);

    return 0;
}