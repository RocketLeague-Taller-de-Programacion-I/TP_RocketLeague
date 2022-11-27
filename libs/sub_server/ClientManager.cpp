//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <functional>
#include "ClientManager.h"
#include "protocolo.h"
#include "ClientReceiver.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
        client(std::move(aClient)),
        gameManager(aGameManager),
        closed(false){}

/*
    Pierden mucha memoria con los commands, y en general en todo el juego. 
    Siempre que hacen new, primero preguntense si realmente es necesario y luego, si estan seguros que lo es, hagan aparecer algún puntero inteligente. 
    En este casi si lo es y lo justifican porque necesitan que los commandos sean polimorficos. 
    La cola bloqueante probablemente sea de std::shared_ptr y la protegida de std::unique_ptr.
    Falta limpiar a las partidas finalizadas (de igual modo que limpian a los clientes que terminaron).
*/

void ClientManager::run() {
    // Las queues no tienen porqué estar en el heap, de hecho podrían hacer un move al contexto que las necesite
    auto initialActionsQueue = new ProtectedQueue<ServerAction*>;
    //ProtectedQueue<ServerAction*>
    auto initialUpdatesQueue = new BlockingQueue<ServerUpdate*>;
    //BlockingQueue<ServerUpdate*>
    startClientThreads(initialActionsQueue, initialUpdatesQueue);
    ServerAction* command;



    std::function<BlockingQueue<ServerUpdate*>*(ProtectedQueue<ServerAction *> *)> queue_setter_callable =
            std::bind(&ClientManager::setQueues, this, std::placeholders::_1);
    bool playing = false; //  Mientras no se una o no cree una partida == no este jugando
    while (!playing) {
        try {
            /*
             * Este es un busy wait. Si usan una cola para recibir en la primera etapa de lobby, esta debe ser bloqueante. 
             * Si es la misma cola la que van a necesitar para la parte del juego, quizás una forma rápida (aunque no muy elegante) de salir del apuro es juntar la cola bloqueante y la protegida en una misma clase y que esta implemente los metodos blocking_pop y non_blocking_pop. 
             */

            // Como alternativa a la implementación de la queue, podrían encarar por este lado (aunque aconsejamos FUERTEMENTE que vayan por la opcion anterior, ya que este es un refactor grande).

            /*
            * Un poquito mas prolijo sería que este callback inicie a los hilos receiver y sender (por como les quedó el diseño).
            * En ese caso, el ClientManager recibiría los primeros comandos (JOIN, CREATE y LIST) por socket. Una vez que reciba
            * un JOIN o un CREATE, dejará de loopear acá, y en caso de que me pueda unir o pueda crear la partida, se iniciarán
            * correctamente ambos hilos
            * ```
            *  // algo menos verboso que bind (pueden seguir usando bind si quieren! podrían reducir la verbosidad utilizando typedef)
            *  auto startThreadsCallable = [this](ProtectedQueue<std::unique_ptr<ActionServer>>& gameQueue) {
            *      this->shouldContinueLooping = false;
            *      this->startThreads(gameQueue);
            *  };
            *
            *  auto recvCallable = [this](uint16_t sizeToReceive) {
            *      std::vector<uint8_t> dataVector(sizeToReceive);
            *      this.socket.recvall(dataVector.data(), sizeToReceive, ...);
            *      return dataVector;
            *  }
            *
            *  auto sendCallable = [this](std::vector<uint8_t> &toSend) {
            *      this.socket.sendAll(dataVector.data(), data.size(), ...);
            *  }
            *  // shouldContinueLooping -> atomic_bool
            *  while (this.shouldContinueLooping) {
            *      uint8_t command = 0x0;
            *      this.socket.recvall(&command, 1);
            *      switch (command) {
            *          case CREATE:
            *          case JOIN:
            *          case LIST:
            *              // actionCommand será alguno de los comandos (ActionCreate, ActionJoin, ActionList)
            *              // cuando se crea, recibe al GameManager (entonces sabe a que metodo de ese monitor llamar)
            *              // deserializeDataOnCommand recibe el opcode del comando (un byte) y switchea sobre el mismo
            *              // El protocolo tiene acceso a recvCallable para recibir el resto del payload del comando y poder crearlo
            *              // Si hay que enviarle una rta. al cliente, hacemos uso del sendCallable!
            *              auto actionCommand = protocol.deserializeDataOnCommand(command,
            *                                                                     aGameManager,
            *                                                                     recvCallable,
            *                                                                     sendCallable,
            *                                                                     startThreadsCallable);
            *              // se llama polimorficamente a execute
            *              actionCommand.execute();
            *          default:
            *              std::cerr << "Bad command received\n";
            *              // handle this
            *      }
            *      // si llegué acá, puedo esperar a los hilos (estaría buena otra funcion de esta clase que me permita cerrar al Receiver!)
            *      clientReceiverThread.join();
            *      clientSenderThread.join();
            *  }
            * ```
            */
            command = initialActionsQueue->pop();
        } catch (...) {
            continue;
        }
        auto action = command->execute(this->gameManager, queue_setter_callable);
        //create,join y list
        if (action->getReturnData() == "OK") {
            playing = true;
            std::cout<<"playing"<<std::endl;
        }
        initialUpdatesQueue->push(action);
    }
}

bool ClientManager::joinThread() {
    if (not closed) return false;
    return this->endManager();
}

bool ClientManager::endManager() {
    closed = true;
    client.shutdown(2);
    client.close();
    this->clientReceiverThread->join();
    this->clientSenderThread->join();
    delete this->clientReceiverThread;
    delete this->clientSenderThread;
    this->join();
    return closed;
}

void ClientManager::attendClient(unsigned long aId) {
    this->id = aId;
    this->start();
}

void ClientManager::startClientThreads(ProtectedQueue<ServerAction *> *qReceiver, BlockingQueue<ServerUpdate *> *senderQueue) {
    //qReceiver -> ServerAction
    //senderQueue -> ServerUpdate

    // los hilos podrían estar en el stack, no hace falta que esten en el heap
    // las queues podrian ser movidas al contexto de los threads

    clientReceiverThread = new ClientReceiver(client, qReceiver, id);
    clientSenderThread = new ClientSender(client, senderQueue, id);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}
BlockingQueue<ServerUpdate *> * ClientManager::setQueues(ProtectedQueue<ServerAction *> *gameQueue) {
    // como el hilo receiver ya está iniciado y posiblemente esté modificando la queue, tienen una data race
    clientReceiverThread->setQueue(gameQueue);
    return (clientSenderThread->getQueue());
}

void ClientManager::stop() {}

ClientManager::~ClientManager() {
    endManager();
}