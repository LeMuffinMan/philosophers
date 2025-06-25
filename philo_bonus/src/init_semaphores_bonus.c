
#include "philo_bonus.h"
#include <fcntl.h>

static int init_semaphores_close_forks(t_simulation **simulation)
{
	sem_close((*simulation)->sems.forks);
	return (init_simulation_print_error_and_free("Semaphore init failed\n", SEM_ERROR, simulation));
}

static int init_semaphores_close_print(t_simulation **simulation)
{
	sem_close((*simulation)->sems.print);
	return (init_semaphores_close_forks(simulation));
}

static int init_semaphores_close_death(t_simulation **simulation)
{
	sem_close((*simulation)->sems.death);
	return (init_semaphores_close_print(simulation));
}

static int init_semaphores_close_fed(t_simulation **simulation)
{
	sem_close((*simulation)->sems.fed);
	return (init_semaphores_close_death(simulation));
}

//renommer le fichier
int init_shared_semaphores(t_simulation **simulation)
{
	unlink_shared_semaphores();
	(*simulation)->sems.forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, (*simulation)->data.nb_philos);
	if ((*simulation)->sems.forks == SEM_FAILED)
		return (init_simulation_print_error_and_free("Semaphore init failed\n", SEM_ERROR, simulation));
	(*simulation)->sems.print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if ((*simulation)->sems.print == SEM_FAILED)
		return (init_semaphores_close_forks(simulation));
	(*simulation)->sems.death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644, 1);
	if ((*simulation)->sems.death == SEM_FAILED)
		return (init_semaphores_close_print(simulation));
	(*simulation)->sems.fed = sem_open("/philo_fed", O_CREAT | O_EXCL, 0644, (*simulation)->data.nb_philos);
	if ((*simulation)->sems.fed == SEM_FAILED)
		return (init_semaphores_close_death(simulation));
	(*simulation)->sems.start = sem_open("/philo_start", O_CREAT | O_EXCL, 0644, 0);
	if ((*simulation)->sems.start == SEM_FAILED)
		return (init_semaphores_close_fed(simulation));
	return (0);
}
