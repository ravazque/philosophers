/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:36 by ravazque          #+#    #+#             */
/*   Updated: 2025/05/27 14:53:38 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_chair	*ft_site(void)
{
	t_chair	*new_chair;

	new_chair = (t_chair *)malloc(sizeof(t_chair));
	if (!new_chair)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (NULL);
	}
	new_chair->next = NULL;
	return (new_chair);
}

void	ft_table(t_chair **table, size_t i)
{
	t_chair	*chair;
	t_chair	*temp;

	chair = ft_site();
	if (!chair)
		return ;
	chair->id = i;
	if (!*table)
	{
		*table = chair;
		return ;
	}
	temp = *table;
	while (temp->next && temp->next != *table)
		temp = temp->next;
	temp->next = chair;
}

void	ft_finsih_table(t_chair **table)
{
	t_chair	*temp;

	if (*table == NULL || (*table)->next == *table)
		return ;
	temp = *table;
	while (temp->next && temp->next != *table)
		temp = temp->next;
	temp->next = *table;
}

static void	free_chair_node(t_chair *node)
{
	if (node == NULL)
		return ;
	if (node->forks != NULL)
		free(node->forks);
	if (node->philo != NULL)
		free(node->philo);
	free(node);
}

void	free_table(t_chair **table)
{
	t_chair	*current;
	t_chair	*next;
	t_args	*args_ptr;

	if (table == NULL || *table == NULL)
		return ;
	current = *table;
	args_ptr = current->args;
	while (current->next != *table)
	{
		next = current->next;
		free_chair_node(current);
		current = next;
	}
	free_chair_node(current);
	if (args_ptr != NULL)
		free(args_ptr);
	*table = NULL;
}
