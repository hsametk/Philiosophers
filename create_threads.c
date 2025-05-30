/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/30 17:22:05 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg);
size_t	get_time(void);

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	while (1)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->dead_lock);
			if (program->dead_flag)
			{
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			if (get_time() - program->philos[i].last_meal > program->time_to_die)
			{
				pthread_mutex_lock(&program->write_lock);
				printf("%zu %d died\n", get_time() - program->start_time, program->philos[i].id);
				pthread_mutex_unlock(&program->write_lock);
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			if (check_all_ate(program))
			{
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&program->dead_lock);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	create_threads(t_program *program)
{
	int	i;
	pthread_t monitor_thread;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philo_routine, &program->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d.\n", i + 1);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, program) != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return ;
	}

	pthread_join(monitor_thread, NULL);

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}

void	init_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void	init_philos(t_program *program)
{
    int	i;

    i = 0;
    while (i < program->num_of_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = program->start_time;
        program->philos[i].program = program;
        program->philos[i].l_fork = &program->forks[i];
        program->philos[i].r_fork = &program->forks[(i + 1) % program->num_of_philos];
        i++;
    }
}

int check_all_ate(t_program *program)
{
    int i;
    
    if (program->num_times_to_eat == -1)
        return (0);
    for (i = 0; i < program->num_of_philos; i++)
        if (program->philos[i].meals_eaten < program->num_times_to_eat)
            return (0);
    return (1);
}
