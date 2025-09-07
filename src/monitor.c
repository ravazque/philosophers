/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:14:16 by ravazque          #+#    #+#             */
/*   Updated: 2025/07/01 16:23:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	all_philosophers_ate(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		count;

	if (data->max_meals == -1)
		return (0);
	philo = data->philos;
	i = 0;
	count = 0;
	while (i++ < data->num_philos)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->meals_eaten >= data->max_meals)
			count++;
		pthread_mutex_unlock(philo->meal_mutex);
		philo = philo->next;
	}
	return (count == data->num_philos);
}

static int	check_philos(t_data *data)
{
	t_philo	*philo;
	int		i;
	long long current_time;

	philo = data->philos;
	i = 0;
	current_time = get_time() - data->start_time;
	while (i++ < data->num_philos)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (current_time - philo->last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d \033[1;31mdied\033[0m\n", current_time, philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->meal_mutex);
		philo = philo->next;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philos(data))
			return (NULL);
		if (all_philosophers_ate(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}
