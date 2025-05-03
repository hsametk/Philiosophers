/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:51:35 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/03 19:38:10 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<limits.h>
# include	<stdbool.h>
# include	<pthread.h>
# include	<stdio.h>

typedef struct s_philosopher
{
	int				id; //masadaki philosopher sayısı
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*die_mutex;
}	t_philosopher;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	is_valid_number(const char *str);
int	define_values(int argc, char *argv[], t_philosopher *philosopher);

#endif // PHILOSOPHERS_H