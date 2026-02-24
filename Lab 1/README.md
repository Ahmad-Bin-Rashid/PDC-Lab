# Lab 1 – Message Passing Interface (MPI)

This lab focuses on **distributed-memory parallel programming** using the
**Message Passing Interface (MPI)**. The objective is to understand how
independent processes communicate using explicit message passing and how
MPI programs scale compared to shared-memory approaches.

The lab includes multiple MPI programs demonstrating process management,
communication latency, collective operations, and performance analysis.

---

## Objectives

- Understand the distributed-memory programming model
- Learn the MPI programming workflow
- Implement parallel programs using MPI
- Measure communication latency using ping-pong benchmarks
- Analyze scalability and speedup of MPI programs
- Compare MPI with shared-memory (Pthreads) implementations

---

## Directory Structure
```
lab1/
│
├── screenshots/
│
├── src/
│ ├── hello_mpi.c
│ ├── ping_pong.c
│ ├── count_mpi.c
│ └── pi_mpi.c
│
├── docs/
│ ├── lab1_report.pdf
| └── lab manual 1a.pdf
| └── lab manual 1b.pdf
|
└── README.md
```

---

## Programs Implemented

- **MPI Hello World**  
  Demonstrates MPI initialization, process ranks, and parallel execution.
- **Ping-Pong Benchmark**  
  Measures round-trip message latency between MPI processes.
- **MPI Counting Program**  
  Distributes computation across processes and combines results using
  collective communication.
- **MPI π Computation**  
  Approximates the value of π using numerical integration in parallel.

---

## Compilation and Execution

### Install MPI
If MPI is not already install in your Linux system, install it using:
```bash
sudo apt update
sudo apt openmpi-bin openmpi-common libopenmpi-dev
```
Verify Installation:
```bash
mpirun --version
```
Should be similar to: mpirun (Open MPI) 4.1.4

### Compile MPI programs
```bash
mpicc -O2 program.c -o program
```

### Run MPI programs
```bash
mpirun -np <num_processes> ./program
```

### For oversubscription:
```bash
mpirun -np <num_processes> --oversubscribe ./program
```

## Key Observations
- MPI enables true parallel execution using multiple processes
- Communication overhead impacts performance at low workloads
- Speedup is non-linear due to synchronization and communication costs
- Oversubscription leads to performance degradation
- MPI scales better than Pthreads for higher process counts

## Report

A detailed report including:
- Execution outputs and screenshots
- Performance tables
- Speedup graphs (TikZ)
- Self-assessment answers
- Reflection and analysis

is available in:
[Lab1 Report (PDF)](report/lab1_report.pdf)
