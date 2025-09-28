/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:51:19 by tshimizu          #+#    #+#             */
/*   Updated: 2025/09/28 11:51:21 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void *routine(void *arg)
{
    t_rules *rules = (t_rules*)arg;
    pthread_mutex_lock(&(rules->mutex));   // ロック開始
    printf("Hello from thread\n");
    pthread_mutex_unlock(&(rules->mutex)); // ロック解除
    return NULL;
}
