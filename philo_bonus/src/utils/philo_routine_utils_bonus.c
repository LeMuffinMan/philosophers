/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 06:42:08 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/02 06:42:10 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	odd_philo_thinking_time(t_simulation *simulation)
{
	long int	think_time;
	long int	last_meal_time_elapsed;
	long int	time_until_starvation;

	last_meal_time_elapsed = get_time() - simulation->data.time.last_meal;
	time_until_starvation = simulation->data.time.die - last_meal_time_elapsed;
	think_time = simulation->data.time.eat;
	if (simulation->data.time.sleep < simulation->data.time.eat
		&& simulation->data.time.eat * 2
		- simulation->data.time.sleep > time_until_starvation
		&& simulation->data.time.sleep
		+ simulation->data.time.eat < simulation->data.time.die)
	{
		think_time = simulation->data.time.die;
		if (accurate_sleep(simulation, think_time) < 0)
			return (false);
	}
	return (true);
}

bool	even_philo_thinking_time(t_simulation *simulation)
{
	long int	think_time;
	long int	last_meal_time_elapsed;
	long int	time_until_starvation;

	last_meal_time_elapsed = get_time() - simulation->data.time.last_meal;
	time_until_starvation = simulation->data.time.die - last_meal_time_elapsed;
	think_time = simulation->data.time.eat / 2;
	if (simulation->data.time.sleep < simulation->data.time.eat
		&& simulation->data.time.eat
		- simulation->data.time.sleep > time_until_starvation
		&& simulation->data.time.sleep
		+ simulation->data.time.eat < simulation->data.time.die)
	{
		think_time = simulation->data.time.die;
		if (accurate_sleep(simulation, think_time) < 0)
			return (false);
	}
	return (true);
}
