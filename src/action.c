/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:25 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:03:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Philosopher takes the left fork, then the right fork, then eats
void	action_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	output_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	output_state(philo, "has taken a fork");
	philo->state = EATING;
	pthread_mutex_lock(&philo->data->meal_mutex);
	output_state(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->num_of_meals++;
	if (philo->num_of_meals == philo->data->num_of_meals)
		philo->state = FULL;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->state != FULL)
		philo->state = IDLE;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

// Philosopher sleeps
void	action_sleep(t_philo *philo)
{
	output_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

// Philosopher thinks
void	action_think(t_philo *philo)
{
	output_state(philo, "is thinking");
}
