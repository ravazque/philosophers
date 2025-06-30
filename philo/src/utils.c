/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:32:59 by ravazque          #+#    #+#             */
/*   Updated: 2025/06/30 19:34:13 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	all_philosophers_ate(t_data *data)
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
