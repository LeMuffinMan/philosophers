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

int simulation_end_unlink_close_free(t_simulation **simulation, int exit_code)
{
  sem_close((*simulation)->sems.forks);
  sem_close((*simulation)->sems.print);
  sem_close((*simulation)->sems.death);
  sem_close((*simulation)->sems.fed);
  sem_close((*simulation)->sems.start);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	free(*simulation);
	return (exit_code);
}

int is_simulation_over(t_simulation **simulation)
{
  int exit_code;

  sem_wait((*simulation)->sems.proc_end);
  exit_code = (*simulation)->data.end;
  sem_post((*simulation)->sems.proc_end);
  return (exit_code);
}

int eating(t_simulation **simulation)
{
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", simulation);
	sem_wait((*simulation)->sems.forks);
	print_log("has taken a fork\n", simulation);
	print_log("is eating\n", simulation);
	(*simulation)->data.time.last_meal = get_time() - (*simulation)->data.time.start;
	accurate_sleep((*simulation)->data.time.eat);
	sem_post((*simulation)->sems.forks);
	sem_post((*simulation)->sems.forks);
	(*simulation)->data.meals_limit--;
	if ((*simulation)->data.meals_limit == 0)
	  sem_post((*simulation)->sems.fed);
	return (0);
}

int philo_process_routine(t_simulation **simulation)
{
  sem_wait((*simulation)->sems.start);
  (*simulation)->data.time.start = get_time();
  (*simulation)->data.time.last_meal = (*simulation)->data.time.start;
	while (!is_simulation_over(simulation))
	{
		eating(simulation);
		print_log("is sleeping\n", simulation);
		accurate_sleep((*simulation)->data.time.sleep);
		print_log("is thinking\n", simulation);
		accurate_sleep(100);
	}
	return (0);
}

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
  printf("waiting threads\n");
  pthread_join((*simulation)->threads.simulation_death_monitor, NULL);
  //gerer l'erreur
  printf("death thread joined\n");
  pthread_join((*simulation)->threads.simulation_fed_monitor, NULL);
  printf("fed thread joined\n");
  //gerer l'erreur
  accurate_sleep(100);
  (*simulation)->data.end = true;
  sem_post((*simulation)->sems.simulation_end); //debloque les childs threads un par un 
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
