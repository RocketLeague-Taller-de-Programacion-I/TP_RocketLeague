//
// Created by lucaswaisten on 31/10/22.
//

#include <gtest/gtest.h>
#include "../common_lib/protocolo.h"

class ProtocoloTest : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        serverProtocolo = new Protocolo("8080");
        clientProtocolo = new Protocolo("localhost","8080");
    }

    virtual void TearDown() {
        delete serverProtocolo;
        delete clientProtocolo;
    }

    Protocolo * serverProtocolo;
    Protocolo * clientProtocolo;
};

TEST(ProtocoloTest,test_clienteEnviaMensaje) {
    ASSERT_EQ(0,0);
}