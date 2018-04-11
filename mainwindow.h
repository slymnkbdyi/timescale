#include <qmainwindow.h>

class Plot;
class Panel;
class QPushbutton;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );

private Q_SLOTS:
    void updatePlot();
    void updatePanel();

private:
    Plot *d_plot;
     Plot *d_plot1;
         Plot *d_plot2;
             Plot *d_plot3;
    Panel *d_panel;
};
