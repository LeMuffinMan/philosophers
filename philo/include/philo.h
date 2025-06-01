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

#ifndef PHILO_H
# define PHILO_H

typedef struct s_data
{

} t_data;

typedef enum e_type
{
  FORK,
  EAT,
  SLEEP,
  THINK,
  DIE
} t_type;

//init.c
int init(t_data *data, char **av);

//prints
int print_update(int time_elapsed, int philo, t_type type);
int print_error(char *input, char *arg_type, t_data *data);
int print_update(int time_elapsed, int philo, t_type type);

//str_utils
char *ft_itoa(int n);
int ft_strlen(char *str);
int copy_chars(char **dest, char *src, int dest_i, int src_i);
char *ft_strjoin3(char *time_elapsed, char *philo, char *action);
int ft_atoi(char *str);

#endif 

