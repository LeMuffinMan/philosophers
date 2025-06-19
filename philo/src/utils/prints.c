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

int print_log(pthread_mutex_t *write_mutex, int time, int id, t_type action)
{
  pthread_mutex_lock(write_mutex);
  if (action == FORK)
    printf("%d : %d has taken a fork\n", time, id);
  else if (action == EAT)
    printf("%d : %d is eating\n", time, id);
  else if (action == SLEEP)
    printf("%d : %d is sleeping\n", time, id);
  else if (action == THINK)
    printf("%d : %d is thinking\n", time, id);
  else if (action == DIE)
    printf("%d : %d died\n", time, id);
  pthread_mutex_unlock(write_mutex);
  return (0);
}

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
