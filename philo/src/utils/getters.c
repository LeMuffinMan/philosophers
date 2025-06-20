/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:17:25 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/20 17:27:24 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h> // POUR NULL !!

long int get_time(void)
{
  struct timeval tv;
  
  /* pthread_mutex_lock(write_mutex); */
  gettimeofday(&tv, NULL);
  //gerer l'erreur du gettimeofday ? 
  /* pthread_mutex_unlock(write_mutex); */
  return (tv.tv_usec); 
}
