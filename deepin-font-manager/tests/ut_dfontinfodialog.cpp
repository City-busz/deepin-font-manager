#define private public
#define protected public
#include "views/dfontinfodialog.h"
#undef private
#undef protected

#include "dfontpreviewitemdef.h"
#include "utils.h"
#include "views/fonticontext.h"
#include "views/dfontinfoscrollarea.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../third-party/stub/stub.h"

#include <QBitmap>
#include <QTest>
#include <QFileInfo>
#include <QFontMetrics>
#include <QTextBlock>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

#include <DApplication>
#include <DApplicationHelper>
#include <DLog>
#include <DFontSizeManager>
#include <DTipLabel>

namespace {
class TestDFontInfoDialog: public testing::Test
{

protected:
    void SetUp()
    {
        w = new QWidget;
        dFontInforDialog = new DFontInfoDialog(&d, w);

    }
    void TearDown()
    {
        delete dFontInforDialog;
        delete  w;
    }
    DFontPreviewItemData d;
    QWidget *w;
    DFontInfoDialog *dFontInforDialog;

};

}

TEST_F(TestDFontInfoDialog, checkKeyPressEvent)
{
    QTest::keyClick(dFontInforDialog, Qt::Key_I, Qt::ControlModifier);

    EXPECT_FALSE(dFontInforDialog->isVisible());
}

TEST_F(TestDFontInfoDialog, checkAutoHeight)
{
    dFontInforDialog->autoHeight(200);
    EXPECT_TRUE(dFontInforDialog->m_scrollArea->viewport()->height() == static_cast<int>(200 * 1.1 + 10));
    dFontInforDialog->autoHeight(350);
    EXPECT_TRUE(dFontInforDialog->m_scrollArea->viewport()->height() == 375);
}

TEST_F(TestDFontInfoDialog, checkResizeEvent)
{
    QSize s;
    QResizeEvent *re = new QResizeEvent(s, s);
    dFontInforDialog->resizeEvent(re);
}

TEST_F(TestDFontInfoDialog, checkInitConnection)
{
    emit DApplicationHelper::instance()->themeTypeChanged(DGuiApplicationHelper::DarkType);

    emit DApplicationHelper::instance()->themeTypeChanged(DGuiApplicationHelper::LightType);
}

TEST_F(TestDFontInfoDialog, checkAutoFeed)
{
    QString str;
    str.fill('a', 100);
    qDebug() << str << endl;
    str = dFontInforDialog->AutoFeed(str);
    EXPECT_TRUE(str.size() != 100);

    QString str2;
    str2.fill('a', 20);
    str2 = dFontInforDialog->AutoFeed(str2);
    EXPECT_TRUE(str2.size() == 20) << str2.size();
}

//fontinfoArea
TEST_F(TestDFontInfoDialog, checkfontinfoAreaEventFilter)
{
    QEvent *e = new QEvent(QEvent::FontChange);

    dFontInforDialog->m_fontinfoArea->eventFilter(dFontInforDialog->m_fontinfoArea, e);
}



