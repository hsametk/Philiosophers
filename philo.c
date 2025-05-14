/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/14 14:51:22 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo		philosopher[PHILO_MAX];
	t_program	program;
	pthread_mutex_t	forks[PHILO_MAX]; // Changed from pointer array to array

	check_input(argc, argv, philosopher); // Pass philosopher directly
	memset(&program, 0, sizeof(t_program));
	program.philos = malloc(sizeof(t_philo) * philosopher[0].num_of_philos);
	if (!program.philos)
		return (1);
	
	init_mutexes(&program, philosopher);
	init_philos(&program, philosopher, forks); // Pass forks array directly
	create_threads(philosopher); // Pass philosopher directly
	
	return (0);	
}

void check_input(int argc, char *argv[], t_philo *philosopher)
{
    if (argv[1] == NULL)
    {
        printf("Error: No arguments provided.\n");
        return;
    }
    if (check_arg(argc, argv, philosopher) != 0)
        return;

    if (philosopher->num_of_philos < 1 || philosopher->num_of_philos > 200)  // Changed <= to <
    {
        printf("Error: Number of philosophers must be between 1 and 200.\n");
        return;
    }
}