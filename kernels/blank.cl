__kernel void blank(__global int* arg, __global int* result) {
   int i = get_global_id(0);
   result[i] = arg[i] * arg[i];
}
