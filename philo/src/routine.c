#include "philo.h"

void *routine(void *arg)
{
    t_rules *rules = (t_rules*)arg;
    pthread_mutex_lock(&(rules->mutex));   // ロック開始
    printf("Hello from thread\n");
    pthread_mutex_unlock(&(rules->mutex)); // ロック解除
    return NULL;
}



