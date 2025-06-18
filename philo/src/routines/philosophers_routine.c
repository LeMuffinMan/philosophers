/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/14 18:20:14 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
//pas clair le arg
/* void *philo_routine(void *arg) */
/* {     */
/*   t_philosopher *philosopher; */
/**/
/*   philosopher = (t_philosopher *)arg; */
/*   //mon mutex_start en dans ma struct data, et dans chaque philo j'ai un pointeur sur mutex_start : ca marche ? */
/*   pthread_mutex_lock(philosopher->mutex_start); */
/*   pthread_mutex_unlock(philosopher->mutex_start);  */
/*   printf("thread %d started\n", philosopher->id); */
/*   while (1) */
/*   { */
/*     printf("thinking\n"); */
/*     printf("eating\n"); */
/*     philosopher->nb_meals_eaten++; */
/*     printf("sleeping\n"); */
/*     //mettre un break dans ce while ou join a la fin suffit ? */
/*   } */
/*   return (0); */
/* } */
/**/

