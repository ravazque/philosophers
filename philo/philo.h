/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:11:58 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/26 16:49:26 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	unsigned long	n_philo;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	n_meals;
}					t_args;

typedef struct s_philo
{
	int				id;
	t_args			*args;
	pthread_mutex_t	*forks;
}					t_philo;

void				*philo_routine(void *arg);
int					ft_parse(t_args *args, int argc, char *argv[], int *flag);

#endif
