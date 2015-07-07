/************************************************
*     Mini Porject for cmake test full feature  *
*     Use of cmake, cTest, cPack, Dashboard     *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/
/*!
 *	@file ProgQt/ProgQt.cpp
 *	@date Jul 2015
 */

#include <QApplication>
#include <QPushButton>
 
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QPushButton button("Hello world !");
    button.show();

    return app.exec();
}
