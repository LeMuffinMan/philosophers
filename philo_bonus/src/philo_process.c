
#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

bool is_simulation_over(t_simulation **simulation)
{
  bool exit_code;

	/* if (get_time() - (*simulation)->data.time.last_meal > (*simulation)->data.time.die) */
	/* { */
		//si une fourchette dans la main la lacher ?
		//un booleen pour chacun
	/* 	sem_post((*simulation)->sems.death); */
	/* 	print_log("%d died\n", (*simulation)->data.id, simulation); */
	/* 	exit(simulation_cleanup(simulation, 0)); //un exit code STARVED ? */
	/* } */
  sem_wait((*simulation)->sems.proc_end);
  exit_code = (*simulation)->data.end;
  sem_post((*simulation)->sems.proc_end);
  /* printf("returned end status = %d\n", (*simulation)->data.end); */
  return (exit_code);
}

int eating(t_simulation **simulation)
{
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", (*simulation)->data.id, simulation);
	if ((*simulation)->data.nb_philos == 1)
	{
		accurate_sleep((*simulation)->data.time.sleep);
		sem_post((*simulation)->sems.forks);
		return (0);
	}
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", (*simulation)->data.id, simulation);
	print_log("is eating\n", (*simulation)->data.id, simulation);
	(*simulation)->data.time.last_meal = get_time() - (*simulation)->data.time.start;
	accurate_sleep((*simulation)->data.time.eat);
	sem_post((*simulation)->sems.forks);
	sem_post((*simulation)->sems.forks);
	(*simulation)->data.meals_limit--;
	if ((*simulation)->data.meals_limit == 0)
	  sem_post((*simulation)->sems.fed);
	return (0);
}

int philo_process_routine(t_simulation **simulation)
{
	//le start est pas synchro
  sem_wait((*simulation)->sems.start);
  (*simulation)->data.time.start = get_time();
	print_log("started\n", (*simulation)->data.id, simulation);
  (*simulation)->data.time.last_meal = (*simulation)->data.time.start;
	while (!is_simulation_over(simulation))
	{
		/* eating(simulation); */
		print_log("is sleeping\n", (*simulation)->data.id, simulation);
		accurate_sleep((*simulation)->data.time.sleep);
  	if (is_simulation_over(simulation))
  		break ;
		print_log("is thinking\n", (*simulation)->data.id, simulation);
		/* accurate_sleep(100); */
	}
  /* printf("proc %d leaving philo process routine\n", (*simulation)->data.id); */
	return (0);
}

int philo_process_life(t_simulation **simulation)
{
  init_processes_monitor_thread(simulation);
  philo_process_routine(simulation);
  /* printf("proc %d waiting his monitor thread\n", (*simulation)->data.id); */
  pthread_join((*simulation)->threads.proc_monitor, NULL);  
  /* printf("proc %d joined monitor thread\n", (*simulation)->data.id); */
  /* printf("%d is about to exit\n", (*simulation)->data.id); */
  simulation_cleanup(simulation, 0);
  return (0);
}
