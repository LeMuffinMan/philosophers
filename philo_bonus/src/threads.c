
#include "philo_bonus.h"
#include <stddef.h>
#include <stdio.h>

void *philo_monitor_thread(void *args)
{
  t_simulation *simulation;

  simulation = (t_simulation *)args;
  sem_wait(simulation->sems.simulation_end);
  sem_wait(simulation->sems.proc_end);
  /* printf("%d knows simulation is over\n", simulation->data.id); */
  simulation->data.end = true;
  sem_post(simulation->sems.proc_end);
  sem_post(simulation->sems.simulation_end);
  return (0);
}

void *simulation_death_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  /* simulation = (t_simulation *)args; */
  /* sem_wait(simulation->sems.death); */
  /* i = 0; */
  /* while (i < simulation->data.nb_philos) */
  /* { */
  /*   sem_post(simulation->sems.fed); */
  /*   i++; */
  /* } */
  return (NULL);
}

void *simulation_fed_monitor_thread(void *args)
{
  t_simulation *simulation;
  int i;

  /* simulation = (t_simulation *)args; */
  /* i = 0; */
  /* while (i < simulation->data.nb_philos) */
  /* { */
  /*   sem_wait(simulation->sems.fed); */
  /*   i++; */
  /* } */
  /* sem_post(simulation->sems.death); */
  return (NULL);
}


