/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:39:01 by mwilline          #+#    #+#             */
/*   Updated: 2025/06/30 19:53:02 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_error(t_data *data, char *msg)
{
    printf("%s\n", msg);
    ft_destroy(data);
    return(EXIT_FAILURE);
}

int is_nbr(char *nbr)
{
    int i;

    i = 0;
    while(nbr[i])
    {
        if(nbr[i] >= '0' && nbr[i] <= '9')
            i++;
        else
            return(0);
    }
    return(1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000
		+ (time.tv_usec / 1000));
}
void    ft_usleep(size_t time, t_data *data)
{
    size_t start;
    start = get_current_time();
    while((get_current_time() - start) < time)
        usleep(data->nbr_philos * 2);
}

void    ft_message(t_data *data, char *str)
{
    pthread_mutex_lock(&data->print_mutex);
    if(!data->dead)
        printf("%ld %d %s\n",get_current_time() - data->start_time, data->philo->id, str);
    if(data->dead)
    {
        pthread_mutex_lock(&data->death_mutex);
        printf("%ld %d %s\n",get_current_time() - data->start_time, data->philo->id, str);
        pthread_mutex_unlock(&data->death_mutex);
        ft_destroy(data);
    }
    pthread_mutex_unlock(&data->print_mutex);
}