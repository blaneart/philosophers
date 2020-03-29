/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:24:36 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/04 18:54:31 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

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

typedef struct		s_sem
{
	sem_t		*forks;
	sem_t		*stdout;
	sem_t		**eating;
}					t_sem;
typedef struct		s_data
{
	int			id;
	t_arg		*args;
	t_sem		*sem;
	pid_t		pid;
}					t_data;

void				philo_action(t_data *data);
int					check(t_data *data);
long unsigned int	ft_get_time();
t_data				*fill_data(t_arg *args, t_sem *sem);
void				state_to_out(char *state, t_arg *args, int n, t_sem *sem);
char				*ft_itoa(char *str, int n);
char				*ft_strdup(const char *s1);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*monitor(void *data);
int					ft_unlink(t_sem *sem, t_arg *args);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					process_init(t_arg *args, t_sem *sem);
int					ft_parse(t_arg *args, int argc, char **argv);
int					ft_error(void);
#endif
