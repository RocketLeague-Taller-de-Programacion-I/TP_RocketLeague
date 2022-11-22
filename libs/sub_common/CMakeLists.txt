add_library(lib_common
        thread.cpp
        thread.h
        liberror.cpp
        liberror.h
        socket.h
        socket.cpp
        resolver.cpp
        resolver.h
        resolvererror.h
        resolvererror.cpp
        protocolo.h
        protocolo.cpp
        BlockingQueue.h
        ClientReceiver.cpp
        ClientReceiver.h
        ClientSender.cpp
        ClientSender.h
        ProtectedQueue.h
        QueueIsEmptyException.cpp
        QueueIsEmptyException.h )
target_link_libraries(lib_common lib_action)
