/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/06 18:54:59 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo		philosopher[PHILO_MAX];
	t_program	program;
	pthread_mutex_t	*forks[PHILO_MAX];

	if (argv[1] == NULL)
	{
		printf("Error: No arguments provided.\n");
		return (1);
	}
	if (define_values(argc, argv, &philosopher) != 0)
		return (1);

	if (philosopher->num_of_philos < 1 || philosopher->num_of_philos > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200.\n");
		return (1);
	}
	memset(&program, 0, sizeof(t_program));
	program.philos = malloc(sizeof(t_philo) * philosopher->num_of_philos);
	if (!program.philos)
		return (1);
	// mutex oluştur
	init_mutexes(&program, philosopher);
	init_philos(&program, philosopher, forks);
	// philoların değerlerini doldur döngü ile atoi ile yap
	create_threads(&philosopher);
	// routine fonksiyonunu yaz 
	// sonrasında 1 thread oluştur monitör için ve onun içinde fonk yaz.
	
	return (0);
	
}
