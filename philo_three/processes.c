/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:24:36 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 20:04:51 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	start_to_eat(t_data *data)
{
	sem_wait(data->sem->forks);
	state_to_out(" has taken the fork\n",
				data->args, data->id, data->sem);
	sem_wait(data->sem->forks);
	state_to_out(" has taken the fork\n",
				data->args, data->id, data->sem);
	state_to_out(" is eating\n", data->args, data->id, data->sem);
	sem_wait(data->sem->eating[data->id]);
	data->args->last_eat[data->id] = ft_get_time();
	usleep(data->args->eat * 1000);
	sem_post(data->sem->eating[data->id]);
	sem_post(data->sem->forks);
	sem_post(data->sem->forks);
}

void	philo_action(t_data *data)
{
	pthread_t	mon;
	int			i;

	i = 0;
	pthread_create(&mon, NULL, &monitor, data);
	while (1)
	{
		state_to_out(" is thinking\n", data->args, data->id, data->sem);
		start_to_eat(data);
		i++;
		if (data->args->eat_n != -1 && i >= data->args->eat_n)
			break ;
		state_to_out(" is sleeping\n", data->args, data->id, data->sem);
		usleep(data->args->sleep * 1000);
	}
	exit(0);
}

void	wait_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || ((WIFEXITED(status)
				|| WIFSIGNALED(status)) && status != 0))
		{
			while (i < data->args->philo_n)
				kill(data[i++].pid, SIGINT);
			exit(WIFEXITED(status));
		}
	}
}

int		process_init(t_arg *args, t_sem *sem)
{
	t_data	*data;
	int		i;

	i = 0;
	args->start = ft_get_time();
	if (!(data = fill_data(args, sem)))
		return (1);
	while (i < args->philo_n)
	{
		if (!(data[i].pid = fork()))
			philo_action(&data[i]);
		i++;
		usleep(10);
	}
	wait_children(data);
	return (0);
}
