#include "philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	sem_unlink("/philo_simulation_end");
	sem_unlink("/philo_proc_end");
	sem_unlink("/philo_can_i_eat");
}

int	init_semaphores_close_forks(t_simulation *simulation)
{
	sem_close(simulation->sems.forks);
	unlink_semaphores();
	return (print_error_and_free("Semaphore init failed\n", SEM_ERROR,
			simulation));
}

int	init_semaphores_close_print(t_simulation *simulation)
{
	sem_close(simulation->sems.print);
	return (init_semaphores_close_forks(simulation));
}

int	init_semaphores_close_death(t_simulation *simulation)
{
	sem_close(simulation->sems.death);
	return (init_semaphores_close_proc_end(simulation));
}

int	init_semaphores_close_fed(t_simulation *simulation)
{
	sem_close(simulation->sems.fed);
	return (init_semaphores_close_death(simulation));
}


