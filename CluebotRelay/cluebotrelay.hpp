//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef CLUEBOTRELAY_H
#define CLUEBOTRELAY_H

#include <QCoreApplication>
#include <iostream>
#include <QTimer>
#include <QObject>
#include "networkirc.hpp"

class CluebotRelay : public QObject
{
    Q_OBJECT
public:
    CluebotRelay(QObject *parent = 0);
    ~CluebotRelay();
    Huggle::IRC::NetworkIrc *tm;
    Huggle::IRC::NetworkIrc *cluenet;
    bool Joined;
    QTimer *timer;
    void Debug(QString text);

public slots:
    void run();
    void OnTick();


signals:
    void finished();
};

#endif // CLUEBOTRELAY_H
