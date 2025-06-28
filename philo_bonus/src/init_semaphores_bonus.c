/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:55:57 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/27 18:55:58 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <stdio.h>

static int init_semaphores_close_forks(t_simulation *simulation)
{
	sem_close(simulation->sems.forks);
	unlink_shared_semaphores();
	return (print_error_and_free("Semaphore init failed\n", SEM_ERROR, simulation));
}

static int init_semaphores_close_print(t_simulation *simulation)
{
	sem_close(simulation->sems.print);
	return (init_semaphores_close_forks(simulation));
}

static int init_semaphores_close_death(t_simulation *simulation)
{
	sem_close(simulation->sems.death);
	return (init_semaphores_close_print(simulation));
}

static int init_semaphores_close_fed(t_simulation *simulation)
{
	sem_close(simulation->sems.fed);
	return (init_semaphores_close_death(simulation));
}

static int init_semaphores_close_sim_end(t_simulation *simulation)
{
	sem_close(simulation->sems.simulation_end);
	return (init_semaphores_close_fed(simulation));
}

static int init_semaphores_close_proc_end(t_simulation *simulation)
{
	sem_close(simulation->sems.proc_end);
	return (init_semaphores_close_sim_end(simulation));
}

static int init_semaphores_close_can_i_eat(t_simulation *simulation)
{
	sem_close(simulation->sems.can_i_eat);
	return (init_semaphores_close_proc_end(simulation));
}

void unlink_shared_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	sem_unlink("/philo_simulation_end");
	sem_unlink("/philo_proc_end");
	sem_unlink("/philo_can_i_eat");
}

int init_shared_semaphores(t_simulation *simulation)
{
	//renommer la fct
	unlink_shared_semaphores();
	simulation->sems.forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, simulation->data.nb_philos);
	if (simulation->sems.forks == SEM_FAILED)
		return (print_error_and_free("Semaphore init failed\n", SEM_ERROR, simulation));
	simulation->sems.print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (simulation->sems.print == SEM_FAILED)
		return (init_semaphores_close_forks(simulation));
	simulation->sems.death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.death == SEM_FAILED)
		return (init_semaphores_close_print(simulation));
	simulation->sems.fed = sem_open("/philo_fed", O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.fed == SEM_FAILED)
		return (init_semaphores_close_death(simulation));
	simulation->sems.start = sem_open("/philo_start", O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.start == SEM_FAILED)
		return (init_semaphores_close_fed(simulation));
	simulation->sems.simulation_end = sem_open("/philo_simulation_end", O_CREAT | O_EXCL, 0644, 0);
	if (simulation->sems.simulation_end == SEM_FAILED)
		return (init_semaphores_close_sim_end(simulation));
	simulation->sems.proc_end = sem_open("/philo_proc_end", O_CREAT | O_EXCL, 0644, 1);
	if (simulation->sems.proc_end == SEM_FAILED)
		return (init_semaphores_close_proc_end(simulation));
	simulation->sems.can_i_eat = sem_open("/philo_can_i_eat", O_CREAT | O_EXCL, 0644, (simulation->data.nb_philos - 1));
	if (simulation->sems.can_i_eat == SEM_FAILED)
		return (init_semaphores_close_can_i_eat(simulation));
	return (0);
}
