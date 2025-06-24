

# Matrix Multiplication

--- 
## Test: 500x500 MatMul

With Memory Pool, return by value:

- 1.01129s
- 1.03555s
- 1.00671s
- 1.05142s
- 1.01122s

With MemoryPool, return in-place:

- 0.969763s
- 0.947997s
- 0.957851s
- 0.95628s
- 0.950764s


---
# goal

Main
│
├── SystemInfo
│   └── getCacheSizes() → {L1, L2, L3}
│
├── BlockSizePlanner
│   └── compute_block_size(L2_size)
│
├── MemoryPool
│   └── allocate(size, alignment)
│
├── Matrix / Vector
│   ├── static Multiply(C, A, B)
│   └── static MultiplyBlocked(C, A, B, blockSize)
│
└── IK Solver (later)
    └── Uses all preallocated Matrix/Vector buffers