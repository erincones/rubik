# Rubik

Cubo Rubik en OpenGL para el proyecto final de Introducción a la Computación Gráfica ([ICG](http://ccg.ciens.ucv.ve/categoria/materias/introduccion-a-la-computacion-grafica/)) I-2017.


### Detalles de implementación

* Lectura y despliegue de archivos OBJ.
* Manejo de datos con Vertex Array Object (VAO).
* Modelo de iluminación Gouraud.
* Mapeo de texturas.
* Animaciones independientes de los FPS.
* Minicubo guía para orientación.
* Interacción con mouse.
  * Rotación con cuaterniones: Arrastrar con click izquierdo.
  * Click and drag: Arrastrar con click derecho.
  * Zoom: Subir y bajar rueda del mouse.
* Interacción con teclado.
  * Jugar: Q, W, E, R, T, Y, A, S, D, F, G, H.
  * Pantalla completa: ALT + Enter.


### Por hacer

* Mostrar controles.
* Mostrar número de pasos.
* Temporizador.
* Mostrar botones para opciones.
* N-Filas x N-Columnas x N-Capas.
* Cambiar calidad del juego.
* Sonido.
* Armar cubo.
* Evitar que el cubo salga de la pantalla.
* Centrar cubo.
* Ajustar velocidad del turno.
* Ajustar FPS.



---

### Dependencias

* [FreeGLUT](http://freeglut.sourceforge.net/)
* [GLEW](http://glew.sourceforge.net/)
* [GLM](https://glm.g-truc.net/)
* [SOIL](http://www.lonesock.net/soil.html)

Los modelos 3D han sido diseñados con [Blender](https://www.blender.org/).

_Aunque se trata de un proyecto de [QtCreator](https://www.qt.io/) en Lubuntu no es difícil migrarlo a Visual Studio._
