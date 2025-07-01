
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

int release_forks(t_simulation *simulation, sem_t *forks, int forks_in_hand)
{
	while (forks_in_hand > 0)
	{
		sem_post(forks);
		/* print_log("has released a fork\n", simulation->data.id, simulation); */
		forks_in_hand--;
	}
	return (0);
}

int take_two_fork(t_simulation *simulation)
{
  /* if (get_proc_end(simulation) || am_i_starving(simulation)) */
  /*   return (0); */
  sem_wait(simulation->sems.forks);
  if (!print_log("has taken a fork\n", simulation->data.id, simulation) || get_proc_end(simulation) || am_i_starving(simulation))
  	return (-1);
  usleep(100);
  sem_wait(simulation->sems.forks);
  if (!print_log("has taken a fork\n", simulation->data.id, simulation) || get_proc_end(simulation) || am_i_starving(simulation))
  	return (-2);
  return (2);
}

int one_fork_case(t_simulation *simulation)
{
	sem_wait(simulation->sems.forks);
  print_log("has taken a fork\n", simulation->data.id, simulation);
  while(!am_i_starving(simulation))
  	usleep(500);
  /* print_log("died\n", simulation->data.id, simulation); */
  simulation->data.exit_code = 1;
  sem_post(simulation->sems.death);
  return (-1);
}

bool eating(t_simulation *simulation)
{
	int forks_in_hand;

  if (simulation->data.nb_philos == 1)
		return (one_fork_case(simulation));
	/* sem_wait(simulation->sems.can_i_eat); */
	/* printf("can i eat -1\n"); */
	forks_in_hand = take_two_fork(simulation);
	if (forks_in_hand <= 0)
	{
		release_forks(simulation, simulation->sems.forks, forks_in_hand * -1);
		sem_post(simulation->sems.can_i_eat);
		return (false);
	}
	simulation->data.time.last_meal = get_time();
	if (!print_log("is eating\n", simulation->data.id, simulation))
	{
		/* sem_post(simulation->sems.can_i_eat); */
		release_forks(simulation, simulation->sems.forks, forks_in_hand);
		return (false);
	}
	if (accurate_sleep(simulation, simulation->data.time.eat) < 0)
	{
		/* sem_post(simulation->sems.can_i_eat); */
		release_forks(simulation, simulation->sems.forks, forks_in_hand);
		return (false);
	}
	/* sem_post(simulation->sems.can_i_eat); */
	/* printf("can i eat +1\n"); */
	release_forks(simulation, simulation->sems.forks, forks_in_hand);
	simulation->data.meals_limit--; 
	if (simulation->data.meals_limit == 0)
	  sem_post(simulation->sems.fed);
	return (true);
}

bool thinking(t_simulation *simulation)
{
	int exit_code;
	long int last_meal_time_elapsed;
	long int time_until_starvation;
	long int think_time;

	last_meal_time_elapsed = get_time() - simulation->data.time.last_meal;
	time_until_starvation = simulation->data.time.die - last_meal_time_elapsed;
	if (!print_log("is thinking\n", simulation->data.id, simulation))
	{
		/* printf("%d la\n", simulation->data.id); // blocage ici */
		return (false);
	}
  if (simulation->data.nb_philos % 2 != 0)
  {
    think_time = simulation->data.time.eat;
		if (simulation->data.time.sleep < simulation->data.time.eat &&
			simulation->data.time.eat * 2 - simulation->data.time.sleep > time_until_starvation &&
			simulation->data.time.sleep + simulation->data.time.eat < simulation->data.time.die)
		{
			think_time = simulation->data.time.die;
  		if (accurate_sleep(simulation, think_time) < 0)
    		return (false);
  	}
	}
  else
  {
    think_time = simulation->data.time.eat / 2;
		if (simulation->data.time.sleep < simulation->data.time.eat &&
			simulation->data.time.eat - simulation->data.time.sleep > time_until_starvation &&
			simulation->data.time.sleep + simulation->data.time.eat < simulation->data.time.die)
		{
			think_time = simulation->data.time.die;
  		if (accurate_sleep(simulation, think_time) < 0)
    		return (false);
  	}
	}
	return (true);
}

bool am_i_starving(t_simulation *simulation)
{
	int exit_code;

	/* if (simulation->data.id == 2) */
	/* 	printf("%ld | time_since_last_meal = %ld | simulation->data.time.die = %ld\n", get_time() - simulation->data.time.start, get_time() - simulation->data.time.last_meal, simulation->data.time.die); */
	if ((get_time() - simulation->data.time.last_meal) > simulation->data.time.die)
	{
  	/* printf("%ld %d died !\n", get_time() - simulation->data.time.start, simulation->data.id); */
		simulation->data.exit_code = get_time() - simulation->data.time.start;
		/* printf("%ld %d ici\n", get_time() - simulation->data.time.start, simulation->data.id); */
			/* printf("%d philo constat dying = %ld\n", simulation->data.id, get_time() - simulation->data.time.start); */
		sem_post(simulation->sems.death);
		/* printf("ici\n"); */
		return (true);
	}
	return (false);
}

bool sleeping(t_simulation *simulation)
{

	if (!print_log("is sleeping\n", simulation->data.id, simulation))
		return (false);
	if (accurate_sleep(simulation, simulation->data.time.sleep) < 0)
		return (false);
	return (true);
}

int philo_process_routine(t_simulation *simulation)
{
  sem_wait(simulation->sems.start);
  if (simulation->data.id % 2 != 0)
  {
  	print_log("is thinking\n", simulation->data.id, simulation);
  	accurate_sleep(simulation, simulation->data.time.eat);
  }
	/* print_log("started\n", simulation->data.id, simulation); */
	/* while (!is_simulation_over(simulation)) */
	while (1)
	{
		if (!eating(simulation) || get_proc_end(simulation) || am_i_starving(simulation))
			break ;
		if (!sleeping(simulation) || get_proc_end(simulation) || am_i_starving(simulation))
			break ;
		if (am_i_starving(simulation))
			break ;
		if (!thinking(simulation) || get_proc_end(simulation) || am_i_starving(simulation))
			break ;
		usleep(500);
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
  /* printf("exit_code child %d = %d\n", simulation->data.id, simulation->data.exit_code); */
  simulation_cleanup(simulation, 0);
  return (simulation->data.exit_code);
}
