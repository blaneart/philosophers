/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:35:02 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:06:36 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void		state_to_char(char *state, t_arg *args, int n, char result[])
{
	int size;
	int time;

	time = (int)(ft_get_time() - args->start);
	ft_itoa(&result[0], time);
	size = ft_strlen(result);
	result[size] = ' ';
	ft_itoa(&result[size + 1], (n + 1));
	ft_memcpy(&result[ft_strlen(result)], state, ft_strlen(state));
}

void		state_to_out(char *state, t_arg *args, int n, t_sem *sem)
{
	char	result[1024];
	int		size;

	state_to_char(state, args, n, result);
	size = ft_strlen(result);
	sem_wait(sem->stdout);
	if (!ft_strncmp(state, " died\n\0", 5) && !args->end)
	{
		write(1, result, size);
		sem_post(sem->stdout);
		return ;
	}
	else if (!args->end && ft_strncmp(state, " died\n\0", 5) != 0)
	{
		write(1, result, size);
	}
	sem_post(sem->stdout);
	ft_memset(result, '\0');
}
