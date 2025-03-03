# Recetario Digital

## Descripción
El **Recetario Digital** es un software diseñado como proyecto final para la materia de **Estructuras de Datos** utilizando c++ y Qt para la UI. Su objetivo es facilitar la captura, almacenamiento y gestión de recetas de platillos, permitiendo una organización eficiente de la información.

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


# Funcionalidades del Recetario Digital

## 1. Página de Inicio
- **Descripción**: Muestra las últimas recetas agregadas.
- ![Imagen de la página de inicio](https://drive.google.com/file/d/1BLFDJrBHide_KlGGlo92B2Udq9tLd1as/view?usp=drive_link)

## 2. Página de Recetas
- **Descripción**: Muestra todas las recetas con su información general y su imagen.
- ![Imagen de la página de recetas](https://drive.google.com/file/d/1n-qlMeqMjOzwjNHjmFFed5Hi5RVc8AUT/view?usp=drive_link)

### 2.1 Búsqueda de Recetas
- **Descripción**: Permite buscar recetas en la lista de recetas disponibles.

#### 2.1.1 Búsqueda
- Se realiza la búsqueda en la lista de recetas al presionar el icono de la lupa o presionar Enter.
- ![Imagen de la búsqueda](https://drive.google.com/file/d/1n-qlMeqMjOzwjNHjmFFed5Hi5RVc8AUT/view?usp=drive_link)

#### 2.1.2 Resultado de la Búsqueda
- **Si se encuentra la receta**: La aplicación redirige automáticamente a la vista detallada de esa receta.
- ![Imagen de receta encontrada](https://drive.google.com/file/d/1WQtYGxgjs7kez5WD5hplGdT-iAIl7cEH/view?usp=drive_link)

- **Si no se encuentra la receta**: Se mostrará un mensaje indicativo de que no se ha encontrado la receta.
- ![Imagen de mensaje no encontrado](https://drive.google.com/file/d/1On9O_g9etTmIn82KKX67opJny1s1bKpk/view?usp=drive_link)

### 2.2 Filtrado por Categoría
- **Descripción**: Filtra las recetas por categorías disponibles.

#### 2.2.1 Categorías Disponibles
- **Desayuno**
- **Comida**
- **Cena**
- **Navideño**
- ![Imagen de filtrado por la categoria de desayuno](https://drive.google.com/file/d/1Uc4A9zEUrzV26Q5Obx7ey-C-skziwBMn/view?usp=drive_link)
- ![Imagen de filtrado por la categoria de comida](https://drive.google.com/file/d/1ogzsM3Fzgm7flAGCpzTD0eqjBNnMjA-x/view?usp=drive_link)
- ![Imagen de filtrado por la categoria de cena](https://drive.google.com/file/d/1hbccGuF9luWV2VoLdqtdqADCIYKJHD5S/view?usp=drive_link)
- ![Imagen de filtrado por la categoria de navideño](https://drive.google.com/file/d/1RfKphFWRMOuUTht8LViyca5a_LhyNa5S/view?usp=drive_link)

### 2.3 Ordenamiento de las Recetas
- **Descripción**: Permite ordenar las recetas por nombre o tiempo de prepación.

#### 2.3.1 Ordenar por Nombre
- **Acción**: Ordena las recetas alfabéticamente por nombre.
- ![Imagen de ordenamiento por nombre](https://drive.google.com/file/d/12UgL2-SC656Kz2QqDjOXZsHgFu_C9DHU/view?usp=drive_link)

#### 2.3.2 Ordenar por Tiempo de Preparación
- **Acción**: Ordena las recetas por tiempo de preparación (de menor a mayor).
- ![Imagen de ordenamiento por tiempo](https://drive.google.com/file/d/1DRyxjBolU1HJ0hRZpU5eKv0QugIwJTAK/view?usp=drive_link)

### 2.4 Eliminar Todas las Recetas
- **Descripción**: Elimina todas las recetas de la lista.

#### 2.4.1 Confirmación de Eliminación
- **Acción**: Al presionar el botón de eliminar, se pedirá la confirmación antes de eliminar todas las recetas de la lista.
- ![Imagen de confirmación de eliminación](https://drive.google.com/file/d/16GKHlBb_A5NSJFbtgYrXjZnAV9jwxWXJ/view?usp=drive_link)

## 3. Página para Agregar una Receta
- **Descripción**: Permite agregar nuevas recetas a la lista.
- ![Imagen de página para agregar receta](https://drive.google.com/file/d/14VaRLLAjIPt0GQ_fv4j2ORxqEkut-Zoi/view?usp=drive_link)

### 3.1 Agregar Foto y Seleccionar Categoría
- **Acción**: Permite agregar una foto y seleccionar la categoría de la receta.
- ![Imagen de agregar foto y seleccionar categoría](https://drive.google.com/file/d/1l3nhhfe_YEpdmIvXKmzgKyTJlutkCgn7/view?usp=drive_link)

### 3.2 Agregar Ingredientes
- **Acción**: Permite agregar los ingredientes necesarios para la receta.
- ![Imagen de agregar ingredientes](https://drive.google.com/file/d/1-eFYbMIt-PXo0kOvhubEgWUHkb7uYpg4/view?usp=drive_link)

### 3.3 Agregar Procedimiento y Guardar
- **Acción**: Permite agregar el procedimiento para la receta y guardar la información.
- ![Imagen de agregar procedimiento](https://drive.google.com/file/d/19jX-lAxoVz_IzCGgdQ0XxcmWF-Mk6pnv/view?usp=drive_link)

### 3.4 Representación en la Interfaz
- **Acción**: Se crea la representación visual de la receta en la interfaz.
- ![Imagen de representación en la interfaz](https://drive.google.com/file/d/1rjQii71oUK5W82vNN1I5DoVuLvGtZkAD/view?usp=drive_link)

## 4. Modificar Receta
- **Descripción**: Permite modificar recetas existentes.

### 4.1 Modificar Receta
- **Acción**: Se reutiliza la página de agregar receta. Al presionar el botón de modificar en una receta, los campos se llenan automáticamente, permitiendo modificar lo necesario.
- ![Imagen de modificar receta](https://drive.google.com/file/d/1G9u9ReaVEemltOzZmnquEdDYlceh02XI/view?usp=drive_link)

### 4.2 Eliminar Todos los Ingredientes de una Receta
- **Acción**: Al presionar el botón de eliminar los ingredientes estando en la página de modificación, se pedirá confirmación antes de eliminar todos los ingredientes (solo se elimina la representacion visual hasta que confirme los cambios de la receta).
- ![Imagen de eliminar ingredientes](https://drive.google.com/file/d/1EBSAFp90oWqMrCz0dS_vYN75nA-dVhmZ/view?usp=drive_link)

#### 4.2.1 Confirmación de Eliminación
- **Acción**: La eliminación de los ingredientes solo ocurrirá cuando el usuario presione "Guardar cambios".
- ![Imagen de confirmación de eliminación de ingredientes](https://drive.google.com/file/d/14ZMiFR8zJzENoER4UYNc_z2_di4oZqMo/view?usp=drive_link)

#### 4.2.2 Cancelar Cambios
- **Acción**: Si se presiona "Cancelar", simplemente regresa a la página de recetas y no se realizan cambios en la receta.



