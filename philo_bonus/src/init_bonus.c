
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



static int	init_meals_limit(t_data **data, char **av)
{
	(*data)->meals_limit = ft_atoi(av[5]);
	if ((*data)->meals_limit <= 0)
		return (init_data_print_error_and_free(
				"Incorrect number of times each philosopher must eat\n",
				INVALID_ARG, data));
	return (0);
}

int	init_user_inputs(t_data **data, char **av)
{
	(*data)->nb_philos = ft_atoi(av[1]);
	if ((*data)->nb_philos <= 0)
		return (init_data_print_error_and_free(
				"Incorrect number_of_philosophers\n",
				INVALID_ARG, data));
	(*data)->time.die = ft_atoi(av[2]);
	if ((*data)->time.die <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_die\n",
				INVALID_ARG, data));
	(*data)->time.eat = ft_atoi(av[3]);
	if ((*data)->time.eat <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_eat\n",
				INVALID_ARG, data));
	(*data)->time.sleep = ft_atoi(av[4]);
	if ((*data)->time.sleep <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_sleep\n",
				INVALID_ARG, data));
	if (av[5])
		return (init_meals_limit(data, av));
	else
		(*data)->meals_limit = -1;
	return (0);
}

int	init_data(t_data **data, char **av)
{
	int	exit_code;

	*data = malloc(sizeof(t_data));
	if (!*data)
	{
	  printf("Data struct mem_alloc failed\n");
	  return (MALLOC_ERROR);
	}
	exit_code = init_user_inputs(data, av);
	if (exit_code)
		return (exit_code);
	(*data)->time.last_meal = 0;
	(*data)->time.start = 0;
	return (0);
}
