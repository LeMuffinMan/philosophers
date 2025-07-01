/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:55:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:27:32 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int launch_simulation(t_simulation *simulation)
{
	while (simulation->data.id <= simulation->data.nb_philos)
	{
		simulation->philos[simulation->data.id - 1] = fork();
		if (simulation->philos[simulation->data.id - 1] < 0)
		{

			return (FORK_ERROR);
		}
		if (simulation->philos[simulation->data.id - 1] == 0)
			exit(philo_process(simulation));
		simulation->data.id++;
	}
	while (simulation->data.id >= 1)
	{
		sem_post(simulation->sems.start);
		simulation->data.id--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_simulation	simulation;
	int				exit_code;

	exit_code = are_valids_args(ac, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_simulation(&simulation, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_semaphores(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_processes(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = launch_simulation(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = monitor_simulation(&simulation);
	if (exit_code)
		return (exit_code);
	return (simulation_cleanup(&simulation, 0));
}
