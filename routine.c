/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/04 13:36:12 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void thinking(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->program->write_lock);
//     if (!philo->program->dead_flag)
//         printf("%zu %d is thinking\n", 
//             get_time() - philo->program->start_time, philo->id);
//     pthread_mutex_unlock(&philo->program->write_lock);
// }

// void eating(t_philo *philo)
// {
//     // Tek filozofsa sadece bir çatal alabilir — sonsuza kadar diğerini bekler
//     if (philo->program->num_of_philos == 1)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         pthread_mutex_lock(&philo->program->write_lock);
//         printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
//         pthread_mutex_unlock(&philo->program->write_lock);

//         // Diğer çatal yok, ölene kadar bekle
//         while (!philo->program->dead_flag)
//             usleep(100);
//         pthread_mutex_unlock(philo->r_fork);
//         return ;
//     }

//     // Deadlock önlemek için: çift ID önce sol, tek ID önce sağ çatal alır
//     if (philo->id % 2 == 0)
//     {
//         pthread_mutex_lock(philo->l_fork);
//         pthread_mutex_lock(&philo->program->write_lock);
//         printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
//         pthread_mutex_unlock(&philo->program->write_lock);

//         pthread_mutex_lock(philo->r_fork);
//         pthread_mutex_lock(&philo->program->write_lock);
//         printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
//         pthread_mutex_unlock(&philo->program->write_lock);
//     }
//     else
//     {
//         pthread_mutex_lock(philo->r_fork);
//         pthread_mutex_lock(&philo->program->write_lock);
//         printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
//         pthread_mutex_unlock(&philo->program->write_lock);

//         pthread_mutex_lock(philo->l_fork);
//         pthread_mutex_lock(&philo->program->write_lock);
//         printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
//         pthread_mutex_unlock(&philo->program->write_lock);
//     }

//     // Yeme zamanı
//     pthread_mutex_lock(&philo->program->dead_lock);
//     philo->last_meal = get_time();
//     pthread_mutex_unlock(&philo->program->dead_lock);

//     pthread_mutex_lock(&philo->program->write_lock);
//     printf("%zu %d is eating\n", get_time() - philo->program->start_time, philo->id);
//     pthread_mutex_unlock(&philo->program->write_lock);

//     usleep(philo->program->time_to_eat * 1000);

//     // Çatalları serbest bırak
//     pthread_mutex_unlock(philo->l_fork);
//     pthread_mutex_unlock(philo->r_fork);
// }

// void sleeping(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->program->write_lock);
//     if (!philo->program->dead_flag)
//         printf("%zu %d is sleeping\n", 
//             get_time() - philo->program->start_time, philo->id);
//     pthread_mutex_unlock(&philo->program->write_lock);
//     usleep(philo->program->time_to_sleep * 1000);
// }
void thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->dead_lock);
    if (philo->program->dead_flag)
    {
        pthread_mutex_unlock(&philo->program->dead_lock);
        return;
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    pthread_mutex_lock(&philo->program->write_lock);
    printf("%zu %d is thinking\n",
        get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);
}

void eating(t_philo *philo)
{
    // Tek filozof kontrolü
    if (philo->program->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", 
            get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
        
        // Ölene kadar bekle
        while (1)
        {
            pthread_mutex_lock(&philo->program->dead_lock);
            if (philo->program->dead_flag)
            {
                pthread_mutex_unlock(&philo->program->dead_lock);
                pthread_mutex_unlock(philo->l_fork);
                return;
            }
            pthread_mutex_unlock(&philo->program->dead_lock);
            usleep(500);
        }
    }

    // Her işlem öncesi ölüm kontrolü
    pthread_mutex_lock(&philo->program->dead_lock);
    if (philo->program->dead_flag)
    {
        pthread_mutex_unlock(&philo->program->dead_lock);
        return;
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    // Sol çatalı al
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(&philo->program->dead_lock);
    if (!philo->program->dead_flag)
    {
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    // Sağ çatalı al
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(&philo->program->dead_lock);
    if (!philo->program->dead_flag)
    {
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d has taken a fork\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    // Yeme işlemi
    pthread_mutex_lock(&philo->program->dead_lock);
    if (!philo->program->dead_flag)
    {
        pthread_mutex_lock(&philo->program->write_lock);
        printf("%zu %d is eating\n", get_time() - philo->program->start_time, philo->id);
        pthread_mutex_unlock(&philo->program->write_lock);
        philo->last_meal = get_time();
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    // Yeme süresini bekle
    size_t start = get_time();
    while (get_time() - start < philo->program->time_to_eat)
    {
        pthread_mutex_lock(&philo->program->dead_lock);
        if (philo->program->dead_flag)
        {
            pthread_mutex_unlock(&philo->program->dead_lock);
            break;
        }
        pthread_mutex_unlock(&philo->program->dead_lock);
        usleep(500);
    }

    // Çatalları bırak
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);

    pthread_mutex_lock(&philo->program->dead_lock);
    if (!philo->program->dead_flag)
        philo->meals_eaten++;
    pthread_mutex_unlock(&philo->program->dead_lock);
}

void sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->dead_lock);
    if (philo->program->dead_flag)
    {
        pthread_mutex_unlock(&philo->program->dead_lock);
        return;
    }
    pthread_mutex_unlock(&philo->program->dead_lock);

    pthread_mutex_lock(&philo->program->write_lock);
    printf("%zu %d is sleeping\n",
        get_time() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(&philo->program->write_lock);
    usleep(philo->program->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->program->dead_lock);
    philo->last_meal = get_time(); // Başlangıç yemek zamanını ayarla
    pthread_mutex_unlock(&philo->program->dead_lock);

    if (philo->id % 2 == 0)
        usleep(1000);

    while (1)
    {
        pthread_mutex_lock(&philo->program->dead_lock);
        if (philo->program->dead_flag)
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