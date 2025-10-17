/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcao <lcao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:58:26 by lcao              #+#    #+#             */
/*   Updated: 2025/10/01 16:58:35 by lcao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->data->time_to_die + 1);
}

static void	eat_meal(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
}

static void	take_forks_and_eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		handle_single_philo(philo);
		return ;
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	eat_meal(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	should_stop(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->death_mutex);
	result = (philo->data->someone_died || philo->data->finished);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (result);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (!should_stop(philo))
	{
		take_forks_and_eat(philo);
		if (should_stop(philo) || philo->data->num_philos == 1)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		if (should_stop(philo))
			break ;
		print_status(philo, "is thinking");
		if (philo->data->num_philos % 2 == 1)
			usleep((philo->data->time_to_eat * 1000) / philo->data->num_philos);
	}
	return (NULL);
}
