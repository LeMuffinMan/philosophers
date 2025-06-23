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

	//revoir inversion des bools 
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
	//revoir inversion des bools 
	if (id == (id + 1) % (*data)->nb_philo)
		return (false);
	if (!get_fork_state(&(*data)->philosophers[id], id)
		&& !get_fork_state(&(*data)->philosophers[id], (id + 1)
			% (*data)->nb_philo))
		return (true);
	else
		return (false);
}

static int	are_philo_starving(t_data **data)
{
	int			i;
	long int	time_elapsed;
	long int	last_meal_time;

	//revoir inversion des bools 
	i = 0;
	while (i < (*data)->nb_philo)
	{
		last_meal_time = get_last_meal_time(&(*data)->philosophers[i]);
		pthread_mutex_lock(&(*data)->time_mutex);
		time_elapsed = get_time(data) - (*data)->start_time - last_meal_time;
		pthread_mutex_unlock(&(*data)->time_mutex);
		if (time_elapsed == GETTIMEOFDAY_ERROR)
			return (true);
		if (last_meal_time >= 0 && time_elapsed > (*data)->time_to_die
			&& !is_philo_eating(data, i))
		{
			print_log(data, &(*data)->philosophers[i], "died");
			set_end(data, &(*data)->end_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

int	main_thread_monitoring(t_data **data)
{
	int	exit_code;

	//revoir inversion des bools 
	while (1)
	{
		exit_code = are_philo_fed(data);
		if (exit_code)
		{
			return (exit_code);
		}
		exit_code = are_philo_starving(data);
		if (exit_code)
		{
			return (exit_code);
		}
		exit_code = accurate_sleep(data, 5);
		if (exit_code == GETTIMEOFDAY_ERROR)
			return (exit_code);
	}
	return (0);
}
