# 🧠 PHILO – Estudio técnico (Primera hora)

> 📅 Día 1 – 2 de septiembre 2025  
> ⏱️ Duración: 1 hora activa  
> 🎯 Objetivo: Entender los conceptos fundamentales del proyecto `philo/` usando el código de base sucio

---

## 🔹 1. Threads (`pthread_create`, `pthread_join`)

### Qué debes saber:
[X] Qué es un hilo vs. proceso
- Cómo se crea un hilo en C
- Qué pasa cuando varios hilos acceden a la misma memoria
- Cuándo usar `join` y cuándo `detach`

### En tu código:
```c
pthread_create(&clock, NULL, clock_thread, &data);
pthread_detach(clock);

pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, &data.philosophers[i]);
pthread_join(data.philosophers[i].thread, NULL);
```

### Tarea:
- Dibuja cómo se ve el programa al iniciar 5 hilos de filósofos y 1 hilo de reloj.
- Pregúntate: ¿por qué el reloj está `detached` y los filósofos no?

---

## 🔹 2. Mutex

### Qué debes saber:
- Para qué sirve un mutex
- Qué pasa si dos hilos acceden a la misma variable sin mutex
- Cómo se evita un deadlock

### En tu código:
```c
pthread_mutex_lock(philo->left_fork);
pthread_mutex_unlock(philo->right_fork);
```

### Tarea:
- ¿Qué recurso está protegido? ¿forks? ¿printf?
- Dibuja un círculo con 5 filósofos y los forks entre ellos

---

## 🔹 3. Tiempo en milisegundos

### Qué debes saber:
- Cómo se mide tiempo con `gettimeofday`
- Diferencia entre `usleep` y `sleep`

### En tu código:
```c
gettimeofday(&now, NULL);
long time_ms = now.tv_sec * 1000L + now.tv_usec / 1000L;
```

### Tarea:
- Aprende a calcular los ms entre dos eventos
- ¿Por qué usamos `usleep(1000)` y no `sleep(1)`?

---

## 🔹 4. Detección de muerte

### Qué debes saber:
- Condiciones que provocan la muerte
- Cómo detener la simulación y mostrar mensaje correctamente

### En tu código:
```c
if (time_since_last_meal > data->time_to_die)
```

### Tarea:
- Simula la lógica con papel y lápiz
- ¿Hay conflicto de escritura al morir y al imprimir?

---

## 🔹 5. Alternancia y deadlocks

### Qué debes saber:
- Qué es un deadlock
- Cómo `alternance_cycle` ayuda a evitarlo

### En tu código:
```c
while ((philo->id + data->alternance_cycle) % 2 != 0)
```

### Tarea:
- Simula cómo se alternan los filósofos pares e impares
- ¿Hay otras formas de evitar deadlocks?

---

## 🔹 6. Inicialización y punteros

### Qué debes saber:
- Cómo se inicializan structs y mutexes
- Cómo liberar correctamente la memoria

### En tu código:
```c
data.philosophers[i].left_fork = &data.forks[i];
data.philosophers[i].right_fork = &data.forks[(i + 1) % data.number_of_philosophers];
```

### Tarea:
- Asegúrate de entender por qué se usa `(i + 1) % n`
- Verifica si estás liberando todo correctamente

---

## ✅ Final de la hora

- Marca lo que **entiendes completamente**
- Anota lo que **necesitas preguntar a un compañero**
- Prepárate para usar esto en el diseño de estructuras mañana