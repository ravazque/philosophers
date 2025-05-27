/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:47:32 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/27 14:10:11 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_chair	*table;
	size_t	i;
	bool	flag;

	table = NULL;
	i = 0;
	ft_parse(&table, argc, argv, &flag);
	if (flag == false)
		return (2);
	while (++i <= table->args->n_philo)
		ft_table(&table, i);
	ft_finsih_table(&table);
	free_table(&table);
	return (0);
}
