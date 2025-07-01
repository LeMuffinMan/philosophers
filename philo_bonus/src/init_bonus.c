/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:56:05 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:27:04 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static int	init_meals_limit(t_simulation *simulation, char **av)
{
	simulation->data.meals_limit = ft_atoi(av[5]);
	if (simulation->data.meals_limit <= 0)
		return (print_error_and_free("Incorrect number of times each philosopher must eat\n",
				INVALID_ARG, simulation));
	return (0);
}

int	init_user_inputs(t_simulation *simulation, char **av)
{
	simulation->data.nb_philos = ft_atoi(av[1]);
	if (simulation->data.nb_philos <= 0)
		return (print_error_and_free("Incorrect number_of_philosophers\n",
				INVALID_ARG, simulation));
	simulation->data.time.die = ft_atoi(av[2]);
	if (simulation->data.time.die <= 0)
		return (print_error_and_free("Incorrect data.time_to_die\n",
				INVALID_ARG, simulation));
	simulation->data.time.eat = ft_atoi(av[3]);
	if (simulation->data.time.eat <= 0)
		return (print_error_and_free("Incorrect data.time_to_eat\n",
				INVALID_ARG, simulation));
	simulation->data.time.sleep = ft_atoi(av[4]);
	if (simulation->data.time.sleep <= 0)
		return (print_error_and_free("Incorrect data.time_to_sleep\n",
				INVALID_ARG, simulation));
	if (av[5])
		return (init_meals_limit(simulation, av));
	else
		simulation->data.meals_limit = -1;
	simulation->data.end = false;
	return (0);
}

int	init_simulation(t_simulation *simulation, char **av)
{
	int	exit_code;

	exit_code = init_user_inputs(simulation, av);
	if (exit_code)
		return (exit_code);
	simulation->data.time.last_meal = 0;
	simulation->data.time.start = 0;
	return (0);
}

int	init_processes_monitor_thread(t_simulation *simulation)
{
	if (pthread_create(&simulation->monitor, NULL, philo_monitor_thread,
			simulation) != 0)
		return (THREAD_ERROR);
	return (0);
}

int	init_processes(t_simulation *simulation)
{
	simulation->philos = malloc(sizeof(pid_t) * simulation->data.nb_philos);
	if (!simulation->philos)
		return (simulation_cleanup(simulation, MALLOC_ERROR));
	simulation->data.id = 1;
	simulation->data.end = false;
	simulation->data.exit_code = 0;
	simulation->data.time.start = get_time();
	simulation->data.time.last_meal = simulation->data.time.start;
	while (simulation->data.id <= simulation->data.nb_philos)
	{
		simulation->philos[simulation->data.id - 1] = fork();
		if (simulation->philos[simulation->data.id - 1] != 0)
			if (simulation->philos[simulation->data.id - 1] < 0)
				return (FORK_ERROR);
		if (simulation->philos[simulation->data.id - 1] == 0)
			exit(philo_process_life(simulation));
		simulation->data.id++;
	}
	while (simulation->data.id >= 1)
	{
		sem_post(simulation->sems.start);
		simulation->data.id--;
	}
	return (0);
}
