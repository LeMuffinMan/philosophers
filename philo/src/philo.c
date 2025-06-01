/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:26:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 18:57:44 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>
#include "philo.h"
#include <stdio.h>

int main (int ac, char **av)
{
  t_data data;
  int exit_code;

  if (ac < 4 || ac > 5)
  {
    printf("Usage :\n./philo <number_of_philosophers time_to_die time_to_eat> <time_to_sleep> (optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
    //est-ce que le dernier argument doit forcement etre entre corchets ?
    return (1);
  }
  exit_code = init(&data, av);
  if (exit_code != 0)
    return (exit_code);
  return (0); 
}
