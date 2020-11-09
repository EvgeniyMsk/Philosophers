/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:11:43 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 14:52:28 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# define END 1
# define SUCCESS 0
# define DIED -1
# define WRONG_ARG -2
# define MALLOC -3
# define MUTEX -4
# define PTHREAD -5
# define SLEEP -6
# define TIME -7
# define ONE_FORK -8

typedef struct		s_param
{
	int				n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_must_eat;
	struct timeval	*t_start;
}					t_param;
typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			n_last;
}					t_fork;
typedef struct		s_philo
{
	size_t			n;
	size_t			n_eat;
	t_param			*param;
	pthread_t		*thread;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_mutex_t *lock_last_meal;
	struct timeval	*t_last_meal;
	void			*next;
}					t_philo;

typedef struct		s_task_1
{
	t_param			*param;
	t_philo			*philo;
}					t_task_1;

int					init(int ac, char **av, t_task_1 *p);
int					ft_initialize_ph(t_task_1 *p);
int					run_philo(t_task_1 *p);
void				ft_set_philosophers(t_task_1 *p);
void				*ft_do_processing(void *args);
int					ft_atoi(char *str, size_t *n);
t_param				*ft_param_dup(t_param *param);
int					print_error(int error);
int					print(struct timeval *st, struct timeval *tv,
										size_t number, char *msg);
int					ft_clean(t_task_1 *p);

#endif
