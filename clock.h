#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT
public slots:
    void slotTimeOutSec();
    void slotTimeOutMin();

public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();

    void paintEvent(QPaintEvent *ev);

private:
    Ui::Clock *ui;
    QTimer *m_timer;
    int m_second;
    int m_hour;
    int m_minute;
};

#endif // CLOCK_H
