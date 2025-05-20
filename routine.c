/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/20 20:25:57 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!*(philo->dead))
    {
        pthread_mutex_lock(philo->write_lock);
        printf("%zu %d is thinking\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->write_lock);
        eating(philo);
        sleeping(philo);
    }
    
    return (NULL);
}
void sleeping(t_philo *philo)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d is sleeping\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);
    usleep(philo->time_to_sleep * 1000); // Uyuma süresi (milisaniyeden mikrosaniyeye çevrildi)
}
void eating(t_philo *philo)
{
    // Sağ çatalı al
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d has taken a fork\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);

    // Sol çatalı al
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d has taken a fork\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);

    // Yemek yeme
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_time(); // Son yemek yeme zamanını güncelle
    pthread_mutex_unlock(philo->meal_lock);

    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d is eating\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);

    usleep(philo->time_to_eat * 1000); // Yemek yeme süresi (milisaniyeden mikrosaniyeye çevrildi)

    // Çatalları bırak
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}