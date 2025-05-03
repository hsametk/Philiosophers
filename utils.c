/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:07:25 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/03 19:36:48 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;

	sign = 1;
	result = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		printf("Error: Argument is empty.\n");
		return (0);
	}
	if (str[0] == '-' || str[0] == '+')
	{
		printf("Error: Negative or positive signs are not allowed.\n");
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("Error: Argument contains non-digit characters.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	define_values(int argc, char *argv[], t_philosopher *philosopher)
{
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4])
		|| (argc == 6 && !is_valid_number(argv[5])))
	{
		return (1); // Hatalı bir argüman varsa işlemi durdur
	}

	philosopher->id = ft_atoi(argv[1]);
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philosopher->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philosopher->number_of_times_each_philosopher_must_eat = -1; // Opsiyonel argüman yoksa -1 olarak ayarla

	return (0); // Başarılı
}
