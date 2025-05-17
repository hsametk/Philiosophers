/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/17 19:41:03 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
    t_program	program;
    t_philo		philosopher[PHILO_MAX];
    pthread_mutex_t	forks[PHILO_MAX];

    if (check_input(argc, argv) != 0)
        return (1);
    memset(&program, 0, sizeof(t_program));
    program.philos = malloc(sizeof(t_philo) * ft_atol(argv[1]));
    if (program.philos == NULL)
    {
        printf("Error: Failed to allocate memory for philosophers.\n");
        return (1);
    }
    if (!program.philos)
        return (1);
    init_mutexes(&program, philosopher);
    init_philos(&program, philosopher, forks);
    create_threads(philosopher);
    return (0);
}

int check_input(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("Error: No arguments provided.\n");
        return (1);
    }
    if (check_arg(argc, argv) != 0)
        return (1);

    if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
    {
        printf("Error: Number of philosophers must be between 1 and 200.\n");
        return (1);
    }
    return (0);  // Eksik return değeri eklendi
}
