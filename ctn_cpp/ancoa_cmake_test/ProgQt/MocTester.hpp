#ifndef MocTester_hpp
#define MocTester_hpp


#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QCheckBox;

/** \class MocTester
 *
 *  \brief
 *
 */
class MocTester : public QWidget
{
    Q_OBJECT
public:

    // MocTester 
    MocTester();
    ~MocTester();
    
signals:
    void aSignal();
};

#endif // MocTester_hpp
