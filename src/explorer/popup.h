
/**
 * @file        popup.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class used for displaying success/failure message of operations
 *              made within the UI of the application.
 **/

#pragma once

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>

class PopUp : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

    public:
        explicit PopUp(QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent *event);

    public slots:
        void set_pop_up(const QString& text, bool is_positive);
        void show();

    private slots:
        void hideAnimation();
        void hide();

    private:
        QLabel label;
        QGridLayout layout;
        QPropertyAnimation animation;
        float popupOpacity;
        QTimer *timer;          // timer to hide popup

        bool is_positive = true;
};
