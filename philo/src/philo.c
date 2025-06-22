/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:26:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/19 19:57:20 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* #include <threads.h> */
#include "philo.h"
#include <stdio.h>
#include <unistd.h>
/* #include <sys/time.h> */
/* #include <unistd.h> */
/* #include <limits.h> */

int print_data(t_data *data)
{
  printf("nb_philo = %d\n", data->nb_philo);
  printf("time_to_die = %d\n", data->time_to_die);
  printf("time_to_eat = %d\n", data->time_to_eat);
  printf("time_to_sleep = %d\n", data->time_to_sleep);
  if (data->meals_limit)
    printf("meals_limit = %d\n", data->meals_limit);
  return (0);
}

int main (int ac, char **av)
{
  t_data *data;
  int exit_code;

  data = NULL;
  if (ac < 5 || ac > 6)
  {
    printf("Usage :\n./philo <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> (optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
    //est-ce que le dernier argument doit forcement etre entre corchets ?
    return (1);
  }
  exit_code = are_valids_args(av);
  if (exit_code != 0)
    return (exit_code);
  exit_code = init_data(&data, av);
  if (exit_code != 0)
    return (exit_code);
  /* print_data(data); */
  exit_code = init_mutex(&data);
  if (exit_code != 0)
    return (exit_code);
  exit_code = init_threads(&data);
  if (exit_code != 0)
    return (exit_code);
  exit_code = main_thread_monitoring(&data);
  /* printf("DONE\n"); */
  return (simulation_end_destroy_and_free(&data));
}

// TESTS
// MAC
// ./bin/philo 1 610 300 300 : il doit mourrir direct : OK
// ./bin/philo 2 610 300 300 : personne ne meurt : FAIL ?
// ./bin/philo 4 610 300 300 : personne ne meurt : FAIL ?
// ./bin/philo 6 610 300 300 : personne ne meurt : FAIL ?
// ./bin/philo 7 610 300 300 : personne ne meurt : FAIL ?
// ./bin/philo 10 610 300 300 : personne ne meurt : FAIL ?
// ./bin/philo 200 610 300 300 : personne ne meurt : FAIL ? : meurt + imprime des messages ensuite
//
