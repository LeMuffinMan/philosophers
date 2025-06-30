
#include "philo_bonus.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void *philo_monitor_thread(void *args)
{
  t_simulation *simulation;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.simulation_end);
  /* printf("%d knows someone died\n", simulation->data.id); */
  sem_wait(simulation->sems.proc_end);
  /* printf("%d knows simulation is over\n", simulation->data.id); */
  simulation->data.end = true;
  sem_post(simulation->sems.proc_end);
  /* sem_post(simulation->sems.simulation_end); */
  return (0);
}

int print_death(t_simulation *simulation, int id)
{
  sem_wait(simulation->sems.print);
  printf("%ld %d died\n", get_time() - simulation->data.time.start, id + 1);
  sem_post(simulation->sems.fed);
  sem_post(simulation->sems.print);
  return (0);
}


int wait_children(t_simulation *simulation)
{
  int status;
  pid_t pid;
  int i;
  int exit_code;
  int success = 1;

  i = 0;
  exit_code = 0;
  while (i < simulation->data.nb_philos)
  {
    pid = wait(&status);
    if (pid == -1)
    {
      //gerer l'erreur
        return (1);
    }
    if (WIFEXITED(status))
      exit_code = WEXITSTATUS(status);
    if (exit_code)
      return (print_death(simulation, i));
    i++;
  }
  return (0);
}

void *simulation_death_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.death);
  /* printf("soneone died !\n"); */
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    sem_post(simulation->sems.simulation_end); 
    i++;
  }
  wait_children(simulation);
  i = 0;
  while (i < simulation->data.nb_philos)
  {
    /* printf("iterate sems.fed\n"); */
    sem_post(simulation->sems.fed);
    i++;
  }
  return (NULL);
}

/* void *simulation_fed_monitor_thread(void *args) */
/* { */
/*   t_simulation *simulation; */
/*   int i; */
/**/
/*   simulation = (t_simulation *)args; */
/*   i = 0; */
/*   while (i < simulation->data.nb_philos) */
/*   { */
/*     sem_wait(simulation->sems.fed); */
/*     printf("%d philos fed\n", i); */
/*     i++; */
/*   } */
/*   sem_post(simulation->sems.death); */
/*   return (NULL); */
/* } */


