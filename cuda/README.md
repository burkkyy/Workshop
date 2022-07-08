Random cuda mini tests

CUDA vector addition
--------------------
nvcc vector_add.cu -o vector && time ./vector


CUDA matrix dot product on NxN matrix
-------------------------------------
nvcc sq_mat_dot.cu -o sq_dot && time ./sq_dot

