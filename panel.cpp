#include "panel.h"
#include "settings.h"
#include <qwt_date.h>
#include <qdatetimeedit.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
Panel::Panel( QWidget *parent ):
    QWidget( parent )
{
    // create widgets

    d_startDateTime = new QDateTimeEdit();
    d_startDateTime->setDisplayFormat( "M/d/yyyy h:mm AP :zzz" );
    d_startDateTime->setCalendarPopup( true );

    d_endDateTime = new QDateTimeEdit();
    d_endDateTime->setDisplayFormat( "M/d/yyyy h:mm AP :zzz" );
    d_endDateTime->setCalendarPopup( true );
    
    d_maxMajorSteps = new QSpinBox();
    d_maxMajorSteps->setRange( 0, 50 );

    d_maxMinorSteps = new QSpinBox();
    d_maxMinorSteps->setRange( 0, 50 );

    d_maxWeeks = new QSpinBox();
    d_maxWeeks->setRange( -1, 100 );
    d_maxWeeks->setSpecialValueText( "Disabled" );

    // layout

    QGridLayout *layout = new QGridLayout( );
  //  layout->setAlignment( Qt::AlignLeft | Qt::AlignTop );

    int row = 0;
    layout->addWidget( new QLabel( "From" ), row, 0 );
    layout->addWidget( d_startDateTime, row, 1 );

    row++;
    layout->addWidget( new QLabel( "To" ), row, 0 );
    layout->addWidget( d_endDateTime, row, 1 );

    row++;
    layout->addWidget( new QLabel( "Max. Major Steps" ), row, 0 );
    layout->addWidget( d_maxMajorSteps, row, 1 );

    row++;
    layout->addWidget( new QLabel( "Max. Minor Steps" ), row, 0 );
    layout->addWidget( d_maxMinorSteps, row, 1 );

    row++;
    layout->addWidget( new QLabel( "Max Weeks" ), row, 0 );
    layout->addWidget( d_maxWeeks, row, 1 );

    QGridLayout *videolayout=new QGridLayout();
    videowidget1 = new QPushButton(this);
    videowidget2 = new QPushButton(this);
    videowidget3 = new QPushButton(this);
    videowidget4 = new QPushButton(this);
    videowidget5 = new QPushButton(this);
    videowidget6 = new QPushButton(this);

    videowidget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    videowidget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    videowidget3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    videowidget4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    videowidget5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    videowidget6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);



    videowidget1->setStyleSheet("background-image:url(video_bk.jpg)");
    videowidget2->setStyleSheet("background-image:url(video_bk.jpg)");
    videowidget3->setStyleSheet("background-image:url(video_bk.jpg)");
    videowidget4->setStyleSheet("background-image:url(video_bk.jpg)");
    videowidget5->setStyleSheet("background-image:url(video_bk.jpg)");
    videowidget6->setStyleSheet("background-image:url(video_bk.jpg)");



videolayout->addWidget(videowidget1,0,0);
videolayout->addWidget(videowidget2,0,1);
videolayout->addWidget(videowidget3,1,0);
videolayout->addWidget(videowidget4,1,1);
videolayout->addWidget(videowidget5,2,0);
videolayout->addWidget(videowidget6,2,1);


QHBoxLayout *main_layout = new QHBoxLayout(this);
main_layout->addLayout(layout);

main_layout->addLayout(videolayout);


    connect( d_startDateTime,
        SIGNAL( dateTimeChanged( const QDateTime & ) ), SIGNAL( edited() ) );
    connect( d_endDateTime,
        SIGNAL( dateTimeChanged( const QDateTime & ) ), SIGNAL( edited() ) );
    connect( d_maxMajorSteps,
        SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
    connect( d_maxMinorSteps,
        SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
    connect( d_maxWeeks,
        SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
}

void Panel::setSettings( const Settings &settings )
{
    blockSignals( true );

    d_startDateTime->setDateTime( settings.startDateTime );
    d_endDateTime->setDateTime( settings.endDateTime );

    d_maxMajorSteps->setValue( settings.maxMajorSteps );
    d_maxMinorSteps->setValue( settings.maxMinorSteps );
    d_maxWeeks->setValue( settings.maxWeeks );
        
    blockSignals( false );
}

Settings Panel::settings() const
{
    Settings settings;

    settings.startDateTime = d_startDateTime->dateTime();
    settings.endDateTime = d_endDateTime->dateTime();

    settings.maxMajorSteps = d_maxMajorSteps->value();
    settings.maxMinorSteps = d_maxMinorSteps->value();
    settings.maxWeeks = d_maxWeeks->value();

    return settings;
}
