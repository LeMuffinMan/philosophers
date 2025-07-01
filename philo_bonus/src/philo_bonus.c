/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:55:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:53:53 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

int monitor_simulation(t_simulation *simulation)
{
  int i;
  int j;

  if (pthread_create(&simulation->monitor, NULL, simulation_death_monitor_thread, simulation) != 0)
  {
    //error
    return (THREAD_ERROR);
  }
  i = 0;
  while (simulation->data.meals_limit > 0 && i < simulation->data.nb_philos)
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
  pthread_join(simulation->monitor, NULL);
  return (0);
}

int main (int ac, char **av)
{
  t_simulation simulation;
  int exit_code;

  if (check_user_inputs(ac))
    return (INVALID_ARG);
  exit_code = are_valids_args(av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_simulation(&simulation, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_shared_semaphores(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_processes(&simulation);
	if (exit_code != 0)
		return (exit_code);
	exit_code = monitor_simulation(&simulation);
	if (exit_code)
	  return (exit_code);
  return (simulation_cleanup(&simulation, 0));
}

