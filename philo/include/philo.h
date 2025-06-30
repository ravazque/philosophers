/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:34:21 by ravazque          #+#    #+#             */
/*   Updated: 2025/06/30 20:27:54 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*meal_mutex;
	t_data				*data;
	struct s_philo		*next;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					someone_died;
	int					all_ate;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*meal_mutexes;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_check_mutex;
	t_philo				*philos;
}						t_data;

void		cleanup(t_data *data);
void		*routine(void *arg);
void		ft_usleep(long long ms);
void		print_invalid_args_error(void);
void		print_action(t_philo *philo, char *msg);
long long	get_time(void);
int			init_data(t_data *data, int argc, char **argv);
int			init_philosophers(t_data *data);
int			start_threads(t_data *data);
int			is_positive_number(char *str);
int			valid_args(int argc, char **argv);
int			check_death(t_philo *philo);
int			all_philosophers_ate(t_data *data);
int			set_philo_links(t_data *data, t_philo *first, t_philo *prev);
int			init_mutexes(t_data *data);
int			pick_up_forks(t_philo *philo);
int			pick_up_forks_part2(t_philo *philo, pthread_mutex_t *first_fork,
				pthread_mutex_t *second_fork);
int			check_philos(t_data *data);

#endif
