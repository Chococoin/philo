// philo_metronomo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define N_PHILOSOPHERS 5
#define TIME_TO_DIE 800
#define TIME_TO_EAT 200
#define TIME_TO_SLEEP 100
#define METRONOME_BEAT_MS 200

typedef struct s_philo {
    int id;
    long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_lock;
    long start_time;
} t_philo;

long get_time_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int get_metronome_beat(long start_time) {
    return (get_time_in_ms() - start_time) / METRONOME_BEAT_MS;
}

void precise_usleep(int ms) {
    long start = get_time_in_ms();
    while ((get_time_in_ms() - start) < ms)
        usleep(100);
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (1) {
        int beat = get_metronome_beat(philo->start_time);

        if ((philo->id % 2) != (beat % 2)) {
            // Pensando
            usleep(1000);
            continue;
        }

        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);

        pthread_mutex_lock(philo->print_lock);
        printf("[%ld ms] Philosopher %d is eating 🍝\n", get_time_in_ms() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->print_lock);

        philo->last_meal = get_time_in_ms();
        precise_usleep(TIME_TO_EAT);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        pthread_mutex_lock(philo->print_lock);
        printf("[%ld ms] Philosopher %d is sleeping 😴\n", get_time_in_ms() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->print_lock);

        precise_usleep(TIME_TO_SLEEP);
        // Pensar de nuevo (espera activa por beat)
    }
    return NULL;
}

int main(void) {
    pthread_t threads[N_PHILOSOPHERS];
    pthread_mutex_t forks[N_PHILOSOPHERS];
    pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;
    t_philo philos[N_PHILOSOPHERS];

    for (int i = 0; i < N_PHILOSOPHERS; i++)
        pthread_mutex_init(&forks[i], NULL);

    long start_time = get_time_in_ms();

    for (int i = 0; i < N_PHILOSOPHERS; i++) {
        philos[i].id = i + 1;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % N_PHILOSOPHERS];
        philos[i].print_lock = &print_lock;
        philos[i].last_meal = start_time;
        philos[i].start_time = start_time;

        pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
    }

    for (int i = 0; i < N_PHILOSOPHERS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}