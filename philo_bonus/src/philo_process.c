
#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

bool get_proc_end(t_simulation *simulation)
{
	int exit_code;

  sem_wait(simulation->sems.proc_end);
  exit_code = simulation->data.end;
  /* if (exit_code != 0) */
		/* print_log("found end bool true\n", simulation->data.id, simulation); */
  sem_post(simulation->sems.proc_end);
	return (exit_code);
}

int set_proc_end(t_simulation *simulation)
{
	sem_wait(simulation->sems.proc_end);
	simulation->data.end = true;
  sem_post(simulation->sems.proc_end);
  return (0);
}

bool take_two_fork(t_simulation *simulation)
{
  if (get_proc_end(simulation))
    return (false);
  if (simulation->data.nb_philos == 1)
  {
		sem_wait(simulation->sems.forks);
		if (!print_log("has taken a fork\n", simulation->data.id, simulation))
		{
  		accurate_sleep(simulation, simulation->data.time.die);
  		sem_post(simulation->sems.forks);
  		return (false);
		}
  }
  sem_wait(simulation->sems.can_i_eat);
  sem_wait(simulation->sems.forks);
  if (get_proc_end(simulation) || am_i_starving(simulation) || !print_log("has taken a fork\n", simulation->data.id, simulation))
  {
    sem_post(simulation->sems.forks);
    sem_post(simulation->sems.can_i_eat);
    return (false);
  }
  if (get_proc_end(simulation) || am_i_starving(simulation) || !print_log("has taken a fork\n", simulation->data.id, simulation))
  {
    sem_post(simulation->sems.forks);
    sem_post(simulation->sems.can_i_eat);
    return (false);
  }
  return (true);
}

bool eating(t_simulation *simulation)
{
	if (!take_two_fork(simulation))
	{
		return (false);
	}
	if (!print_log("is eating\n", simulation->data.id, simulation))
	{
		sem_post(simulation->sems.forks);
		/* printf("%d released a fork\n", simulation->data.id); */
		sem_post(simulation->sems.forks);
		/* printf("%d released a fork\n", simulation->data.id); */
		sem_post(simulation->sems.can_i_eat);
		return (false);
	}
	simulation->data.time.last_meal = get_time();
	/* printf("%d updated last meal = %ld\n", simulation->data.id, simulation->data.time.last_meal); */
	/* printf("%ld about to wait %ld\n", simulation->data.time.last_meal - simulation->data.time.start, simulation->data.time.eat); */
	if (accurate_sleep(simulation, simulation->data.time.eat) < 0)
	{
		sem_post(simulation->sems.forks);
		/* printf("%d released a fork\n", simulation->data.id); */
		sem_post(simulation->sems.forks);
		/* printf("%d released a fork\n", simulation->data.id); */
		sem_post(simulation->sems.can_i_eat);
		return (false);
	}
	sem_post(simulation->sems.forks);
	/* printf("%d released a fork\n", simulation->data.id); */
	sem_post(simulation->sems.forks);
	/* printf("%d released a fork\n", simulation->data.id); */
	sem_post(simulation->sems.can_i_eat);
	simulation->data.meals_limit--; 
	if (simulation->data.meals_limit == 0)
	  sem_post(simulation->sems.fed);
	return (true);
}

bool thinking(t_simulation *simulation)
{
	int exit_code;

	if (!print_log("is thinking\n", simulation->data.id, simulation))
		return (false);
	if (simulation->data.nb_philos % 2 != 0)
	{
			/* printf("%d : ici\n", simulation->data.id); */
		exit_code = accurate_sleep(simulation, simulation->data.time.eat);
		if (exit_code > 0)
			return (true);
		else 
			return (false); 
	}
	else
		usleep(100);
	return (true);
}

bool am_i_starving(t_simulation *simulation)
{
	long int elapsed_time;
	int exit_code;

	elapsed_time = get_time() - simulation->data.time.last_meal;
	/* printf("get_time - last meal = %ld\n", elapsed_time); */
	if ((get_time() - simulation->data.time.last_meal) > simulation->data.time.die)
	{
		print_log("died\n", simulation->data.id, simulation);
		sem_post(simulation->sems.death);
		set_proc_end(simulation);
		return (true);
	}
	return (false);
}

bool sleeping(t_simulation *simulation)
{
	if (am_i_starving(simulation))
		return (false);
	if (!print_log("is sleeping\n", simulation->data.id, simulation))
		return (false);
	if (accurate_sleep(simulation, simulation->data.time.sleep) < 0)
		return (false);
	return (true);
}

int philo_process_routine(t_simulation *simulation)
{
  sem_wait(simulation->sems.start);
  simulation->data.time.start = get_time();
  simulation->data.time.last_meal = simulation->data.time.start;
	/* print_log("started\n", simulation->data.id, simulation); */
	/* while (!is_simulation_over(simulation)) */
	while (1)
	{
		if (get_proc_end(simulation) || am_i_starving(simulation) || !thinking(simulation))
		{
			sem_post(simulation->sems.death);
			break ;
		}
		if (get_proc_end(simulation) || am_i_starving(simulation) || !eating(simulation))
		{
			sem_post(simulation->sems.death);
			break ;
		}
		if (get_proc_end(simulation) || am_i_starving(simulation) || !sleeping(simulation))
		{
			sem_post(simulation->sems.death);
			break ;
			usleep(500);
		}
	}
  /* printf("proc %d leaving philo process routine\n", simulation->data.id); */
	return (0);
}

int philo_process_life(t_simulation *simulation)
{
  init_processes_monitor_thread(simulation);
  philo_process_routine(simulation);
  /* printf("proc %d waiting his monitor thread\n", simulation->data.id); */
  pthread_join(simulation->monitor, NULL);  
  /* printf("proc %d joined monitor thread\n", simulation->data.id); */
  /* printf("%d is about to exit\n", simulation->data.id); */
  simulation_cleanup(simulation, 0);
  return (0);
}
