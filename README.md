# Fundamentos de la Programación — UNED

Ejercicios, prácticas, PEC y apuntes propios de la asignatura, realizados con el entorno C±.

## Organización

- `ejercicios/`: ejercicios de práctica, organizados por tema.
- `pecs/`: trabajos de evaluación, organizados por entrega o ejercicio.
- `apuntes/`: notas y resúmenes propios.

El primer ejemplo está en [`Ejercicios/Ej1.cpp`](Ej1.cpp): muestra cinco datos por pantalla. Los datos de la versión publicada son ficticios.

## Compilar y ejecutar

1. Abre el entorno C±.
2. Abre el archivo `.cpp` que quieras ejecutar.
3. Pulsa **F6** para compilar y ejecutar, o utiliza **Generar → Compilar y Ejecutar en C±**.

Los ejecutables y archivos de compilación quedan excluidos de Git.

## Subir nuevos ejercicios

Guarda las fuentes `.cpp` y `.h` en la carpeta correspondiente. Desde la carpeta del repositorio, abre una terminal y ejecuta:

```powershell
git status
git add ejercicios pecs apuntes
git diff --cached
git commit -m "Añadir ejercicios de la asignatura"
git push
```

Revisa los cambios antes del commit. Al ser un repositorio público, utiliza datos de ejemplo en lugar de DNI, correos personales u otros datos identificativos.

Este es un repositorio personal de estudio, sin vinculación oficial con la UNED. Los enunciados y materiales docentes se consultan en el campus de la asignatura.
