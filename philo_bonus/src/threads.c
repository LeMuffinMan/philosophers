/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:54:58 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:24:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

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

int	print_death(t_simulation *simulation, int id, long int death_time)
{
	sem_wait(simulation->sems.print);
	printf("%ld %d died\n", death_time, id + 1);
	sem_post(simulation->sems.fed);
	sem_post(simulation->sems.print);
	return (0);
}

int	wait_children(t_simulation *simulation, long int death_time)
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
			if (exit_code)
				return (print_death(simulation, i, death_time));
		}
		i++;
	}
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
