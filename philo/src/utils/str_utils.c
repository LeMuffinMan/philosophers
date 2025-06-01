/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 18:56:05 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *ft_itoa(int n)
{
  char *str;
  int nb;
  int digits;
  int i;

  nb = n;
  while (nb > 10)
  {
    digits++;
    nb = nb / 10;
  }
  str = malloc(sizeof(char) * digits + 1);
  if (!str)
    return (NULL);
  str[digits + 1] = '\0';
  while (digits >= 0)
  {
    str[digits] = n % 10;
    digits--; 
    n = n / 10;
  }
  return (str);
}

int ft_strlen(char *str)
{
  int i;

  i = 0;
  if (!str || !*str)
    return (0);
  while (str[i])
    i++;
  return (i);
}

int copy_chars(char **dest, char *src, int dest_i, int src_i)
{
  while (src[src_i])
  {
    *dest[dest_i] = src[src_i];
    dest_i++;
    src_i++;
  }
  return (dest_i);
}

char *ft_strjoin3(char *time_elapsed, char *philo, char *action)
{
  int i;
  int j;
  char *log;

  if (!time_elapsed || !philo)
    return (NULL);
  log = malloc(sizeof(char) * ft_strlen(time_elapsed) + ft_strlen(philo) + ft_strlen(action) + 1);
  if (!log)
    return (NULL);
  i = copy_chars(&log, time_elapsed, 0, 0);
  i = copy_chars(&log, philo, i, 0);
  i = copy_chars(&log, action, i, 0);
  log[i] = '\0';
  free(time_elapsed);
  free(philo);
  return (log);
}

int ft_atoi(char *str)
{
  int res;
  int i;

  i = 0;
  res = 0;
  while (str[i])
  {
    res = res * 10 + str[i] - '0';
    i++;
  }
  return (res);
}
