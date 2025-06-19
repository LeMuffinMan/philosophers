/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/19 20:02:23 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdlib.h> */
/* #include <unistd.h> */
/* #include <stdio.h> */
#include <limits.h>
#include <stdbool.h>
#include "philo.h"
#include <stdio.h>

int ft_atoi(const char *nptr)
{
    unsigned long long    n;
    
    n = 0;
    while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
      nptr++;
    if (*nptr == '+')
      nptr++;
    while (*nptr >= '0' && *nptr <= '9')
    {
      n = n * 10 + (*nptr - '0');
      nptr++;
      if (n > INT_MAX)
        return (-1);
    }
    return ((int)n);
}

bool is_only_digits(char *str)
{
  int i;
  
  i = 0;
  while (str[i])
  {
    if (str[i] < '0' || str[i] > '9')
      return (false);
    i++;
  }
  return (true);
}

int are_valids_args(char **av)
{
  if (!is_only_digits(av[1]) || av[1][0] == '-' ||
      !is_only_digits(av[2]) || av[2][0] == '-' ||
      !is_only_digits(av[3]) || av[3][0] == '-' ||
      !is_only_digits(av[4]) || av[4][0] == '-' ||
      (av[5] && (!is_only_digits(av[5]) || av[5][0] == '-')))
  {
    printf("Invalid(s) argument(s)\n");
    return (INVALID_ARG);
  }
  return (0);
}

/**/
/* char *ft_itoa(int n) */
/* { */
/*   char *str; */
/*   int nb; */
/*   int digits; */
/*   int i; */
/**/
/*   nb = n; */
/*   while (nb > 10) */
/*   { */
/*     digits++; */
/*     nb = nb / 10; */
/*   } */
/*   str = malloc(sizeof(char) * digits + 1); */
/*   if (!str) */
/*     return (NULL); */
/*   str[digits + 1] = '\0'; */
/*   while (digits >= 0) */
/*   { */
/*     str[digits] = n % 10; */
/*     digits--;  */
/*     n = n / 10; */
/*   } */
/*   return (str); */
/* } */
/**/
/* int ft_strlen(char *str) */
/* { */
/*   int i; */
/**/
/*   i = 0; */
/*   if (!str || !*str) */
/*     return (0); */
/*   while (str[i]) */
/*     i++; */
/*   return (i); */
/* } */
/**/
/* int copy_chars(char **dest, char *src, int dest_i, int src_i) */
/* { */
/*   while (src[src_i]) */
/*   { */
/*     *dest[dest_i] = src[src_i]; */
/*     dest_i++; */
/*     src_i++; */
/*   } */
/*   return (dest_i); */
/* } */
/**/
/* char *ft_strjoin3(char *time_elapsed, char *philo, char *action) */
/* { */
/*   int i; */
/*   int j; */
/*   char *log; */
/**/
/*   if (!time_elapsed || !philo) */
/*     return (NULL); */
/*   log = malloc(sizeof(char) * ft_strlen(time_elapsed) + ft_strlen(philo) + ft_strlen(action) + 1); */
/*   if (!log) */
/*     return (NULL); */
/*   i = copy_chars(&log, time_elapsed, 0, 0); */
/*   i = copy_chars(&log, philo, i, 0); */
/*   i = copy_chars(&log, action, i, 0); */
/*   log[i] = '\0'; */
/*   free(time_elapsed); */
/*   free(philo); */
/*   return (log); */
/* } */
/**/
/* int ft_atoi(char *str) */
/* { */
/*   int res; */
/*   int i; */
/**/
/*   i = 0; */
/*   res = 0; */
/*   while (str[i]) */
/*   { */
/*     res = res * 10 + str[i] - '0'; */
/*     i++; */
/*   } */
/*   return (res); */
/* } */
