# Lab 0 – Foundations of Parallel Computing

This lab introduces the fundamental concepts of **parallel and concurrent
programming** using threads and processes. The objective is to understand how
modern multicore systems execute programs and how different programming models
affect performance.

The lab focuses on implementing and comparing sequential and parallel versions
of a simple counting and searching problem using C and Python.

---

## Objectives

- Understand the motivation for parallel computing on multicore processors
- Distinguish between processes and threads
- Implement shared-memory parallel programs using POSIX threads (Pthreads)
- Observe race conditions and apply synchronization using mutexes
- Analyze the effect of Python’s Global Interpreter Lock (GIL)
- Measure execution time, speedup, and scalability

---

## Directory Structure

```
lab0/
│
├── src/
│ ├── count_seq.c
│ ├── count_pthread.c
│ ├── search_pthread.c
│ ├── count_seq.py
│ ├── count_threads.py
│ └── count_mp.py
│
├── screenshots/
│
├── report/
│ ├── lab0_report.pdf
│
├── Lab 0 (Manual)
└── README.md
```

---

## Experiments Performed

- Sequential counting in C
- Sequential counting in Python
- Parallel counting using Pthreads (1, 2, 4, 6, 8 threads)
- Parallel counting using Python threading
- Parallel counting using Python multiprocessing
- Parallel search using Pthreads (optional task)
- Performance monitoring using Linux tools

---

## How to Compile and Run

### Compile C programs
```bash
gcc -O2 -pthread file.c -o output
./output
```
### Run Python programs
```bash
python3 file.py
```

---

## Observations

- C implementations significantly outperform Python for CPU-bound tasks
- Pthreads provide speedup but are limited by memory bandwidth and overhead
- Python threading does not improve performance due to the GIL
- Python multiprocessing achieves true parallelism but incurs IPC overhead
- Speedup deviates from ideal linear scaling as predicted by Amdahl’s Law

---

## Key Concepts Demonstrated

- Concurrency vs parallelism
- Shared-memory programming
- Race conditions and mutex-based synchronization
- Performance measurement and analysis
- Limitations of parallel scaling

---

