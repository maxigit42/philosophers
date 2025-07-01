/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:37:05 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/01 17:03:49 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_args(t_data *data, char **argv)
{
    data->nbr_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->meals_nbr = ft_atoi(argv[5]);
    data->dead = 0;
    if(!init_malloc(data))
        ft_error(data, "Error\nmalloc\n");
    init_mutex(data);
    start_philo(data);
}