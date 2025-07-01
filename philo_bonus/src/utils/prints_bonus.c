
#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>

int	print_error_and_free(char *msg, int exit_code, t_simulation *simulation)
{
	if (simulation)
		free(simulation);
	printf("%s", msg);
	return (exit_code);
}

static bool can_i_print(t_simulation *simulation)
{
	if (get_proc_end(simulation))
	{
		sem_post(simulation->sems.print);
		return (false);
	}
	if ((get_time()
			- simulation->data.time.last_meal) > simulation->data.time.die)
	{
		simulation->data.exit_code = 1;
		sem_post(simulation->sems.death);
		if (get_proc_end(simulation))
		{
			sem_post(simulation->sems.print);
			return (false);
		}
		set_proc_end(simulation);
		sem_post(simulation->sems.print);
		return (false);
	}
	return (true);
}

bool	print_log(char *msg, int id, t_simulation *simulation)
{
	long int	time;

	if (am_i_starving(simulation))
		return (false);
	sem_wait(simulation->sems.print);
	time = get_time() - simulation->data.time.start;
  if (!can_i_print(simulation))
    return (false);
	printf("%ld %d %s", time, id, msg);
	sem_post(simulation->sems.print);
	return (true);
}

int	print_death(t_simulation *simulation, int id, long int death_time)
{
	sem_wait(simulation->sems.print);
	printf("%ld %d died\n", death_time, id + 1);
	sem_post(simulation->sems.fed);
	sem_post(simulation->sems.print);
	return (0);
}

int print_eat_and_sleep(t_simulation *simulation, int forks_in_hand)
{
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
	return (true);	
} 
