/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:12:13 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/20 19:15:36 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atoi(const char *str)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '+' || str[i] == '-' || str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > ULONG_MAX)
			return (0);
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0' || num == 0)
		return (0);
	return (num);
}

int	ft_isdigit(char **argv)
{
	int	i;

	i = 1;
	while (i <= 5)
	{
		if (ft_atoi(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_parse(t_args *args, int argc, char *argv[], int *flag)
{
	if (argc != 6)
		return (write(2, "\nError\n\n", 8), *flag = 1, 0);
	if (ft_isdigit(argv) != 0)
		return (write(2, "\nError\n\n", 8), *flag = 1, 0);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_meals = ft_atoi(argv[5]);
	if (args->n_philo == 0 || args->t_die == 0 || args->t_eat == 0
		|| args->t_sleep == 0 || args->n_meals == 0)
	{
		return (write(2, "\nError\n\n", 8), *flag = 1, 0);
	}
	return (0);
}
