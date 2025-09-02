#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	pthread_t thread;
} Philosopher;

typedef struct {
	Philosopher philosophers[5]; // Para 5 filósofos
	int number_of_philosophers;
	// Otros datos globales, como time_stamp, clock_on, etc.
} Data;

void* clock_thread(void* arg) {
	// Data* data = (Data*)arg;
	int time_stamp = 0;
	int running = 1;
	(void)arg;

	while (running) {
		printf("Reloj: %d ms\n", time_stamp);
		// printf("ID del hilo clock: %lu\n", (unsigned long)clock);
		time_stamp += 1;
		usleep(100000); // 100 ms
		// Aquí podrías agregar lógica para terminar el reloj
		// Por ejemplo: if (time_stamp > 1000) running = 0;
		if (time_stamp > 5000)
			running = 0;
	}
	printf("Reloj terminado\n");
	return NULL;
}

void* philosopher_routine(void* arg)
{
	(void)arg;
	printf("Rutina de los filosofos comiendo.\n");
	printf("recuerda que si uno muere se debe terminar el programa.\n");
	sleep(1);
	printf("Termina el proceso.\n");
	return (0);
}

int main()
{
	pthread_t clock;
	Data data = {
		.number_of_philosophers = 5,
		.philosophers = { {0}, {0}, {0}, {0}, {0} }
	};
	pthread_create(&clock, NULL, clock_thread, &data);
	pthread_detach(clock);
	printf("Proceso principal.\n");
	int i = 0;
	pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, &data.philosophers[i]);
	pthread_join(data.philosophers[i].thread, NULL);
}
