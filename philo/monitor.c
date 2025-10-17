/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcao <lcao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:58:08 by lcao              #+#    #+#             */
/*   Updated: 2025/10/02 19:34:47 by lcao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	announce_death(t_data *data, int i, long current_time)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", current_time - data->start_time,
		data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

int	check_if_dead(t_data *data)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	i = 0;
	current_time = get_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		time_since_meal = current_time - data->philos[i].last_meal_time;
		if (time_since_meal >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			announce_death(data, i, current_time);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

int	check_meals_done(t_data *data)
{
	int	i;
	int	all_done;

	if (data->meals_required == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->meals_required)
			all_done = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (all_done)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->finished = 1;
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (all_done);
}

void	monitor_simulation(t_data *data)
{
	while (!data->someone_died && !data->finished)
	{
		if (check_if_dead(data) || check_meals_done(data))
			break ;
		usleep(50);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]);
		i++;
	}
	monitor_simulation(data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
