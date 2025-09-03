# 🧠 PHILO – Estudio técnico (Hora 2)

> 📅 Día 1 – continuación  
> ⏱️ Duración: 1 hora activa (estimada)  
> 🎯 Objetivo: Comprender a fondo cómo se mide el tiempo y se detecta la muerte de un filósofo

---

## 🔹 3. Tiempo en milisegundos

### Qué debes saber:
- [ ] Cómo se mide tiempo con `gettimeofday`
- [ ] Cómo convertir `struct timeval` a milisegundos
- [ ] Por qué se prefiere `usleep` sobre `sleep`
- [ ] Qué precisión tiene `usleep`

### En tu código:
```c
gettimeofday(&now, NULL);
long time_ms = now.tv_sec * 1000L + now.tv_usec / 1000L;
```

### Tareas:
- [ ] Escribe una función simple que imprima el tiempo actual en ms
- [ ] Compara `usleep(1000)` y `sleep(1)` con `gettimeofday` (haz experimentos)
- [ ] Verifica en documentación qué tan precisa es `usleep` (realmente puede dormir más)

---

## 🔹 4. Detección de muerte

### Qué debes saber:
- [ ] Qué condición provoca la muerte de un filósofo
- [ ] Qué significa "morir" en el contexto del programa
- [ ] Cómo se mide el tiempo desde la última comida
- [ ] Qué pasa si dos filósofos mueren "casi" al mismo tiempo
- [ ] Por qué el mensaje de muerte debe imprimirse en < 10ms

### En tu código:
```c
if (time_since_last_meal > data->time_to_die)
{
    printf("Philosopher %d died after %ld ms without eating\n", philo->id, time_since_last_meal);
    data->someone_died = 1;
}
```

### Tareas:
- [ ] Simula con papel/lápiz: filósofo 3 come a 100ms, siguiente comida a 950ms, `time_to_die` es 800ms → ¿muere?
- [ ] Revisa si el `printf()` está protegido con mutex
- [ ] Revisa si `data->someone_died` podría ser leído/escrito por múltiples hilos a la vez (¿data race?)
- [ ] Verifica si `clock_thread` realmente se ejecuta a tiempo (¿hay retardo acumulado?)

---

## ✅ Al finalizar esta hora:

- [ ] Entiendo perfectamente cómo se mide y se calcula el tiempo
- [ ] Sé cuándo y cómo muere un filósofo
- [ ] Puedo modificar el código para mejorar la precisión de detección de muerte
- [ ] Puedo explicarle a alguien más cómo funciona esta parte del proyecto

---

## 🛠 Sugerencias de prueba:

- Ejecuta el programa con `valgrind --tool=helgrind` y observa si hay data races en el acceso a `someone_died`
- Agrega un `printf` en `clock_thread` para ver si corre en intervalos estables