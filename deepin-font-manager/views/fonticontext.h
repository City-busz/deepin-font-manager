#pragma once

#include <QWidget>
#include <DSvgRenderer>
/*************************************************************************
 <Class>         FontIconText
 <Description>   构造函数-构造字体图标对象
 <Author>
 <Note>          null
*************************************************************************/
class FontIconText : public QWidget
{
    Q_OBJECT
public:
    explicit FontIconText(const QString picPath, QWidget *parent = nullptr);
    //设置字体名
    void setFontName(const QString &familyName, const QString &styleName);
    //设置是否为ttf字体属性
    void setContent(bool isTtf);

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    QString m_picPath;
    DTK_GUI_NAMESPACE::DSvgRenderer *render;
    QFont m_font;
    bool m_isTtf;
};
