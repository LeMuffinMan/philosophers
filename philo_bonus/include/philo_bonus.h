/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:56:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:14:09 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdbool.h>

# define INVALID_ARG 1
# define MALLOC_ERROR -1
# define SEM_ERROR -2
# define THREAD_ERROR -3
# define SIMULATION_END -4
# define FORK_ERROR -5

typedef struct s_time
{
	int				die;
	int				eat;
	int				sleep;
	long int		last_meal;
	long int		start;
}					t_time;

typedef struct s_data
{
	int				id;
	int				nb_philos;
	int				meals_limit;
	long int		exit_code;
	bool			end;
	struct s_time	time;
}					t_data;

typedef struct s_sems
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	sem_t			*fed;
	sem_t			*start;
	sem_t			*simulation_end;
	sem_t			*proc_end;
	sem_t			*can_i_eat;
}					t_sems;

typedef struct s_simulation
{
	struct s_data	data;
	pthread_t		monitor;
	pid_t			*philos;
	struct s_sems	sems;
}					t_simulation;

// void				unlink_semaphores(void);
// void				unlink_shared_semaphores(void);
// int					philo_process_routine(t_simulation *simulation);
// bool				should_i_stop(t_simulation *simulation);

/* ------------------------ Utils ----------------------- */
// cleanup.c
int					simulation_cleanup(t_simulation *simulation, int exit_code);

// getters_setters.c
bool				get_proc_end(t_simulation *simulation);
int					set_proc_end(t_simulation *simulation);

// time_bonus.c
long int			get_time(void);
long int			accurate_sleep(t_simulation *simulation, int time_to_sleep);
bool				am_i_starving(t_simulation *simulation);

// str_utils_bonus.c
int					are_valids_args(int ac, char **av);
int					ft_atoi(const char *nptr);
bool				print_log(char *msg, int id, t_simulation *simulation);
int					print_error_and_free(char *msg, int exit_code,
						t_simulation *simulation);

// philo_routine_utils.c
bool odd_philo_thinking_time(t_simulation *simulation);
bool even_philo_thinking_time(t_simulation *simulation);

// prints.c
int	print_death(t_simulation *simulation, int id, long int death_time);
int print_eat_and_sleep(t_simulation *simulation, int forks_in_hand);

//init_semaphores_utils_bonus.c
int	init_semaphores_close_fed(t_simulation *simulation);
int	init_semaphores_close_death(t_simulation *simulation);
int	init_semaphores_close_print(t_simulation *simulation);
int	init_semaphores_close_forks(t_simulation *simulation);
int	init_semaphores_close_proc_end(t_simulation *simulation);
void	unlink_semaphores(void);

/* ------------------------ SRC ----------------------- */

// forks.c
int					one_fork_case(t_simulation *simulation);
int					take_two_fork(t_simulation *simulation);
int					release_forks(sem_t *forks, int forks_in_hand);

// init_bonus.c
bool				check_user_inputs(int ac);
int					init_processes_monitor_thread(t_simulation *simulation);
int					init_processes(t_simulation *simulation);
int					init_user_inputs(t_simulation *simulation, char **av);
int	init_simulation(t_simulation *simulation, char **av);

// init_bonus_semaphores.c
void				unlink_shared_semaphores(void);
int					init_semaphores(t_simulation *simulation);

// philo_bonus.c
int					monitor_simulation(t_simulation *simulation);

// threads.c
void				*philo_monitor_thread(void *args);
void				*simulation_death_monitor_thread(void *args);
void				*simulation_fed_monitor_thread(void *args);

// philo_process
int					philo_process(t_simulation *simulation);

#endif
