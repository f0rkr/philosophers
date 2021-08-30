# Philosophers dining problem

<img height="500px" width="950px" src="https://cdn.thecollector.com/wp-content/uploads/2020/12/greek-philosophers-presocratics-heraclitus-democritus-pickenoy.jpg">

<strong><i>The dining philosophers problem</i></strong> is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

# Problem introduction:
<img src="https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/DIAGRAM-philosopher-lefty-has-1.jpg">
The Dining Philosopher Problem states that N philosophers seated around a circular table with a large bowl of spaghetti and one fork between each pair of philosopher. Each philosopher is doing one of the three things: eating, sleeping, thinking. While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping. I should state that philosophers aren’t aware of other philosophers status.



The goal here is to create a program that simulate the 3 states of philosophers and log print any change of status as follow:

- **timestamp_in_ms** X has taken a fork
- **timestamp_in_ms** X is eating
- **timestamp_in_ms** X is sleeping
- **timestamp_in_ms** X is thinking
- **timestamp_in_ms** X died

The program need 5 arguments which are:

- **number_of_philosophers[nop]**: is the number of philosophers and also the number of forks.
- **time_to_die[ttd]**: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.
- **time_to_eat[tte]**: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
- **time_to_sleep[tts]**: is in milliseconds and is the time the philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat**: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
A philosopher may eat if he can pick up the two forks adjacent to him. One fork may be picked up by any one of its adjacent followers but not both as it would result in a problem that we will discuss forthcoming.

Visit my blog to read <a href="https://f0rkr.me/dining-philosophers-problem/">more</a>.

# Resources I used:
* [Parallel computing tutorial](https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial)
* [POSIX threads programming](https://hpc-tutorials.llnl.gov/posix/)
* [Thread and C](https://franckh.developpez.com/tutoriels/posix/pthreads/)
* [Condition variables](https://greenteapress.com/thinkos/html/thinkos012.html)
* [Mltiple child process](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphores](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)
