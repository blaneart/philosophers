/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:15 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/23 19:35:15 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		mutex_init(t_mut *mut, t_arg args)
{
	int i;

	i = 0;
	if (!(mut->forks = malloc(sizeof(pthread_mutex_t) * args.philo_n)))
		return (1);
	if (!(mut->eating = malloc(sizeof(pthread_mutex_t) * args.philo_n)))
		return (1);
	pthread_mutex_init(&mut->stdout, NULL);
	while (i < args.philo_n)
	{
		pthread_mutex_init(&mut->eating[i], NULL);
		pthread_mutex_init(&mut->forks[i], NULL);
		i++;
	}
	return (0);
}
