:- dynamic favorito/4.
:- dynamic programa_ejecutado/0.

% Base de conocimiento de libros y sus características
libro('El nombre del viento', ['Fantasía', 'Aventura', 'Magia']).
libro('1984', ['Ciencia ficción', 'Distopía']).
libro('Cien años de soledad', ['Realismo mágico', 'Ficción']).
libro('El señor de los anillos', ['Fantasía', 'Aventura']).
libro('Crimen y castigo', ['Novela', 'Psicológico']).
libro('Los pilares de la Tierra', ['Histórico', 'Drama']).
libro('Juego de tronos', ['Fantasía', 'Aventura']).
libro('El fin de la eternidad', ['Ciencia ficción', 'Viajes en el tiempo']).

% Mensaje explicativo
:- not(programa_ejecutado),
   write('Bienvenido al programa de recomendación de libros.'), nl,
   write('Puedes explorar las opciones del menú para recomendar libros,'), nl,
   write('ver tus favoritos, marcar libros como leídos y más.'), nl,
   write('Disfruta explorando y ¡feliz lectura!'), nl,
   assert(programa_ejecutado).

% Menú principal
menu :-
    write('*** Menú Principal ***'), nl,
    write('1. Recomendar libro'), nl,
    write('2. Mostrar lista de favoritos'), nl,
    write('3. Marcar libro como leído, añadir descripción y calificar'), nl,
    write('4. Salir del programa'), nl,
    write('Seleccione una opción (1-4): '),
    read(Opcion),
    ejecutarOpcion(Opcion).

% Ejecutar la opción seleccionada
ejecutarOpcion(1) :-
    write('Ingrese la categoría para recomendar libros: '),
    read(Categoria),
    recomendarLibros(Categoria),
    menu.

ejecutarOpcion(2) :-
    mostrarFavoritos,
    menu.

ejecutarOpcion(3) :-
    marcarLeidoCalificar,
    menu.

ejecutarOpcion(4) :-
    write('¡Hasta luego!'), nl,
    goodbye.

goodbye :- throw(finalizar_programa).

% Reglas para la recomendación
recomendarLibros(Categoria) :-
    findall(Titulo, (libro(Titulo, Categorias), member(Categoria, Categorias), not(favorito(Titulo, _, _, _))), Libros),
    mostrarLibros(Libros, Categoria),
    menu.

mostrarLibros([], _) :-
    write('No hay libros disponibles en esta categoría.'), nl.

mostrarLibros(Libros, Categoria) :-
    write('Libros disponibles en la categoría '), write(Categoria), write(':'), nl,
    mostrarLibrosAux(Libros, 1),
    seleccionarLibro(Libros, Categoria).

mostrarLibrosAux([], _).

mostrarLibrosAux([Libro|Resto], N) :-
    write(N), write('. '), write(Libro), nl,
    N1 is N + 1,
    mostrarLibrosAux(Resto, N1).

seleccionarLibro(Libros, Categoria) :-
    length(Libros, NumLibros),
    write('Seleccione el número del libro que desea recomendar (1-' ), write(NumLibros), write('): '),
    read(Seleccion),
    (Seleccion >= 1, Seleccion =< NumLibros ->
        nth1(Seleccion, Libros, Titulo),
        recomendarLibro(Titulo, Categoria),
        nl,
        preguntarAgregarFavorito(Titulo)
        ;
        write('Selección no válida. Inténtelo de nuevo.'), nl,
        seleccionarLibro(Libros, Categoria)
    ).

% Reglas para la recomendación individual
recomendarLibro(Titulo, Categoria) :-
    write('Te recomiendo el libro: '), write(Titulo), write(' (Categoría: '), write(Categoria), write(')'), nl.

% Preguntar al usuario si desea agregar un libro a favoritos
preguntarAgregarFavorito(Titulo) :-
    write('¿Quieres agregar '), write(Titulo), write(' a tus favoritos? (si/no): '),
    read(Respuesta),
    (
        Respuesta == 'si' ->
        agregarFavorito(Titulo, no, '', 0),
        write('Libro añadido a favoritos: '), write(Titulo), nl,
        nl,  % Añadí una nueva línea para mejorar la presentación
        menu;  % Vuelvo al menú
        write('Libro no añadido a favoritos.'), nl,
        nl,  % Añadí una nueva línea para mejorar la presentación
        menu  % Vuelvo al menú
    ).

% Añadir libro a la lista de favoritos
agregarFavorito(Titulo, Leido, Descripcion, Calificacion) :-
    assert(favorito(Titulo, Leido, Descripcion, Calificacion)).

% Mostrar la lista de libros favoritos
mostrarFavoritos :-
    write('Tus libros favoritos son: '), nl,
    favorito(Titulo, Leido, Descripcion, Calificacion),
    write('- '), write(Titulo), write(', Leído: '), write(Leido),
    write(', Descripción: '), write(Descripcion), write(', Calificación: '), write(Calificacion), nl,
    fail.
mostrarFavoritos.

% Marcar libro como leído, añadir descripción y calificar
marcarLeidoCalificar :-
    write('Ingrese el título del libro que has leído: '),
    read(Titulo),
    (
        favorito(Titulo, _, _, _) ->
        write('¿Has leído el libro? (si/no): '),
        read(Leido),
        (
            Leido == 'si' ->
            write('Añade una descripción del libro: '),
            read(Descripcion),
            write('Califica el libro del 1 al 10: '),
            read(Calificacion),
            retract(favorito(Titulo, _, _, _)),
            agregarFavorito(Titulo, Leido, Descripcion, Calificacion),
            write('Libro marcado como leído y calificado.'), nl;
            retract(favorito(Titulo, _, _, _)),
            agregarFavorito(Titulo, no, '', 0),
            write('Libro marcado como no leído.'), nl
        ),
        nl,  % Añadí una nueva línea para mejorar la presentación
        menu  % Vuelvo al menú
        ;
        write('Libro no encontrado en la lista de favoritos.'), nl,
        nl,  % Añadí una nueva línea para mejorar la presentación
        menu  % Vuelvo al menú
    ).

% Iniciar el programa mostrando el menú principal
:- menu.