/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:59:48 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:47:59 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_message(data, "has taken a fork", philo->id, get_current_time());
	pthread_mutex_lock(philo->left_fork);
	ft_message(data, "has taken a fork", philo->id, get_current_time());
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eating = 1;
	philo->meals++;
	philo->last_meal = get_current_time();
	ft_message(data, "is eating", philo->id, get_current_time());
	if (philo->meals == data->meals_nbr)
		data->finish++;
	ft_usleep((size_t)data->time_to_eat, data);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_thread(philo->data);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (philo->data->dead == 0
		&& philo->data->finish < philo->data->nbr_philos)
	{
		if (philo->meals == philo->data->meals_nbr)
			break ;
		ft_eat(philo->data, philo);
		ft_message(philo->data, "is sleeping", philo->id, get_current_time());
		ft_usleep(philo->data->time_to_sleep, philo->data);
		ft_message(philo->data, "is thinking", philo->id, get_current_time());
	}
	return ((void *)0);
}

void	*monitor(void *data)
{
	t_data	*monitor;
	int		i;

	monitor = (t_data *)data;
	wait_thread(monitor);
	while (monitor->dead == 0 && monitor->finish < monitor->nbr_philos)
	{
		i = 0;
		while ((i < monitor->nbr_philos && monitor->dead == 0)
			&& (monitor->finish < monitor->nbr_philos))
		{
			pthread_mutex_lock(&monitor->philo[i].eat_mutex);
			if ((get_current_time() - monitor->philo[i].last_meal)
				> (unsigned long)(monitor->time_to_die)
				&& monitor->philo[i].eating != 1)
			{
				monitor->dead = 1;
				ft_message(monitor, "died", monitor->philo[i].id,
					get_current_time());
			}
			pthread_mutex_unlock(&monitor->philo[i].eat_mutex);
			i++;
		}
	}
	return ((void *)0);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	if (pthread_create(&data->check, NULL, &monitor, data))
		ft_error(data, "Error\nMonitor\n");
	while (i < data->nbr_philos)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&(data->thread_id[i]), NULL, &routine,
				&data->philo[i]))
			ft_error(data, "Error\nThread\n");
		i++;
	}
	data->wait = 0;
	i = -1;
	while (++i < data->nbr_philos)
	{
		if (pthread_join(data->thread_id[i], NULL))
			ft_error(data, "Error\nJoin threads\n");
	}
	if (pthread_join(data->check, NULL))
		ft_error(data, "Error\nMonitor thread\n");
	return (0);
}
