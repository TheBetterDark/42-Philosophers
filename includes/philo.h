/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:24 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:01:00 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Standard library headers

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// Macros

# define PHILO_MAX 200

// Enumerations

typedef enum e_state
{
	IDLE = 0,
	EATING = 1,
	FULL = 2,
	DEAD = 3
}						t_state;

// Struct declarations

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	t_data				*data;
	t_state				state;
	pthread_t			thread;

	int					num_of_meals;
	size_t				last_meal;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philo;

typedef struct s_data
{
	int					num_of_philos;
	int					num_of_meals;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;

	size_t				start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;

	pthread_t			monitor_thread;

	bool				death_flag;

	pthread_mutex_t		write_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		dead_mutex;
}						t_data;

// Function declarations

t_data					*initialize_data(char *argv[]);
void					cleanup_data(t_data *data);

t_philo					*init_philos(t_data *data);
pthread_mutex_t			*init_forks(t_data *data);
void					cleanup_forks(t_data *data);

void					*philosopher_routine(t_philo *philo);
bool					initialize_simulation(t_data *data);
void					*observe_philosophers(t_data *data);

void					action_eat(t_philo *philo);
void					action_sleep(t_philo *philo);
void					action_think(t_philo *philo);

void					output_state(t_philo *philo, char *info);
int						ft_atoi(const char *str);
int						ft_usleep(size_t milliseconds);
size_t					get_current_time(void);

#endif
