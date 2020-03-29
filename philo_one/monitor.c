/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:21 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 16:12:45 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor(void *data)
{
	t_data *my;

	my = (t_data *)data;
	while (!my->args->end && my->args->fin != my->args->philo_n)
	{
		pthread_mutex_lock(&my->mut->eating[my->id]);
		if ((((int)(ft_get_time() - my->args->last_eat[my->id])) >
			my->args->die) && !my->args->end)
		{
			state_to_out(" died\n", my->args, my->id, my->mut);
			my->args->end = 1;
			pthread_mutex_unlock(&my->mut->stdout);
		}
		pthread_mutex_unlock(&my->mut->eating[my->id]);
		usleep(5000);
	}
	my->args->end = 1;
	pthread_exit(NULL);
}

int		check(t_arg *args, t_mut *mut)
{
	int			i;
	pthread_t	*mon;
	t_data		*data;

	i = 0;
	if (!(mon = malloc(sizeof(pthread_t) * (args->philo_n))))
		return (1);
	if (!(data = fill_data(args, mut, mon)))
		return (1);
	while (i < args->philo_n)
	{
		pthread_create(&mon[i], NULL, monitor, (void *)&data[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < args->philo_n)
		pthread_join(mon[i++], NULL);
	while (!args->end)
	{
	}
	free(data);
	free(mon);
	return (0);
}
