# 🧠 PHILO – Diagrama de sincronización

> Visualización del comportamiento del programa `philosophers`:  
> Reloj, filósofos, turnos, forks, muerte

---

## 📦 Estructura general de ejecución

```text
                           +-----------------------------+
                           |         MAIN THREAD         |
                           |-----------------------------|
                           | - Lee argumentos            |
                           | - Inicializa forks          |
                           | - Crea filósofos (hilos)    |
                           | - Crea hilo clock_thread    |
                           +-----------------------------+
                                       |
                                       v
                           +-----------------------------+
                           |        CLOCK_THREAD         |
                           |-----------------------------|
                           | loop:                       |
                           |  - Revisa si alguien murió  |
                           |  - Si sí: set someone_died  |
                           |  - Cada X ms:               |
                           |    alternance_cycle++       |
                           +-----------------------------+
                                       |
                                       v
                           +-----------------------------+
                           |    PHILOSOPHER_THREAD (n)   |
                           |-----------------------------|
                           | loop:                       |
                           |  if (NOT MY TURN):          |
                           |     - esperar (usleep)      |
                           |  else:                      |
                           |     - mutex_lock forks      |
                           |     - comer (usleep)        |
                           |     - mutex_unlock forks    |
                           |     - dormir (usleep)       |
                           |     - pensar                |
                           +-----------------------------+
```

---

## 🌀 Ejemplo de turnos con 5 filósofos

| alternance_cycle | Fórmula `(id + cycle) % 2 == 0` | Filosofos que pueden comer |
|------------------|----------------------------------|-----------------------------|
| 0                | 2, 4                             | pares comen                 |
| 1                | 1, 3, 5                          | impares comen              |
| 2                | 2, 4                             | pares otra vez             |

---

## ⏱️ Visualización temporal

```text
Tiempo (ms) | Turno actual | Actúan los filósofos
------------|--------------|----------------------
0–200       | 0            | 2 y 4
200–400     | 1            | 1, 3 y 5
400–600     | 2            | 2 y 4
...
```

---

## 💀 Detección de muerte

```text
CLOCK_THREAD:
  Para cada filósofo:
    si (tiempo_actual - last_meal_time > time_to_die)
      -> Imprimir "X died"
      -> someone_died = 1
      -> Terminar simulación
```

---

## 🔁 Ciclo de vida de un filósofo

```text
START
  ↓
CHECK: ¿Es mi turno?
  ↓                ↘
NO → esperar     SÍ
                    ↓
        mutex_lock forks
                    ↓
        actualizar last_meal_time
                    ↓
        comer (usleep)
                    ↓
        mutex_unlock forks
                    ↓
        dormir (usleep)
                    ↓
        pensar
                    ↓
          volver a START
```