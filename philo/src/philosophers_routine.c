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
#include <unistd.h> //usleep

int thinking(t_philosopher *philosopher)
{
  print_log(philosopher, THINK);
  usleep(philosopher->time_to_eat * 2 / philosopher->time_to_sleep);
  return (0);
}

int eating(t_philosopher *philosopher)
{
  print_log(philosopher, EAT);
  usleep(philosopher->time_to_eat * 1000);
  return (0);
}

int sleeping(t_philosopher *philosopher)
{
  print_log(philosopher, SLEEP);
  usleep(philosopher->time_to_sleep * 1000);
  return (0);
}

//revoir la logique ici pour quoie le chiffre le plus petit en prio ?
/* int take_forks(t_philosopher *philosopher) */
/* { */
/*   if (philosopher->id < (philosopher->id + 1) % philosopher->data->nb_philo) */
/*   { */
/*     pthread_mutex_lock(&philosopher->data->forks_mutex[philosopher->id]); */
/*     philosopher->data->forks[philosopher->id] = false; */
/*     print_log(philosopher, take_fork); */
/*     pthread_mutex_lock(&philosopher->data->forks_mutex[(philosopher->id + 1) % philosopher->nb_philo]); */
/*     philosopher->data->forks[(philosopher->id + 1) % philosopher->nb_philo] = false; */
/*     print_log(philosopher, take_fork); */
/*   } */
/*   else */
/*   { */
/*     pthread_mutex_lock(&philosopher->data->forks_mutex[(philosopher->id) % philosopher->nb_philo]); */
/*     philosopher->data->forks[(philosopher->id + 1) % philosopher->nb_philo] = false; */
/*     print_log(philosopher, take_fork); */
/*     pthread_mutex_lock(&philosopher->data->forks_mutex[philosopher->id]); */
/*     philosopher->data->forks[philosopher->id] = false; */
/*     print_log(philosopher, take_fork); */
/*   } */
/*   return (0); */
/* } */
/**/
/* int release_forks(t_philosopher *philosopher) */
/* { */
/*   if (philosopher->id < (philosopher->id + 1) % philosopher->data->nb_philo) */
/*   { */
/*     pthread_mutex_unlock(&philosopher->data->forks_mutex[(philosopher->id + 1) % 2]); */
/*     philosopher->data->forks[(philosopher->id + 1) % 2] = true; */
/*     print_log(philosopher, release_fork); */
/*     pthread_mutex_unlock(&philosopher->data->forks_mutex[philosopher->id]); */
/*     philosopher->data->forks[philosopher->id] = true; */
/*     print_log(philosopher, release_fork); */
/*   } */
/*   else */
/*   { */
/*     pthread_mutex_unlock(&philosopher->data->forks_mutex[philosopher->id]); */
/*     philosopher->data->forks[philosopher->id] = true; */
/*     print_log(philosopher, release_fork); */
/*     pthread_mutex_unlock(&philosopher->data->forks_mutex[(philosopher->id) % 2]); */
/*     philosopher->data->forks[(philosopher->id + 1) % 2] = true; */
/*     print_log(philosopher, release_fork); */
/*   } */
/*   return (0); */
/* } */

int take_forks(t_philosopher *philosopher)
{
    int left = philosopher->id;
    int right = (philosopher->id + 1) % philosopher->nb_philo;
    
    if (philosopher->id % 2 == 0) {
        pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
        philosopher->data->forks[left] = false;
        print_log(philosopher, TAKE_FORK);
        pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
        philosopher->data->forks[right] = false;
        print_log(philosopher, TAKE_FORK);
    } else {
        pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
        philosopher->data->forks[right] = false;
        print_log(philosopher, TAKE_FORK);
        pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
        philosopher->data->forks[left] = false;
        print_log(philosopher, TAKE_FORK);
    }
    return (0);
}

int release_forks(t_philosopher *philosopher)
{
    int left = philosopher->id;
    int right = (philosopher->id + 1) % philosopher->nb_philo;
    
    pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
    philosopher->data->forks[left] = true;
    /* print_log(philosopher, RELEASE_FORK); */
    pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
    philosopher->data->forks[right] = true;
    /* print_log(philosopher, RELEASE_FORK); */
    return (0);
}

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;

  philosopher = (t_philosopher *)arg;
  pthread_mutex_lock(&philosopher->data->time_mutex); //soit je me sert que de l'etat du mutex, soit je check la valeur de start 
  if (philosopher->data->start_time != -1)
  {
    pthread_mutex_unlock(&philosopher->data->time_mutex); 
    pthread_mutex_lock(&philosopher->data->write_mutex);
    /* printf("thread %d started at %ld\n", philosopher->id, (get_time() - *(philosopher->start_time))); */
    pthread_mutex_unlock(&philosopher->data->write_mutex);
  }
  else
    return (NULL); // gestion d'erreur ? on peut ajouter un arg dans le create pour recuperer la valeur de retour 
  while (1)
  {
    thinking(philosopher);
    take_forks(philosopher);
    eating(philosopher);
    release_forks(philosopher);
    sleeping(philosopher);
  }
  return (NULL);
}
