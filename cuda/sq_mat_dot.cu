#include "cudahelper.hpp"

#define N (1 << 10)

__global__ void dot(float* a, float* b, float* c, const int size){
	int m = blockIdx.y * blockDim.y + threadIdx.y;
	int n = blockIdx.x * blockDim.x + threadIdx.x;
	
	//printf("m: %d n: %d\n", m, n);
	//printf("blockDim.x: %d blockDim.y: %d blockIdx.x: %d blockIdx.y: %d threadIdx.x: %d threadIdx.y: %d\n", blockDim.x, blockDim.y, blockIdx.x, blockIdx.y, threadIdx.x, threadIdx.y);
	
	if(m < N && n < N){
		int temp = 0;
		for(int i = 0; i < size; i++){
			temp += a[m * size + i] * b[i * size + n];
		}
		c[m * size + n] = temp;
	}
}

void dot_cpu(float* a, float* b, float* c, const int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			int temp = 0;
			for(int k = 0; k < size; k++){
				temp += a[i * size + k] * b[k * size + j];
			}
			c[i * size + j] = temp;
		}
	}
}

void check_dot(float* a, float* b, float* c, const int size){
	float ans;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			ans = 0;
			for(int k = 0; k < size; k++){
				ans += a[i * size + k] * b[k * size + j];
			}
			assert(ans == c[i * size + j]);
		}
	}
}

int main(int argc, char** argv){
	double start, end, gpu_time, cpu_time, total_start, total_end, total_time;
	
	total_start = monotime();

	int size = N * N * sizeof(float);
	
	float* a = new float[N*N];
	float* b = new float[N*N];
	float* c = new float[N*N];

	cudaMallocManaged(&a, size);
	cudaMallocManaged(&b, size);
	cudaMallocManaged(&c, size);

	const int threads = 16;
	const int blocks = (N + threads - 1) / threads;
	
	dim3 BLOCKS(blocks, blocks);
	dim3 THREADS(threads, threads);
	
	start = monotime();
	dot<<< BLOCKS, THREADS >>>(a, b, c, N);
	cudaDeviceSynchronize();
	end = monotime();
	gpu_time = end - start;

	check_dot(a, b, c, N);
	P("gpu passed check");

	start = monotime();
	dot_cpu(a, b, c, N);
	end = monotime();
	cpu_time = end - start;

	check_dot(a, b, c, N);
	P("cpu passed check");
	
	total_end = monotime();
	total_time = total_end - total_start;

	P("Success. Results from taking dot prodcut from size " << N << "x" << N << " matrices:");

#define sec
#ifndef sec
	P("gpu time: " << gpu_time << " ns");
	P("cpu time: " << cpu_time << " ns");
	P("total time: " << total_time << " ns");
#else
	P("gpu time: " << gpu_time * 1e-9 << " sec");
	P("cpu time: " << cpu_time * 1e-9 << " sec");
	P("total time: " << total_time * 1e-9 << " sec");
#endif

	cudaFree(a);
	cudaFree(b);
	cudaFree(c);
	return 0;
}

