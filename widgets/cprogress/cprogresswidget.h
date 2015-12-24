#ifndef CPROGRESSWIDGET_H
#define CPROGRESSWIDGET_H

#include <QWidget>
#include <QPaintEvent>


class cProgressWidget : public QWidget
{
  Q_OBJECT
public:
  explicit cProgressWidget(QWidget *parent = 0);

signals:

public slots:
  void setProgress(int val);

protected:
    void paintEvent(QPaintEvent *);

private:
    double progress;
};

#endif // CPROGRESSWIDGET_H
