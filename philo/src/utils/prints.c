/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 19:42:01 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int print_error_and_free(char *msg, int exit_code, t_data *data)
{
  printf("%s", msg);
  if (data)
    free(data);
  return (exit_code);
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
