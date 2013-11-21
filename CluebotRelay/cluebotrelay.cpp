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
    this->timer = new QTimer(this);
    this->Joined = false;
}

CluebotRelay::~CluebotRelay()
{
    delete this->cluenet;
    delete this->tm;
    delete this->timer;
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

    this->timer->start(200);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(OnTick()));
}

void CluebotRelay::OnTick()
{
    if (!Joined && this->cluenet->IsConnected() && this->tm->IsConnected())
    {
        this->tm->Join("#en.wikipedia.huggle");
        this->cluenet->Join("#cluebotng-spam");
        this->cluenet->Join("#wikipedia-van");
        Joined = true;
    }
    Huggle::IRC::Message *message;
    message = this->cluenet->GetMessage();
    while (message != NULL)
    {
        // get a diff id
        if (message->Text.contains("?diff="))
        {
            QString diff = message->Text.mid(message->Text.indexOf("?diff=") + 6);
            if (diff.contains("&"))
            {
                diff = diff.mid(0, diff.indexOf("&"));
            }
            if (message->Text.endsWith("# Reverted"))
            {
                this->tm->Send("#en.wikipedia.huggle", QString(QChar(001)) + QString(QChar(001)) + "ROLLBACK " + diff);
            } else
            {
                QString score = message->Text;
                int i = 2;
                while (i > 0)
                {
                    if (score.contains("#"))
                    {
                        score = score.mid(0, score.lastIndexOf("#"));
                        i--;
                    } else
                    {
                        score = "";
                        break;
                    }
                }
                if (score.contains("#"))
                {
                    score = score.mid(score.indexOf("#") + 1);
                    score = score.replace(" ", "");
                    if (score != "0" && score != "N/A")
                    {
                        double s = score.toDouble();
                        if (s == 0)
                        {
                            this->Debug("Invalid score: " + score);
                        } else if (s > 0.1)
                        {
                            s = s - 0.2;
                            int HuggleScore = (int)(s * 1000);
                            this->tm->Send("#en.wikipedia.huggle", QString(QChar(001)) + QString(QChar(001)) + "SCORED " + diff + " " + QString::number(HuggleScore));
                        }
                    }
                }
            }
        }
        delete message;
        message = this->cluenet->GetMessage();
    }
}
