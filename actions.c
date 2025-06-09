/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:07:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/05 14:33:03 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_single_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	wait_until_death(philo);
	pthread_mutex_unlock(philo->l_fork);
}

static void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
	{
		philo->last_meal = get_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}

void	eating(t_philo *philo)
{
	if (philo->program->num_of_philos == 1)
	{
		handle_single_philo_eat(philo);
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
	print_status(philo, "is sleeping");
	precise_sleep(philo->program->time_to_sleep);
}
