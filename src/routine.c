/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:13:52 by ravazque          #+#    #+#             */
/*   Updated: 2025/07/01 16:34:42 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_usleep(long long ms)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

static void	eat(t_philo *philo, t_data *data)
{
	print_action(philo, "\033[38;5;120mis eating\033[0m");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_time() - data->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	pick_up_forks_part2(t_philo *philo, pthread_mutex_t *first_fork,
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

static int	pick_up_forks(t_philo *philo)
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_die / 2);
		
	while (!check_death(philo))
	{
		print_action(philo, "\033[38;5;215mis thinking\033[0m");
		if (philo->id % 2 == 0)
			usleep(100);
		if (pick_up_forks(philo))
			break ;
		eat(philo, philo->data);
		if (check_death(philo))
			break ;
		print_action(philo, "\033[38;5;117mis sleeping\033[0m");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
