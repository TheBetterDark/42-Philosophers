/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:07:16 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:04:43 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_if_all_philos_full(t_data *data);
static bool	check_if_starving(t_philo *philo);
static bool	check_if_dead(t_data *data);

// Observe the philosophers and check if they are dead or full
void	*observe_philosophers(t_data *data)
{
	while (true)
	{
		if (check_if_all_philos_full(data) || check_if_dead(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->death_flag = true;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		ft_usleep(1);
	}
	pthread_exit(NULL);
}

// Check if all philosophers have eaten the required number of meals
static bool	check_if_all_philos_full(t_data *data)
{
	int	i;

	if (data->num_of_meals == -1)
		return (false);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].num_of_meals < data->num_of_meals)
			return (pthread_mutex_unlock(&data->meal_mutex), false);
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (true);
}

// Check if any philosopher is starving
static bool	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (check_if_starving(&data->philos[i]))
		{
			output_state(&data->philos[i], "died");
			return (true);
		}
		i++;
	}
	return (false);
}

// Check if a philosopher is starving
static bool	check_if_starving(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (get_current_time() - philo->last_meal >= philo->data->time_to_die
		&& philo->state != EATING)
		return (pthread_mutex_unlock(&philo->data->meal_mutex), true);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (false);
}
