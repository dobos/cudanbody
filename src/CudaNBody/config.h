#pragma once

#include "cuda_runtime.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

typedef double ttt_t;	// Type of time variables
typedef double var_t;	// Type of variables
typedef double4 vec_t;   // Type of vectors, use 4dim for coalesced memory access
typedef bool bool_t;	// Type of booleans
typedef int int_t;
typedef int2 int2_t;

typedef thrust::host_vector<var_t> host_var_t;
typedef thrust::device_vector<var_t> device_var_t;

typedef thrust::host_vector<vec_t> host_vec_t;
typedef thrust::device_vector<vec_t> device_vec_t;

typedef thrust::host_vector<int_t> host_int_t;
typedef thrust::device_vector<int_t> device_int_t;

typedef thrust::device_vector<int2_t> device_int2_t;

#define NVAR 2			// Number of variables per body (coord, veloc)
#define NPAR 2			// Number of parameters per body
#define NDIM 4			// Number of dimensions, 4 to coalesce memory copies

#define NTILE 256

//#define RK 4			// Runge-Kutta order
//#define RKN 9			// Runge-Kutta-Nystrom order

#define K2 (var_t)0.0002959122082855911025
#define MASS_SUN (var_t)1.9891E+30
#define DT (var_t)0.1

//#define SOFTENING_EPS (var_t)0.00001
