# TP_RocketLeague

Logica de movimiento.
En la metadata de las actions move tiene que estar el ID del player para que
el monitor pueda buscar en que partida esta el player.
Luego de eso, la partida le avisa al jugador que hizo un Action de type move,
el jugador le dice le avisa la juego que hizo tal move y el juego se encarga de corroborar 
toda la fisica, possiciones, socres, etc de lo que hizo el jugador.
El juego retorna la metada de todos los objetos update, y player retorna esta metadata.
Por ultimo la partida crea un Update con esta metadata y la pushea a la queueSender.
clientSender popea este ultimo update y lo envia por medio del socket.