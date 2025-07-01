/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:14:30 by ravazque          #+#    #+#             */
/*   Updated: 2025/07/01 03:22:20 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	print_action(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	free_philos(t_philo *first, int count)
{
	t_philo	*tmp;
	t_philo	*next;
	int		i;

	tmp = first;
	i = 0;
	while (i++ < count)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->meal_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_check_mutex);
}

void	cleanup(t_data *data)
{
	if (data->philos)
		free_philos(data->philos, data->num_philos);
	if (data->forks)
		free(data->forks);
	if (data->meal_mutexes)
		free(data->meal_mutexes);
	destroy_mutexes(data);
}
