/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 19:42:08 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

int ft_strjoin3(char *time_elapsed, char *philo, char *action)
{
  int i;
  int j;
  char *log;

  log = malloc(sizeof(char) * ft_strlen(time_elapsed) + ft_strlen(philo) + ft_strlen(action) + 1);
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
  return (res)
}
