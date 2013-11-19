//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "cluebotrelay.hpp"


CluebotRelay::CluebotRelay(QObject *parent) : QObject(parent)
{
    this->tm = new Huggle::IRC::NetworkIrc("irc.tm-irc.org", "ClueBot");
    this->cluenet = new Huggle::IRC::NetworkIrc("irc.cluenet.org", "HuggleBot");
}

CluebotRelay::~CluebotRelay()
{
    delete this->cluenet;
    delete this->tm;
}

void CluebotRelay::Debug(QString text)
{
    text = "<" + QDateTime::currentDateTime().toString() + "> " + text;
    std::cout << text.toStdString() << std::endl;
}

void CluebotRelay::run()
{
    if (!this->tm->Connect())
    {
        this->Debug("Unable to connect to tm-irc");
        QCoreApplication::exit(4);
        return;
    }

    if (!this->cluenet->Connect())
    {
        this->Debug("Unable to connect to cluenet");
        QCoreApplication::exit(6);
        return;
    }
}