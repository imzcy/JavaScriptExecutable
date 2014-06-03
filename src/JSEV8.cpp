#include "JSE.h"

#include <fstream>
#include <QtWidgets/QMessageBox>

#include "JSEProcess.h"

#include "JSEUIWindow.h"
#include "JSEUIButton.h"
#include "JSEUILabel.h"
#include "JSEUILineEdit.h"
#include "JSEUIMenu.h"
#include "JSEUIMenuLeaf.h"

#include "JSEV8.h"

using namespace v8;
using namespace JSE::UI;

namespace JSE {

JSEV8::JSEV8(JSEApplication &app)
{
    isolate = Isolate::GetCurrent();
    V8::Initialize();

    this->app = &app;
}

JSEV8::~JSEV8()
{
}

void JSEV8::exit(void)
{
    V8::TerminateExecution();
}

void JSEV8::start(void)
{
    V8::Initialize();

    Locker locker(isolate);
    HandleScope handle_scope(isolate);

    Local<Context> context = Context::New(isolate);
    Context::Scope context_scope(context);

    auto argv = app->arguments();
    /*
    if (argv.length() != 2)
    {
        QMessageBox::critical(nullptr, "Fatal Error", "No input file specified.", QMessageBox::Ok);
        app->exit(-1);
        return;
    }
    */
    //std::ifstream ifs(argv[1].toLocal8Bit().constData(), std::ios::in | std::ios::binary);
    std::ifstream ifs("C:\\Users\\zcy\\Desktop\\jsx\\JavaScriptExecutable\\x64\\Debug\\app.js", std::ios::in | std::ios::binary);

    if (!ifs.good())
    {
        QMessageBox::critical(nullptr, "Fatal Error", "Cannot open input file.", QMessageBox::Ok);
        app->exit(-2);
        return;
    }

    std::string content;
    ifs.seekg(0, std::ios::end);
    content.resize(ifs.tellg());
    ifs.seekg(0);
    ifs.read(&content[0], content.size());
    ifs.close();

    // Setup global objects
    Handle<Object> objGlobal = context->Global();

    // Setup process
    Persistent<Object> objProcess;
    SetupProcessObject(app, this, objProcess, isolate);
    objGlobal->Set(String::NewFromUtf8(isolate, "process"), Local<Object>::New(isolate, objProcess));

    // Setup common controls
    JSEUIWindow::Initialize(objGlobal, "Window");
    JSEUIButton::Initialize(objGlobal, "Button");
    JSEUILabel::Initialize(objGlobal, "Label");
    JSEUILineEdit::Initialize(objGlobal, "LineEdit");
    JSEUIMenu::Initialize(objGlobal, "Menu");
    JSEUIMenuLeaf::Initialize(objGlobal, "MenuLeaf");
    
    TryCatch try_catch;

    Local<String> source = String::NewFromUtf8(isolate, content.c_str());

    Local<Script> script = Script::Compile(source, String::NewFromUtf8(isolate, "app.js"));

    script->Run();

    if (try_catch.HasCaught())
    {
        QMessageBox::critical(nullptr, "Runtime Error", (std::string() + "Line " + std::to_string(try_catch.Message()->GetLineNumber()) + ", column " + std::to_string(try_catch.Message()->GetStartColumn()) + ":\n" + *String::Utf8Value(try_catch.Message()->Get()) + ".").c_str(), QMessageBox::Ok);
        app->exit(-3);
        return;
    }
}

}