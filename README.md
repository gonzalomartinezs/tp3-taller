# Trabajo Práctico 3
### Taller de Programacion I (75.42)

#### Martinez Sastre, Gonzalo Gabriel - 102321

Link al repositorio de Github: https://github.com/gonzalomartinezs/tp3-taller

## Introducción
El objetivo del presente trabajo consiste en desarrollar un cliente-servidor multithreading en el cual, el primero le enviará al segundo un petitorio HTML y este, tras procesarlo, le responderá con el mensaje correspondiente.

La característica principal de este programa reside en la unión del multithreading con el comcepto de cliente-servidor, permitiendo que este último sea capaz de atender a varios clientes en paralelo.

## Desarrollo del programa
Para la realización de esta actividad se decidió dividir el desarrollo de la misma en bloques. Por este motivo, en un principio se procedió a adaptar las implementaciones de socket, cliente y servidor realizadas para el primer trabajo práctico de la materia y, una vez finalizado esto, se puso a prueba el correcto funcionamiento de las mismas.

El siguiente paso fue aplicar la lógica multithreading a lo previamente implentado para así obtener un servidor capaz de intercambiar mensajes con varios clientes en simultáneo. Análogamente al caso anterior, se corroboró el funcionamiento de las clases desarroladas mediante sus respectivos tests.

A continuación, se codificaron las clases involucradas en la atención a petitorios HTML (`HTMLRequestParser`, `HTMLInstruction`, `ProtectedResources`, e `InstructionExecutor` y sus hijas). Tras esto, se procedió a juntar todo lo implementado hasta el momento de manera que se cumpliera la consigna y se corroboró que se pudiera responder a petitorios de varios clientes por medio de distintos hilos de ejecución en paralelo.

Finalmente,  una vez terminado todo lo anterior, se inició el proceso de debugging y refactorización, el cual se vió intercalado con entregas en el SERCOM. 

## Compilación y ejecución
Para compilar el programa simplemente se debe correr el comando:

```
make
```
Luego, se ejecutará el servidor con el siguiente comando:
```
./server <server_port> <root_file>
```
Donde  `<puerto/servicio>` es el puerto TCP (o servicio) el cual el servidor deberá escuchar las conexiones entrantes.

El parámetro  `<root_file>`  representa la ruta a un archivo con una respuesta para el recurso “/”.

Tras esto, el cliente se ejecuta como se muestra a continuación:
```
./client <server_host> <server_port>
```
De esta manera, quedará en espera a que se ingrese un petitorio por `stdin` y, al presionar `Ctrl+D`, se enviará el mismo al servidor, el cual generará una respuesta que aparecerá en la terminal del cliente. Por su parte, en la salida estándar del servidor figurará la primer línea del petitorio.

Además, también se puede correr este programa utilizando el comando de redirección `< <filepath>` en el comando principal para enviar el contenido de un determinado archivo al servidor, como se indica debajo:

```
./client <server_host> <server_port> < <filepath>
```
Cabe destacar que el orden de los comandos debe ser igual al mostrado, de lo contrario el programa no funcionará.

## Sobre el programa

### Estructura

Se puede decir que este programa se divide en tres bloques que resultan interesantes de analizar. Por un lado, se encuentra la interacción entre el cliente y la clase `Socket` para enviar el petitorio y recibir la respuesta. La misma se muestra a continuación junto con la clase `SocketException`.

![alt text][cliente_socket]

Luego, se encuentra el mecanismo por el cual el servidor es capaz de atender a numerosos clientes en simultáneo. El siguiente diagrama esquematiza dicho mecanismo.

![alt text][server] 

Aquí se puede observar como `ClientsAcceptor` y `ClientThread` (ambas hijas de `Thread`) son las responsables de llevar a cabo la lógica multithreading del programa. Por un lado, la primera contiene una lista de hilos de clientes que fueron aceptados y, por el otro, cada isntancia de `ClientThread` se encarga de llevar a cabo la respuesta al petitorio de un único cliente.

Finalmente, el último bloque consiste en el parseo del petitrio y generación de la respuesta adecuada, el cual se diagrama a continuación.

![alt text][request] 


Como aspecto destacable, se puede observar que la clase `HTMLInstruction` contiene un puntero a una instancia de `InstructionExecutor` el cual, al haber implementado un modelo polimórfico, puede apuntar a cualquiera de las clases hijas las cuales están diseñadas para cada una responder a un tipo de petitorio distinto.  

### Flujo de ejecución

El aspecto principal de este programa reside en la posibilidad de utilizar varios hilos para atender a los distintos clientes. Dicha dinámica se resume a grandes rasgos en el siguiente esquema.

![alt text][sec_server]

Cabe destacar que en este diagrama se obvió la relación de `Server` con su propio socket para facilitar el entendimiento del flujo de ejecución y mantener el foco de la atención en la secuencia de threading. 

CCon fines de ahondar aún más en la secuencia descrita, una vez que `ClientsAcceptor` envía el mensaje `start()` a una instancia de `ClientThread`, el esquema que se muestra a continuación resume qué ocurre dentro de dicha clase.  
  
![alt text][sec_request]

Finalmente, resulta interesante repasar la interacción entre el cliente y el socket para enviar y recibir la información.

![alt text][sec_cliente]


### Detalles de implementación
En esta sección se indican algunas suposiciones realizadas y decisiones tomadas a la hora de desarrollar el programa.

- Siempre que se definió un destructor no vacío, se respetò la *"Regla de los tres"* (*Rule of three*), definiendo así el constructor por copia y el operador asignación.

- Los petitorios son cargados en su totalidad en memoria puesto que, a fines de simplificar la tarea, se indicó al alumnado que era viable implementarlo de tal manera.

- En caso de que se haga un POST de dos recursos iguales pero con distintos cuerpos, se sobrescribirá el original.

- Puede ocurrir que el servidor cierre el socket (tras haber ingresado 'q' por entrada estándar) cuando este está por realizar un `accept()`. En dicho caso, en lugar de lanzar un excepción, se optó por agregar al socket el método `is_valid()` de manera tal que si falla `accept()` y se le asigna al socket peer el file descriptor igual a -1, no se ejecutarán las instrucciones posteriores y se saldrá limpia y prolijamente del hilo sin lanzar ningún tipo de excepción.

- Una de las mayores dificultades enfrentadas fue el hecho de encontrarse que dentro de `ClientThread` el método `send()` del socket siempre fallaba. Esto se debía a que si bien `ClientsAcceptor` le pasaba por moviemiento el socket peer al hilo, el constructor por moviemiento de dicho socket no se encontraba implementado. ESto significaba que cada vez que se llamaba al destructor del objeto que cedió el ownership, se cerraba el file descriptor que ahora estaba en manos del hilo. Finalmente, tras implementar dicho constructor, el problema se vio solucionado.

## Conclusión

Este trabajo resultó de gran ayuda para comprender el funcionamiento de un cliente-servidor multithreading en un programa. Las implementaciones realizadas permitieron comprender en buena medida cómo funciona este aspecto básico y fundamental para un ingeniero informático/licenciado en sistemas.



[cliente_socket]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/cliente_socket.png
[request]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/request.png
[server]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/server.png
[sec_cliente]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/sec_cliente.png
[sec_request]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/sec_request.png
[sec_server]:https://github.com/gonzalomartinezs/tp3-taller/blob/master/img/sec_server.png