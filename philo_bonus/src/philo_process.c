
#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

bool eating(t_simulation *simulation)
{
	int forks_in_hand;

  if (simulation->data.nb_philos == 1)
		return (one_fork_case(simulation));
	forks_in_hand = take_two_fork(simulation);
	if (forks_in_hand <= 0)
	{
		release_forks(simulation->sems.forks, forks_in_hand * -1);
		sem_post(simulation->sems.can_i_eat);
		return (false);
	}
	simulation->data.time.last_meal = get_time();
	if (!print_log("is eating\n", simulation->data.id, simulation))
	{
		release_forks(simulation->sems.forks, forks_in_hand);
		return (false);
	}
	if (accurate_sleep(simulation, simulation->data.time.eat) < 0)
	{
		release_forks(simulation->sems.forks, forks_in_hand);
		return (false);
	}
	release_forks(simulation->sems.forks, forks_in_hand);
	simulation->data.meals_limit--; 
	if (simulation->data.meals_limit == 0)
	  sem_post(simulation->sems.fed);
	return (true);
}

bool thinking(t_simulation *simulation)
{
	long int last_meal_time_elapsed;
	long int time_until_starvation;
	long int think_time;

	last_meal_time_elapsed = get_time() - simulation->data.time.last_meal;
	time_until_starvation = simulation->data.time.die - last_meal_time_elapsed;
	if (!print_log("is thinking\n", simulation->data.id, simulation))
	{
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
	if ((get_time() - simulation->data.time.last_meal) > simulation->data.time.die)
	{
		simulation->data.exit_code = get_time() - simulation->data.time.start;
		sem_post(simulation->sems.death);
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
		usleep(100);
	}
	return (0);
}

int philo_process_life(t_simulation *simulation)
{
  init_processes_monitor_thread(simulation);
  philo_process_routine(simulation);
  pthread_join(simulation->monitor, NULL);  
  simulation_cleanup(simulation, 0);
  return (simulation->data.exit_code);
}
