/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:01 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 19:33:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static bool	try_to_catch_fork(t_philosopher *philosopher, int fork_to_catch, bool attempt)
{
	while (!get_fork_state(philosopher, fork_to_catch) && !is_simulation_over(philosopher))
	{
		/* if (is_simulation_over(philosopher)) */
		/* 	return (false); */
		usleep(100);
		/* if (is_simulation_over(philosopher)) */
		/* 	return (false); */
		if (attempt == true)
			return (false);
	}
	return (true);
}

bool take_two_forks(t_philosopher *philosopher)
{
	int left;
	int right;
	int first;
	int second;
	int exit_code;

	left = philosopher->id - 1;
	right = philosopher->id % philosopher->nb_philo;
  if (philosopher->id % 2 == 0)
  {
    pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
    while (philosopher->data->forks[left] == false && !is_simulation_over(philosopher)) 
    {
      pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
      usleep(50);
      pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
    }
    philosopher->data->forks[left] = false;
    pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
		if (!print_log(&philosopher->data, philosopher, "has taken a fork"))
			return (false);
    pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
    while (philosopher->data->forks[right] == false)
    {
      pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
    	if (is_simulation_over(philosopher))
    	{
    		set_fork(philosopher, left, true);
    		return (false);
    	}
      usleep(50);
      pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
    }
    philosopher->data->forks[right] = false;
    pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
		if (!print_log(&philosopher->data, philosopher, "has taken a fork"))
			return (false);
  }
  else
  {
    pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
    while (philosopher->data->forks[left] == false) 
    {
      pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
      usleep(50);
      pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
    }
    philosopher->data->forks[right] = false;
    pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
		if (!print_log(&philosopher->data, philosopher, "has taken a fork"))
			return (false);
    pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
    while (philosopher->data->forks[left] == false) 
    {
      pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
    	if (is_simulation_over(philosopher))
    	{
    		set_fork(philosopher, left, true);
    		return (false);
    	}
      usleep(50);
      pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
    }
    philosopher->data->forks[left] = false;
    pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
		if (!print_log(&philosopher->data, philosopher, "has taken a fork"))
			return (false);
  }
  return (true);
}

bool	release_forks(t_philosopher *philosopher)
{
	int		left;
	int		right;
	bool	exit_code;

	left = philosopher->id - 1;
	right = (philosopher->id) % philosopher->nb_philo;
	if (is_simulation_over(philosopher))
		return (false);
	if (philosopher->id % 2 == 0)
	{
		set_fork(philosopher, left, true);
		set_fork(philosopher, right, true);
	}
	else
	{
		set_fork(philosopher, right, true);
		set_fork(philosopher, left, true);
	}
	if (is_simulation_over(philosopher))
		return (false);
	/* if (philosopher->id != 1) */
	/* 	printf("caught fork %d and %d\n", left, right); */
	return (true);
}
