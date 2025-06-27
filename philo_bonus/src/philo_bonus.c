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

void *philo_monitor_thread(void *args)
{
  t_simulation *simulation;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.simulation_end);
  sem_wait(simulation->sems.proc_end);
  simulation->data.end = true;
  sem_post(simulation->sems.proc_end);
  return (0);
}

//pb ici, il faut que j'init ce semaphore dans l'init de base
int init_processes_monitor_thread(t_simulation **simulation)
{
  if (pthread_create(&(*simulation)->threads.simulation_death_monitor, NULL, philo_monitor_thread, &simulation) != 0)
  {
    //revoir le retrun
    /* return (wait_close_unlink_free(simulation, 0, (*simulation)->data.id, THREAD_ERROR)); */
    return (THREAD_ERROR);
  }
  if (pthread_create(&(*simulation)->threads.simulation_fed_monitor, NULL, philo_monitor_thread, &simulation) != 0)
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
    return (simulation_end_unlink_close_free(simulation, MALLOC_ERROR));
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
      /* init_processes_monitor_thread(simulation); */
      /* philo_process_routine(simulation); */
      /* pthread_join((*simulation)->threads.simulation_death_monitor, NULL);   */
      /* pthread_join((*simulation)->threads.simulation_fed_monitor, NULL);   */
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
      exit (0);
    }
    (*simulation)->data.id++;
  }
  return (0);
}

void *simulation_death_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.death);
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    sem_post(simulation->sems.fed);
    i++;
  }
  return (NULL);
}

void *simulation_fed_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  simulation = (t_simulation *)args;
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    sem_wait(simulation->sems.fed);
    i++;
  }
  sem_post(simulation->sems.death);
  return (NULL);
}

/* int init_monitor(t_simulation **simulation) */
/* { */
/*   (*simulation)->pids.monitor = fork(); */
/*   if ((*simulation)->pids.monitor < 0) */
/*   { */
/*     //fork error */
/*     return (FORK_ERROR); */
/*   } */
/*   if ((*simulation)->pids.monitor == 0) */
/*   { */
/*   } */
/*   return (0); */
/* } */

int wait_philos(t_pids pids, int nb_philos)
{
  int status;
  int exit_code;
  int i;

  i = 0;
  while (i < nb_philos)
  {
    exit_code = waitpid(pids.philos[i], &status, 0);
    /* if (exit_code == -1) */
    /* { */
    /*   //error waitpid */
      /* return (WAITPID_ERROR); */
    /*   return (1); */
    /* } */
    i++;
  }
  //wait_monitor ?
  return (0);
}

int close_unlink_semaphores(t_sems sems)
{
  sem_close(sems.forks);
  sem_close(sems.print);
  sem_close(sems.death);
  sem_close(sems.fed);
  sem_close(sems.start);
  sem_close(sems.simulation_end);
  sem_close(sems.proc_end);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	sem_unlink("/philo_simulation_end");
	sem_unlink("/philo_proc_end");
	return (0);
}

int free_simulation(t_simulation **simulation)
{
  free((*simulation)->pids.philos);
  free(*simulation);
  return (0);
}

int simulation_cleanup(t_simulation **simulation)
{
  //! .. marche si renvoie -1 ?
  wait_philos((*simulation)->pids, (*simulation)->data.nb_philos);
  close_unlink_semaphores((*simulation)->sems);
  free_simulation(simulation);
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
  pthread_join((*simulation)->threads.simulation_death_monitor, NULL);
  //gerer l'erreur
  pthread_join((*simulation)->threads.simulation_fed_monitor, NULL);
  //gerer l'erreur
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
  return (simulation_cleanup(&simulation));
}
