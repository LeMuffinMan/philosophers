/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:17:14 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 15:18:47 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_meals_limit(t_data **data, char **av)
{
	(*data)->meals_limit = ft_atoi(av[5]);
	if ((*data)->meals_limit <= 0)
		return (init_data_print_error_and_free(
				"Incorrect number of times each philosopher must eat\n",
				INVALID_ARG, data));
	return (0);
}

int	init_user_inputs(t_data **data, char **av)
{
	//1\00 passe !!! 
	(*data)->nb_philo = ft_atoi(av[1]);
	if ((*data)->nb_philo <= 0)
		return (init_data_print_error_and_free(
				"Incorrect number_of_philosophers\n",
				INVALID_ARG, data));
	(*data)->time_to_die = ft_atoi(av[2]);
	if ((*data)->time_to_die <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_die\n",
				INVALID_ARG, data));
	(*data)->time_to_eat = ft_atoi(av[3]);
	if ((*data)->time_to_eat <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_eat\n",
				INVALID_ARG, data));
	(*data)->time_to_sleep = ft_atoi(av[4]);
	if ((*data)->time_to_sleep <= 0)
		return (init_data_print_error_and_free("Incorrect time_to_sleep\n",
				INVALID_ARG, data));
	if (av[5])
		return (init_meals_limit(data, av));
	else
		(*data)->meals_limit = -1;
	return (0);
}
