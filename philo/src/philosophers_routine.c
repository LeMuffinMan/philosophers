/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/20 17:22:29 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;

  philosopher = (t_philosopher *)arg;
  pthread_mutex_lock(philosopher->start_mutex); //soit je me sert que de l'etat du mutex, soit je check la valeur de start 
  if ((*philosopher->start_time) != -1)
  {
    pthread_mutex_unlock(philosopher->start_mutex); 
    pthread_mutex_lock(philosopher->write_mutex);
    printf("thread %d started at %ld\n", philosopher->id, (get_time() - *(philosopher->start_time)));
    pthread_mutex_unlock(philosopher->write_mutex);
  }
  else
    return (NULL); // gestion d'erreur ? on peut ajouter un arg dans le create pour recuperer la valeur de retour 
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

