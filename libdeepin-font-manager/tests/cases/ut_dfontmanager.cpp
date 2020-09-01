#define private public
#define protected public
#include "dfontmanager.h"
#include "dcopyfilesmanager.h"
#undef private

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../third-party/stub/stub.h"

#include "signalmanager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QSignalSpy>

const QString sysDir = QDir::homePath() + "/.local/share/fonts";

namespace {
class TestDfontmanager : public testing::Test
{

protected:
    void SetUp()
    {
        fm = DFontManager::instance();
    }
    void TearDown()
    {
    }
    // Some expensive resource shared by all tests.
    DFontManager *fm;
};

void stub_Handle()
{

}



}

TEST_F(TestDfontmanager, checkSetType)
{
    fm->setType(DFontManager::Install);
    EXPECT_EQ(fm->m_type, DFontManager::Install);
//    delete fm;
}

TEST_F(TestDfontmanager, checkSetInstallFileList)
{
    QStringList list;
    list << "first" << "second" << "third" << "fouth";
    fm->setInstallFileList(list);
    EXPECT_EQ(fm->m_instFileList.count(), 4);
    EXPECT_EQ(true, fm->m_instFileList.contains("first"));

    list.clear();
    list << "fifth";
    fm->setInstallFileList(list);
    EXPECT_EQ(fm->m_instFileList.count(), 1);
    EXPECT_EQ(true, fm->m_instFileList.contains("fifth"));
//    delete fm;
}

TEST_F(TestDfontmanager, checkSetUnInstallFile)
{
    QStringList list;
    list << "first" << "second" << "third" << "fouth";
    fm->setUnInstallFile(list);
    EXPECT_EQ(fm->m_uninstFile.count(), 4);
    EXPECT_EQ(true, fm->m_uninstFile.contains("first"));
}


TEST_F(TestDfontmanager, checkRunInstall)
{
    Stub s;
    s.set(ADDR(DFontManager, handleInstall), stub_Handle);

    fm->setType(DFontManager::Install);
    fm->run();

    fm->setType(DFontManager::HalfwayInstall);
    fm->run();

    fm->setType(DFontManager::ReInstall);
    fm->run();
}

TEST_F(TestDfontmanager, checkRunUnInstall)
{
    Stub s;
    s.set(ADDR(DFontManager, handleUnInstall), stub_Handle);

    fm->setType(DFontManager::UnInstall);
    fm->run();

    fm->setType(DFontManager::DefaultNullType);
    fm->run();
}

TEST_F(TestDfontmanager, checkDoCmdInstall)
{
    Stub s;
    s.set(ADDR(DFontManager, doInstall), stub_Handle);

    fm->setType(DFontManager::Install);
    fm->doCmd(QStringList());

    fm->setType(DFontManager::HalfwayInstall);
    fm->doCmd(QStringList());

    fm->setType(DFontManager::ReInstall);
    fm->doCmd(QStringList());
}

TEST_F(TestDfontmanager, checkDoCmdUnInstall)
{
    Stub s;
    s.set(ADDR(DFontManager, handleUnInstall), stub_Handle);

    fm->setType(DFontManager::UnInstall);
    fm->doCmd(QStringList());

    fm->setType(DFontManager::DefaultNullType);
    fm->doCmd(QStringList());
}

TEST_F(TestDfontmanager, checkHandleInstallAndDoInstall)
{
    Stub s;
    s.set(ADDR(DCopyFilesManager, copyFiles), stub_Handle);

    QSignalSpy spy(fm, SIGNAL(requestCancelInstall));

    fm->setType(DFontManager::Install);
    fm->m_instFileList << "first";
    fm->handleInstall();

    EXPECT_TRUE(spy.count() == 0);

    fm->cancelInstall();
    fm->handleInstall();

    EXPECT_TRUE(spy.count() == 0);
}

TEST_F(TestDfontmanager, checkHandleUnInstall)
{
    Stub s;
    s.set(ADDR(DFontManager, doCmd), stub_Handle);
    QStringList list;
    list << "first" << "endl";

    fm->setUnInstallFile(list);
    fm->handleUnInstall();
    EXPECT_EQ(true, fm->m_uninstFile.isEmpty());

}

TEST_F(TestDfontmanager, checkDoUnstall)
{
    QSignalSpy spy(fm, SIGNAL(uninstallFontFinished(QStringList)));
    QSignalSpy spys(fm, SIGNAL(uninstallFcCacheFinish()));

    QStringList list;

    QString str = QDir::homePath() + "/.local/share/fonts/Addictype";
    QString filePathOrig = QDir::homePath() + "/Desktop/1048字体/Addictype-Regular.otf";
//    QFile::copy(filePathOrig, str);
//    qDebug() << str << endl;
    QDir d;
    //新建文件夹并确认创建成功
    d.mkdir(str);
    EXPECT_EQ(true, d.exists());
    QFile::copy(filePathOrig, str + "/Addictype-Regular.otf");

    list << str + "/Addictype-Regular.otf";
    fm->doUninstall(list);
    QDir dd(str);
    EXPECT_EQ(false, dd.exists());

}

TEST_F(TestDfontmanager, checkOnInstallResultInstall)
{
    QSignalSpy spy(fm, SIGNAL(installFinished(int, const QStringList)));

    fm->m_instFileList.clear();
    fm->m_instFileList << "first";
    fm->setType(DFontManager::Install);
    fm->setCacheStatus(DFontManager::CacheNow);
    fm->onInstallResult("first", "");

    EXPECT_TRUE(spy.count() == 1);
}

TEST_F(TestDfontmanager, checkOnInstallResultReInstall)
{
    QSignalSpy spy(fm, SIGNAL(reInstallFinished(int, const QStringList)));

    fm->m_instFileList.clear();
    fm->m_instFileList << "first";
    fm->setType(DFontManager::ReInstall);
    fm->setCacheStatus(DFontManager::CacheNow);
    fm->onInstallResult("first", "");

    EXPECT_TRUE(spy.count() == 1);

}


//TEST_F(TestDfontmanager, checkSetSystemFontCount)
//{
//    fm->setSystemFontCount(6);
//    EXPECT_EQ(6, fm->m_systemFontCount);
////    delete fm;
//}

TEST_F(TestDfontmanager, checkSetCacheStatus)
{
    fm->setCacheStatus(DFontManager::CacheNow);
    EXPECT_EQ(fm->m_CacheStatus, DFontManager::Install);
}

TEST_F(TestDfontmanager, checkCancelInstall)
{
    fm->cancelInstall();
    EXPECT_TRUE(fm->m_installCanceled);
}

TEST_F(TestDfontmanager, checkDoCache)
{
    QSignalSpy spy(fm, SIGNAL(cacheFinish()));
    fm->doCache();
    EXPECT_EQ(1, spy.count());
    delete fm;
}






