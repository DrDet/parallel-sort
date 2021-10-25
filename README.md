# Parallel quick sort
Simple parallel quick sort implementation using OpenMP.
## Prerequisites
You need to have a compiler compatible with OpenMP and `libomp-dev` package installed.
## Build
```
cmake -B build -DCMAKE_BUILD_TYPE=Release
make -C build
```
## Run
```
build/parsort seq    # run serial version
build/parsort par 8  # run parallel version on 8 threads
```
## Results
Let's compare parallel and serial version. We will sort array of length 10^8 with random integers.

Serial execution:
```
time ./build/parsort seq

# real    0m16,371s
# user    0m16,203s
# sys     0m0,168s
```
Parallel execution:
```
time ./build/parsort par 8

# real    0m8,424s
# user    0m19,659s
# sys     0m0,132s
```

Thus, parallel version is about 2 times faster.
