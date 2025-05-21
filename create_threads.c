/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/21 18:23:15 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_program *program)
{
    int i;

    i = 0;
    while (i < program->num_of_philos)
    {
        if (pthread_create(&program->philos[i].thread, NULL, philo_routine, &program->philos[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d.\n", i + 1);
            return;
        }
        i++;
    }

    i = 0;
    while (i < program->num_of_philos)
    {
        pthread_join(program->philos[i].thread, NULL);
        i++;
    }
}

void init_mutexes(t_program *program)
{
    int i;

    i = 0;
    while (i < program->num_of_philos)
    {
        pthread_mutex_init(&program->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
}

void init_philos(t_program *program)
{
    int i;

    i = 0;
    while (i < program->num_of_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = program->start_time;
        program->philos[i].program = program;
        program->philos[i].r_fork = &program->forks[i];
        program->philos[i].l_fork = &program->forks[(i + 1) % program->num_of_philos];
        i++;
    }
}
