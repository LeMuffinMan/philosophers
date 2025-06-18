/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 18:56:05 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <pthread.h>

# define INVALID_ARG 1
# define MALLOC_ERROR -1
# define MUTEX_ERROR -2
# define THREAD_ERROR -3

// typedef struct s_philosopher
// {
//   int id;
//   int *time_start;
//   int last_meal;
//   pthread_mutex_t mutex_nb_meals_eaten;
//   pthread_mutex_t *mutex_start;
//   int nb_meals_eaten;
//   pthread_t thread; 
// } t_philosopher;

typedef struct s_data
{
  int nb_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_times_each_philosopher_must_eat;
  bool *forks;
  pthread_mutex_t *fork_mutex;
  // t_philosopher *philosophers;
  // pthread_t monitor;
  // pthread_mutex_t mutex_start;
  // int time_start;
  // pthread_mutex_t mutex_end;
  // bool end;
  //death mutex
  //write_mutex
} t_data;


typedef enum e_type
{
  FORK,
  EAT,
  SLEEP,
  THINK,
  DIE
} t_type;

//init.c
int init_data(t_data **data, char **av);
// int init_forks(t_data *data);
// int init_threads(t_data *data);

//utils 
  //prints
int print_error_and_free(char *msg, int exit_code, t_data *data);
// int print_update(int time_elapsed, int philo, t_type type);
// int print_error(char *input, char *arg_type, t_data *data);
// int print_update(int time_elapsed, int philo, t_type type);

  //str_utils
int are_valids_args(char **av);
int ft_atoi(const char *nptr);
// char *ft_itoa(int n);
// int ft_strlen(char *str);
// int copy_chars(char **dest, char *src, int dest_i, int src_i);
// char *ft_strjoin3(char *time_elapsed, char *philo, char *action);
// int ft_atoi(char *str);

  //free_fcts.c
// int destroy_mutex_free_exit(t_data *data, pthread_mutex_t *fork_mutex, int i, int exit_code);

//routines
  //monitor_routine
// void *monitor_routine(void *arg);
  //philosophers_routine
// void *philo_routine(void *arg);

#endif 

