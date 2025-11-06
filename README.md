
# PHILOSOPHERS

## 📖 About

"philosophers" is a project at 42 Madrid that involves solving the famous "Dining Philosophers Problem" using multithreading and synchronization mechanisms. This project introduces concurrent programming, thread management, mutexes, and teaches how to handle shared resources and avoid deadlocks in a systematic way.

The goal is to implement a simulation where philosophers sitting around a circular table alternate between eating, thinking, and sleeping, while sharing forks and ensuring no philosopher dies of starvation.

## 🎯 Objectives

- Understanding and implementing multithreading with pthreads
- Learning about synchronization mechanisms (mutexes, semaphores)
- Managing shared resources and preventing race conditions
- Implementing deadlock and starvation prevention strategies
- Handling timing constraints and thread lifecycle management
- Managing edge cases in concurrent programming

## 📋 Function Overview

<details>
<summary><strong>philo</strong></summary>

### Concepts

**Description:** Simulation of the Dining Philosophers Problem using threads and mutexes  
**Usage:** `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`  
**Behavior:** Each philosopher alternates between eating, thinking, and sleeping  

```c
int main(int argc, char **argv);
```

### Use of threads and synchronization
The implementation of **philosophers** requires creating multiple threads and managing shared resources. For this, POSIX threads and synchronization primitives are used:

The main functions and concepts are:

- **`pthread_create()`** ➜ Creates a new thread that executes a specified function.

```c
pthread_create(&thread_id, NULL, philosopher_routine, &philosopher_data);
```

- **`pthread_mutex_lock()`** / **`pthread_mutex_unlock()`** ➜ Locks and unlocks a mutex to protect shared resources.

```c
pthread_mutex_lock(&fork_mutex);
// Critical section
pthread_mutex_unlock(&fork_mutex);
```

- **`pthread_join()`** ➜ Waits for a thread to terminate and collects its return value.

```c
pthread_join(thread_id, NULL);
```

- **`usleep()`** ➜ Suspends execution for microsecond intervals to simulate time passing.

```c
usleep(time_to_eat * 1000); // Convert ms to microseconds
```

- **`gettimeofday()`** ➜ Gets the current time to track philosopher states and detect deaths.

```c
gettimeofday(&current_time, NULL);
```

These functions are essential for implementing **philosophers**, as they allow concurrent execution, resource protection, and precise timing control.

</details>

<details>
<summary><strong>Arguments and Functioning</strong></summary>

### Program Arguments

- **`number_of_philosophers`**: The number of philosophers (and forks)
- **`time_to_die`**: Time in milliseconds a philosopher can survive without eating
- **`time_to_eat`**: Time in milliseconds it takes for a philosopher to eat
- **`time_to_sleep`**: Time in milliseconds a philosopher spends sleeping
- **`[number_of_times_each_philosopher_must_eat]`**: Optional argument for simulation end condition

### Simulation Rules

- Philosophers sit in a circle with one fork between each pair
- A philosopher needs both adjacent forks to eat
- After eating, philosophers put down forks and start sleeping
- After sleeping, philosophers start thinking
- The simulation stops when a philosopher dies or all have eaten enough times

### Output Format

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

</details>

## 🚀 Installation & Structure

<details>
<summary><strong>📥 Download & Compilation</strong></summary>
    
<br>

```bash
# Clone the repository
git clone https://github.com/ravazque/philosophers.git
cd philosophers

# Compile the program
make

# Clean object files
make clean

# Clean everything including executable
make fclean

# Recompile everything
make re

# Run the program
./philo 5 800 200 200 [5]
```

<br>

</details>

<details>
<summary><strong>📁 Project Structure</strong></summary>

<br>

```
philosophers/
├──┬ include/
│  └── philo.h                          # Header file with prototypes and structures
├──┬ src/
│  ├── init.c                           # Data initialization, philosophers setup and mutex creation
│  ├── monitor.c                        # Death detection, meal counting and simulation monitoring
│  ├── parsing.c                        # Argument validation and positive number checking
│  ├── philo.c                          # Main program, thread creation and time utilities
│  ├── routine.c                        # Philosopher lifecycle (thinking, eating, sleeping)
│  └── utils.c                          # Helper functions (printing, cleanup, error messages)
├── Makefile                            # Compilation rules
└── README.md                           # Project documentation
```

<br>

</details>

## 💡 Key Learning Outcomes

The philosophers project teaches advanced concurrent programming concepts:

- **Multithreading**: Understanding pthread creation, management, and synchronization
- **Mutex Operations**: Learning to protect shared resources and prevent race conditions
- **Deadlock Prevention**: Implementing strategies to avoid circular waiting and deadlocks
- **Timing Management**: Precise control of thread execution timing and state monitoring
- **Resource Sharing**: Managing concurrent access to limited resources (forks)
- **Thread Safety**: Writing code that works correctly in multithreaded environments

## ⚙️ Technical Specifications

- **Language**: C (C90 standard)
- **Compiler**: cc with flags `-Wall -Wextra -Werror -pthread`
- **Threading Library**: POSIX threads (pthreads)
- **Synchronization**: Mutexes for fork protection and state management
- **Timing Functions**: gettimeofday(), usleep() for precise timing control
- **Memory Management**: Proper cleanup of threads and mutex resources
- **Platform**: UNIX-like systems (Linux, macOS)
- **Output**: Thread-safe printing with timestamp precision

---

> [!NOTE]
> This project serves as an introduction to concurrent programming and demonstrates proficiency in multithreading, synchronization, and deadlock prevention concepts.
