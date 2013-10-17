# Compilers
NVCC   = nvcc
CXX    = g++
LINK   = $(NVCC)

# Flags
COMMONFLAGS = -O2
NVCCFLAGS   = --compiler-options -fno-strict-aliasing -arch sm_21
CXXFLAGS    = -fno-strict-aliasing
CFLAGS      = -g -fno-strict-aliasing

# Paths
INCLUDES    = -I. -I/usr/local/cuda-5.0/include/
LIBS        = -L/usr/local/cuda-5.0/lib64
BIN         = bin/Release
CUDANBODY   = src/CudaNBody

#Build rules
all : CudaNBody

CudaNBody : CudaNBody.o euler.o integrator.o nbody.o nbody_exception.o ode.o options.o rungekutta.o rungekuttanystrom.o util.o
	$(LINK) $(LIBS) -o $(BIN)/CudaNBody $(BIN)/CudaNBody.o $(BIN)/euler.o $(BIN)/integrator.o $(BIN)/nbody.o $(BIN)/nbody_exception.o $(BIN)/ode.o $(BIN)/options.o $(BIN)/rungekutta.o $(BIN)/rungekuttanystrom.o $(BIN)/util.o

CudaNBody.o : $(CUDANBODY)/main.cpp
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/CudaNBody.o -c $< 

euler.o : $(CUDANBODY)/euler.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/euler.o -c $<

integrator.o : $(CUDANBODY)/integrator.cpp
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/integrator.o -c $<

nbody.o : $(CUDANBODY)/nbody.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/nbody.o -c $<

nbody_exception.o : $(CUDANBODY)/nbody_exception.cpp
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/nbody_exception.o -c $<

ode.o : $(CUDANBODY)/ode.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/ode.o -c $<

options.o : $(CUDANBODY)/options.cpp
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/options.o -c $<

rungekutta.o : $(CUDANBODY)/rungekutta.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/rungekutta.o -c $<

rungekuttanystrom.o : $(CUDANBODY)/rungekuttanystrom.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/rungekuttanystrom.o -c $<

util.o : $(CUDANBODY)/util.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -o $(BIN)/util.o -c $<



clean:
	rm -f $(BIN)
