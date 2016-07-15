
#include <stdio.h>

/**
   GPU用strcpy
   GPUの関数を指定するには__device__をつける
 **/
__device__ void dev_strcpy(char *dst, const char *src) {
    while (*dst++ = *src++);
}

/**
   GPU側エントリ		
**/
__global__ void gen_hello(char *A) {
    dev_strcpy(A, "Hello, World");
}

int main() {
    char *d_hello;

    // ホストでメモリを確保
    char hello[128];

    // GPU側のメモリ（デバイスメモリ）を確保
    cudaMalloc((void**)&d_hello, 128);

    // gen_hello呼び出し
    gen_hello<<<1,1>>>(d_hello);

    // GPU側データの取得
    cudaMemcpy(hello, d_hello, 128, cudaMemcpyDeviceToHost);

    // 確保したメモリを解放
    cudaFree(d_hello);

    // 出力
    puts(hello);
}
