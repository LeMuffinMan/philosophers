
#include "philo_bonus.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	unsigned long long	n;

	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
		if (n > INT_MAX)
			return (-1);
	}
	return ((int)n);
}

static bool	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	are_valids_args(char **av)
{
	if (!is_only_digits(av[1]) || av[1][0] == '-' || !is_only_digits(av[2])
		|| av[2][0] == '-' || !is_only_digits(av[3]) || av[3][0] == '-'
		|| !is_only_digits(av[4]) || av[4][0] == '-' || (av[5]
			&& (!is_only_digits(av[5]) || av[5][0] == '-')))
	{
		printf("Invalid(s) argument(s)\n");
		return (INVALID_ARG);
	}
	return (0);
}

int init_data_print_error_and_free(char *msg, int exit_code, t_data **data)
{
  if (*data)
    free(*data);
  printf("%s", msg);
  return (exit_code);
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
