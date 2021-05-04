#ifndef DASHBOARDCONNECTOR_H
#define DASHBOARDCONNECTOR_H

#include <QObject>

class DashboardController : public QObject
{
    Q_OBJECT
public:
    explicit DashboardController(QObject *parent = nullptr);

signals:

};

#endif // DASHBOARDCONNECTOR_H
