#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "v8_base.lib")
#pragma comment(lib, "v8_snapshot.lib")
#pragma comment(lib, "v8_nosnapshot.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")
#endif

#include "JSE.h"
#include "JSEApplication.h"
#include "JSEV8.h"

using namespace JSE;

int main(int argc, char *argv[])
{
    JSEApplication app(argc, argv);

    JSEV8 v8app(app);

    QObject::connect(&app, SIGNAL(start()), &v8app, SLOT(start()));

    return app.exec();
}