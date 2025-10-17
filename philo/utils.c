/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcao <lcao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:59:11 by lcao              #+#    #+#             */
/*   Updated: 2025/09/30 17:33:09 by lcao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
}

static int	should_print(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->death_mutex);
	result = (!philo->data->someone_died && !philo->data->finished);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (result);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	if (!should_print(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (should_print(philo))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
