#ifndef _JSEPROCESS_H_
#define _JSEPROCESS_H_

#include <v8.h>
#include <QtCore/QStringList>

#include "JSEApplication.h"
#include "JSEV8.h"

namespace JSE {

    void SetupProcessObject(JSEApplication *app, JSEV8 *v8app, v8::Persistent<v8::Object> &process, v8::Isolate *isolate);

}

#endif