/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:32:04 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:32:09 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].eat_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->waiter, NULL);
}

int	init_malloc(t_data *data)
{
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philo)
		ft_error(data, "Error\nmalloc\n");
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nbr_philos);
	if (!data->forks)
	{
		ft_error(data, "Error\nmalloc\n");
		free(data->philo);
	}
	data->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * data->nbr_philos);
	if (!data->thread_id)
	{
		ft_error(data, "Error\nmalloc\n");
		free(data->philo);
		free(data->forks);
	}
	init_mutex(data);
	return (1);
}

void	start_philo(t_data *data)
{
	int	i;

	i = 0;
	while (data->nbr_philos > i)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].right_fork = &data->forks[i];
		if (data->nbr_philos != 1)
			data->philo[i].left_fork = &data->forks[(i + 1) % data->nbr_philos];
		i++;
	}
}

void	ft_destroy(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->waiter);
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philo[i].eat_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->thread_id);
	free(data->philo);
	free(data->forks);
}
