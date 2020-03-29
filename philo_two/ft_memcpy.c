/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:36:06 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 17:01:52 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
	p[i] = '\0';
	return (dst);
}
