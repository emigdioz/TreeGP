#include "cprogresswidget.h"
#include <QPainter>

cProgressWidget::cProgressWidget(QWidget *parent) : QWidget(parent)
{
  setProgress(0);
}

void cProgressWidget::setProgress(int val)
{
    progress = (double)val/100;
    //yes, it is not very good, the best approach is to
    //create something similar to QProgressBar
    this->update();
}


void cProgressWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::gray);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setCapStyle(Qt::FlatCap);
    pen.setMiterLimit(0);

    p.setRenderHint(QPainter::Antialiasing);

    QRectF rectangle(10.0, 20.0, 80.0, 80.0);
    //to understand these magic numbers, look drawArc method in Qt doc
    int startAngle = -90 * 16;
    int spanAngle = progress * 360 * 16;
    p.setPen(pen);
    p.drawEllipse(rectangle);
    pen.setColor(Qt::white);
    p.setPen(pen);
    p.drawArc(rectangle, startAngle, spanAngle);

    p.drawText(rectangle,Qt::AlignCenter,QString::number(progress*100)+" %");
}
