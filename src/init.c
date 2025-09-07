/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:14:23 by ravazque          #+#    #+#             */
/*   Updated: 2025/07/01 16:26:33 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_philos(t_philo **philo, t_data *data, int i)
{
	(*philo)->id = i + 1;
	(*philo)->last_meal = 0;
	(*philo)->meals_eaten = 0;
	(*philo)->right_fork = &data->forks[i];
	(*philo)->meal_mutex = &data->meal_mutexes[i];
}

static int	set_philo_links(t_data *data, t_philo *first, t_philo *prev)
{
	t_philo	*philo;
	int		i;

	prev->next = first;
	philo = first;
	i = 0;
	while (i++ < data->num_philos)
	{
		philo->left_fork = philo->next->right_fork;
		philo = philo->next;
	}
	data->philos = first;
	return (0);
}

static int	init_philosophers(t_data *data)
{
	t_philo	*first;
	t_philo	*prev;
	t_philo	*philo;
	int		i;

	first = NULL;
	prev = NULL;
	i = 0;
	while (i < data->num_philos)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (1);
		set_philos(&philo, data, i);
		philo->data = data;
		if (!first)
			first = philo;
		else
			prev->next = philo;
		prev = philo;
		i++;
	}
	return (set_philo_links(data, first, prev));
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->meal_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_check_mutex, NULL);
	return (init_philosophers(data));
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->max_meals = atoi(argv[5]);
	else
		data->max_meals = -1;
	data->someone_died = 0;
	data->all_ate = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	data->meal_mutexes = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->meal_mutexes)
	{
		free(data->forks);
		return (1);
	}
	return (init_mutexes(data));
}
