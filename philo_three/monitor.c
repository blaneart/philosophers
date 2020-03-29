/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:21 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 14:07:44 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor(void *data)
{
	t_data	*my;
	int		i;

	i = 0;
	my = (t_data *)data;
	while (!my->args->end)
	{
		sem_wait(my->sem->eating[my->id]);
		if ((((int)(ft_get_time() - my->args->last_eat[my->id])) >
			my->args->die) && !my->args->end)
		{
			state_to_out(" died\n", my->args, my->id, my->sem);
			my->args->end = 1;
			exit(1);
		}
		sem_post(my->sem->eating[my->id]);
		usleep(5000);
	}
	my->args->end = 1;
	exit(1);
	pthread_exit(NULL);
}
