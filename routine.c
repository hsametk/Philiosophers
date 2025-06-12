/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/12 23:19:54 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	wait_until_death(philo);
	pthread_mutex_unlock(philo->l_fork);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_status(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_status(philo, "is sleeping");
	precise_sleep(philo->program->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->last_meal = get_time();
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
