#include "mywindow.h"
#include <QVBoxLayout>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <stack>
using namespace std;

MyWindow::MyWindow(QWidget *parent): QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Oswietlenie w Qt");


    // Ustawiamy wymiary obrazka
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;

    //Zmieniamy rozmiar okna
    resize(szer+2*poczX+300,wys+2*poczY);


    // Tworzymy obiekty klasy QImage
    img = new QImage(szer,wys,QImage::Format_RGB32);
    bg = new QImage(szer, wys, QImage::Format_RGB32);
    kopia = new QImage(szer, wys, QImage::Format_RGB32);


    grupa = new QGroupBox(this);
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,275,wys));
    QVBoxLayout *boxLayout = new QVBoxLayout;

    poz = new QLabel("Pozyzja");

    pozX = new QSlider(Qt::Horizontal);
    pozX->setMinimum(-szer);
    pozX->setMaximum(szer);
    pozX->setValue(0);

    connect(pozX, SIGNAL(valueChanged(int)), this, SLOT(slotPozX(int)));


    pozY = new QSlider(Qt::Horizontal);
    pozY->setMinimum(-wys);
    pozY->setMaximum(wys);
    pozY->setValue(0);

    connect(pozY, SIGNAL(valueChanged(int)), this, SLOT(slotPozY(int)));


    pozZ = new QSlider(Qt::Horizontal);
    pozZ->setMinimum(-100);
    pozZ->setMaximum(100);
    pozZ->setValue(0);

    connect(pozZ, SIGNAL(valueChanged(int)), this, SLOT(slotPozZ(int)));


    roz = new QLabel("Rozmiar");

    rozX = new QSlider(Qt::Horizontal);
    rozX->setMinimum(0);
    rozX->setMaximum(1000);
    rozX->setValue(100);

    connect(rozX, SIGNAL(valueChanged(int)), this, SLOT(slotRozX(int)));


    rozY = new QSlider(Qt::Horizontal);
    rozY->setMinimum(0);
    rozY->setMaximum(1000);
    rozY->setValue(100);

    connect(rozY, SIGNAL(valueChanged(int)), this, SLOT(slotRozY(int)));

    rozZ = new QSlider(Qt::Horizontal);
    rozZ->setMinimum(0);
    rozZ->setMaximum(1000);
    rozZ->setValue(100);

    connect(rozZ, SIGNAL(valueChanged(int)), this, SLOT(slotRozZ(int)));


    ro = new QLabel("Rotacja");

    rotX = new QSlider(Qt::Horizontal);
    rotX->setMinimum(-650);
    rotX->setMaximum(650);
    rotX->setValue(0);

    connect(rotX, SIGNAL(valueChanged(int)), this, SLOT(slotRotX(int)));

    rotY = new QSlider(Qt::Horizontal);
    rotY->setMinimum(-650);
    rotY->setMaximum(650);
    rotY->setValue(0);

    connect(rotY, SIGNAL(valueChanged(int)), this, SLOT(slotRotY(int)));

    rotZ = new QSlider(Qt::Horizontal);
    rotZ->setMinimum(-650);
    rotZ->setMaximum(650);
    rotZ->setValue(0);

    connect(rotZ, SIGNAL(valueChanged(int)), this, SLOT(slotRotZ(int)));

    tryb = new QCheckBox();
    tryb->setText("Ukrywanie krawedzi");

    connect(tryb,SIGNAL(stateChanged(int)), this, SLOT(slotTryb(int)));




    boxLayout->addWidget(poz);
    boxLayout->addWidget(pozX);
    boxLayout->addWidget(pozY);
    boxLayout->addWidget(pozZ);

    boxLayout->addWidget(roz);
    boxLayout->addWidget(rozX);
    boxLayout->addWidget(rozY);
    boxLayout->addWidget(rozZ);

    boxLayout->addWidget(ro);
    boxLayout->addWidget(rotX);
    boxLayout->addWidget(rotY);
    boxLayout->addWidget(rotZ);

    boxLayout->addWidget(tryb);

    grupa->setLayout(boxLayout);

    szescian(100,200,img);


}


MyWindow::~MyWindow()
{
    delete img;
    delete bg;

}




// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{

    QPainter p(this);


    p.drawImage(poczX,poczY, *img);


    update();
}



// Funkcja kopiujaca obraz
void MyWindow::kopiuj(QImage *img1, QImage *img2, int szer, int wys)
{
    unsigned char *ptrImg1;
    unsigned char *ptrImg2;

    ptrImg1 = img1->bits();
    ptrImg2 = img2->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // Przepisuje wartosci pikseli z Bg do Img
        for(j=0; j<szer; j++)
        {
            ptrImg2[szer*4*i + 4*j] = ptrImg1[szer*4*i + 4*j]; // Skladowa BLUE
            ptrImg2[szer*4*i + 4*j + 1] = ptrImg1[szer*4*i + 4*j + 1] ; // Skladowa GREEN
            ptrImg2[szer*4*i + 4*j + 2] = ptrImg1[szer*4*i + 4*j + 2]; // Skladowa RED
        }
    }

}

//funkcja czyszczaca
void MyWindow::czysc(QImage *img)
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}

//Funkcja wstawiajaca piksel
void MyWindow::wstawPiksel(int x, int y, double r, double g, double b, QImage *img)
{
    unsigned char *ptr;
    ptr = img->bits();


    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        ptr[szer*4*y + 4*x] = b;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x + 2] = r;
    }

}



//Funkcja rysujaca linie
void MyWindow::rysujLinie(double x1, double y1, double x2, double y2, int r, int g, int b, QImage *img)
{

    double a,b1;

    if(x1==x2)
    {
        x=x1;

        if(y1>y2){
            std::swap(y1,y2);
        }

            for(int y=y1;y<y2;y++)
            {

                wstawPiksel(x,y,r,g,b,img);
            }

    }
    else
    {

    a = (y2 - y1)/(x2-x1);
    b1 = y1 - a*x1;


    if(abs(a)<=1)
    {

        if(x1>x2)
            std::swap(x1,x2);

        for(x=x1;x<x2;x++)
        {
            y = a*x+b1;

            wstawPiksel(x,y,r,g,b,img);

       }

    }
    else
    {


        if(y1>y2)
            std::swap(y1,y2);

        for(y=y1;y<=y2;y++)
        {
            x=(y-b1)/a;


            wstawPiksel(x,y,r,g,b,img);

        }

    }


    }

}

//Funkcja rysujaca okrag
void MyWindow::rysujOkrag(double x1, double y1, double x2, double y2, QImage *img)
{
    double R;

    R = sqrt( pow(x2-x1,2) + pow(y2-y1,2) );


    for(int x=0; x< R/(sqrt(2)); x++)
    {
        y = sqrt(pow(R,2) - pow(x,2) );




        wstawPiksel(x+x1,y+y1,255,0,0,img);
        wstawPiksel(x+x1,-y+y1,255,0,0,img);
        wstawPiksel(-x+x1,y+y1,255,0,0,img);
        wstawPiksel(-x+x1,-y+y1,255,0,0,img);
        wstawPiksel(y+x1,x+y1,255,0,0,img);
        wstawPiksel(y+x1,-x+y1,255,0,0,img);
        wstawPiksel(-y+x1,x+y1,255,0,0,img);
        wstawPiksel(-y+x1,-x+y1,255,0,0,img);


    }

}


//funkcja rysujaca trojkat
void MyWindow::trojkat(pkt punkty[], QImage *img)
{



     rysujLinie(punkty[0].x,punkty[0].y,punkty[1].x,punkty[1].y,255,0,0,img);
     rysujLinie(punkty[0].x,punkty[0].y,punkty[2].x,punkty[2].y,255,0,0,img);
     rysujLinie(punkty[1].x,punkty[1].y,punkty[2].x,punkty[2].y,255,0,0,img);

}

//funkcja wykonujaca operacje macierzowe i aktualizujaca punkt
void MyWindow::aktualizuj(int x, int y, int z)
{
    macierz punkt = macierz(x,0,0,0,
                            y,0,0,0,
                            z,0,0,0,
                            1,0,0,0);

    macierz T0 = macierz(1,0,0,0,
                        0,1,0,0,
                        0,0,1,200,
                        0,0,0,1);

    macierz T = macierz(1,0,0,tx,
                        0,1,0,ty,
                        0,0,1,tz,
                        0,0,0,1);

    macierz S = macierz(sx,0,0,0,
                        0,sy,0,0,
                        0,0,sz,0,
                        0,0,0,1);

    macierz Rx = macierz(1,0,0,0,
                         0, cos(alfaX), -sin(alfaX), 0,
                         0, sin(alfaX), cos(alfaX), 0,
                         0, 0 , 0 ,1);

    macierz Ry = macierz(cos(alfaY), 0, sin(alfaY), 0,
                         0,1,0,0,
                         -sin(alfaY), 0, cos(alfaY), 0,
                         0,0,0,1);

    macierz Rz = macierz(cos(alfaZ) , -sin(alfaZ), 0, 0,
                         sin(alfaZ), cos(alfaZ), 0, 0,
                         0         , 0        , 1, 0,
                         0,0,0,1);


    mnozenieMacierzy(T0,T);
    mnozenieMacierzy(wynik,Rz);
    mnozenieMacierzy(wynik,Ry);
    mnozenieMacierzy(wynik,Rx);
    mnozenieMacierzy(wynik,S);

    mnozenieMacierzy(wynik,punkt);

}

//funkcja obslugujaca tworzenie szescianu
void MyWindow::szescian(int r, int f, QImage *img)
{
    czysc(img);

    pkt3d punkty[8] = {pkt3d(-r,r,r),
                       pkt3d(r,r,r),
                       pkt3d(-r,-r,-r),
                       pkt3d(r,-r,-r),
                       pkt3d(-r,-r,r),
                       pkt3d(r,-r,r),
                       pkt3d(-r,r,-r),
                       pkt3d(r,r,-r)};

    pkt punkty2[8];

    for(int i=0;i<8;i++)
    {
        int tmpx, tmpy, tmpz;
        int x, y;
        int cx = szer/2;
        int cy = wys/2;

        aktualizuj(punkty[i].x, punkty[i].y, punkty[i].z);


        punkty[i].x=wynik.a11;
        punkty[i].y=wynik.a21;
        punkty[i].z=wynik.a31;


        tmpx=wynik.a11;
        tmpy=wynik.a21;
        tmpz=wynik.a31;

        if(tmpz>-200)
        {
        x=((tmpx*f)/(tmpz+f))+cx;
        y=((tmpy*f)/(tmpz+f))+cy;
        }
        else
        {
            x=(tmpx*f)+cx;
            y=(tmpy*f)+cy;
        }

        punkty2[i].x = x;
        punkty2[i].y = y;

    }


    pkt3d w1;
    pkt3d w2;

    w1 = pkt3d(punkty[7].x-punkty[6].x, punkty[7].y-punkty[6].y, punkty[7].z-punkty[6].z);
    w2 = pkt3d(punkty[2].x-punkty[6].x, punkty[2].y-punkty[6].y, punkty[2].z-punkty[6].z);
    pkt3d n1 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    w1 = pkt3d(punkty[5].x-punkty[4].x, punkty[5].y-punkty[4].y, punkty[5].z-punkty[4].z);
    w2 = pkt3d(punkty[0].x-punkty[4].x, punkty[0].y-punkty[4].y, punkty[0].z-punkty[4].z);
    pkt3d n2 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    w1 = pkt3d(punkty[3].x-punkty[2].x, punkty[3].y-punkty[2].y, punkty[3].z-punkty[2].z);
    w2 = pkt3d(punkty[4].x-punkty[2].x, punkty[4].y-punkty[2].y, punkty[4].z-punkty[2].z);
    pkt3d n3 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    w1 = pkt3d(punkty[7].x-punkty[3].x, punkty[7].y-punkty[3].y, punkty[7].z-punkty[3].z);
    w2 = pkt3d(punkty[5].x-punkty[3].x, punkty[5].y-punkty[3].y, punkty[5].z-punkty[3].z);
    pkt3d n4 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    w1 = pkt3d(punkty[6].x-punkty[7].x, punkty[6].y-punkty[7].y, punkty[6].z-punkty[7].z);
    w2 = pkt3d(punkty[1].x-punkty[7].x, punkty[1].y-punkty[7].y, punkty[1].z-punkty[7].z);
    pkt3d n5 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    w1 = pkt3d(punkty[2].x-punkty[6].x, punkty[2].y-punkty[6].y, punkty[2].z-punkty[6].z);
    w2 = pkt3d(punkty[0].x-punkty[6].x, punkty[0].y-punkty[6].y, punkty[0].z-punkty[6].z);
    pkt3d n6 = pkt3d(w1.y*w2.z-w1.z*w2.y, w2.x*w1.z-w1.x*w2.z, w1.x*w2.y-w1.y*w2.x);

    cout << "w1.x "<<w1.x<<" w1.y "<<w1.y<<" w1.z "<<w1.z<<" "<<endl;

    pkt3d v1 = pkt3d(-(punkty[7].x+punkty[2].x)/2, -(punkty[7].y+punkty[2].y)/2, -f - (punkty[7].z+punkty[2].z)/2);
    pkt3d v2 = pkt3d(-(punkty[5].x+punkty[0].x)/2, -(punkty[5].y+punkty[0].y)/2, -f - (punkty[5].z+punkty[0].z)/2);
    pkt3d v3 = pkt3d(-(punkty[5].x+punkty[2].x)/2, -(punkty[5].y+punkty[2].y)/2, -f - (punkty[5].z+punkty[2].z)/2);
    pkt3d v4 = pkt3d(-(punkty[7].x+punkty[5].x)/2, -(punkty[7].y+punkty[5].y)/2, -f - (punkty[7].z+punkty[5].z)/2);
    pkt3d v5 = pkt3d(-(punkty[7].x+punkty[0].x)/2, -(punkty[7].y+punkty[0].y)/2, -f - (punkty[7].z+punkty[0].z)/2);
    pkt3d v6 = pkt3d(-(punkty[0].x+punkty[2].x)/2, -(punkty[0].y+punkty[2].y)/2, -f - (punkty[0].z+punkty[2].z)/2);


    nov1 = n1.x*v1.x + n1.y*v1.y + n1.z*v1.z;
    nov2 = n2.x*v2.x + n2.y*v2.y + n2.z*v2.z;
    nov3 = n3.x*v3.x + n3.y*v3.y + n3.z*v3.z;
    nov4 = n4.x*v4.x + n4.y*v4.y + n4.z*v4.z;
    nov5 = n5.x*v5.x + n5.y*v5.y + n5.z*v5.z;
    nov6 = n6.x*v6.x + n6.y*v6.y + n6.z*v6.z;

if(tryb1==0)
{

    rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[1].x, punkty2[1].y,255,0,0,img);
    rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[4].x, punkty2[4].y,255,0,0,img);
    rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[6].x, punkty2[6].y,255,0,0,img);


    rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[5].x, punkty2[5].y,255,0,0,img);
    rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[7].x, punkty2[7].y,255,0,0,img);

    rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[3].x, punkty2[3].y,255,0,0,img);
    rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[6].x, punkty2[6].y,255,0,0,img);

    rysujLinie(punkty2[3].x,punkty2[3].y, punkty2[7].x, punkty2[7].y,255,0,0,img);

    rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[5].x, punkty2[5].y,255,0,0,img);
    rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[2].x, punkty2[2].y,255,0,0,img);

    rysujLinie(punkty2[5].x,punkty2[5].y, punkty2[3].x, punkty2[3].y,255,0,0,img);

    rysujLinie(punkty2[6].x,punkty2[6].y, punkty2[7].x, punkty2[7].y,255,0,0,img);


}
else
{

    if(nov1>0)
    {


       int dlv = sqrt(pow(v1.x,2)+pow(v1.y,2)+pow(v1.z,2));
       v1.x = v1.x/dlv;
       v1.y = v1.y/dlv;
       v1.z = v1.z/dlv;

       int dln = sqrt(pow(n1.x,2)+pow(n1.y,2)+pow(n1.z,2));
       n1.x = n1.x/dln;
       n1.y = n1.y/dln;
       n1.z = n1.z/dln;


       cout << v1.x << v1.y << v1.z<<endl;
       cout << n1.x << n1.y << n1.z<<endl;


       double I = n1.x*v1.x + n1.y*v1.y + n1.z*v1.z;

       cout<< I<<endl;


      if(I > 1)
          I=1;

      if(I < 0.2)
          I=0.2;

      rysujLinie(punkty2[6].x,punkty2[6].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);
      rysujLinie(punkty2[3].x,punkty2[3].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);
      rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[6].x, punkty2[6].y,255*I,0,0,img);
      rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[3].x, punkty2[3].y,255*I,0,0,img);




      pkt punkty3[4] = {punkty2[2],punkty2[3],punkty2[7],punkty2[6]};

      scanLine(punkty3,4,255*I,0,0);

    }
    if(nov2>0)
    {


        int dlv = sqrt(pow(v2.x,2)+pow(v2.y,2)+pow(v2.z,2));
        v2.x = v2.x/dlv;
        v2.y = v2.y/dlv;
        v2.z = v2.z/dlv;

        int dln = sqrt(pow(n2.x,2)+pow(n2.y,2)+pow(n2.z,2));
        n2.x = n2.x/dln;
        n2.y = n2.y/dln;
        n2.z = n2.z/dln;


        double I = n2.x*v2.x + n2.y*v2.y + n2.z*v2.z;


       if(I > 1)
           I=1;

       if(I < 0.2)
           I=0.2;

       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[1].x, punkty2[1].y,255*I,0,0,img);
       rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[5].x, punkty2[5].y,255*I,0,0,img);
       rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[5].x, punkty2[5].y,255*I,0,0,img);
       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[4].x, punkty2[4].y,255*I,0,0,img);



        pkt punkty3[4] = {punkty2[0],punkty2[1],punkty2[5],punkty2[4]};

        scanLine(punkty3,4,255*I,0,0);
    }
    if(nov3>0)
    {


       int dlv = sqrt(pow(v3.x,2)+pow(v3.y,2)+pow(v3.z,2));
       v3.x = v3.x/dlv;
       v3.y = v3.y/dlv;
       v3.z = v3.z/dlv;

       int dln = sqrt(pow(n3.x,2)+pow(n3.y,2)+pow(n3.z,2));
       n3.x = n3.x/dln;
       n3.y = n3.y/dln;
       n3.z = n3.z/dln;


       double I = n3.x*v3.x + n3.y*v3.y + n3.z*v3.z;

      if(I > 1)
          I=1;

      if(I < 0.2)
          I=0.2;

      rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[3].x, punkty2[3].y,255*I,0,0,img);
      rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[2].x, punkty2[2].y,255*I,0,0,img);
      rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[5].x, punkty2[5].y,255*I,0,0,img);
      rysujLinie(punkty2[5].x,punkty2[5].y, punkty2[3].x, punkty2[3].y,255*I,0,0,img);



      pkt punkty3[4] = {punkty2[2],punkty2[3],punkty2[5],punkty2[4]};

      scanLine(punkty3,4,255*I,0,0);

    }
    if(nov4>0)
    {


       int dlv = sqrt(pow(v4.x,2)+pow(v4.y,2)+pow(v4.z,2));
       v4.x = v4.x/dlv;
       v4.y = v4.y/dlv;
       v4.z = v4.z/dlv;

       int dln = sqrt(pow(n4.x,2)+pow(n4.y,2)+pow(n4.z,2));
       n4.x = n4.x/dln;
       n4.y = n4.y/dln;
       n4.z = n4.z/dln;


       double I = n4.x*v4.x + n4.y*v4.y + n4.z*v4.z;

      if(I > 1)
          I=1;

      if(I < 0.2)
          I=0.2;

      rysujLinie(punkty2[5].x,punkty2[5].y, punkty2[3].x, punkty2[3].y,255*I,0,0,img);
      rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[5].x, punkty2[5].y,255*I,0,0,img);
      rysujLinie(punkty2[3].x,punkty2[3].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);
      rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);



      pkt punkty3[4] = {punkty2[3],punkty2[7],punkty2[1],punkty2[5]};

      scanLine(punkty3,4,255*I,0,0);

    }
    if(nov5>0)
    {


        int dlv = sqrt(pow(v5.x,2)+pow(v5.y,2)+pow(v5.z,2));
        v5.x = v5.x/dlv;
        v5.y = v5.y/dlv;
        v5.z = v5.z/dlv;

        int dln = sqrt(pow(n5.x,2)+pow(n5.y,2)+pow(n5.z,2));
        n5.x = n5.x/dln;
        n5.y = n5.y/dln;
        n5.z = n5.z/dln;


        double I = n5.x*v5.x + n5.y*v5.y + n5.z*v5.z;

       if(I > 1)
           I=1;

       if(I < 0.2)
           I=0.2;

       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[1].x, punkty2[1].y,255*I,0,0,img);
       rysujLinie(punkty2[1].x,punkty2[1].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);
       rysujLinie(punkty2[6].x,punkty2[6].y, punkty2[7].x, punkty2[7].y,255*I,0,0,img);
       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[6].x, punkty2[6].y,255*I,0,0,img);



       pkt punkty3[4] = {punkty2[7],punkty2[1],punkty2[0],punkty2[6]};

       scanLine(punkty3,4,255*I,0,0);

    }
    if(nov6>0)
    {


        int dlv = sqrt(pow(v6.x,2)+pow(v6.y,2)+pow(v6.z,2));
        v6.x = v6.x/dlv;
        v6.y = v6.y/dlv;
        v6.z = v6.z/dlv;

        int dln = sqrt(pow(n6.x,2)+pow(n6.y,2)+pow(n6.z,2));
        n6.x = n6.x/dln;
        n6.y = n6.y/dln;
        n6.z = n6.z/dln;


        double I = n6.x*v6.x + n6.y*v6.y + n6.z*v6.z;

       if(I > 1)
           I=1;

       if(I < 0.2)
           I=0.2;

       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[6].x, punkty2[6].y,255*I,0,0,img);
       rysujLinie(punkty2[2].x,punkty2[2].y, punkty2[6].x, punkty2[6].y,255*I,0,0,img);
       rysujLinie(punkty2[4].x,punkty2[4].y, punkty2[2].x, punkty2[2].y,255*I,0,0,img);
       rysujLinie(punkty2[0].x,punkty2[0].y, punkty2[4].x, punkty2[4].y,255*I,0,0,img);



       pkt punkty3[4] = {punkty2[6],punkty2[0],punkty2[4],punkty2[2]};

       scanLine(punkty3,4,255*I,0,0);

    }

}
}


//funkcja pozwalajaca na mnozenie macierzy
void MyWindow::mnozenieMacierzy(macierz m1, macierz m2)
{
    wynik.a11=m1.a11*m2.a11 + m1.a12*m2.a21 + m1.a13*m2.a31 + m1.a14*m2.a41;
    wynik.a12=m1.a11*m2.a12 + m1.a12*m2.a22 + m1.a13*m2.a32 + m1.a14*m2.a42;
    wynik.a13=m1.a11*m2.a13 + m1.a12*m2.a23 + m1.a13*m2.a33 + m1.a14*m2.a43;
    wynik.a14=m1.a11*m2.a14 + m1.a12*m2.a24 + m1.a13*m2.a34 + m1.a14*m2.a44;

    wynik.a21=m1.a21*m2.a11 + m1.a22*m2.a21 + m1.a23*m2.a31 + m1.a24*m2.a41;
    wynik.a22=m1.a21*m2.a12 + m1.a22*m2.a22 + m1.a23*m2.a32 + m1.a24*m2.a42;
    wynik.a23=m1.a21*m2.a13 + m1.a22*m2.a23 + m1.a23*m2.a33 + m1.a24*m2.a43;
    wynik.a24=m1.a21*m2.a14 + m1.a22*m2.a24 + m1.a23*m2.a34 + m1.a24*m2.a44;

    wynik.a31=m1.a31*m2.a11 + m1.a32*m2.a21 + m1.a33*m2.a31 + m1.a34*m2.a41;
    wynik.a32=m1.a31*m2.a12 + m1.a32*m2.a22 + m1.a33*m2.a32 + m1.a34*m2.a42;
    wynik.a33=m1.a31*m2.a13 + m1.a32*m2.a23 + m1.a33*m2.a33 + m1.a34*m2.a43;
    wynik.a34=m1.a31*m2.a14 + m1.a32*m2.a24 + m1.a33*m2.a34 + m1.a34*m2.a44;

    wynik.a41=m1.a41*m2.a11 + m1.a42*m2.a21 + m1.a43*m2.a31 + m1.a44*m2.a41;
    wynik.a42=m1.a41*m2.a12 + m1.a42*m2.a22 + m1.a43*m2.a32 + m1.a44*m2.a42;
    wynik.a43=m1.a41*m2.a13 + m1.a42*m2.a23 + m1.a43*m2.a33 + m1.a44*m2.a43;
    wynik.a44=m1.a41*m2.a14 + m1.a42*m2.a24 + m1.a43*m2.a34 + m1.a44*m2.a44;



}

//funkcja scanLine
void MyWindow::scanLine(pkt punkty[100],int licz, int r, int g, int b)
{

    //wyznaczenie minimalnego i maksymalnego y

    int ymin=600, ymax=0;

    for(int i=0;i<licz;i++)
    {
        if(punkty[i].y > ymax)
            ymax=punkty[i].y;

        if(punkty[i].y < ymin)
            ymin = punkty[i].y;
    }

    //petla od y minimalnego do y maksymalnego
    for(int y=ymin;y<=ymax;y++){

        //sprawdzenie przeciec w linii
        sprawdzLinie(y,punkty,licz);

        sort(przeciecia, przeciecia+ilosc);

        for(int i=0;i<ilosc;i++)
        {
            //rysowanie linii miedzy parzystymi, a nieparzystymi przecieciami
            if(i%2==0 && i+1<ilosc){
            rysujLinie(przeciecia[i].x,przeciecia[i].y,przeciecia[i+1].x,przeciecia[i+1].y,r,g,b, img);

            }
        }

    }

}

//funkcja sprawdzajaca przeciecia w danej linii
void MyWindow::sprawdzLinie(int y, pkt punkty[100], int licz)
{
    ilosc=0;
    for(int i=0;i<licz-1;i++){

        //sprawdzenie czy y znajduje sie miedzy 2 punktami
        if((punkty[i].y>y && punkty[i+1].y<y) || (punkty[i].y<y && punkty[i+1].y>y)){


            pkt punkt(punkty[i].x+((y-punkty[i].y)*(punkty[i+1].x-punkty[i].x))/(punkty[i+1].y-punkty[i].y) , y);
            przeciecia[ilosc] = punkt;
            ilosc++;
        }
        //sprawdzenie czy liczyc przeciecie z punktem
        else if(i>0 && y==punkty[i].y && ((punkty[i-1].y>y && punkty[i+1].y<=y) || (punkty[i-1].y<=y && punkty[i+1].y>y) ) )
        {
            przeciecia[ilosc] = punkty[i];
            ilosc++;
        }

    }
    //sprawdzenie czy y znajduje sie miedzy 2 punktami dla odcinka miedzy ostatnim, a pierwszym puntem
    if((punkty[0].y>y && punkty[licz-1].y<y) || (punkty[0].y<y && punkty[licz-1].y>y)){

        pkt punkt(punkty[0].x+((y-punkty[0].y)*(punkty[licz-1].x-punkty[0].x))/(punkty[licz-1].y-punkty[0].y) , y);
        przeciecia[ilosc] = punkt;
        ilosc++;


    }
    //sprawdzenie czy liczyc przeciecie z punktem pierwszym
    else if(y==punkty[0].y && ((punkty[licz-1].y>y && punkty[1].y<=y) || (punkty[licz-1].y<=y && punkty[1].y>y) ) )
    {
        przeciecia[ilosc] = punkty[0];
        ilosc++;
    }
    //sprawdzenie czy liczyc przeciecie z punktem ostatnim
    else if(y==punkty[licz-1].y && ((punkty[licz-2].y>y && punkty[0].y<=y) || (punkty[licz-2].y<=y && punkty[0].y>y) ) )
    {
        przeciecia[ilosc] = punkty[licz-1];
        ilosc++;
    }

}



void MyWindow::slotPozX(int val)
{
    tx=val;
    szescian(100,200,img);
}

void MyWindow::slotPozY(int val)
{
    ty=val;
    szescian(100,200,img);
}

void MyWindow::slotPozZ(int val)
{
    tz=val;
    szescian(100,200,img);
}

void MyWindow::slotRozX(int val)
{
    sx=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotRozY(int val)
{
    sy=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotRozZ(int val)
{
    sz=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotRotX(int val)
{
    alfaX=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotRotY(int val)
{
    alfaY=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotRotZ(int val)
{
    alfaZ=(double)val/100;
    szescian(100,200,img);
}

void MyWindow::slotTryb(int state)
{
    tryb1=state;
    szescian(100,200,img);

}











