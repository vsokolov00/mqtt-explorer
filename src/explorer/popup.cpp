
/**
 * @file        popup.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the PopUp class.
 **/

#include "popup.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

PopUp::PopUp(QWidget *parent) : QWidget(parent)
{
    this->setParent(parent);
    setWindowFlags(Qt::FramelessWindowHint |        // widget is frameless
                   Qt::Tool |                       // not separate window
                   Qt::WindowStaysOnTopHint);       // widget is on top
    setAttribute(Qt::WA_TranslucentBackground);     // background is tranparent
    setAttribute(Qt::WA_ShowWithoutActivating);     // no focus

    animation.setTargetObject(this);
    animation.setPropertyName("popupOpacity");
    connect(&animation, &QAbstractAnimation::finished, this, &PopUp::hide);

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    layout.addWidget(&label, 0, 0);
    setLayout(&layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PopUp::hideAnimation);
}

PopUp::~PopUp()
{
    delete timer;
}

void PopUp::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0, 0 , 0, 180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void PopUp::set_pop_up(const QString &text, bool is_positive)
{
    label.setText(text);
    adjustSize();

    if (is_positive)
    {
        label.setStyleSheet("QLabel { color : #90ee90; "
                            "margin-top: 6px;"
                            "margin-bottom: 6px;"
                            "margin-left: 10px;"
                            "margin-right: 10px; }");
    }
    else
    {
        label.setStyleSheet("QLabel { color : #ff0033; "
                            "margin-top: 6px;"
                            "margin-bottom: 6px;"
                            "margin-left: 10px;"
                            "margin-right: 10px; }");
    }
}

void PopUp::show()
{
    setWindowOpacity(0.0);

    animation.setDuration(150);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);

    QWidget::show();

    animation.start();              // start the animation
    timer->start(3000);             // timer that will hide notification in 3 seconds
}

void PopUp::hideAnimation()
{
    timer->stop();
    animation.setDuration(1000);    // duration of the animation
    animation.setStartValue(1.0);   // widget is 0% transparent
    animation.setEndValue(0.0);     // widget is 100% transparent
    animation.start();              // animation start
}

void PopUp::hide()
{
    //if widget is transparent -> hide it
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void PopUp::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float PopUp::getPopupOpacity() const
{
    return popupOpacity;
}
