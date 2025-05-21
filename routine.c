/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/21 18:29:34 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->program->dead_flag) // `dead_flag` artık `t_program` içinde
    {
        pthread_mutex_lock(&philo->program->write_lock); // `write_lock` artık `t_program` içinde
        printf("%zu %d is thinking\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
        eating(philo);
        sleeping(philo);
    }
    return (NULL);
}

void sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->write_lock); // `write_lock` artık `t_program` içinde
    printf("%zu %d is sleeping\n", get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);
    usleep(philo->program->time_to_sleep * 1000); // `time_to_sleep` artık `t_program` içinde
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(&philo->program->write_lock); // `write_lock` artık `t_program` içinde
    printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);

    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(&philo->program->write_lock);
    printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);

    pthread_mutex_lock(&philo->program->dead_lock); // `dead_lock` artık `t_program` içinde
    philo->last_meal = get_time(); // `last_meal` hala `t_philo` içinde
    pthread_mutex_unlock(&philo->program->dead_lock);

    pthread_mutex_lock(&philo->program->write_lock);
    printf("%zu %d is eating\n", get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);

    usleep(philo->program->time_to_eat * 1000); // `time_to_eat` artık `t_program` içinde

    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}