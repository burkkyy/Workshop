#include <iostream>

#define N 268435456

double monotime(){
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec * 1e-9;
}

/*
   This kernel(gpu function) will be ran in parallel
   by N different cuda threads
 */
__global__ void vec_add_gpu(float* a, float* b, float* c){
	int i = blockDim.x * blockIdx.x + threadIdx.x; // get thread number
	c[i] = a[i] + b[i];
}

void vec_add_cpu(float* a, float* b, float* c, const int n){
	for(auto i = 0; i < n; i++){
		c[i] = a[i] + b[i];
	}
}

int main(int argc, char** argv){
	int size = N * sizeof(float);
	
	float* a = new float[N];
	float* b = new float[N];
	float* c = new float[N];

	double start, end, gpu_time, cpu_time;
	
	cudaMallocManaged(&a, size);
	cudaMallocManaged(&b, size);
	cudaMallocManaged(&c, size);
	
	for(int i = 0; i < N; i++){
		a[i] = 1.0f;
		b[i] = 2.0f;
	}
	
	const int threads_per_block = 256;
	const int num_of_blocks = std::ceil(float(N) / threads_per_block);

	start = monotime();	
	
	vec_add_gpu<<< num_of_blocks, threads_per_block >>>(a, b, c);
	cudaDeviceSynchronize(); // wait for all threads to finish
	
	end = monotime();
	gpu_time = end - start;

	start = monotime();
	
	vec_add_cpu(a, b, c, N);
	
	end = monotime();
	cpu_time = end - start;
	
	for(int i = 0; i < N; i++){
		if(c[i] != 3){
			std::cout << "error at " << i << " output: " << c[i] << std::endl;
			exit(-1);
		}
	}

	std::cout << "Success" << std::endl;	
	std::cout << "Results over adding a " << N << " size vector" << std::endl;
	std::cout << "cpu time " << cpu_time << std::endl;
	std::cout << "gpu time " << gpu_time << std::endl;

	cudaFree(a);
	cudaFree(b);
	cudaFree(c);
	return 0;
}

