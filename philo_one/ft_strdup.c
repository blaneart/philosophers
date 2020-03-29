/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:46:44 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/23 14:19:45 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static size_t	len(const char *s1)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

char			*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	length;
	size_t	i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	length = len(s1);
	if (!(ret = (char*)malloc(sizeof(char) * (length + 1))))
		return (0);
	while (i < length)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
