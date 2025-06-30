/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:33:07 by ravazque          #+#    #+#             */
/*   Updated: 2025/06/30 22:24:23 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_action(philo, "\033[38;5;183mhas taken a fork\033[0m");
	return (pick_up_forks_part2(philo, first_fork, second_fork));
}

int	pick_up_forks_part2(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_action(philo, "\033[38;5;183mhas taken a fork\033[0m");
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

int	check_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philos;
	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (get_time() - philo->last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d ", get_time() - data->start_time, philo->id);
			printf("\033[1;31mdied\033[0m\n");
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_unlock(philo->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->meal_mutex);
		philo = philo->next;
	}
	return (0);
}

int	start_threads(t_data *data)
{
	t_philo		*current;
	pthread_t	monitor_thread;
	int			i;

	current = data->philos;
	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_mutex_lock(current->meal_mutex);
		current->last_meal = get_time();
		pthread_mutex_unlock(current->meal_mutex);
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
