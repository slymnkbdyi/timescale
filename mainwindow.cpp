#include "plot.h"
#include "panel.h"
#include "mainwindow.h"
#include <qwt_date.h>
#include <qwt_scale_widget.h>
#include <qlayout.h>
#include <qwt_plot_canvas.h>
MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{




    // default degerlerin tanımlandığı yer   TARİH ve ARALIK Boşlugu vs..
    Settings settings;
#if 1
    settings.startDateTime = QDateTime( QDate( 2012, 10, 27 ), QTime( 0, 0, 0, 0 ) );
    settings.endDateTime = QDateTime( QDate( 2012, 10, 27 ), QTime( 23, 59, 0, 0 ) );
#else
    settings.startDateTime = QDateTime( QDate( 2011, 5, 3 ), QTime( 0, 6, 0, 0 ) );
    settings.endDateTime = QDateTime( QDate( 2012, 3, 10 ), QTime( 0, 5, 0, 0 ) );
#endif
    settings.maxMajorSteps = 10;
    settings.maxMinorSteps = 8;
    settings.maxWeeks = -1;

    //Kullanılacak nesneler oluşturuluyor
    d_plot = new Plot();
    d_plot1 = new Plot();
    d_plot2 = new Plot();
      d_plot3= new Plot();

    d_panel = new Panel();
    d_panel->setSettings( settings );


    //Genel çerçeve widget tanımlanıyor
    QWidget *box = new QWidget( this );

    //Genel cerceved kullanılacak
     QVBoxLayout *layout = new QVBoxLayout( box );

    // panel ve plot konumlandırılıyor
    layout->addWidget( d_panel);

     QVBoxLayout *chart_layout =new QVBoxLayout();
     chart_layout->addWidget(d_plot);
     chart_layout->addWidget(d_plot1);
     chart_layout->addWidget(d_plot2);
     chart_layout->addWidget(d_plot3);



   //    layout->addWidget(d_plot);
       layout->addLayout(chart_layout,3);




    setCentralWidget( box );

    updatePlot();
    //sinyal olusturuldu  panel düzenlenirse updateplot slotu
    connect( d_panel, SIGNAL( edited() ), SLOT( updatePlot() ) );
    //scalediv değisirse update plot slotu
    connect( d_plot->axisWidget( QwtPlot::xTop ),
        SIGNAL( scaleDivChanged() ), SLOT( updatePanel() ) );
}

void MainWindow::updatePlot()
{
    d_plot->blockSignals( true );
    d_plot->applySettings( d_panel->settings() );
    d_plot->blockSignals( false );
    d_plot1->blockSignals( true );
    d_plot1->applySettings( d_panel->settings() );
    d_plot1->blockSignals( false );
    d_plot2->blockSignals( true );
    d_plot2->applySettings( d_panel->settings() );
    d_plot2->blockSignals( false );
    d_plot3->blockSignals( true );
    d_plot3->applySettings( d_panel->settings() );
    d_plot3->blockSignals( false );
}

void MainWindow::updatePanel()
{
    const QwtScaleDiv scaleDiv = d_plot->axisScaleDiv( QwtPlot::xTop );

    Settings settings = d_panel->settings();
    settings.startDateTime = QwtDate::toDateTime( scaleDiv.lowerBound(), Qt::LocalTime );
    settings.endDateTime = QwtDate::toDateTime( scaleDiv.upperBound(), Qt::LocalTime );

    d_panel->setSettings( settings );
}
