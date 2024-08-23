/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:22:58 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:05:32 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_if_dead(t_philo *philo);

// Handle the philosopher life cycle
void	*philosopher_routine(t_philo *philo)
{
	if (philo->data->num_of_philos == 1)
		pthread_exit(NULL);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_if_dead(philo))
	{
		action_eat(philo);
		if (philo->state == FULL)
			break ;
		action_sleep(philo);
		action_think(philo);
	}
	pthread_exit(NULL);
}

// Initialize the simulation
bool	initialize_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitor_thread, NULL,
			(void *)observe_philosophers, data) != 0)
		return (false);
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				(void *)philosopher_routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
	i = 0;
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (false);
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

// Output the philosopher state
void	output_state(t_philo *philo, char *info)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!check_if_dead(philo))
	{
		printf("%zu %d %s\n", get_current_time() - philo->data->start_time,
			philo->id, info);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

// Check if a philosopher is dead
static bool	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->death_flag == true)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (false);
}
