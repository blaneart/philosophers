/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:22:20 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 13:19:44 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		*memcp(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;
	unsigned char	*q;

	p = (unsigned char*)dst;
	i = 0;
	q = (unsigned char*)src;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dst);
}

static int		count(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i - 1);
}

static char		*itoahelper(int n, int i, char *str)
{
	str[i + count(n) + 1] = '\0';
	while (n != 0)
	{
		str[(count(n) + i)] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

char			*ft_itoa(char *str, int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			memcp(str, "-2147483648\0", 12);
			return (str);
		}
		n = -1 * n;
		str[i] = '-';
		i++;
	}
	if (n == 0)
	{
		memcp(str, "0\0", 2);
		return (str);
	}
	str = itoahelper(n, i, str);
	return (str);
}
