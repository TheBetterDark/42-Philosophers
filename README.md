# 42-Philosophers

## Description

This project is an introduction to threading in C. The goal is to create a simulation of the dining philosophers problem using threads and mutexes. The simulation must be able to handle up to 200 philosophers and must not have any data races. The simulation must also be able to handle philosophers dying and must print the time of death and the philosopher that died.

## Usage

```bash
$> make
$> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments:

- number_of_philosophers: The number of philosophers in the simulation. Must be greater than 1 and less than or equal to 200.
- time_to_die: The time in milliseconds that a philosopher will die if they have not started eating.
- time_to_eat: The time in milliseconds that a philosopher will take to eat.
- time_to_sleep: The time in milliseconds that a philosopher will take to sleep.
- number_of_times_each_philosopher_must_eat: Optional argument. The number of times each philosopher must eat before the simulation ends. If not provided, the simulation will run until a philosopher dies.

## Example

```bash
$> ./philo 5 800 200 200
```

This will run a simulation with 5 philosophers. Each philosopher will die if they have not started eating within 800 milliseconds. Each philosopher will take 200 milliseconds to eat and 200 milliseconds to sleep. This example will run forever and no philosopher should die.

## Rules

- Each philosopher is seated between a fork.
- A philosopher must eat when they have both forks.
- A philosopher must sleep after eating.
- A philosopher must think when they are not eating or sleeping.

## Note

The simulation may not work as expected on low performance machines. The simulation was tested on the following machine:

- Processor: 12th Gen Intel(R) Core(TM) i7-12700
- RAM: 16 GB
