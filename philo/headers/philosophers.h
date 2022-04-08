/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:09:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/08 09:44:29 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

// Style de typo :
# define _END "\x1B[0m"

// Couleurs des lettres :
# define _RED "\x1B[31m"
# define _GREEN "\x1B[32m"
# define _YELLOW "\x1B[33m"
# define _BLUE "\x1B[34m"
# define _PURPLE "\x1B[35m"

typedef struct s_infos	t_infos;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_infos
{
	int				nb_philos;
	int				ms_die;
	int				ms_eat;
	int				ms_sleep;
	int				nb_eat;
	t_philo			*philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_w;
	pthread_mutex_t	mutex_ate;
	pthread_mutex_t	mutex_dead;
};

struct s_fork
{
	int				id;
	int				used;
	pthread_mutex_t	mutex;
};

struct s_philo
{
	int				index;
	int				nb_eat;
	int				eat_time;
	int				run;
	int				dead;
	char			*state;
	pthread_t		thread;
	t_infos			*infos;
	t_fork			fork;
};

/* philo.c */
void		philo(t_infos infos);

/* actions.c */
int			get_sleep(t_philo *philo);
int			get_think(t_philo *philo);
int			get_eat(t_philo *philo);

/* forks.c */
int			first_fork(t_philo *p1, t_philo *philo, t_philo *next);
int			second_fork(t_philo *p1, t_philo *p2, t_philo *philo);
int			take_fork(t_philo *philo);
void		free_fork(t_philo *philo);

/* check_process.c */
int			ate_enough(t_philo *philos);
int			is_dead(t_philo *philos);
int			one_is_good(t_philo *philos);

/* time.c */
long		get_time(void);
long		calcul_ms(void);
void		ft_usleep(long wait);

/* messages.c */
void		msg_dead(int ms, int index, t_philo *philo);
void		msg_think(int ms, int index, t_philo *philo);
void		msg_sleep(int ms, int index, t_philo *philo);
void		msg_eat(int ms, int index, t_philo *philo);
void		msg_take(int ms, int index, t_philo *philo);

/* utils.c */
int			ft_atoi(char *nptr);
long long	ft_atoll(char *nptr);
int			ft_strcmp(char *s1, char *s2);

/* check_args.c */
int			are_valid_args(char **av);

/* errors.c */
void		error(void);
void		error_args(void);
void		error_occured(void);

#endif
