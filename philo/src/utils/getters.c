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
  
  gettimeofday(&tv, NULL);
  //gerer l'erreur du gettimeofday ? 
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)); 
}
