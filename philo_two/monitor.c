/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:21 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 19:50:28 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor(void *data)
{
	t_data	*my;
	int		i;

	i = 0;
	my = (t_data *)data;
	while (!my->args->end && my->args->fin != my->args->philo_n)
	{
		sem_wait(my->sem->eating[my->id]);
		if ((((int)(ft_get_time() - my->args->last_eat[my->id])) >
			my->args->die) && !my->args->end)
		{
			state_to_out(" died\n\0", my->args, my->id, my->sem);
			my->args->end = 1;
			sem_post(my->sem->stdout);
			pthread_exit(NULL);
		}
		sem_post(my->sem->eating[my->id]);
		usleep(5000);
	}
	my->args->end = 1;
	pthread_exit(NULL);
}

int		check(t_arg *args, t_sem *sem)
{
	int			i;
	pthread_t	*mon;
	t_data		*data;

	i = 0;
	if (!(mon = malloc(sizeof(pthread_t) * (args->philo_n))))
		return (1);
	if (!(data = fill_data(args, sem, mon)))
		return (1);
	while (i < args->philo_n)
	{
		pthread_create(&mon[i], NULL, monitor, (void *)&data[i]);
		i++;
	}
	i = 0;
	while (i < args->philo_n)
	{
		pthread_join(mon[i], NULL);
		i++;
	}
	return (0);
}
