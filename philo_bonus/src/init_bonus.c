
#include "philo_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>



bool	check_user_inputs(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage :\n./philo <number_of_philosophers> "
			"<time_to_die time_to_eat> "
			"<time_to_sleep> "
			"(optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
		return (true);
	}
	return (false);
}



static int	init_meals_limit(t_simulation **simulation, char **av)
{
	(*simulation)->data.meals_limit = ft_atoi(av[5]);
	if ((*simulation)->data.meals_limit <= 0)
		return (init_simulation_print_error_and_free(
				"Incorrect number of times each philosopher must eat\n",
				INVALID_ARG, simulation));
	return (0);
}

int	init_user_inputs(t_simulation **simulation, char **av)
{
	(*simulation)->data.nb_philos = ft_atoi(av[1]);
	if ((*simulation)->data.nb_philos <= 0)
		return (init_simulation_print_error_and_free(
				"Incorrect number_of_philosophers\n",
				INVALID_ARG, simulation));
	(*simulation)->time.die = ft_atoi(av[2]);
	if ((*simulation)->time.die <= 0)
		return (init_simulation_print_error_and_free("Incorrect time_to_die\n",
				INVALID_ARG, simulation));
	(*simulation)->time.eat = ft_atoi(av[3]);
	if ((*simulation)->time.eat <= 0)
		return (init_simulation_print_error_and_free("Incorrect time_to_eat\n",
				INVALID_ARG, simulation));
	(*simulation)->time.sleep = ft_atoi(av[4]);
	if ((*simulation)->time.sleep <= 0)
		return (init_simulation_print_error_and_free("Incorrect time_to_sleep\n",
				INVALID_ARG, simulation));
	if (av[5])
		return (init_meals_limit(simulation, av));
	else
		(*simulation)->data.meals_limit = -1;
	return (0);
}

int	init_simulation(t_simulation **simulation, char **av)
{
	int	exit_code;

	*simulation = malloc(sizeof(t_simulation));
	if (!*simulation)
	{
	  printf("simulation struct mem_alloc failed\n");
	  return (MALLOC_ERROR);
	}
	exit_code = init_user_inputs(simulation, av);
	if (exit_code)
		return (exit_code);
	(*simulation)->time.last_meal = 0;
	(*simulation)->time.start = 0;
	return (0);
}
