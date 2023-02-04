#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QWidget>
#include <QPushButton>

class LandingPage : public QWidget {
Q_OBJECT
public:
    explicit LandingPage(QWidget *parent = 0);

signals:

    void switchSelectSignal();

    void switchCreateSignal();

public slots:

    void switchSelectSlot();

    void switchCreateSlot();

};


#endif
