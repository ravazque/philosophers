/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:33:28 by ravazque          #+#    #+#             */
/*   Updated: 2025/06/30 20:07:06 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_positive_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_invalid_args_error(void)
{
	write(2, "\033[1;31mError:\033[0m\nYou must enter positive numbers", 50);
	write(2, " up to 18446744073709551615.\nThese should be for:\n", 50);
	write(2, "\tNumber of philosophers.\n", 25);
	write(2, "\tTime to die.\n", 14);
	write(2, "\tTime to eat.\n", 14);
	write(2, "\tTime to sleep.\n", 16);
	write(2, "\tNumber of times each philosopher must eat. - [OPTIONAL]\n", 57);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
	{
		print_invalid_args_error();
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	data.start_time = get_time();
	start_threads(&data);
	cleanup(&data);
	return (0);
}
