/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:55:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/27 18:55:39 by oelleaum         ###   ########lyon.fr   */
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

int monitor_simulation(t_simulation **simulation)
{
  if (pthread_create(&(*simulation)->threads.simulation_death_monitor, NULL, simulation_death_monitor_thread, *simulation) != 0)
  {
    //error
    return (THREAD_ERROR);
  }
  if (pthread_create(&(*simulation)->threads.simulation_fed_monitor, NULL, simulation_fed_monitor_thread, *simulation) != 0)
  {
    //error
    return (THREAD_ERROR);
  }
  /* printf("waiting threads\n"); */
  pthread_join((*simulation)->threads.simulation_death_monitor, NULL);
  //gerer l'erreur
  /* printf("death thread joined\n"); */
  pthread_join((*simulation)->threads.simulation_fed_monitor, NULL);
  /* printf("fed thread joined\n"); */
  //gerer l'erreur
  /* accurate_sleep(1000); */
  sleep(2);
  /* printf("END set to TRUE\n"); */
  (*simulation)->data.end = true;
  sem_post((*simulation)->sems.simulation_end); 
  return (0);
}

int main (int ac, char **av)
{
  t_simulation *simulation;
  int exit_code;

  simulation = NULL;
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
