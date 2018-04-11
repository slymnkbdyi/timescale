#ifndef _PANEL_
#define _PANEL_

#include "settings.h"
#include <qwidget.h>

class QDateTimeEdit;
class QSpinBox;
class QPushButton;
class Panel: public QWidget
{
    Q_OBJECT

public:
    Panel( QWidget *parent = NULL );

    void setSettings( const Settings &);
    Settings settings() const;
    
Q_SIGNALS:
    void edited();

private:
    QDateTimeEdit* d_startDateTime;
    QDateTimeEdit* d_endDateTime;

    QSpinBox *d_maxMajorSteps;
    QSpinBox *d_maxMinorSteps;
    QSpinBox *d_maxWeeks;

    QPushButton *videowidget1;
    QPushButton *videowidget2;
    QPushButton *videowidget3;
    QPushButton *videowidget4;
    QPushButton *videowidget5;
    QPushButton *videowidget6;

};

#endif
