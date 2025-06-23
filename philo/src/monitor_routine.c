/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:12:39 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:48:32 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	are_philo_fed(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->nb_philo)
	{
		if (!get_fed_state(&(*data)->philosophers[i]))
			return (false);
		i++;
	}
	set_end(data, &(*data)->end_mutex);
	return (true);
}

static bool	is_philo_eating(t_data **data, int id)
{
	if (id == (id + 1) % (*data)->nb_philo)
		return (false);
	if (!get_fork_state(&(*data)->philosophers[id], id)
		&& !get_fork_state(&(*data)->philosophers[id], (id + 1)
			% (*data)->nb_philo))
		return (true);
	else
		return (false);
}

static int	print_death(t_data **data, int id)
{
	int	exit_code;

	exit_code = 1;
	if (!print_log(data, &(*data)->philosophers[id], "died"))
		exit_code = GETTIMEOFDAY_ERROR;
	set_end(data, &(*data)->end_mutex);
	return (exit_code);
}

static int	are_philo_starving(t_data **data)
{
	int			i;
	long int	time_elapsed;
	long int	last_meal_time;
	int			exit_code;

	i = 0;
	exit_code = 0;
	while (i < (*data)->nb_philo)
	{
		last_meal_time = get_last_meal_time(&(*data)->philosophers[i]);
		time_elapsed = get_elapsed_time_since_last_meal(data, last_meal_time);
		if (last_meal_time >= 0 && time_elapsed > (*data)->time_to_die
			&& !is_philo_eating(data, i))
			return (print_death(data, i));
		i++;
	}
	return (exit_code);
}

int	main_thread_monitoring(t_data **data)
{
	int	exit_code;

	while (1)
	{
		exit_code = are_philo_fed(data);
		if (exit_code != 0)
			return (exit_code);
		exit_code = are_philo_starving(data);
		if (exit_code != 0)
			return (exit_code != 0);
		exit_code = accurate_sleep(data, 5);
		if (exit_code == GETTIMEOFDAY_ERROR)
			return (exit_code);
	}
	return (0);
}
