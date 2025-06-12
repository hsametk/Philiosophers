/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:07:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/12 23:29:02 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
	{
		pthread_mutex_lock(&philo->program->write_lock);
		printf("%zu %d %s\n",
			get_time() - philo->program->start_time,
			philo->id,
			status);
		pthread_mutex_unlock(&philo->program->write_lock);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}

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