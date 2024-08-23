/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:51:39 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:04:03 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Initialize the data structure
t_data	*initialize_data(char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->death_flag = false;
	data->start_time = get_current_time();
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
	data->forks = init_forks(data);
	if (!data->forks)
		return (cleanup_data(data), NULL);
	data->philos = init_philos(data);
	if (!data->philos)
		return (cleanup_data(data), NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	return (data);
}

// Initialize the philosophers
t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].state = IDLE;
		philo[i].num_of_meals = 0;
		philo[i].last_meal = get_current_time();
		philo[i].left_fork = &data->forks[i];
		if (i == data->num_of_philos - 1)
			philo[i].right_fork = &data->forks[0];
		else
			philo[i].right_fork = &data->forks[i + 1];
		i++;
	}
	return (philo);
}

// Initialize the forks
pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

// Cleanup the forks
void	cleanup_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

// Cleanup the data structure
void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	if (data->forks)
		cleanup_forks(data);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data);
}
