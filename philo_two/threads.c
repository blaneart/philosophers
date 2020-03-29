/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:08 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 19:49:20 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	start_to_eat(t_data *data)
{
	sem_wait(data->sem->forks);
	state_to_out(" has taken the fork\n\0",
				data->args, data->id, data->sem);
	sem_wait(data->sem->forks);
	state_to_out(" has taken the fork\n\0",
				data->args, data->id, data->sem);
	state_to_out(" is eating\n\0", data->args, data->id, data->sem);
	sem_wait(data->sem->eating[data->id]);
	data->args->last_eat[data->id] = ft_get_time();
	usleep(data->args->eat * 1000);
	sem_post(data->sem->eating[data->id]);
	sem_post(data->sem->forks);
	sem_post(data->sem->forks);
}

void	*philo_action(void *data)
{
	int		i;
	t_data	*my;

	my = (t_data *)data;
	i = 0;
	while (!my->args->end)
	{
		state_to_out(" is thinking\n\0", my->args, my->id, my->sem);
		start_to_eat(my);
		i++;
		if (my->args->eat_n != -1 && i >= my->args->eat_n)
			break ;
		state_to_out(" is sleeping\n\0", my->args, my->id, my->sem);
		usleep(my->args->sleep * 1000);
	}
	my->args->fin++;
	pthread_exit(NULL);
}

int		destroy(pthread_t *threads, t_arg *args)
{
	int i;

	i = 0;
	while (i < args->philo_n)
		pthread_detach(threads[i++]);
	return (0);
}

int		thread_init(t_arg *args, t_sem *sem)
{
	pthread_t	*threads;
	int			i;
	t_data		*data;

	i = 0;
	args->start = ft_get_time();
	if (!(threads = malloc(sizeof(pthread_t) * (args->philo_n))))
		return (1);
	if (!(data = fill_data(args, sem, threads)))
		return (1);
	while (i < args->philo_n)
	{
		pthread_create(&threads[i], NULL, philo_action, (void *)&data[i]);
		usleep(30);
		i++;
	}
	i = 0;
	if (!check(args, sem))
		return (destroy(threads, args));
	return (0);
}
