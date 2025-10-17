/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcao <lcao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:57:57 by lcao              #+#    #+#             */
/*   Updated: 2025/10/02 16:27:16 by lcao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_arg_err(char **av, int ac)
{
	int	i;

	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) <= 0)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (1);
	i = 2;
	while (i < ac)
	{
		if ((i != 5 && ft_atoi(av[i]) <= 0) || !is_valid_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6 || has_arg_err(av, ac))
	{
		printf("Error:Invalid arguments\n");
		return (1);
	}
	if (parse_args(ac, av, &data) != 0)
	{
		printf("Usage: %s num_philos time_die time_eat time_sleep [meals]\n",
			av[0]);
		return (1);
	}
	if (init_data(&data) != 0)
	{
		printf("Error: Init failed\n");
		return (1);
	}
	start_simulation(&data);
	cleanup_data(&data);
	return (0);
}
