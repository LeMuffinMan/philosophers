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

struct s_philosopher;
typedef struct s_philosopher t_philosopher;


typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks_mutex;
	bool			*forks;
	pthread_mutex_t	time_mutex;
	long int		start_time;
	pthread_mutex_t	end_mutex;
	bool			end;
	pthread_mutex_t	meals_limit_mutex;
	int				meals_limit;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	t_philosopher	*philosophers;
}					t_data;

typedef struct s_philosopher
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			meals_limit;
	int				id;
	pthread_mutex_t	last_meal_mutex;
	long int				last_meal;
	int				nb_meals_eaten;
	pthread_mutex_t	fed_mutex;
	bool fed;
	t_data *data;
	// pthread_t		*threads;
	// pthread_mutex_t	*time_mutex;
	// long int		*start_time;
	// pthread_mutex_t	*end_mutex;
	// pthread_mutex_t	*write_mutex;
}					t_philosopher;

typedef enum e_type
{
	TAKE_FORK,
	// RELEASE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}					t_type;

// --------------------------------------- INIT -------------------------------------//
// init.c
int					init_data(t_data **data, char **av);
int					init_mutex(t_data **data);
int					init_threads(t_data **data);
int					init_philo_struct(t_data **data, int i);

// init_forks.c
int					init_mutex_forks_bool(t_data **data);
int					init_mutex_forks_mutex(t_data **data);

// init_mutex_utils.c
int					init_mutex_time_mutex(t_data **data);
int					init_mutex_end_mutex(t_data **data);
int					init_mutex_write_mutex(t_data **data);
int					init_mutex_meals_limit_mutex(t_data **data);
int					init_philo_struct_mutex(t_data **data, int i);
int					join_threads_backward(t_data **data, int i);

// --------------------------------------- UTILS -------------------------------------//

// destroy_mutex.c
int					destroy_all_data_mutex_and_free(t_data **data);
int					destroy_all_philo_mutex(t_data **data, int i);
int					destroy_forks_mutex(t_data **data, int last_mutex);

// free_fcts.c
int					free_allocated_memory(t_data **data);
int					simulation_end_destroy_and_free(t_data **data);
int					init_data_print_error_and_free(char *msg, int exit_code,
						t_data **data);

// time.c
long int			get_time(void);
bool is_simulation_over(t_philosopher *philosopher);
bool is_time_started(t_philosopher *philosopher);
int accurate_sleep(int time_to_sleep);

// prints
int					print_error_and_free(char *msg, int exit_code,
						t_data **data);
int					print_log(t_philosopher *philosopher, t_type action);

// str_utils
int					are_valids_args(char **av);
int					ft_atoi(const char *nptr);

// --------------------------------------- src/ -------------------------------------//
void				*philosophers_routine(void *arg);
int main_thread_monitoring(t_data **data);

//forks.c 
bool take_one_fork(t_philosopher *philosopher, int i);
bool take_two_forks(t_philosopher *philosopher);
int release_forks(t_philosopher *philosopher);

#endif
