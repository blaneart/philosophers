/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:02 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:35:42 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_memset(void *s, char c)
{
	char	*q;
	int		i;

	i = 0;
	q = (char *)s;
	while (q[i])
	{
		q[i] = c;
		i++;
	}
}

void		state_to_char(char *state, t_arg *args, int n)
{
	int		size;
	char	result[2048];
	int		time;

	time = (int)(ft_get_time() - args->start);
	ft_itoa(&result[0], time);
	size = ft_strlen(result);
	result[size] = ' ';
	result[size + 1] = '\0';
	ft_itoa(&result[size + 1], (n + 1));
	ft_memcpy(&result[ft_strlen(result)], state, ft_strlen(state));
	write(1, &result[0], ft_strlen(&result[0]));
	ft_memset(result, '\0');
}

void		state_to_out(char *state, t_arg *args, int n, t_sem *sem)
{
	sem_wait(sem->stdout);
	if (!ft_strncmp(state, " died\n", 5) && !args->end)
	{
		state_to_char(state, args, n);
		exit(1);
	}
	else if (!args->end && ft_strncmp(state, " died\n", 5) != 0)
		state_to_char(state, args, n);
	if (ft_strncmp(state, " died\n", 5) != 0)
		sem_post(sem->stdout);
}
