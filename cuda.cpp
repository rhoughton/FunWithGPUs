#include <iostream>
#include <math.h>
//by adding global i am telling the program to do gpu stuff now
//this add function is now a function the gpu can run!
__global__
void add(int n, float *x, float *y)
{
    int index = threadIdx.x;
    int stride = blockDim.x;
    for (int i =index; i<n; i+= stride)
    y[i] = x[i] + y[i];
}
int main(void)
{
    int N =1<<20 //1mil elements
    float *x, float *y
    //allocate unified memory accessible from cpu or gpu
    //unified memory provides a single mem space accessible by either the cpu or gpu
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));
    // initialize x and y arrays on the host
    for (int i = 0; i<N; i++){
        x[i] = 1.0f;
        y[i] = 2.0f;
    }
    //run kernal on 1mil elements on cpu
    add<<<1, 256>>>(N,x,y);
    //wait for gpu to finish before accessing on host
    cudaDeviceSynchonrize();
    //fre memory
    cudaFree(x);
    cudaFree(y);
    return 0;
}
