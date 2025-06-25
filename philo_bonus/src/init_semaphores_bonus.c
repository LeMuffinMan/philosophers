
#include "philo_bonus.h"
#include <fcntl.h>

static int init_semaphores_close_forks(t_data **data)
{
	sem_close((*data)->sems.forks);
	return (init_data_print_error_and_free("Semaphore init failed\n", SEM_ERROR, data));
}

static int init_semaphores_close_print(t_data **data)
{
	sem_close((*data)->sems.print);
	return (init_semaphores_close_forks(data));
}

static int init_semaphores_close_death(t_data **data)
{
	sem_close((*data)->sems.death);
	return (init_semaphores_close_print(data));
}

static int init_semaphores_close_fed(t_data **data)
{
	sem_close((*data)->sems.fed);
	return (init_semaphores_close_death(data));
}

int init_semaphores(t_data **data)
{
	unlink_semaphores();
	(*data)->sems.forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, (*data)->nb_philos);
	if ((*data)->sems.forks == SEM_FAILED)
		return (init_data_print_error_and_free("Semaphore init failed\n", SEM_ERROR, data));
	(*data)->sems.print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->sems.print == SEM_FAILED)
		return (init_semaphores_close_forks(data));
	(*data)->sems.death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->sems.death == SEM_FAILED)
		return (init_semaphores_close_print(data));
	(*data)->sems.fed = sem_open("/philo_fed", O_CREAT | O_EXCL, 0644, (*data)->nb_philos);
	if ((*data)->sems.fed == SEM_FAILED)
		return (init_semaphores_close_death(data));
	(*data)->sems.start = sem_open("/philo_start", O_CREAT | O_EXCL, 0644, 0);
	if ((*data)->sems.start == SEM_FAILED)
		return (init_semaphores_close_fed(data));
	return (0);
}
