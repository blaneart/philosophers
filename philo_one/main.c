/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:08:23 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 16:41:12 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_error(void)
{
	write(2, "Arguments are wrong\n", 20);
	return (1);
}

t_data				*fill_data(t_arg *args, t_mut *mut, pthread_t *thread)
{
	int		i;
	t_data	*data;

	i = 0;
	if (!(data = malloc(sizeof(t_data) * args->philo_n)))
		return (NULL);
	while (i < args->philo_n)
	{
		(data[i]).id = i;
		(data[i]).args = args;
		(data[i]).mut = mut;
		data[i].thread = &thread[i];
		i++;
	}
	return (data);
}

int					start_init(t_arg *args)
{
	int i;

	i = 0;
	args->end = 0;
	args->fin = 0;
	if (!(args->last_eat = malloc(sizeof(unsigned long int) * args->philo_n)))
		return (1);
	while (i < args->philo_n)
	{
		args->last_eat[i] = ft_get_time();
		i++;
	}
	return (0);
}

void				destroy(t_arg *args, t_mut *mut)
{
	int i;

	i = 0;
	while (i < args->philo_n)
	{
		pthread_mutex_destroy(&mut->eating[i]);
		pthread_mutex_destroy(&mut->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&mut->stdout);
	free(mut->forks);
	free(mut->eating);
	free(args->last_eat);
}

int					main(int argc, char **argv)
{
	t_arg	args;
	t_mut	mut;

	args.start = ft_get_time();
	if (ft_parse(&args, argc, argv) == 0)
		return (ft_error());
	else if (start_init(&args) || mutex_init(&mut, args) ||
		(thread_init(&args, &mut)))
		write(1, "Error\n", 6);
	destroy(&args, &mut);
	return (0);
}
