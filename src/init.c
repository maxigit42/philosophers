/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:37:05 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:31:30 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *data, char **argv, int argc)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nbr = ft_atoi(argv[5]);
	else
		data->meals_nbr = -1;
	data->dead = 0;
	data->wait = 1;
	if (!init_malloc(data))
		ft_error(data, "Error\nmalloc\n");
	start_philo(data);
}

void	wait_thread(t_data *data)
{
	pthread_mutex_lock(&data->waiter);
	while (data->wait)
		;
	pthread_mutex_unlock(&data->waiter);
}
