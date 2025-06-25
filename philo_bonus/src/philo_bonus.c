
#include "philo_bonus.h"
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

void unlink_shared_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
}

int simulation_end_unlink_close_free(t_simulation **simulation, int exit_code)
{
  sem_close((*simulation)->sems.forks);
  sem_close((*simulation)->sems.print);
  sem_close((*simulation)->sems.death);
  sem_close((*simulation)->sems.fed);
  sem_close((*simulation)->sems.start);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	free(*simulation);
	return (exit_code);
}

int is_simulation_over(t_simulation **simulation)
{
  int exit_code;

  sem_wait((*simulation)->sems.philo_end);
  exit_code = (*simulation)->data.end;
  sem_post((*simulation)->sems.philo_end);
  return (exit_code);
}

int eating(t_simulation **simulation)
{
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", simulation);
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", simulation);
	print_log("is eating\n", simulation);
	(*simulation)->time.last_meal = get_time() - (*simulation)->time.start;
	accurate_sleep((*simulation)->time.eat);
	sem_post((*simulation)->sems.forks);
	sem_post((*simulation)->sems.forks);
	(*simulation)->data.meals_limit--;
	if ((*simulation)->data.meals_limit == 0)
	  sem_post((*simulation)->sems.fed);
	return (0);
}
int philo_process_routine(t_simulation **simulation)
{
  sem_wait((*simulation)->sems.start);
  (*simulation)->time.start = get_time();
  (*simulation)->time.last_meal = (*simulation)->time.start;
	while (!is_simulation_over(simulation))
	{
		eating(simulation);
		print_log("is sleeping\n", simulation);
		accurate_sleep((*simulation)->time.sleep);
		print_log("is thinking\n", simulation);
		accurate_sleep(100);
	}
	return (0);
}

void *philo_monitor_thread(void *args)
{
  t_simulation *simulation;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.simulation_end);
  sem_wait(simulation->sems.philo_end);
  simulation->data.end = true;
  sem_post(simulation->sems.philo_end);
  return (0);
}

int init_processes_thread_and_sem(t_simulation **simulation)
{
	(*simulation)->sems.philo_end = sem_open("/philo_philo_end", O_CREAT | O_EXCL, 0644, 1);
	if ((*simulation)->sems.philo_end == SEM_FAILED)
	{
    //revoir le return ici
		return (init_simulation_print_error_and_free("Semaphore init failed\n", SEM_ERROR, simulation));
	}
  (*simulation)->data.end = false;
  if (pthread_create(&(*simulation)->threads.philo_monitor, NULL, philo_monitor_thread, &simulation) != 0)
  {
    //revoir le retrun
    /* return (wait_close_unlink_free(simulation, 0, (*simulation)->data.id, THREAD_ERROR)); */
    return (THREAD_ERROR);
  }
  return (0);
}

int init_processes(t_simulation **simulation)
{
  int exit_code;

  (*simulation)->pids.philos = malloc(sizeof(pid_t) * (*simulation)->data.nb_philos);
  if (!(*simulation)->pids.philos)
    return (simulation_end_unlink_close_free(simulation, MALLOC_ERROR));
  (*simulation)->data.id = 1;
  while ((*simulation)->data.id <= (*simulation)->data.nb_philos)
  {
    (*simulation)->pids.philos[(*simulation)->data.id - 1] = fork();
    if ((*simulation)->pids.philos[(*simulation)->data.id - 1] < 0)
    {
      /* return (wait_close_unlink_free(data, 0, (*simulation)->data.id, FORK_ERROR)); */
      return (FORK_ERROR);
    }
    if ((*simulation)->pids.philos[(*simulation)->data.id - 1] == 0)
    {
      init_processes_thread_and_sem(simulation);
      philo_process_routine(simulation);
      pthread_join((*simulation)->threads.philo_monitor, NULL);  
      /* close_free_philo_data(simulation); */
      exit (0);
    }
    (*simulation)->data.id++;
  }
  return (0);
}

void *simulation_death_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.death);
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    sem_post(simulation->sems.fed);
    i++;
  }
  return (NULL);
}

void *simulation_fed_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  simulation = (t_simulation *)args;
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    sem_wait(simulation->sems.fed);
    i++;
  }
  sem_post(simulation->sems.death);
  return (NULL);
}

int init_monitor(t_simulation **simulation)
{
  (*simulation)->pids.monitor = fork();
  if ((*simulation)->pids.monitor < 0)
  {
    //fork error
    return (FORK_ERROR);
  }
  if ((*simulation)->pids.monitor == 0)
  {
    if (pthread_create(&(*simulation)->threads.simulation_death_monitor, NULL, simulation_death_monitor_thread, &simulation) != 0)
    {
      //error
      return (THREAD_ERROR);
    }
    if (pthread_create(&(*simulation)->threads.simulation_fed_monitor, NULL, simulation_fed_monitor_thread, &simulation) != 0)
    {
      //error
      return (THREAD_ERROR);
    }
    pthread_join((*simulation)->threads.simulation_death_monitor, NULL);
    pthread_join((*simulation)->threads.simulation_fed_monitor, NULL);
    sem_wait((*simulation)->sems.simulation_end);
    (*simulation)->data.end = true;
    sem_post((*simulation)->sems.simulation_end);
  }
  return (0);
}

int main (int ac, char **av)
{
  t_simulation *simulation;
  int exit_code;

  simulation = NULL;
  if (check_user_inputs(ac))
    return (INVALID_ARG);
  exit_code = are_valids_args(av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_simulation(&simulation, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_shared_semaphores(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_processes(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_monitor(&simulation);
	if (exit_code)
	  return (exit_code);
	/* exit_code = wait_philos(&simulation); */
	if (exit_code)
	  return (exit_code);
  /* return (wait_close_unlink_free(simulation)); */
  return (0);
}
