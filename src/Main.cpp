#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "D3d9.lib")
#pragma comment(lib, "dxguid.lib")
#include <d3d9.h>
#include <QtCore/qplugin.h>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#ifdef _DEBUG
#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")
#pragma comment(lib, "v8_based.lib")
#pragma comment(lib, "v8_snapshotd.lib")
#pragma comment(lib, "v8_nosnapshotd.lib")
#pragma comment(lib, "libEGLd.lib")
#pragma comment(lib, "libGLESv2d.lib")
#pragma comment(lib, "preprocessord.lib")
#pragma comment(lib, "translatord.lib")
#pragma comment(lib, "Qt5PlatformSupportd.lib")
#pragma comment(lib, "platforms/qwindowsd.lib")
#else
#pragma comment(lib, "v8_base.lib")
#pragma comment(lib, "v8_snapshot.lib")
#pragma comment(lib, "v8_nosnapshot.lib")
#pragma comment(lib, "Qt5Core.lib")
#pragma comment(lib, "Qt5Gui.lib")
#pragma comment(lib, "Qt5Widgets.lib")
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#pragma comment(lib, "preprocessor.lib")
#pragma comment(lib, "translator.lib")
#pragma comment(lib, "Qt5PlatformSupport.lib")
#pragma comment(lib, "platforms/qwindows.lib")
#endif // DEBUG
#endif // _MSC_VER

#include "JSE.h"
#include "JSEApplication.h"
#include "JSEV8.h"

using namespace JSE;

int main(int argc, char *argv[])
{
    JSEApplication app(argc, argv);
    ::app = &app;

    JSEV8 v8app(app);

    QObject::connect(&app, SIGNAL(start()), &v8app, SLOT(start()));

    return app.exec();
}