#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <stack>

using namespace std;


class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private:

    // Pola przechowujace obrazek
    QImage *img;
    QImage *bg;
    QImage *kopia;

    QLabel *poz;
    QSlider *pozX;
    QSlider *pozY;
    QSlider *pozZ;

    QLabel *roz;
    QSlider *rozX;
    QSlider *rozY;
    QSlider *rozZ;

    QLabel *ro;
    QSlider *rotX;
    QSlider *rotY;
    QSlider *rotZ;

    QCheckBox *tryb;

    QGroupBox *grupa;




    // Zmienne
    int szer;
    int wys;
    int poczX;
    int poczY;

    int x,y,z;

    int x1,y1;

    int x2,y2;


    int idObrazka;

    class pkt{
    public:
        int x;
        int y;
        pkt(){
            x=0;
            y=0;
        }
        pkt(int x, int y){
            this->x = x;
            this->y = y;

        }

        bool operator< (pkt const &q) const { return x<q.x; };

    };

    class pkt3d{
    public:
        double x;
        double y;
        double z;
        pkt3d(){
            x=0;
            y=0;
            z=0;
        }
        pkt3d(double x, double y, double z){
            this->x = x;
            this->y = y;
            this->z = z;

        }
    };

    class macierz{

    public:
        double a11; double a12; double a13; double a14;
        double a21; double a22; double a23; double a24;
        double a31; double a32; double a33; double a34;
        double a41; double a42; double a43; double a44;

        macierz(){
            a11=0; a12=0; a13=0; a14=0;
            a21=0; a22=0; a23=0; a24=0;
            a31=0; a32=0; a33=0; a34=0;
            a41=0; a42=0; a43=0; a44=0;

        }

        macierz(double a11, double a12, double a13, double a14,
        double a21, double a22, double a23, double a24,
        double a31, double a32, double a33, double a34,
        double a41, double a42, double a43, double a44)
        {
            this->a11=a11; this->a12=a12; this->a13=a13; this->a14=a14;
            this->a21=a21; this->a22=a22; this->a23=a23; this->a24=a24;
            this->a31=a31; this->a32=a32; this->a33=a33; this->a34=a34;
            this->a41=a41; this->a42=a42; this->a43=a43; this->a44=a44;
        }



    };

    macierz wynik;

    int tx=0;
    int ty=0;
    int tz=0;

    double sx=1;
    double sy=1;
    double sz=1;

    double alfaX=0;
    double alfaY=0;
    double alfaZ=0;

    int nov1, nov2, nov3, nov4, nov5, nov6;

    int tryb1=0;

     pkt punkty[100];

     int liczba=0;

     pkt przeciecia[100];

     int ilosc = 0;



    // Deklaracje funkcji
    void kopiuj(QImage *img1, QImage *img2, int szer, int wys);

    void wstawPiksel(int x, int y, double r, double g, double b, QImage *img);

    void rysujLinie(double x1, double y1, double x2, double y2, int r, int g, int b, QImage *img);

    void trojkat(pkt punkty[], QImage *img);

    void rysujOkrag(double x1, double y1, double x2, double y2, QImage *img);

    void czysc(QImage *img);

    void szescian(int r, int f, QImage *img);

    void mnozenieMacierzy(macierz m1, macierz m2);

    void aktualizuj(int x, int y, int z);

    void scanLine(pkt punkty[],int licz, int r, int g, int b);

    void sprawdzLinie(int y,pkt punkty[],int licz);



    // Deklaracje sygnalow
signals:


    void valueChanged(int value);

    void stateChanged(int state);




    // Deklaracje slotow
private slots:

    void paintEvent(QPaintEvent*);

    void slotPozX(int val);

    void slotPozY(int val);

    void slotPozZ(int val);

    void slotRozX(int val);

    void slotRozY(int val);

    void slotRozZ(int val);

    void slotRotX(int val);

    void slotRotY(int val);

    void slotRotZ(int val);

    void slotTryb(int state);



};

