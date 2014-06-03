#include <QtCore/QTimer>

#include "JSEApplication.h"

namespace JSE {

JSEApplication::JSEApplication(int &argc, char **argv)
: QApplication(argc, argv)
{
    QTimer::singleShot(0, this, SIGNAL(start()));
}

}