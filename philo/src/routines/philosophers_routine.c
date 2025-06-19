/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/19 19:49:49 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;

  philosopher = (t_philosopher *)arg;
  pthread_mutex_lock(philosopher->start_mutex); //soit je me sert que de l'etat du mutex, soit je check la valeur de start 
  if ((*philosopher->start) == true)
    pthread_mutex_unlock(philosopher->start_mutex); 
  else
    return (NULL); // gestion d'erreur ? on peut ajouter un arg dans le create pour recuperer la valeur de retour 
  printf("thread %d started\n", philosopher->id);
  /* while (1) */
  /* { */
  /*   printf("thinking\n"); */
  /*   printf("eating\n"); */
  /*   philosopher->nb_meals_eaten++; */
  /*   printf("sleeping\n"); */
  /*   //mettre un break dans ce while ou join a la fin suffit ? */
  /* } */
  /* return (0); */
  return (NULL);
}
/**/

