/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilline <mwilline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:36:01 by mwilline          #+#    #+#             */
/*   Updated: 2025/07/07 20:28:46 by mwilline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		ft_error(data, "Invalid Nº of args");
	i = 1;
	while (argv[i])
	{
		if (!is_nbr(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (!check_args(&data, argc, argv))
		ft_error(&data, "Only numbers");
	init_args(&data, argv, argc);
	if (data.nbr_philos == 1)
		init_one_philo(&data);
	else
		init_threads(&data);
	while (i < data.nbr_philos)
	{
		printf("%d\n", data.philo[i].meals);
		i++;
	}
	ft_destroy(&data);
	return (0);
}
