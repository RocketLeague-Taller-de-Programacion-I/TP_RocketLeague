add_library( lib_action
        ActionCreate.cpp
        ActionCreate.h
        ActionJoin.cpp
        ActionJoin.h
        ActionList.cpp
        ActionList.h
        ActionUpdate.cpp
        ActionUpdate.h
        ActionMove.cpp
        ActionMove.h ActionLeft.cpp ActionLeft.h ActionRight.cpp ActionRight.h ActionUp.cpp ActionUp.h ActionDown.cpp ActionDown.h ActionJump.cpp ActionJump.h ActionTurbo.cpp ActionTurbo.h)
target_link_libraries(lib_action)