/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:51:19 by tshimizu          #+#    #+#             */
/*   Updated: 2025/10/04 15:14:42 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_rules *rules = (t_rules*)arg;
    pthread_mutex_lock(&(rules->print_mutex));   // ロック開始
    printf("Hello from thread\n");
    pthread_mutex_unlock(&(rules->print_mutex)); // ロック解除
    return NULL;
}


