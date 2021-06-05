# DeustoChess
Proyecto de Programación IV de la Universidad de Deusto. Desarrollado en Visual Studio. 

# Descripción del proyecto
Nuestro proyecto se basa en el juego del ajedrez. Se comenzará con un menú en el que tendremos diferentes modalidades de juego y la opción de salida. Se puede jugar online, local (offline), contra la máquina y una parte de puzzles.

La modalidad online, como su propio nombre indica, se juega una partida 1 contra 1 de forma online. La modalidad local, es un 1 contra 1 en la que no necesita conexión a internet y se juega en el mismo ordenador. En la modalidad 1 contra máquina, dejaremos elegir dificultad para jugar contra la inteligencia artificial. Y por último, los puzzles, los cuales tienen una serie de retos. Por ejemplo, con unas posiciones en concreto, hacer jaque en 1 movimiento.

Cada movimiento será registrado en un historial en la base de datos, en la que se guardará el id, la puntuación ELO, y las estadísticas del usuario (winner).

Además, dispone de un reloj con un tiempo seleccionable en las tres primeras modalidades en las que seleccionas el tiempo que quieras para jugar. Tras cada movimiento se parará el tiempo y comenzará a correr el tiempo del oponente y así sucesivamente hasta terminarse el tiempo o la partida.

# Estructura del proyecto
El archivo CMakeList.txt contiene un conjunto de directivas e instrucciones que describen los archivos fuente y los destinos del proyecto.
<br /> Ademas el proyecto se divide en 4 grandes carpetas: data, dependencies, src y server.
<br /> La carpeta ***data*** tiene las imagenes y los puzzles.
<br /> La carpeta ***dependencies*** tiene 3 subcarpetas. La carpeta blah se utiliza para la interfaz. La carpeta sqlite para la base de datos, y la carpeta stockfish para la IA.
<br /> La carpeta ***src*** se divide en tres subcarpetas: la carpeta clock que se implementa en un hijo mientras juegas en las tres primeras modalidades como se ha explicado antes, la carpeta game que tiene el menu, las modalidades de juego y la implementacion de los puzzles, y la carpeta utility, que implementa lo basico del juego (las piezas, el tablero, los movimientos...)
<br /> La carpeta ***server*** para la conexion con el servidor (al jugar en la modalidad online), este se encargará de esperar la conexión de ambos jugadores antes de comenzar el tránsito y administración de la información. 

# Conexión online
Para jugar online tienes que meter la IP del servidor que tu abras o de un servidor que ya este abierto. A la hora de crear una conexión online entre dos jugadores, se establecerá una conexión entre puertos a un servidor intermedio que se encargue de administrar la partida. Es una modalidad de juego de 1 contra 1. Para la implementacion de la conexion online tenemos la clase sconector (con sus correspondientes ficheros de cabezera e implementacion) que controla la partida que transcurre de forma online (datos, prioridad...).

# IA
Se ha implementado una IA para una de las modalidades. Se puede elegir dificultad y el tiempo. Nos servimos de la carpeta stockfish que hemos mencionado anteriormente y la implementamos en la clase modulo (con su correspondiente fichero de cabezera e implementacion)

# BD
La base de datos implementada en sqlite realiza todas las operaciones con la BD. Almacena la informacion del jugador (tanto la personal como la relacionada con las partidas), guarda la partida, los participantes y el resultado, y tiene todos los movimientos asociados a la partida correspondiente.

# Pasos
Al comenzar el juego se debe iniciar sesión. Si tienes cuenta, te registras, y a continuación te llevará al menú. Se continua en el menú hasta que se elija una opción: 
<br /> 1. Jugar Local
<br /> 2. Jugar Online
<br /> 3. Jugar contra IA
<br /> 4. Puzzles Rush
<br /> 0. Salir
<br /> Tras elegir una opción. Se continuará a la modalidad de juego elegida o se saldrá del juego.
<br /> **A DISFRUTAR!**
