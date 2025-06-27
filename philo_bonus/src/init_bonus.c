/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:56:05 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/27 18:56:06 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

bool	check_user_inputs(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage :\n./philo <number_of_philosophers> "
			"<time_to_die time_to_eat> "
			"<time_to_sleep> "
			"(optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
		return (true);
	}
	return (false);
}

static int	init_meals_limit(t_simulation **simulation, char **av)
{
	(*simulation)->data.meals_limit = ft_atoi(av[5]);
	if ((*simulation)->data.meals_limit <= 0)
		return (init_simulation_print_error_and_free(
				"Incorrect number of times each philosopher must eat\n",
				INVALID_ARG, simulation));
	return (0);
}

int	init_user_inputs(t_simulation **simulation, char **av)
{
	(*simulation)->data.nb_philos = ft_atoi(av[1]);
	if ((*simulation)->data.nb_philos <= 0)
		return (init_simulation_print_error_and_free(
				"Incorrect number_of_philosophers\n",
				INVALID_ARG, simulation));
	(*simulation)->data.time.die = ft_atoi(av[2]);
	if ((*simulation)->data.time.die <= 0)
		return (init_simulation_print_error_and_free("Incorrect data.time_to_die\n",
				INVALID_ARG, simulation));
	(*simulation)->data.time.eat = ft_atoi(av[3]);
	if ((*simulation)->data.time.eat <= 0)
		return (init_simulation_print_error_and_free("Incorrect data.time_to_eat\n",
				INVALID_ARG, simulation));
	(*simulation)->data.time.sleep = ft_atoi(av[4]);
	if ((*simulation)->data.time.sleep <= 0)
		return (init_simulation_print_error_and_free("Incorrect data.time_to_sleep\n",
				INVALID_ARG, simulation));
	if (av[5])
		return (init_meals_limit(simulation, av));
	else
		(*simulation)->data.meals_limit = -1;
  (*simulation)->data.end = false;
	return (0);
}

int	init_simulation(t_simulation **simulation, char **av)
{
	int	exit_code;

	*simulation = malloc(sizeof(t_simulation));
	if (!*simulation)
	{
	  printf("simulation struct mem_alloc failed\n");
	  return (MALLOC_ERROR);
	}
	exit_code = init_user_inputs(simulation, av);
	if (exit_code)
		return (exit_code);
	(*simulation)->data.time.last_meal = 0;
	(*simulation)->data.time.start = 0;
	return (0);
}


int init_processes_monitor_thread(t_simulation **simulation)
{
  if (pthread_create(&(*simulation)->threads.proc_monitor, NULL, philo_monitor_thread, *simulation) != 0)
  {
    //revoir le retrun
    /* return (wait_close_unlink_free(simulation, 0, (*simulation)->data.id, THREAD_ERROR)); */
    return (THREAD_ERROR);
  }
  return (0);
}

int init_processes(t_simulation **simulation)
{
  int exit_code;

  (*simulation)->pids.philos = malloc(sizeof(pid_t) * (*simulation)->data.nb_philos);
  if (!(*simulation)->pids.philos)
    return (simulation_cleanup(simulation, MALLOC_ERROR));
  (*simulation)->data.id = 1;
  while ((*simulation)->data.id <= (*simulation)->data.nb_philos)
  {
    (*simulation)->pids.philos[(*simulation)->data.id - 1] = fork();
    if ((*simulation)->pids.philos[(*simulation)->data.id - 1] < 0)
    {
      /* return (wait_close_unlink_free(data, 0, (*simulation)->data.id, FORK_ERROR)); */
      return (FORK_ERROR);
    }
    if ((*simulation)->pids.philos[(*simulation)->data.id - 1] == 0)
    {
      init_processes_monitor_thread(simulation);
      philo_process_routine(simulation);
      printf("proc %d waiting his monitor thread\n", (*simulation)->data.id);
      pthread_join((*simulation)->threads.proc_monitor, NULL);  
      printf("proc %d joined monitor thread\n", (*simulation)->data.id);
  sem_close((*simulation)->sems.forks);
  sem_close((*simulation)->sems.print);
  sem_close((*simulation)->sems.death);
  sem_close((*simulation)->sems.fed);
  sem_close((*simulation)->sems.start);
  sem_close((*simulation)->sems.simulation_end);
  sem_close((*simulation)->sems.proc_end);
      unlink_shared_semaphores();
      free((*simulation)->pids.philos);
      free(*simulation);
      printf("%d is about to exit\n", (*simulation)->data.id);
      exit (0);
    }
    (*simulation)->data.id++;
  }
  return (0);
}
