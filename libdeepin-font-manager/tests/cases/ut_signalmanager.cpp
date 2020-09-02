#define private public
#include "signalmanager.h"
#undef private

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../third-party/stub/stub.h"

#include <QDir>

#include <DLog>

namespace {
class TestSignalManager : public testing::Test
{
protected:
    void SetUp()
    {
        sig = SignalManager::instance();
    }
    void TearDown()
    {
        delete  sig;
    }
    // Some expensive resource shared by all tests.
    SignalManager *sig;
};
}

TEST_F(TestSignalManager, check)
{
    emit sig->prevFontChanged();
}
