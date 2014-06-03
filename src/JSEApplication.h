#ifndef _JSEAPPLICATION_H_
#define _JSEAPPLICATION_H_

#include <QtWidgets/QApplication>

namespace JSE {

class JSEApplication : public QApplication
{

    Q_OBJECT

public:
    JSEApplication(int &argc, char **argv);

signals:
    void start(void);
};

}

#endif // _JSEAPPLICATION_H_