/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:37:50 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:38:40 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					ft_pos_atoi(char *s)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (-1);
		res = res * 10 + s[i] - 48;
		i++;
	}
	return (res);
}

int					ft_error(void)
{
	write(2, "Arguments are wrong\n", 20);
	return (1);
}

int					ft_parse(t_arg *args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (((*args).philo_n = ft_pos_atoi(argv[1])) < 1)
		return (0);
	if (((*args).die = ft_pos_atoi(argv[2])) < 0)
		return (0);
	if (((*args).eat = ft_pos_atoi(argv[3])) < 0)
		return (0);
	if (((*args).sleep = ft_pos_atoi(argv[4])) < 0)
		return (0);
	if (argc == 6)
		return (((*args).eat_n = ft_pos_atoi(argv[5])) > 0);
	(*args).eat_n = -1;
	return (1);
}

long unsigned int	ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
