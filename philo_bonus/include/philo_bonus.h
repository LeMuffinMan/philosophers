
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdbool.h>

# define INVALID_ARG 1
# define MALLOC_ERROR -1
# define SEM_ERROR -2
// # define THREAD_ERROR -3
# define GETTIMEOFDAY_ERROR -4
// # define SIMULATION_END -5

typedef struct s_time
{
  int die;
  int eat;
  int sleep;
  long int last_meal;
  long int start;
} t_time;

typedef struct s_pids
{
  pid_t watch_death;
  pid_t watch_fed;
  pid_t *philos;
} s_pids;

typedef struct s_sems
{
  sem_t *forks;
  sem_t *print;
  sem_t *death;
  sem_t *fed;
  sem_t *start;
} t_sems;

typedef struct s_data
{
  int id;
  int nb_philos;
  int meals_limit;
  struct s_time time;
  struct s_pids pids;
  struct s_sems sems;
} t_data;


int								init_data(t_data **data, char **av);
int								init_user_inputs(t_data **data, char **av);
int init_semaphores(t_data **data);
void unlink_semaphores(void);
int init_data_print_error_and_free(char *msg, int exit_code, t_data **data);
int print_log(char *msg, t_data **data);

//Utils
long int	get_time(void);
int	accurate_sleep(int time_to_sleep);

// str_utils
int								are_valids_args(char **av);
int								ft_atoi(const char *nptr);

// prints
int								print_error_and_free(char *msg, int exit_code,
									t_data **data);
int								init_data_print_error_and_free(char *msg,
									int exit_code, t_data **data);


// init_bonus.c
bool	check_user_inputs(int ac);
int init_semaphores(t_data **data);
int								init_data(t_data **data, char **av);

// init_data_utils.c
int								init_user_inputs(t_data **data, char **av);

#endif
