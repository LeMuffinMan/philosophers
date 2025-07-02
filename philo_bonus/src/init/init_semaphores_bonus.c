/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:55:57 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/02 06:43:44 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>

static int	init_semaphores_close_start(t_simulation *simulation)
{
	sem_close(simulation->sems.start);
	return (init_semaphores_close_fed(simulation));
}

int	init_binary_semaphores(t_simulation *simulation)
{
	simulation->sems.print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644,
			1);
	if (simulation->sems.print == SEM_FAILED)
		return (init_semaphores_close_forks(simulation));
	simulation->sems.proc_end = sem_open("/philo_proc_end", O_CREAT | O_EXCL,
			0644, 1);
	if (simulation->sems.proc_end == SEM_FAILED)
		return (init_semaphores_close_print(simulation));
	return (0);
}

int	init_blocking_semaphores(t_simulation *simulation)
{
	simulation->sems.death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644,
			0);
	if (simulation->sems.death == SEM_FAILED)
		return (init_semaphores_close_proc_end(simulation));
	simulation->sems.fed = sem_open("/philo_fed", O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.fed == SEM_FAILED)
		return (init_semaphores_close_death(simulation));
	simulation->sems.start = sem_open("/philo_start", O_CREAT | O_EXCL, 0644,
			0);
	if (simulation->sems.start == SEM_FAILED)
		return (init_semaphores_close_fed(simulation));
	simulation->sems.simulation_end = sem_open("/philo_simulation_end",
			O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.simulation_end == SEM_FAILED)
		return (init_semaphores_close_start(simulation));
	return (0);
}

int	init_semaphores(t_simulation *simulation)
{
	int	exit_code;

	unlink_semaphores();
	simulation->sems.forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			simulation->data.nb_philos);
	if (simulation->sems.forks == SEM_FAILED)
		return (print_error_and_free("Semaphore init failed\n", SEM_ERROR,
				simulation));
	exit_code = init_binary_semaphores(simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_blocking_semaphores(simulation);
	if (exit_code != 0)
		return (exit_code);
	return (0);
}
