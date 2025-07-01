/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:14:09 by ravazque          #+#    #+#             */
/*   Updated: 2025/07/01 16:25:51 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	start_threads(t_data *data)
{
	t_philo		*current;
	pthread_t	monitor_thread;
	int			i;

	current = data->philos;
	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_mutex_lock(current->meal_mutex);
		current->last_meal = 0;
		pthread_mutex_unlock(current->meal_mutex);
		current = current->next;
	}
	current = data->philos;
	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_create(&current->thread, NULL, routine, current);
		current = current->next;
	}
	pthread_create(&monitor_thread, NULL, monitor, data);
	pthread_join(monitor_thread, NULL);
	current = data->philos;
	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	return (0);
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
