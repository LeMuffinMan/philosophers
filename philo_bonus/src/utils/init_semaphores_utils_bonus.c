/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 06:41:58 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/02 06:41:58 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores_close_forks(t_simulation *simulation)
{
	sem_close(simulation->sems.forks);
	unlink_semaphores();
	return (print_error_and_free("Semaphore init failed\n", SEM_ERROR,
			simulation));
}

int	init_semaphores_close_print(t_simulation *simulation)
{
	sem_close(simulation->sems.print);
	return (init_semaphores_close_forks(simulation));
}

int	init_semaphores_close_death(t_simulation *simulation)
{
	sem_close(simulation->sems.death);
	return (init_semaphores_close_proc_end(simulation));
}

int	init_semaphores_close_fed(t_simulation *simulation)
{
	sem_close(simulation->sems.fed);
	return (init_semaphores_close_death(simulation));
}

int	init_semaphores_close_proc_end(t_simulation *simulation)
{
	sem_close(simulation->sems.proc_end);
	return (init_semaphores_close_print(simulation));
}
