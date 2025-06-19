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

# include <pthread.h>
# include <stdbool.h>

# define INVALID_ARG 1
# define MALLOC_ERROR -1
# define MUTEX_ERROR -2
# define THREAD_ERROR -3

typedef struct s_philosopher
{
  int id;
  // int *time_start;
  pthread_mutex_t last_meal_mutex;
  int last_meal;
  pthread_mutex_t nb_meals_eaten_mutex;
  int nb_meals_eaten;
  pthread_t *threads;
  pthread_mutex_t *start_mutex;
  bool *start;
  pthread_mutex_t *end_mutex;
} t_philosopher;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			*forks;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	start_mutex;
	bool			start;
	pthread_mutex_t	end_mutex;
	bool			end;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meals_limit_mutex;
	int				meals_limit;
	pthread_t		*threads;
	pthread_t monitor;
	t_philosopher *philosophers;
	// pthread_t monitor;
	// int time_start;
	// pthread_mutex_t mutex_end;
}					t_data;

typedef enum e_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}					t_type;

// init.c
int					init_data(t_data **data, char **av);
int					init_mutex(t_data **data);
int init_threads(t_data **data);
// int init_forks(t_data *data);

// init_mutex_utils
int					init_mutex_start_mutex(t_data **data);
int					init_mutex_end_mutex(t_data **data);
int					init_mutex_write_mutex(t_data **data);
int					init_mutex_meals_limit_mutex(t_data **data);
int					destroy_forks_mutex(t_data **data, int last_mutex);

// utils
// prints
int					print_error_and_free(char *msg, int exit_code,
						t_data **data);
// int print_update(int time_elapsed, int philo, t_type type);
// int print_error(char *input, char *arg_type, t_data *data);
// int print_update(int time_elapsed, int philo, t_type type);

// str_utils
int					are_valids_args(char **av);
int					ft_atoi(const char *nptr);
// char *ft_itoa(int n);
// int ft_strlen(char *str);
// int copy_chars(char **dest, char *src, int dest_i, int src_i);
// char *ft_strjoin3(char *time_elapsed, char *philo, char *action);
// int ft_atoi(char *str);

// free_fcts.c
int					free_allocated_memory(t_data **data);
int simulation_end_destroy_and_free(t_data **data);
int join_threads(t_data **data, int i);
int destroy_all_philo_mutex(t_data **data, int i);
// int destroy_mutex_free_exit(t_data *data, pthread_mutex_t *fork_mutex, int i, int exit_code);

// routines
// monitor_routine
void *monitor_routine(void *arg);
// philosophers_routine
void *philosophers_routine(void *arg);

#endif
