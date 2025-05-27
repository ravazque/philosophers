/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:12:13 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/27 14:54:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pars_err(void)
{
	write(2, "\033[1;31mError:\033[0m\nYou must enter positive numbers", 49);
	write(2, " up to 18446744073709551615.\nThese should be for:\n\tNum", 54);
	write(2, "ber of philosophers.\n\tTime to die.\n\tTime to eat.\n\tT", 51);
	write(2, "ime to sleep.\n\tNumber of times each philosopher must ", 53);
	write(2, "eat. - [ OPTIONAL ]\n", 20);
}

static size_t	ft_atoul(const char *str)
{
	int		i;
	size_t	num;

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

static int	ft_isdigit(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i <= argc - 1)
	{
		if (ft_atoul(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_parse(t_chair **table, int argc, char *argv[], bool *flag)
{
	*flag = true;
	if (argc < 5 || argc > 6)
		return (pars_err(), *flag = false, 0);
	if (ft_isdigit(argc, argv) != 0)
		return (pars_err(), *flag = false, 0);
	(*table)->args->n_philo = ft_atoul(argv[1]);
	(*table)->args->t_die = ft_atoul(argv[2]);
	(*table)->args->t_eat = ft_atoul(argv[3]);
	(*table)->args->t_sleep = ft_atoul(argv[4]);
	if (argc == 6)
		(*table)->args->n_meals = ft_atoul(argv[5]);
	else
		(*table)->args->n_meals = 0;
	if ((*table)->args->n_philo == 0 || (*table)->args->t_die == 0 || (*table)->args->t_eat == 0 || (*table)->args->t_sleep == 0 || ((*table)->args->n_meals == 0 && argc == 6))
	{
		return (pars_err(), *flag = false, 0);
	}
	return (0);
}
