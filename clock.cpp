#include "clock.h"
#include "ui_clock.h"
#include <QDebug>
#include <QTimer>
#include <QTime>

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);

    m_second = QTime::currentTime().second();
    m_hour = QTime::currentTime().hour();
    m_minute = QTime::currentTime().minute();

    qDebug() << m_hour << m_minute << m_second;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(slotTimeOutSec()));

    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(slotTimeOutMin()));
    m_timer->start(1000);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::slotTimeOutSec()
{
    m_second++;

    if (m_second%60 == 0)
    {
        m_second = 0;
        m_minute++;
        if(m_minute%60 == 0)
        {
            m_minute = 0;
            //hour change
        }
    }
    repaint();            
}

void Clock::slotTimeOutMin()
{
    //repaint();
}

void Clock::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    int extent;
    if (width()>height())
    {
        extent = height() - 20;
    }
    else
    {
        extent = width() - 20;
    }

    p.translate((width() - extent) / 2, (height() - extent) / 2);
    p.setPen(Qt::red);
    p.setBrush(Qt::darkBlue);
    p.drawEllipse(0, 0, extent, extent);

    p.translate(extent/2, extent/2);
    for(int angle = 0; angle <= 360; angle += 6)
    {
        p.save();
        p.rotate(angle);
        if (angle % 30 == 0)
        {
            p.drawLine(extent*0.45, 0, extent*0.50, 0);
        }
        else
        {
            p.drawLine(extent*0.48, 0, extent*0.50, 0);
        }
        p.restore();
    }
    p.setPen(Qt::green);
    p.drawPoint(0,0);

    p.rotate(6.0 * (m_minute + m_second/60.0) - 90);
    p.setPen(Qt::yellow);
    p.drawLine(QPoint(-extent*0.05, 0),QPoint(extent*0.38, 0));
    p.save();
    
    p.rotate(m_second*6.0 - 90);
    p.setPen(Qt::red);
    p.drawLine(QPoint(-extent*0.05, 0),QPoint(extent*0.42, 0));
    p.save();

}
