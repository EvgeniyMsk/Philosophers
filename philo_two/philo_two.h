/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:41:39 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:42:55 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define END 1
# define SUCCESS 0
# define DIED -1
# define WRONG_ARG -2
# define MALLOC -3
# define SEMAPHORE -4
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
	sem_t			*forks;
	sem_t			*a_eat;
	struct timeval	*t_start;
}					t_param;
typedef struct		s_philo
{
	size_t			n;
	size_t			n_eat;
	t_param			*param;
	pthread_t		*thread;
	struct timeval	*t_last_meal;
	sem_t			*sem_last_meal;
	void			*next;
}					t_philo;
typedef struct		s_task_2
{
	t_param			*param;
	t_philo			*philo;
}					t_task_2;
int					init(int ac, char **av, t_task_2 *p);
int					ft_initialize_ph(t_task_2 *p);
int					run_philo(t_task_2 *p);
void				*ft_do_processing(void *args);
int					ft_atoi(char *str, size_t *n);
t_param				*ft_param_dup(t_param *param);
int					print_error(int error);
int					print(struct timeval *st, struct timeval *tv,
										size_t number, char *msg);
int					ft_clean(t_task_2 *p);

#endif
