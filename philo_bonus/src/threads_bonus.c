/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:54:58 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/02 07:28:30 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>

static int	wait_children(t_simulation *simulation, long int death_time)
{
	int	status;
	int	exit_code;
	int	i;

	i = 0;
	while (i < simulation->data.nb_philos)
	{
		waitpid(simulation->philos[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (exit_code > 0)
				return (print_death(simulation, i, death_time));
		}
		i++;
	}
	return (0);
}

int	simulation_fed_monitor_thread(t_simulation *simulation)
{
	int	i;
	int	j;

	i = 0;
	while (i < simulation->data.nb_philos)
	{
		sem_wait(simulation->sems.fed);
		i++;
		if (i == simulation->data.nb_philos)
		{
			j = 0;
			while (j < simulation->data.nb_philos)
			{
				sem_post(simulation->sems.simulation_end);
				j++;
			}
			sem_post(simulation->sems.death);
		}
	}
	printf("fed\n");
	return (0);
}

void	*simulation_death_monitor_thread(void *args)
{
	t_simulation	*simulation;
	int				i;
	long int		death_time;

	simulation = (t_simulation *)args;
	sem_wait(simulation->sems.death);
	death_time = get_time() - simulation->data.time.start;
	i = 0;
	while (i < simulation->data.nb_philos)
	{
		sem_post(simulation->sems.simulation_end);
		i++;
	}
	wait_children(simulation, death_time);
	i = 0;
	while (i < simulation->data.nb_philos)
	{
		sem_post(simulation->sems.fed);
		i++;
	}
	return (NULL);
}

void	*philo_monitor_thread(void *args)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)args;
	sem_wait(simulation->sems.simulation_end);
	sem_wait(simulation->sems.proc_end);
	simulation->data.end = true;
	sem_post(simulation->sems.proc_end);
	return (0);
}
