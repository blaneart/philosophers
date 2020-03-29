/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:08 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 16:30:46 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	start_to_eat(t_data *data)
{
	pthread_mutex_lock(&data->mut->forks[data->id]);
	state_to_out(" has taken the fork\n", data->args, data->id, data->mut);
	pthread_mutex_lock(&data->mut->forks[(data->id + 1) % data->args->philo_n]);
	state_to_out(" has taken the fork\n", data->args, data->id, data->mut);
	state_to_out(" is eating\n", data->args, data->id, data->mut);
	pthread_mutex_lock(&data->mut->eating[data->id]);
	data->args->last_eat[data->id] = ft_get_time();
	usleep(data->args->eat * 1000);
	pthread_mutex_unlock(&data->mut->eating[data->id]);
	pthread_mutex_unlock(&data->mut->forks[data->id]);
	pthread_mutex_unlock(&data->mut->forks[(data->id + 1) %
			data->args->philo_n]);
}

void	*philo_action(void *data)
{
	int		i;
	t_data	*my;

	my = (t_data *)data;
	i = 0;
	while (1)
	{
		state_to_out(" is thinking\n", my->args, my->id, my->mut);
		start_to_eat(my);
		i++;
		if (my->args->eat_n != -1 && i >= my->args->eat_n)
			break ;
		state_to_out(" is sleeping\n", my->args, my->id, my->mut);
		usleep(my->args->sleep * 1000);
	}
	my->args->fin++;
	pthread_exit(NULL);
}

int		ft_free_data_threads(t_data *data, pthread_t *thread)
{
	free(data);
	free(thread);
	return (0);
}

int		thread_init(t_arg *args, t_mut *mut)
{
	pthread_t	*threads;
	int			i;
	t_data		*data;
	void		*status;

	i = 0;
	args->start = ft_get_time();
	if (!(threads = malloc(sizeof(pthread_t) * (args->philo_n))))
		return (1);
	if (!(data = fill_data(args, mut, threads)))
		return (1);
	while (i < args->philo_n)
	{
		pthread_create(&threads[i], NULL, philo_action, (void *)&data[i]);
		usleep(10);
		i++;
	}
	if (!check(args, mut))
		return (ft_free_data_threads(data, threads));
	i = 0;
	while (i < args->philo_n)
		pthread_join(threads[i++], &status);
	return (ft_free_data_threads(data, threads));
}
