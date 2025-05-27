/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:11:58 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/27 14:07:47 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	size_t			n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_meals;
}					t_args;

typedef struct s_chair
{
	pthread_mutex_t	*forks;
	pthread_t		*philo;
	size_t			id;

	t_args			*args;

	struct s_chair	*next;
}					t_chair;

void	ft_table(t_chair **table, size_t i);
void	ft_finsih_table(t_chair **table);
void	free_table(t_chair **table);
int		ft_parse(t_chair **table, int argc, char *argv[], bool *flag);

#endif
