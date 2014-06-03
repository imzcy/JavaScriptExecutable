#ifndef _JSEV8_H_
#define _JSEV8_H_

#include <QtCore/QObject>
#include <v8.h>

#include "JSEApplication.h"

namespace JSE {

class JSEV8 : public QObject
{

    Q_OBJECT

public:
    JSEV8(JSEApplication &app);
    ~JSEV8();

    void exit(void);

public slots:
    void start(void);

private:
    v8::Isolate *isolate;
    JSEApplication *app;
};

}


#endif // _JSEV8_H_