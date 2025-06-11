/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/09 20:26:46 by hakotu           ###   ########.fr       */
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

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
	{
		philo->last_meal = get_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}

// void thinking(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->program->dead_lock);
// 	if (philo->program->dead_flag)
// 	{
// 		pthread_mutex_unlock(&philo->program->dead_lock);
// 		return;
// 	}
// 	pthread_mutex_unlock(&philo->program->dead_lock);

// 	pthread_mutex_lock(&philo->program->write_lock);
// 	printf("%zu %d is thinking\n",
// 		get_time() - philo->program->start_time, philo->id);
// 	pthread_mutex_unlock(&philo->program->write_lock);
// }

void	eating(t_philo *philo)
{
	if (philo->program->num_of_philos == 1)
	{
		handle_single_philo(philo);
		return ;
	}
	take_forks(philo);
	print_status(philo, "is eating");
	update_meal_time(philo);
	precise_sleep(philo->program->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
