
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

/**
 * @brief Manages pop up UI messages.
 **/
class PopUp : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    private:
        /**
         * @brief Sets an opacity on a pop up.
         * @param opacity the opacity.
         **/
        void setPopupOpacity(float opacity);

        /**
         * @brief Gets the current opacity of a pop up.
         * @return the current opacity.
         **/
        float getPopupOpacity() const;

    public:
        explicit PopUp(QWidget *parent = 0);
        ~PopUp();

    protected:
        /**
         * @brief Draw the pop up part of the UI.
         * @param event dummy.
         **/
        void paintEvent(QPaintEvent *event);

    public slots:
        /**
         * @brief Sets a popup.
         * @param text the text of the popup.
         * @param is_positiv creates a success styled pop up when true, otherwise failure pop up is created.
         **/
        void set_pop_up(const QString& text, bool is_positive);

        /**
         * @brief Shows a pop up.
         **/
        void show();

    private slots:
        /**
         * @brief Hides a pop up.
         **/
        void hide();

        /**
         * @brief Manages hide animation of a pop up.
         **/
        void hideAnimation();

    private:
        QLabel label;                       ///< text label of a pop up
        QGridLayout layout;                 ///< layout of a pop up
        QPropertyAnimation animation;       ///< animation of a pop up
        float popupOpacity;                 ///< opacity of a pop up
        QTimer *timer;                      ///< timer used to hide a pop up

        bool is_positive = true;            ///< true when the pop up shows success message, oherwise false and failure message is shown.
};
