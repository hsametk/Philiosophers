/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/23 17:57:58 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->write_lock);
    if (!philo->program->dead_flag)
        printf("%zu %d is thinking\n", 
            get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);
}

// void eating(t_philo *philo)
// {
//     if (philo->id % 2 == 0)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         pthread_mutex_lock(philo->l_fork);
//     }
//     else
//     {
//         usleep(100);
//         pthread_mutex_lock(philo->l_fork);
//         pthread_mutex_lock(philo->r_fork);
//     }

//     pthread_mutex_lock(&philo->program->write_lock);
//     if (!philo->program->dead_flag)
//     {
//         printf("%zu %d has taken a fork\n", 
//             get_time() - philo->program->start_time, philo->id);
//         printf("%zu %d has taken a fork\n", 
//             get_time() - philo->program->start_time, philo->id);
//         philo->last_meal = get_time();
//         printf("%zu %d is eating\n", 
//             get_time() - philo->program->start_time, philo->id);
//         philo->meals_eaten++;
//     }
//     pthread_mutex_unlock(&philo->program->write_lock);

//     usleep(philo->program->time_to_eat * 1000);
//     pthread_mutex_unlock(philo->r_fork);
//     pthread_mutex_unlock(philo->l_fork);
// }
void eating(t_philo *philo)
{
    // Tek filozofsa sadece bir çatal alabilir — sonsuza kadar diğerini bekler
    if (philo->program->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);

        // Diğer çatal yok, ölene kadar bekle
        while (!philo->program->dead_flag)
            usleep(100);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }

    // Deadlock önlemek için: çift ID önce sol, tek ID önce sağ çatal alır
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);

        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);

        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
    }

    // Yeme zamanı
    pthread_mutex_lock(&philo->program->dead_lock);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->program->dead_lock);

    pthread_mutex_lock(&philo->program->write_lock);
    printf("%zu %d is eating\n", get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);

    usleep(philo->program->time_to_eat * 1000);

    // Çatalları serbest bırak
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->write_lock);
    if (!philo->program->dead_flag)
        printf("%zu %d is sleeping\n", 
            get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);
    usleep(philo->program->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);

    while (1)
    {
        pthread_mutex_lock(&philo->program->dead_lock);
        if (philo->program->dead_flag || 
            (philo->program->num_times_to_eat != -1 && 
             philo->meals_eaten >= philo->program->num_times_to_eat))
        {
            pthread_mutex_unlock(&philo->program->dead_lock);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->program->dead_lock);

        thinking(philo);
        eating(philo);
        sleeping(philo);
    }
    return (NULL);
}