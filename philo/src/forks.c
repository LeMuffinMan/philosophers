
#include "philo.h"
#include <pthread.h>
#include <unistd.h>

bool get_fork_state(t_philosopher *philosopher, int i)
{
  bool exit_code;
  exit_code = false;
  pthread_mutex_lock(&philosopher->data->forks_mutex[i]);
  if (philosopher->data->forks[i] == true)
  {
    /* printf("fork %d taken\n", i); */
    exit_code = true;
    philosopher->data->forks[i] = false;
  }
  pthread_mutex_unlock(&philosopher->data->forks_mutex[i]);
  return (exit_code);
}

int try_to_catch_fork(t_philosopher *philosopher, int fork_to_catch)
{
  int exit_code;

  exit_code = get_fork_state(philosopher, fork_to_catch);
  while (!exit_code)
  {
    usleep(100);
    exit_code = get_fork_state(philosopher, fork_to_catch);
  }
  return (exit_code);
}

bool take_two_forks(t_philosopher *philosopher)
{
  int left;
  int right;

  left = philosopher->id;
  right = (philosopher->id + 1) % philosopher->nb_philo;
  if (left > right)
  {
    try_to_catch_fork(philosopher, left);
    try_to_catch_fork(philosopher, right);
    return (true);
  }
  else
  {
    try_to_catch_fork(philosopher, right);
    try_to_catch_fork(philosopher, left);
    return (true);
  }
}

int set_fork(t_philosopher *philosopher, int fork, bool state)
{
  pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
  philosopher->data->forks[fork] = state;
  pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
}

int release_forks(t_philosopher *philosopher)
{
  int left;
  int right;
  bool exit_code;

  left = philosopher->id;
  right = (philosopher->id + 1) % philosopher->nb_philo;
  if (left > right)
  {
    set_fork(philosopher, left, true);
    set_fork(philosopher, right, true);
  }
  else
  {
    set_fork(philosopher, right, true);
    set_fork(philosopher, left, true);
  }
  return (0);
}
