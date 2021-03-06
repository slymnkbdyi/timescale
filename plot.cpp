#include "plot.h"
#include "settings.h"
#include <qwt_date.h>
#include <qwt_date_scale_draw.h>
#include <qwt_date_scale_engine.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>
#include <QFont>
Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{

QFont serifFont("Times", 6);


    this->setMaximumHeight(50);

    //çercevedeki etikleteri gösterilmesini saglar
    setAutoFillBackground( true );

    //çerceve rengi
    setPalette( Qt::darkGray);
    // iç canvas rengi
    setCanvasBackground( Qt::white);



    plotLayout()->setAlignCanvasToScales(true );

    //
    initAxis( QwtPlot::xTop, "", Qt::LocalTime );
    initAxis( QwtPlot::xBottom,  "Local Time", Qt::LocalTime);



     // canvas kaydırılabilir hale getiriliyor
    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
    //mouse ile zoomlama özelligi ekleniyor
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( canvas() );

    //imlec ile uzak bulma koordinatı verme özelliği
    QwtPlotPicker *picker = new QwtPlotPicker( canvas() );
    picker->setTrackerMode( QwtPlotPicker::AlwaysOn );
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
    {
        const bool on = axis == QwtPlot::xBottom;
            this->setAxisFont(axis,serifFont);
        enableAxis( axis, on );
        panner->setAxisEnabled( axis, on );
        magnifier->setAxisEnabled( axis, on );
    }

  // canvas ızgara özellği ekleniyor    kalın cizgi icin setmajorpen ince cizgiler icin setminorpen
  // x ekseni icin ızgara aktif   y ekseni icin kapatılıyor
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen( Qt::black, 1, Qt::SolidLine );
    grid->setMinorPen( Qt::gray, 1 , Qt::SolidLine );
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( false );
    grid->enableYMin( false);
    grid->attach( this );
}

void Plot::initAxis( int axis, const QString& title, Qt::TimeSpec timeSpec )
{
    //eksene baslık ekleniyor
   // setAxisTitle( axis, title );

    QwtDateScaleDraw *scaleDraw = new QwtDateScaleDraw( timeSpec );
    QwtDateScaleEngine *scaleEngine = new QwtDateScaleEngine( timeSpec );

#if 0
    if ( timeSpec == Qt::LocalTime )
    {
        scaleDraw->setTimeSpec( Qt::OffsetFromUTC );
        scaleDraw->setUtcOffset( 10 );

        scaleEngine->setTimeSpec( Qt::OffsetFromUTC );
        scaleEngine->setUtcOffset( 10 );
    }
#endif
    setAxisScaleDraw( axis, scaleDraw );
    setAxisScaleEngine( axis, scaleEngine );
}

void Plot::applySettings( const Settings &settings )
{
    applyAxisSettings( QwtPlot::xTop, settings );
    applyAxisSettings( QwtPlot::xBottom, settings );

    replot();
}

void Plot::applyAxisSettings( int axis, const Settings &settings )
{
    QwtDateScaleEngine *scaleEngine = 
        static_cast<QwtDateScaleEngine *>( axisScaleEngine( axis ) );

    scaleEngine->setMaxWeeks( settings.maxWeeks );
    setAxisMaxMinor( axis, settings.maxMinorSteps );
    setAxisMaxMajor( axis, settings.maxMajorSteps );


    setAxisScale( axis, QwtDate::toDouble( settings.startDateTime ), 
        QwtDate::toDouble( settings.endDateTime ) );
}
