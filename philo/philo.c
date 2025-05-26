/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:24:24 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/26 16:51:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg) 			//test
{
	t_philo	*philo_data;

	philo_data = (t_philo *)arg;
	printf("ID: %i\n", philo_data->id);
	return (NULL);
}

int	init_pthreads(pthread_t **philos, pthread_mutex_t **mutex, t_philo **philo_data, t_args *args)
{
	long unsigned int	i;

	*philos = malloc(args->n_philo * sizeof(pthread_t));
	*mutex = malloc(args->n_philo * sizeof(pthread_mutex_t));
	*philo_data = malloc(args->n_philo * sizeof(t_philo));
	if (!*philos || !*mutex || !*philo_data)
		return (free(*philos), free(*mutex), free(*philo_data), 1);
	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_init(&(*mutex)[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->n_philo)
	{
		(*philo_data)[i].id = i;
		(*philo_data)[i].args = args;
		(*philo_data)[i].forks = *mutex;
		pthread_create(&(*philos)[i], NULL, philo_routine, &(*philo_data)[i]);
		i++;
	}
	return (0);
}

void	clean_pthreads(pthread_t *philos, pthread_mutex_t *mutex, t_philo *philo_data, t_args *args)
{
	long unsigned int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(philos);
	free(mutex);
	free(philo_data);
}

int	main(int argc, char **argv)
{
	pthread_t		*philos;
	pthread_mutex_t	*mutex;
	t_philo			*philo_data;
	t_args			args;
	int				flag;

	flag = 0;
	ft_parse(&args, argc, argv, &flag);
	if (flag == 1)
		return (2);
	if (init_pthreads(&philos, &mutex, &philo_data, &args) == 1)
		return (write(2, "Malloc Error\n", 13), 2);
	clean_pthreads(philos, mutex, philo_data, &args);
	return (0);
}
