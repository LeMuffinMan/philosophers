
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
    /* pthread_mutex_lock(&philosopher->data->write_mutex); */
    /* printf("fork %d taken\n", i); */
    /* pthread_mutex_unlock(&philosopher->data->write_mutex); */
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
    if (is_simulation_over(philosopher))
      return (false);
    pthread_mutex_lock(&philosopher->data->write_mutex);
    /* printf("trying to catch fork %d\n", fork_to_catch); */
    pthread_mutex_unlock(&philosopher->data->write_mutex);
    usleep(100);
    exit_code = get_fork_state(philosopher, fork_to_catch);
  }
  return (exit_code);
}

int set_fork(t_philosopher *philosopher, int fork, bool state)
{
  pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
  philosopher->data->forks[fork] = state;
  pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
  return (0);
}

bool take_two_forks(t_philosopher *philosopher) //ajouter une detection de fin par la simu 
{
  int left;
  int right;

  left = philosopher->id;
  right = (philosopher->id + 1) % philosopher->nb_philo;
  if (left > right)
  {
    if (!try_to_catch_fork(philosopher, left))
      return (false);
    if (!try_to_catch_fork(philosopher, right))
    {
      set_fork(philosopher, left, true);
      return (false);
    }
    return (true);
  }
  else
  {
    if (!try_to_catch_fork(philosopher, right))
      return (false);
    if (!try_to_catch_fork(philosopher, left))
    {
      set_fork(philosopher, right, true);
      return (false);
    }
    return (true);
  }
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
