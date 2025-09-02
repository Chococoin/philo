# 🧠 Philosophers – Sprint 1 (C Piscine @ 42 Firenze)

> 📅 Semana: 2–8 septiembre 2025  
> 🎯 Objetivo: Comprender, implementar y testear la versión mandatory del proyecto `philo/`  
> 🕒 Tiempo estimado: 35 horas (~5h/día)  
> 📌 Recomendación oficial: ~70 horas en total

---

## ✅ Objetivos del Sprint 1

- Entender el proyecto y cómo funciona la concurrencia con threads y mutexes
- Implementar una primera versión estable de `philo/` (mandatory)
- Dominar la lógica de detección de muerte y sincronización de forks
- Garantizar que el código no tenga memory leaks ni data races
- Practicar la defensa oral explicando cada decisión de diseño

---

## 📆 Plan de trabajo por día

### 📍 Día 1 – Lectura profunda + visualización (2 sept)
- [ ] Leer el subject completo con atención
- [ ] Dibujar esquema de:
  - [ ] Filósofos y forks
  - [ ] Ciclo de vida: thinking → eating → sleeping
  - [ ] Uso de `mutex` para forks
- [ ] Estudiar funciones clave:
  - [ ] `pthread_create`, `pthread_mutex_lock`, `usleep`, `gettimeofday`
- [ ] Escribir ideas clave en un documento personal

---

### 📍 Día 2 – Planificación de estructuras (3 sept)
- [ ] Diseñar las `struct` principales
  - [ ] `t_philo`, `t_rules`, etc.
- [ ] Esquematizar funciones necesarias (`init`, `life`, `cleanup`, etc.)
- [ ] Crear Makefile base
- [ ] Escribir pseudocódigo del flujo principal
- [ ] Inicializar control de versiones con `git init`

---

### 📍 Día 3 – Setup y parsing (4 sept)
- [ ] Implementar el `main()`
- [ ] Parsear y validar argumentos
- [ ] Inicializar estructuras de reglas y filósofos
- [ ] Crear forks como `mutex` y asignarlos a cada filósofo
- [ ] Comenzar la creación de threads

---

### 📍 Día 4 – Rutina del filósofo (5 sept)
- [ ] Implementar `philosopher_routine()`
- [ ] Agregar comportamiento:
  - [ ] Tomar forks (mutex lock)
  - [ ] Comer (`usleep`, actualizar tiempo última comida)
  - [ ] Soltar forks (mutex unlock)
  - [ ] Dormir y pensar
- [ ] Imprimir logs con timestamp y número del filósofo

---

### 📍 Día 5 – Detección de muerte (6 sept)
- [ ] Crear función de monitoreo (`check_death()` o `monitor_thread`)
- [ ] Comparar tiempo actual con `last_meal`
- [ ] Detener simulación si un filósofo muere
- [ ] Mostrar log de muerte en < 10ms

---

### 📍 Día 6 – Pruebas y errores (7 sept)
- [ ] Verificar comportamiento con distintos inputs
- [ ] Testear casos extremos (1 filósofo, 200 filósofos, etc.)
- [ ] Verificar:
  - [ ] No hay data races
  - [ ] No hay memory leaks (`valgrind`)
  - [ ] Los mensajes no se solapan (usar `mutex` de impresión)

---

### 📍 Día 7 – Refactor + documentación (8 sept)
- [ ] Limpiar y dividir funciones
- [ ] Comentar el código
- [ ] Escribir un mini `README.md`
- [ ] Preparar presentación oral del código
- [ ] Crear primeros test automáticos (opcional)

---

## 📋 Checklist final del Sprint 1

- [ ] Subject comprendido 100%
- [ ] Código funcional sin errores visibles
- [ ] No hay memory leaks
- [ ] Los mensajes no se pisan entre sí
- [ ] Se detecta la muerte correctamente
- [ ] Se puede explicar cada función y cada `struct`
- [ ] Makefile funciona (`make`, `make clean`, etc.)
- [ ] Proyecto listo para defensa o avanzar con bonus

---

## 🛠 Herramientas útiles

- `valgrind --tool=helgrind ./philo ...`
- `man pthread_create`, `man usleep`, `man gettimeofday`
- [42docs](https://harm-smits.github.io/42docs/)
- `draw.io` o papel para diagramar forks, filósofos y tiempos

---

## 🚀 Preparado para el Sprint 2:
Si todo esto está completo y entendido, estás listo para:
- Implementar el argumento opcional `number_of_times_each_philosopher_must_eat`
- Explorar la parte bonus con procesos y semáforos (`philo_bonus/`)
- O empezar `minishell`

---

### 🧠 Recuerda:
No copies código que no entiendas. Defiende cada línea.  
La AI te asiste, pero tú debes ser el autor y comprender el 100%.

> _"Philosophy begins in wonder."_ – Platón 🏛️