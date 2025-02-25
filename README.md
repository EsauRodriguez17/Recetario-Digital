# Recetario Digital

## Descripción
El **Recetario Digital** es un software diseñado como proyecto final para la materia de **Estructuras de Datos**. Su objetivo es facilitar la captura, almacenamiento y gestión de recetas de platillos, permitiendo una organización eficiente de la información.

## Clases Principales
1. **Receta**: Representa una receta y almacena atributos como el nombre del platillo, autor, tiempo de preparación, procedimiento y una lista de ingredientes.
   
2. **Ingrediente**: Permite representar cada ingrediente de una receta, incluyendo su nombre, cantidad y unidad de medida.
   
3. **ListaRecetas**: Gestiona una colección de objetos de tipo **Receta** mediante una lista ligada doblemente enlazada, lo que permite un acceso eficiente y operaciones como inserciones y eliminaciones.
   
4. **ListaIngredientes**: Maneja una colección de objetos de tipo **Ingrediente** utilizando una lista ligada simplemente enlazada.

## Funcionalidades
- Visualización de recetas almacenadas, con opción de filtrado por categoría (Desayuno, Comida, Cena, Navideño).
- Agregar, modificar y eliminar recetas o ingredientes.
- Buscar recetas específicas por nombre o categoría, mostrando atributos relevantes.
- Ordenar recetas por nombre o tiempo de preparación.
- Manejar ingredientes de cada receta con inserción ordenada.
- Almacenar y leer el recetario en el disco para mantener la información permanentemente.

## Interfaz Gráfica
La interfaz gráfica está creada con **Qt**, proporcionando un entorno visual intuitivo. Permite la interacción sencilla con las funcionalidades del recetario.

### Clases Adicionales
1. **RecipeCard**: Representa una tarjeta visual que muestra la información principal de una receta, incluyendo imagen, tiempo de preparación, nombre, categoría, y botones para modificar o eliminar.
   
2. **IngredientWidget**: Componente visual para mostrar y gestionar la información de un ingrediente al añadir o modificar una receta.


