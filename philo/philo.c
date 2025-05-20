/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:12:24 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/20 19:19:12 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	args;
	int		flag;

	flag = 0;
	ft_parse(&args, argc, argv, &flag);
	if (flag == 1)
		return (2);
	return (0);
}
