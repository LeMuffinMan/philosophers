/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_unlink_free_bonus.case                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:32:09 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:25:40 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

void	unlink_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	sem_unlink("/philo_simulation_end");
	sem_unlink("/philo_proc_end");
}

int close_semaphores(t_sems sems)
{
  sem_close(sems.forks);
  sem_close(sems.print);
  sem_close(sems.death);
  sem_close(sems.fed);
  sem_close(sems.start);
  sem_close(sems.simulation_end);
  sem_close(sems.proc_end);
	return (0);
}

int close_unlink_free(t_simulation *simulation, int exit_code, bool unlink)
{
  close_semaphores(simulation->sems);
  if (unlink)
    unlink_semaphores();
  free(simulation->philos);
  return (exit_code);
}


