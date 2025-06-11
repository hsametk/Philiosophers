/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/06 14:20:57 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	usleep(100);
	while (1)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->dead_lock);
			if (check_philosopher_status(program, i))
			{
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&program->dead_lock);
			usleep(100);
			i++;
		}
	}
	return (NULL);
}

void	create_threads(t_program *program)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philo_routine, &program->philos[i]) != 0)
		{
			printf("Error creating philosopher thread %d\n", i + 1);
			return ;
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, program) != 0)
	{
		printf("Error creating monitor thread\n");
		return ;
	}
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < program->num_of_philos)
		pthread_join(program->philos[i].thread, NULL);
}

void	init_mutexes(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
		pthread_mutex_init(&program->forks[i], NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void	init_philos(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = program->start_time;
		program->philos[i].program = program;
		program->philos[i].l_fork = &program->forks[i];
		program->philos[i].r_fork = &program->forks[(i + 1)
			% program->num_of_philos];
	}
}

int	check_all_ate(t_program *program)
{
	int	i;

	if (program->num_times_to_eat == -1)
		return (0);
	i = -1;
	while (++i < program->num_of_philos)
		if (program->philos[i].meals_eaten < program->num_times_to_eat)
			return (0);
	return (1);
}
