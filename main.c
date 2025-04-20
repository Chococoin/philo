#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data t_data;

struct s_philosopher {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread;
};

struct s_data {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    pthread_mutex_t *forks;
    struct s_philosopher *philosophers;
    int someone_died;
    int alternance_cycle;
};

void *philosopher_routine(void *arg)
{
    struct s_philosopher *philo = (struct s_philosopher *)arg;
    t_data *data = philo->data;

    while (!data->someone_died)
    {
        while ((philo->id + data->alternance_cycle) % 2 != 0)
        {
            if (data->someone_died)
                return NULL;
            usleep(100); // espera breve hasta que llegue su turno
        }

        // Tomar tenedores
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->right_fork);
            printf("Philosopher %d has taken the right fork\n", philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("Philosopher %d has taken the left fork\n", philo->id);
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            printf("Philosopher %d has taken the left fork\n", philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("Philosopher %d has taken the right fork\n", philo->id);
        }

        // Comer
        struct timeval now;
        gettimeofday(&now, NULL);
        philo->last_meal_time = now.tv_sec * 1000L + now.tv_usec / 1000L;
        printf("Philosopher %d is eating 🍝\n", philo->id);
        usleep(data->time_to_eat * 1000);

        // Soltar tenedores
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Dormir
        printf("Philosopher %d is sleeping 😴\n", philo->id);
        usleep(data->time_to_sleep * 1000);

        // Pensar
        printf("Philosopher %d is thinking 🤔\n", philo->id);
    }

    return NULL;
}

void *clock_thread(void *arg)
{
    t_data *data = (t_data *)arg;
    struct timeval now;
    long time_since_last_meal;

    while (!data->someone_died)
    {
        gettimeofday(&now, NULL);

        for (int i = 0; i < data->number_of_philosophers; i++)
        {
            struct s_philosopher *philo = &data->philosophers[i];

            if (philo->last_meal_time == 0)
                continue;

            time_since_last_meal = (now.tv_sec * 1000L + now.tv_usec / 1000L) - philo->last_meal_time;

            if (time_since_last_meal > data->time_to_die)
            {
                printf("Philosopher %d died after %ld ms without eating\n", philo->id, time_since_last_meal);
                data->someone_died = 1;
                return NULL;
            }
        }

        data->alternance_cycle++;
        usleep(1000);
    }

    return NULL;
}

long get_elapsed_time(struct timeval start)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    long elapsed = (now.tv_sec - start.tv_sec) * 1000L;
    elapsed += (now.tv_usec - start.tv_usec) / 1000L;

    return elapsed;
}

int main(void)
{
    struct timeval start;

    gettimeofday(&start, NULL);

    t_data data;
    data.number_of_philosophers = 5; // por ahora, valor fijo
    data.time_to_die = 800;
    data.time_to_eat = 200;
    data.time_to_sleep = 100;
    data.someone_died = 0;
    data.alternance_cycle = 0;

    // Crear tenedores
    data.forks = malloc(sizeof(pthread_mutex_t) * data.number_of_philosophers);
    for (int i = 0; i < data.number_of_philosophers; i++)
        pthread_mutex_init(&data.forks[i], NULL);

    // Crear filósofos
    data.philosophers = malloc(sizeof(struct s_philosopher) * data.number_of_philosophers);
    for (int i = 0; i < data.number_of_philosophers; i++)
    {
        data.philosophers[i].id = i + 1;
        data.philosophers[i].left_fork = &data.forks[i];
        data.philosophers[i].right_fork = &data.forks[(i + 1) % data.number_of_philosophers];
        data.philosophers[i].data = &data;
        data.philosophers[i].meals_eaten = 0;
        data.philosophers[i].last_meal_time = 0;
    }

    pthread_t clock;
    pthread_create(&clock, NULL, clock_thread, &data);
    pthread_detach(clock);

    for (int i = 0; i < data.number_of_philosophers; i++)
        pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, &data.philosophers[i]);

    for (int i = 0; i < data.number_of_philosophers; i++)
        pthread_join(data.philosophers[i].thread, NULL);

    long elapsed_time = get_elapsed_time(start);

    printf("Tiempo transcurrido: %ld ms\n", elapsed_time);

    // Destruir mutexes de los tenedores
    for (int i = 0; i < data.number_of_philosophers; i++)
        pthread_mutex_destroy(&data.forks[i]);

    // Liberar memoria
    free(data.forks);
    free(data.philosophers);

    return 0;
}
