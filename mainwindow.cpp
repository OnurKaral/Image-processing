#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered(void){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

    im1.load( fileName );

    //im1 = im1.convertToFormat(QImage::Format_Grayscale8);
    //im1.invertPixels( QImage::InvertRgb );

    pix1 = QPixmap::fromImage( im1 );
    sahne1.addPixmap( pix1 );

    ui->graphicsView->setScene( &sahne1 );
}

void MainWindow::on_pushButton_clicked()
{

    Mat src1, src_gray;
    src1 = conv.QImage2Mat( im1 );
    cvtColor(src1, src_gray, COLOR_BGR2GRAY);
      GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
       std::vector<Vec3f> circles;
       int maxtrehhold = ui->verticalSlider->value();

       HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/maxtrehhold, 200, 100, 0, 0 );

       for( size_t i = 0; i < circles.size(); i++ )
         {
             Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
             int radius = cvRound(circles[i][2]);
             // circle center
             circle( src1, center, 3, Scalar(0,255,0), -1, 8, 0 );
             // circle outline
             circle( src1, center, radius, Scalar(0,0,255), 3, 8, 0 );
          }


   im2 = conv.Mat2QImage(src1);
    pix2 = QPixmap::fromImage(im2);
    sahne2.addPixmap( pix2 );

    ui->graphicsView_2->setScene( &sahne2 );


}

void MainWindow::on_pushButton_2_clicked()
{
    Mat src1;
    Mat  dst1,cdst;
    src1 = conv.QImage2Mat( im1 );
    Canny(src1, dst1, 50, 200, 3);
     cvtColor(dst1, cdst, CV_GRAY2BGR);
    int lineslider = ui->verticalSlider->value();


  std::vector<Vec4i> lines;
  HoughLinesP(dst1, lines, 1, CV_PI/lineslider, 100, 0, 0 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }


      im2 = conv.Mat2QImage(cdst);
       pix2 = QPixmap::fromImage(im2);
       sahne2.addPixmap( pix2 );

       ui->graphicsView_2->setScene( &sahne2 );

}
void MainWindow::on_verticalSlider_valueChanged(int value)
{

}
