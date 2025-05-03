/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/03 19:43:36 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philosopher	philosopher;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}

	if (define_values(argc, argv, &philosopher) != 0)
		return (1);

	if (philosopher.id < 1 || philosopher.id > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200.\n");
		return (1);
	}

	printf("Philosopher ID: %d\n", philosopher.id);
	printf("Time to die: %d\n", philosopher.time_to_die);
	printf("Time to eat: %d\n", philosopher.time_to_eat);
	printf("Time to sleep: %d\n", philosopher.time_to_sleep);
	if (philosopher.number_of_times_each_philosopher_must_eat != -1)
		printf("Number of times each philosopher must eat: %d\n", philosopher.number_of_times_each_philosopher_must_eat);

	return (0);
}


