
#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

bool should_i_stop(t_simulation *simulation)
{
	long int elapsed_time;
	int exit_code;

	if (get_time() - simulation->data.time.last_meal > simulation->data.time.die)
	{
		print_log("died\n", simulation->data.id, simulation);
		sem_post(simulation->sems.death);
		return (true);
	}
  sem_wait(simulation->sems.proc_end);
  exit_code = simulation->data.end;
  sem_post(simulation->sems.proc_end);
	return (false);
}

bool is_simulation_over(t_simulation *simulation)
{
  bool exit_code;

  sem_wait(simulation->sems.proc_end);
  exit_code = simulation->data.end;
  sem_post(simulation->sems.proc_end);
  if (exit_code)
  	return (exit_code);
  else
  	return (should_i_stop(simulation));
}

int eating(t_simulation *simulation)
{
	sem_wait(simulation->sems.forks);
	print_log("has taken a fork\n", simulation->data.id, simulation);
	if (simulation->data.nb_philos == 1)
	{
		if (accurate_sleep(simulation, simulation->data.time.die) == SIMULATION_END)
		{
			sem_post(simulation->sems.forks);
			return (SIMULATION_END); //exit_code ?
		}
	}
	sem_wait(simulation->sems.forks);
	print_log("has taken a fork\n", simulation->data.id, simulation);
	print_log("is eating\n", simulation->data.id, simulation);
	simulation->data.time.last_meal = get_time();
	simulation->data.meals_limit--; //pas a la fin du repas ??
	if (simulation->data.meals_limit == 0)
	  sem_post(simulation->sems.fed);
	/* printf("%d updated last meal = %ld\n", simulation->data.id, simulation->data.time.last_meal); */
	if (accurate_sleep(simulation, simulation->data.time.eat) == SIMULATION_END)
		return (SIMULATION_END);
	sem_post(simulation->sems.forks);
	sem_post(simulation->sems.forks);
	return (0);
}

int thinking(t_simulation *simulation)
{
	print_log("is thinking\n", simulation->data.id, simulation);
	if (simulation->data.nb_philos % 2 != 0)
	{
		if (accurate_sleep(simulation, simulation->data.time.eat) == SIMULATION_END)
			return (SIMULATION_END);
	}
	return (0);
}

int philo_process_routine(t_simulation *simulation)
{
	//le start est pas synchro
  sem_wait(simulation->sems.start);
  simulation->data.time.start = get_time();
  simulation->data.time.last_meal = simulation->data.time.start;
  if (simulation->data.id % 2 != 0)
		accurate_sleep(simulation, simulation->data.time.eat);
	/* print_log("started\n", simulation->data.id, simulation); */
	while (!is_simulation_over(simulation))
	{
		if (thinking(simulation) == SIMULATION_END)
			break ;
		if (eating(simulation) == SIMULATION_END || is_simulation_over(simulation))
			break ;
		print_log("is sleeping\n", simulation->data.id, simulation);
		accurate_sleep(simulation, simulation->data.time.eat);
  	if (is_simulation_over(simulation))
  		break ;
		/* print_log("is thinking\n", simulation->data.id, simulation); */
		/* accurate_sleep(simulation, 100); */
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
