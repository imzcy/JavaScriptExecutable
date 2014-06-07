#include "JSE.h"

#include "JSEProcess.h"

using namespace v8;

namespace JSE {

QApplication *_JSEProcess_app;
JSEV8 *_JSEProcess_v8app;

void FuncQuit(const FunctionCallbackInfo<Value> &args)
{
    _JSEProcess_v8app->exit();
    _JSEProcess_app->exit();
}

void SetupProcessObject(JSEApplication *app, JSEV8 *v8app, Persistent<Object> &process, Isolate *isolate)
{
    QStringList argv = app->arguments();

    HandleScope scope(isolate);

    Local<FunctionTemplate> process_template = FunctionTemplate::New(isolate);
    process_template->SetClassName(String::NewFromUtf8(isolate, "process"));

    Local<Object> objProcess = process_template->GetFunction()->NewInstance();

    Local<Object> objArgv = Array::New(isolate, argv.size());
    for (int i = 0; i < argv.size(); i++)
    {
        objArgv->Set(i, String::NewFromUtf8(isolate, argv[i].toUtf8().constData()));
    }
    objProcess->Set(String::NewFromUtf8(isolate, "argv"), objArgv);

    _JSEProcess_app = app;
    _JSEProcess_v8app = v8app;

    JSE_SET_METHOD(objProcess, "quit", FuncQuit);

    process.Reset(isolate, objProcess);
}

}