/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/05 18:16:31 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo	philosopher;
	pthread_mutex_t	mutex;

	if (argv[1] == NULL)
	{
		printf("Error: No arguments provided.\n");
		return (1);
	}
	if (define_values(argc, argv, &philosopher) != 0)
		return (1);

	if (philosopher.id < 1 || philosopher.id > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200.\n");
		return (1);
	}
	return (0);
	
}
