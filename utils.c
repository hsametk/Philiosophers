#include "philosophers.h"

size_t	get_time(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_atol(const char *str)
{
    long		result;
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
    {
        result = (result * 10) + (*str++ - '0');
        if (result < 0)
            return (sign == 1 ? LONG_MAX : LONG_MIN);
    }
    return (result * sign);
}