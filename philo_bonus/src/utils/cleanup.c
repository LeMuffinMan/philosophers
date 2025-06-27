
#include "philo_bonus.h"
#include <stdlib.h>
#include <sys/wait.h>

int wait_philos(t_pids pids, int nb_philos)
{
  int status;
  int exit_code;
  int i;

  i = 0;
  while (i < nb_philos)
  {
    exit_code = waitpid(pids.philos[i], &status, 0);
    if (exit_code == -1)
    {
      //error waitpid
      /* return (WAITPID_ERROR); */
      return (1);
    }
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

int simulation_cleanup(t_simulation **simulation, int exit_code)
{
  //! .. marche si renvoie -1 ?
  wait_philos((*simulation)->pids, (*simulation)->data.nb_philos);
  close_unlink_semaphores((*simulation)->sems);
  free_simulation(simulation);
  return (exit_code);
}


