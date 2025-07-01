/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:56:53 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:58:35 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int release_forks(sem_t *forks, int forks_in_hand)
{
	while (forks_in_hand > 0)
	{
		sem_post(forks);
		forks_in_hand--;
	}
	return (0);
}

int take_two_fork(t_simulation *simulation)
{
  sem_wait(simulation->sems.forks);
  if (!print_log("has taken a fork\n", simulation->data.id, simulation) || get_proc_end(simulation) || am_i_starving(simulation))
  	return (-1);
  usleep(100);
  sem_wait(simulation->sems.forks);
  if (!print_log("has taken a fork\n", simulation->data.id, simulation) || get_proc_end(simulation) || am_i_starving(simulation))
  	return (-2);
  return (2);
}

int one_fork_case(t_simulation *simulation)
{
	sem_wait(simulation->sems.forks);
  print_log("has taken a fork\n", simulation->data.id, simulation);
  while(!am_i_starving(simulation))
  	usleep(100);
  simulation->data.exit_code = 1;
  sem_post(simulation->sems.death);
  return (-1);
}


