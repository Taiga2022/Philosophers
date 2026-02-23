*This project has been created as part of the 42 curriculum by tshimizu.*

# Philosophers

## Description

This project implements a solution to the classic **Dining Philosophers Problem**, a fundamental concurrency challenge in computer science.

The simulation involves N philosophers sitting at a round table, each alternating between thinking, eating, and sleeping. To eat, a philosopher must acquire two forks (one on their left and one on their right), but forks are shared resources that can only be held by one philosopher at a time. The challenge is to prevent deadlock (all philosophers waiting indefinitely) and starvation (a philosopher never getting to eat) while detecting when a philosopher "dies" from not eating within a specified time limit.

This implementation uses **POSIX threads** (`pthread`) and **mutex locks** to manage concurrency, with a dedicated monitor thread to detect termination conditions.

## Instructions

### Compilation

Build the project using the provided Makefile:

```bash
make
```

This generates the `philo` executable in the project root.

### Execution

Run the program with the following syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**

1. `number_of_philosophers`: Number of philosophers (and forks) at the table
2. `time_to_die`: Time in milliseconds before a philosopher dies if they haven't eaten
3. `time_to_eat`: Time in milliseconds a philosopher spends eating
4. `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
5. `[number_of_times_each_philosopher_must_eat]` (optional): Program terminates when all philosophers have eaten this many times

**Example:**

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same, but stop after each philosopher eats 8 times
./philo 5 800 200 200 8
```

### Output Format

The program outputs timestamped actions for each philosopher

```
123 1 has taken a fork
123 1 is eating
323 1 is sleeping
323 1 is thinking
```

Format: `[timestamp_ms] [philosopher_id] [action]`

## Resources

### Classic References

- [Philosophersを理解するためのスライド](https://docs.google.com/presentation/d/12-lAykLu-RVACE1gI2aP-uEYZoOaeeFVYGh8W4ttTNw/edit?slide=id.gd4524b1be8_0_253&pli=1#slide=id.gd4524b1be8_0_253)

### AI Usage

AI tools were used for the following tasks in this project:

- **Code structure planning**: Generating initial outlines for thread synchronization architecture
- **Debugging assistance**: Analyzing race condition scenarios and suggesting mutex placement strategies

AI was **not** used for:
- Core algorithm implementation (deadlock prevention, monitoring logic)
- Thread lifecycle management code
- Mutex synchronization primitives

## Technical Choices

### Deadlock Prevention Strategy

This implementation prevents deadlock using an **asymmetric fork acquisition** approach

- **Even-numbered philosophers**: Acquire right fork first, then left fork
- **Odd-numbered philosophers**: Wait briefly (`usleep(1000)`), then acquire right fork first, then left fork

This strategy breaks the circular wait condition by ensuring not all philosophers can simultaneously hold one fork while waiting for another. The initial delay for odd-numbered philosophers reduces contention during startup, preventing the scenario where all philosophers grab their right fork at once.

### Thread Architecture

- **N philosopher threads**: Each executes the think-eat-sleep cycle independently
- **1 monitor thread**: Continuously checks for death conditions and completion status
- **Mutex protection**: Individual mutexes for each fork, plus global mutexes for printing, death flag, and per-philosopher meal state

### Time Management

- `gettimeofday()` for millisecond-precision timestamps
- `usleep()` for precise sleep intervals
- Monitor thread checks `last_meal` timestamps against `time_to_die` threshold

## Implementation Status

Core features:

- ✅ Argument parsing and validation
- ✅ Thread creation and lifecycle management
- ✅ Fork acquisition/release with mutex protection
- ✅ Philosopher routine (think-eat-sleep loop)
- ✅ Timestamped action logging
- ✅ Monitor thread for death detection
- ✅️ Optional meal count termination (partial implementation)
