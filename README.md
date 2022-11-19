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

El client manager que lanze los thread reciver y sender

La queue receiver la tiene que crear el Game. De alguna manera se tiene que devolver esa queue para que el client manager 
le diga a ClientReceiver la cola a la cula tiene que pushear. 

En el join sera lo mismo


Que la action le pase un callback del client manager al game manager. 
Leer la docu pasada por discord. Bindear el setQueueRecivercer para el client manager

Si client manager se va de scope antes que los hilos de receiver, sender y socket. Tenemos el receriver y el sender apuntando a memoria que fue liberada