/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:00:18 by tshimizu          #+#    #+#             */
/*   Updated: 2025/10/04 11:35:23 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool cleanup_all(t_rules *rules)
{
    int i;

    for (i = 0; i < rules->n_philo; i++)
        if (pthread_mutex_destroy(&(rules->forks[i])) != 0)
            return (perror("cleanup_all: fork mutex destroy failed"), FALSE);

    if (pthread_mutex_destroy(&(rules->print_mutex)) != 0
        || pthread_mutex_destroy(&(rules->death_mutex)) != 0)
        return (perror("cleanup_all: global mutex destroy failed"), FALSE);

    free(rules->forks);
    free(rules->philos);
    return TRUE;
}

t_bool cleanup_on_thread_error(t_rules *rules, int created_count)
{
    int i;

    for (i = 0; i < created_count; i++)
        if (pthread_join(rules->philos[i].thread, NULL) != 0)
            return (perror("pthread_join failed"), FALSE);

    for (i = 0; i < rules->n_philo; i++)
        if (pthread_mutex_destroy(&(rules->forks[i])) != 0)
            return (perror("cleanup_one_thread_error: fork mutex destroy failed"), FALSE);

    if (pthread_mutex_destroy(&(rules->print_mutex)) != 0
        || pthread_mutex_destroy(&(rules->death_mutex)) != 0)
        return (perror("cleanup_one_thread_error: global mutex destroy failed"), FALSE);

    free(rules->forks);
    free(rules->philos);
    return TRUE;
}
