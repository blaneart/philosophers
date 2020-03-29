/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:34:57 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:52:12 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_arg
{
	unsigned long	start;
	unsigned long	*last_eat;
	unsigned long	current;
	int				philo_n;
	int				die;
	int				eat;
	int				sleep;
	int				eat_n;
	int				end;
	int				fin;
}					t_arg;

typedef struct		s_mut
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating;
	pthread_mutex_t	stdout;
}					t_mut;

typedef struct		s_data
{
	int			id;
	t_arg		*args;
	pthread_t	*thread;
	t_mut		*mut;
}					t_data;

int					mutex_init(t_mut *mut, t_arg args);
void				*philo_action(void *data);
int					check(t_arg *args, t_mut *mut);
int					thread_init(t_arg *args, t_mut *mut);
long unsigned int	ft_get_time();
t_data				*fill_data(t_arg *args, t_mut *mut, pthread_t *thread);
void				state_to_out(char *state, t_arg *args, int n, t_mut *mut);
char				*ft_itoa(char *str, int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_parse(t_arg *args, int argc, char **argv);
#endif
