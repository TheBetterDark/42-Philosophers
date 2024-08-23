/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:58 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/23 16:04:21 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	validate_arguments(char *argv[]);

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Invalid number of arguments\n"), EXIT_FAILURE);
	if (!validate_arguments(argv))
		return (printf("Error: Invalid argument\n"), EXIT_FAILURE);
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (printf("Error: Number of philosophers exceeds PHILO_MAX\n"),
			EXIT_FAILURE);
	data = initialize_data(argv);
	if (!data)
		return (printf("Error: Unable to allocate memory\n"), EXIT_FAILURE);
	if (initialize_simulation(data) == false)
	{
		cleanup_data(data);
		return (printf("Error: Unable to initialize simulation\n"),
			EXIT_FAILURE);
	}
	cleanup_data(data);
	return (EXIT_SUCCESS);
}

// Validate the arguments passed to the program
static bool	validate_arguments(char *argv[])
{
	if (ft_atoi(argv[1]) <= 0)
		return (false);
	if (ft_atoi(argv[2]) <= 0)
		return (false);
	if (ft_atoi(argv[3]) <= 0)
		return (false);
	if (ft_atoi(argv[4]) <= 0)
		return (false);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
			return (false);
	}
	return (true);
}
