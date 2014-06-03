#ifndef _JSEUIBASE_H_
#define _JSEUIBASE_H_

#include "JSE.h"

#include <map>
#include <vector>
#include <string>

#include <QtWidgets/QWidget>
#include <v8.h>

#include "JSEUIWindowImpl.h"

namespace JSE { namespace UI {

class JSEUIBase : public QWidget
{
public:
    JSEUIBase(void);
    static void WeakCallback(const v8::WeakCallbackData<v8::Object, JSEUIBase> &data);
    JSEUIBase *GetImpl(void);
    static JSEUIBase *GetInternal(v8::Local<v8::Object> &obj);

protected:
    static void *MagicNumber;
    static void Initialize(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void Invoke(JSEUIBase *self, std::string evt, int argc, v8::Handle<v8::Value> *argv);
    
private:
    static void Proto_appendTo(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_addEventListener(const v8::FunctionCallbackInfo<v8::Value> &args);

protected:
    std::map <std::string, std::vector<v8::Persistent<v8::Function> *>> EventListeners;
    QWidget *pImpl;
    v8::Persistent<v8::Object> objParent;
    v8::Persistent<v8::Object> objThis;
};

}}

#endif // _JSEUIBASE_H_