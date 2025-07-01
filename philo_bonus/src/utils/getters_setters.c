/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:32:30 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:52:46 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool get_proc_end(t_simulation *simulation)
{
	int exit_code;

  sem_wait(simulation->sems.proc_end);
  exit_code = simulation->data.end;
  sem_post(simulation->sems.proc_end);
	return (exit_code);
}

int set_proc_end(t_simulation *simulation)
{
	sem_wait(simulation->sems.proc_end);
	simulation->data.end = true;
  sem_post(simulation->sems.proc_end);
  return (0);
}


