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
#        ../sub_server/Action.cpp
#        ../sub_server/Action.h
#        ../sub_server/ClientReceiver.cpp
#        ../sub_server/ClientReceiver.h
#        ../sub_server/ClientSender.cpp
#        ../sub_server/ClientSender.h
        ProtectedQueue.h
        QueueIsEmptyException.cpp
        QueueIsEmptyException.h
#        ../sub_server/ActionCreate.cpp
#        ../sub_server/ActionCreate.h
#        ../sub_server/ActionJoin.cpp
#        ../sub_server/ActionJoin.h
#        ../sub_server/ActionList.cpp
#        ../sub_server/ActionList.h
#        ../sub_server/ActionUpdate.cpp
#        ../sub_server/ActionUpdate.h
        )
target_link_libraries(lib_common)
