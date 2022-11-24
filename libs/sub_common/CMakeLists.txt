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
#        ../sub_server/protocolo.h
#        ../sub_server/protocolo.cpp
        BlockingQueue.h
        ProtectedQueue.h
        QueueIsEmptyException.cpp
        QueueIsEmptyException.h
        )
target_link_libraries(lib_common)
