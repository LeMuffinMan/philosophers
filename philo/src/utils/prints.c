/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/19 19:47:33 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//a deplacer dans un init utils
int print_error_and_free(char *msg, int exit_code, t_data **data)
{
  printf("%s", msg);
  free_allocated_memory(data);
  return (exit_code);
}

int print_log(t_philosopher *philosopher, char *msg)
{
  pthread_mutex_lock(&philosopher->data->write_mutex);
  pthread_mutex_lock(&philosopher->data->time_mutex);
  printf("%ld %d %s\n", get_time() - philosopher->data->start_time, philosopher->id, msg);
  pthread_mutex_unlock(&philosopher->data->write_mutex);
  pthread_mutex_unlock(&philosopher->data->time_mutex);
  return (0);
}

/* int print_log(t_philosopher *philosopher, t_type action) */
/* { */
/*   long int time; */
/**/
/*   pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
/*   pthread_mutex_lock(&philosopher->data->time_mutex); */
  /* time = get_time() - philosopher->data->start_time; */
  /* if (action == TAKE_FORK) */
  /*   printf("%ld %d has taken a fork\n", get_time() - philosopher->data->start_time, philosopher->id); */
  /* else if (action == RELEASE_FORK) */
  /*   printf("%ld %d has released a fork\n", get_time() - philosopher->data->start_time, philosopher->id); */
/*   else if (action == EAT) */
/*   { */
/*     printf("%ld %d is eating\n", get_time() - philosopher->data->start_time, philosopher->id); */
/*     philosopher->last_meal = get_time() - philosopher->data->start_time; */
/*     printf("id : %d | last_meal = %ld\n", philosopher-> id, philosopher->last_meal); */
/*   } */
/*   else if (action == SLEEP) */
/*     printf("%ld %d is sleeping\n", get_time() - philosopher->data->start_time, philosopher->id); */
/*   else if (action == THINK) */
/*     printf("%ld %d is thinking\n", get_time() - philosopher->data->start_time, philosopher->id); */
/*   else if (action == DIE) */
/*     printf("%ld %d died\n", get_time() - philosopher->data->start_time, philosopher->id); */
/*   pthread_mutex_unlock(&philosopher->data->time_mutex); */
/*   pthread_mutex_unlock(&philosopher->data->write_mutex); */
/*   return (0); */
/* } */

/* int print_update(int time_elapsed, int philo, t_type type) */
/* { */
/*   char *s; */
/**/
/*   if (type == FORK) */
/*     s = "has taken a fork\n"; */
/*   if (type == EAT) */
/*     s = "is eating\n"; */
/*   if (type == SLEEP) */
/*     s = "is sleeping\n"; */
/*   if (type == THINK) */
/*     s = "is thinking\n"; */
/*   if (type == DIE) */
/*     s = "died\n"; */
/*   s = ft_strjoin3(ft_itoa(time_elapsed), ft_itoa(philo), s); */
/*   if (!s) */
/*     return (-1); */
/*   write(1, s, ft_strlen(s)); */
/*   free(s); */
/*   return (0); */
/* } */
