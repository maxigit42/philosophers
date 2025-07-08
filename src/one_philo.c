/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:37:22 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:32 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_one_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo[0].last_meal = get_current_time();
	data->start_time = data->philo[0].last_meal;
	if (pthread_create(&(data->thread_id[i]), NULL, &one_philo_routine,
			&data->philo[i]))
		ft_error(data, "Error\nThread\n");
	if (pthread_join(data->thread_id[i], NULL))
		ft_error(data, "Error\nThread\n");
	return (0);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_message(philo->data, "has taken a fork", philo->id, get_current_time());
	ft_usleep(philo->data->time_to_die, philo->data);
	ft_message(philo->data, "died", philo->id, get_current_time());
	return (NULL);
}
