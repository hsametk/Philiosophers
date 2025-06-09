/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/09 18:40:38 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_program	program;

	if (check_input(argc, argv) != 0)
		return (1);
	memset(&program, 0, sizeof(t_program));
	if (init_some_struct(argc, argv, &program) != 0)
		return (1);
	init_mutexes(&program);
	init_philos(&program);
	create_threads(&program);
	destroy_mutexes(&program);
	free(program.philos);
	free(program.forks);
	return (0);
}

int	check_input(int argc, char *argv[])
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
	return (0);
}

void	destroy_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
}

int	init_some_struct(int argc, char *argv[], t_program *program)
{
	program->num_of_philos = ft_atol(argv[1]);
	program->start_time = get_time();
	program->time_to_die = ft_atol(argv[2]);
	program->time_to_eat = ft_atol(argv[3]);
	program->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		program->num_times_to_eat = ft_atol(argv[5]);
	else
		program->num_times_to_eat = -1;
	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
	if (!program->philos || !program->forks)
	{
		printf("Error: Memory allocation failed.\n");
		return (1);
	}
	return (0);
}