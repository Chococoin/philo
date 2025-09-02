#include <stdio.h>
#include <pthread.h>

// Función que ejecutará el thread
void* mi_funcion(void* arg) {
    (void)arg;
    printf("¡Hola desde el thread!\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    printf("Proceso principal antes de crear el thread.\n");

    // Crear el thread
    if (pthread_create(&thread_id, NULL, mi_funcion, NULL) != 0) {
        perror("Error al crear el thread");
        return 1;
    }

    printf("Proceso principal despues de crear el thread.\n");

    // Esperar a que el thread termine
    pthread_join(thread_id, NULL);

    printf("Thread finalizado.\n");
    return 0;
}