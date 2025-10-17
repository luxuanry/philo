/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcao <lcao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:02:33 by lcao              #+#    #+#             */
/*   Updated: 2025/10/02 16:29:00 by lcao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;
	long			start_time;
	int				someone_died;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	table_mutex;
	t_philo			*philos;
}	t_data;

int		parse_args(int argc, char **argv, t_data *data);
int		init_data(t_data *data);
void	start_simulation(t_data *data);
void	*philosopher_routine(void *arg);
void	cleanup_data(t_data *data);
long	get_time(void);
void	ft_usleep(long ms);
void	print_status(t_philo *philo, char *status);
int		check_if_dead(t_data *data);
int		check_meals_done(t_data *data);
void	monitor_simulation(t_data *data);

int		is_valid_number(const char *str);
int		ft_atoi(const char *str);

#endif