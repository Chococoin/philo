#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* mi_funcion(void* arg) {
    (void)arg;
    printf("Thread iniciado\n");
    sleep(2); // Simula trabajo
    printf("Thread finalizado\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    // Crear el thread
    if (pthread_create(&thread_id, NULL, mi_funcion, NULL) != 0) {
        perror("Error al crear el thread");
        return 1;
    }

    // Detach el thread
    // pthread_detach(thread_id);
    // pthread_join(thread_id, NULL);

    printf("Proceso principal sigue sin esperar al thread\n");
    sleep(3); // Espera para ver la salida del thread
    printf("Proceso principal termina\n");
    return 0;
}