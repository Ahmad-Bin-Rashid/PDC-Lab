# Lab 2: Message Passing Interface (MPI)

> **Parallel & Distributed Computing — Semester 6**

## Overview

This lab covers distributed-memory parallel programming using the **Message Passing Interface (MPI)**. It explores process-based parallelism, inter-process communication (`MPI_Send`, `MPI_Recv`, `MPI_ANY_SOURCE`), and performance scalability.

## Prerequisites

- GCC compiler
- OpenMPI (`mpicc`, `mpirun`)

```bash
# Ubuntu/Debian
sudo apt install openmpi-bin libopenmpi-dev

# Arch
sudo pacman -S openmpi
```

## Build & Run

Compile any program with `mpicc` and run with `mpirun`:

```bash
cd src

# Compile
mpicc -o exercise1 exercise1.c

# Run with N processes
mpirun -np 4 ./exercise1
```

## Programs

| # | File | Description |
|---|------|-------------|
| 1 | [`send_recv.c`](src/send_recv.c) | Point-to-point communication — Process 2 sends a double array to Process 4 |
| 2 | [`exercise1.c`](src/exercise1.c) | Parallel sum of 1–1000 using master-worker pattern with `MPI_Send`/`MPI_Recv` |
| 3 | [`exercise2.c`](src/exercise2.c) | Array transfer — workers send to master with **fixed source** rank |
| 4 | [`exercise3.c`](src/exercise3.c) | Array transfer — master receives with `MPI_ANY_SOURCE` (non-deterministic order) |

## Screenshots

| Exercise 1 | Exercise 2 | Exercise 3 |
|:---:|:---:|:---:|
| ![Exercise 1](screenshots/exercise%201.png) | ![Exercise 2](screenshots/exercise%202.png) | ![Exercise 3](screenshots/exercise%203.png) |

## Performance Results

### Parallel Sum (Exercise 1)

| Processes | Time (s) | Speedup |
|:---------:|:--------:|:-------:|
| 1 | 0.3267 | 1.00x |
| 2 | 0.1301 | 2.51x |
| 3 | 0.1078 | 3.03x |
| 4 | 0.0923 | 3.54x |
| 5 | 0.0825 | 3.96x |
| 6 | 0.0742 | 4.40x |
| 8 | 0.0956 | 3.42x |

### Parallel π Computation

| Processes | Time (s) | Speedup |
|:---------:|:--------:|:-------:|
| 1 | 5.6752 | 1.00x |
| 2 | 2.7317 | 2.08x |
| 3 | 2.5470 | 2.23x |
| 4 | 2.0729 | 2.74x |
| 6 | 1.8502 | 3.07x |
| 8 | 1.7154 | 3.31x |
| 10 | 2.5837 | 2.20x |

> Speedup degrades beyond 6–8 processes due to oversubscription and communication overhead.

## Key Takeaways

- MPI provides better scalability than Pthreads for larger process counts
- `MPI_ANY_SOURCE` enables non-deterministic message reception (flexible but harder to debug)
- Communication overhead limits linear speedup — π computation scales better due to higher compute-to-communicate ratio
- Oversubscription causes performance degradation at high process counts

## Project Structure

```
Lab 2/
├── README.md
├── docs/
│   └── Lab2 Report              # lab report
├── screenshots/
│   ├── exercise 1.png
│   ├── exercise 2.png
│   └── exercise 3.png
└── src/
    ├── send_recv.c           # Point-to-point demo
    ├── exercise1.c           # Parallel sum
    ├── exercise2.c           # Array send (fixed source)
    └── exercise3.c           # Array send (MPI_ANY_SOURCE)
```
