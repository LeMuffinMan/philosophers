*This project has been created as part of the 42 curriculum by oelleaum.*

# Philosophers — I never thought philosophy would be so deadly

A simulation of the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), implemented in two versions: threads + mutexes (mandatory), and processes + semaphores (bonus).

---

## Description

N philosophers sit at a round table with N forks, one between each pair of neighbors. Each philosopher cycles through three states: **thinking**, **eating**, **sleeping**. To eat, a philosopher must hold both adjacent forks simultaneously.

The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten the required number of times (optional argument).

**Constraints:**
- No data races — all shared state protected by mutexes (mandatory) or semaphores (bonus)
- Death must be logged within 10ms of actual death
- No global variables
- Zero memory leaks

**Mandatory (`philo/`)** — threads + mutexes:
- Each philosopher is a `pthread` thread
- Each fork is protected by a `pthread_mutex`
- A dedicated monitor thread checks for starvation

**Bonus (`philo_bonus/`)** — processes + semaphores:
- Each philosopher is a separate `fork()`ed process
- Forks are represented by a shared semaphore (count = N)
- Death monitoring runs as a thread within each philosopher's process

---

## Instructions

### Dependencies

```bash
sudo apt install make gcc   # Debian/Ubuntu
sudo pacman -S make gcc     # Arch
```

### Build

```bash
# Mandatory (threads + mutexes)
cd philo && make

# Bonus (processes + semaphores)
cd philo_bonus && make
```

### Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` (ms) | Time before a philosopher starves if they haven't started eating |
| `time_to_eat` (ms) | Time it takes to eat (holds 2 forks) |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional — stops simulation when all have eaten this many times |

### Examples

```bash
# 5 philosophers, die in 800ms, eat in 200ms, sleep in 200ms
./philo 5 800 200 200

# Same, but stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: 1 philosopher (will always die — only one fork)
./philo 1 800 200 200
```

### Output format

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

---

## Architecture

```
philo/src/
├── philo.c                   — entry point, argument validation
├── philosophers_routine.c    — philosopher thread lifecycle
├── monitor_routine.c         — death monitoring thread
├── forks.c                   — fork acquisition/release logic
├── init/                     — data, mutex, philosopher struct setup
└── utils/                    — getters, setters, timestamps, prints, cleanup
```

```
philo_bonus/src/
├── philo_bonus.c             — entry point
├── philo_process_bonus.c     — philosopher process lifecycle
├── threads_bonus.c           — monitoring thread per process
├── forks_bonus.c             — semaphore-based fork acquisition
├── init/                     — semaphore and data initialization
└── utils/                    — getters/setters, time, prints, cleanup
```

---

## Resources

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [sem_overview — Linux man page](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [gettimeofday — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
