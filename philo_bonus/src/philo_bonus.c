
#include "philo_bonus.h"
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

/* void close_and_unlink_semaphores(t_data **data) */
/* { */
/* 	if ((*data)->sems.forks != SEM_FAILED) */
/* 		sem_close((*data)->sems.forks); */
/* 	if ((*data)->sems.print != SEM_FAILED) */
/* 		sem_close((*data)->sems.print); */
/* 	if ((*data)->sems.death != SEM_FAILED) */
/* 		sem_close((*data)->sems.death); */
/* 	if ((*data)->sems.fed != SEM_FAILED) */
/* 		sem_close((*data)->sems.fed); */
/* 	if ((*data)->sems.start != SEM_FAILED) */
/* 		sem_close((*data)->sems.start); */
/* 	sem_unlink("/philo_forks"); */
/* 	sem_unlink("/philo_print"); */
/* 	sem_unlink("/philo_death"); */
/* 	sem_unlink("/philo_fed"); */
/* 	sem_unlink("/philo_start"); */
/* 	return ; */
/* } */

int init_data_print_error_and_free(char *msg, int exit_code, t_data **data)
{
  if (*data)
    free(*data);
  printf("%s", msg);
  return (exit_code);
}

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (GETTIMEOFDAY_ERROR);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int print_log(char *msg, t_data **data)
{
  long int time;

  sem_wait((*data)->sems.print);
  time = get_time() - (*data)->time.start;
  if (time == GETTIMEOFDAY_ERROR)
    return (GETTIMEOFDAY_ERROR);
  printf("%ld %s\n", time, msg);
  sem_post((*data)->sems.print);
  return (0);
}

int	accurate_sleep(int time_to_sleep)
{
	int			ret_val;
	long int	start_time;

	start_time = get_time();
	if (start_time == GETTIMEOFDAY_ERROR)
		return (GETTIMEOFDAY_ERROR);
	ret_val = get_time();
	while (ret_val != GETTIMEOFDAY_ERROR && ret_val < time_to_sleep)
	{
		usleep(100);
		ret_val = get_time() - start_time;
	}
	return (ret_val);
}

int eating(t_data **data)
{
	sem_wait((*data)->sems.forks);
	print_log("has taken a fork\n", data);
	sem_wait((*data)->sems.forks);
	print_log("has taken a fork\n", data);
	print_log("is eating\n", data);
	(*data)->time.last_meal = get_time() - (*data)->time.start;
	accurate_sleep((*data)->time.eat);
	sem_post((*data)->sems.forks);
	sem_post((*data)->sems.forks);
	(*data)->meals_limit--;
	if ((*data)->meals_limit == 0)
	  sem_post((*data)->sems.fed);
	return (0);
}

void philo_process_routine(t_data **data, bool *start)
{
  sem_wait((*data)->sems.start);
  (*data)->time.start = get_time();
  (*data)->time.last_meal = (*data)->time.start;
	while (1)
	{
		eating(data);
		print_log("is sleeping\n", data);
		accurate_sleep((*data)->time.sleep);
		print_log("is thinking\n", data);
		accurate_sleep(100);
	}
}
/**/
/* int init_processes(t_data **data) */
/* { */
/*   (*data)->pids.philos = malloc(sizeof(pid_t) * (*data)->nb_philos); */
/*   if (!(*data)->pids.philos) */
/*     return (unlink_and_free(data)); */
/*   data->id = 1; */
/*   while (data->id <= data->nb_philo) */
/*   { */
/*     (*data)->pids.philos[data->id] = fork(); */
/*     if (pid[data->id] < 0) */
/*       return (wait_unlink_and_free(data, (*data)->pids.philos, i)); */
/*     if (pid == 0) */
/*       return (philo_process_routine(data, start)); */
/*     i++; */
/*   } */
/*   (*data)->pids.watch_death = fork(); */
/*   if ((*data)->pids.watch_death < 0) */
/*     return (wait_unlink_and_free(data, (*data)->pids.philos, i, (*data)->pids.watch_death)); */
/*   if ((*data)->pids.watch_death == 0) */
/*     return (sem_wait(data->death)); */
/*   i = 0; */
/*   (*data)->pids.watch_fed = fork(); */
/*   if ((*data)->pids.watch_fed < 0) */
/*     return (wait_unlink_and_free(data, (*data)->pids.philos, i, (*data)->pids.watch_death, (*data)->pids.watch_fed)); */
/*   if ((*data)->pids.watch_fed == 0) */
/*   { */
/*     while (i < data->nb_philo) */
/*     { */
/*       sem_wait(data->sems.fed); */
/*       i++; */
/*     } */
/*     return (1); */
/*   } */
/*   wait_philos(data);  */
/*   return (0); */
/* } */
/**/
/* int wait_philos(t_data **data) */
/* { */
/*   int i; */
/*   int status; */
/*   pid_t pid; */
/**/
/*   pid = waitpid(-1, &status, 0); */
/*   if (pid != -1) */
/*   { */
/*     i = 0; */
/*     while (i < data->nb_philo) */
/*     { */
/*       if (data->pids.philos[i] != pid) */
/*         kill(data->pids.philos[i], SIGTERM); */
/*       i++ */
/*     } */
/*   } */
/*   return (0); */
/* } */


int simulation_end_unlink_close_free(t_data **data, int exit_code)
{
  sem_close((*data)->sems.forks);
  sem_close((*data)->sems.print);
  sem_close((*data)->sems.death);
  sem_close((*data)->sems.fed);
  sem_close((*data)->sems.start);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_fed");
	sem_unlink("/philo_start");
	free(*data);
	return (exit_code);
}

int main (int ac, char **av)
{
  t_data *data;
  int exit_code;

  data = NULL;
  if (check_user_inputs(ac))
    return (INVALID_ARG);
  exit_code = are_valids_args(av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_data(&data, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_semaphores(&data);
	if (exit_code != 0)
		return (exit_code);
	/* exit_code = init_processes(&data); */
	/* if (exit_code != 0) */
	/* 	return (exit_code); */
	/* exit_code = wait_philos(&data); */
	return (simulation_end_unlink_close_free(&data, exit_code));
}
