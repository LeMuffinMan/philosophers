/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:26:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 19:36:17 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static bool	check_user_inputs(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage :\n./philo <number_of_philosophers> "
			"<time_to_die time_to_eat> "
			"<time_to_sleep> "
			"(optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
		return (true);
	}
	return (false);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		exit_code;

	// cas du 1 800 200 200 : il think puis prend la fourchette
	/* make re && ./bin/philo 600 300 300 300 */
	//someone die on 200 610 300 300
	// arret anormal
	data = NULL;
	if (check_user_inputs(ac))
		return (INVALID_ARG);
	exit_code = are_valids_args(av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_data(&data, av);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex(&data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_threads(&data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = main_thread_monitoring(&data);
	return (simulation_end_destroy_and_free(&data, exit_code));
}
