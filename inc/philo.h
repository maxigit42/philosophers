/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:36:41 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:51 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;

	int				id;
	int				meals;
	int				eating;
	unsigned long	last_meal;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;

}					t_philo;

typedef struct s_data
{
	int				nbr_philos;
	long			time_to_die;
	unsigned long	time_to_eat;
	long			time_to_sleep;
	int				meals_nbr;
	int				all_ate;
	int				finish;
	int				wait;

	int				dead;
	long			start_time;

	pthread_mutex_t	waiter;
	pthread_t		*thread_id;
	pthread_t		check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;

	t_philo			*philo;
}					t_data;

//utils
void				ft_usleep(size_t time, t_data *data);
void				ft_message(t_data *data, char *str, int id, size_t time);
size_t				get_current_time(void);
int					ft_error(t_data *data, char *msg);
int					is_nbr(char *nbr);
int					ft_strcmp(char *str1, char *str2);

void				init_args(t_data *data, char **argv, int argc);
void				wait_thread(t_data *data);

long				ft_atoi(char *str);

//init_philo
void				init_mutex(t_data *data);
int					init_malloc(t_data *data);
void				start_philo(t_data *data);
void				ft_destroy(t_data *data);

//routine
void				ft_eat(t_data *data, t_philo *philo);
void				*routine(void *arg);
void				*monitor(void *data);
int					init_threads(t_data *data);

void				*one_philo_routine(void *arg);
int					init_one_philo(t_data *data);

#endif
