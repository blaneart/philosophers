/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:24:12 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:54:37 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_data				*fill_data(t_arg *args, t_sem *sem)
{
	int		i;
	t_data	*data;

	i = 0;
	if (!(data = malloc(sizeof(t_data) * (args->philo_n))))
		return (NULL);
	while (i < args->philo_n)
	{
		(data[i]).id = i;
		(data[i]).args = args;
		(data[i]).sem = sem;
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
	if (!(args->last_eat = malloc(sizeof(unsigned long int) * (args->philo_n))))
		return (1);
	while (i < args->philo_n)
	{
		args->last_eat[i] = ft_get_time();
		i++;
	}
	return (0);
}

int					ft_sem_init(t_arg *args, t_sem *sem)
{
	int		i;
	char	*fo;
	char	*out;
	char	na[2048][2048];

	fo = "/forks";
	out = "/out";
	i = 0;
	sem_unlink(fo);
	if ((sem->forks = sem_open(fo, O_CREAT, 0644, args->philo_n)) == SEM_FAILED)
		return (1);
	sem_unlink(out);
	if ((sem->stdout = sem_open(out, O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	while (i < args->philo_n)
	{
		na[i][0] = '/';
		ft_itoa(&na[i][1], i);
		sem_unlink(na[i]);
		if ((sem->eating[i] = sem_open(na[i], O_CREAT, 0644, 1)) == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

int					ft_unlink(t_sem *sem, t_arg *args)
{
	int i;

	i = 0;
	sem_close(sem->forks);
	sem_close(sem->stdout);
	while (i < args->philo_n)
	{
		sem_close(sem->eating[i]);
		i++;
	}
	i = 0;
	return (0);
}

int					main(int argc, char **argv)
{
	t_arg	args;
	t_sem	sem;

	if (ft_parse(&args, argc, argv) == 0)
		return (ft_error());
	else if (!(sem.eating = malloc(sizeof(sem_t *) * args.philo_n)))
		return (1);
	else if (start_init(&args) || ft_sem_init(&args, &sem) ||
		(process_init(&args, &sem)))
		write(2, "Error\n", 6);
	ft_unlink(&sem, &args);
	return (0);
}
