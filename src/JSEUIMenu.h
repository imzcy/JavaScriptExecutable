#ifndef _JSEUIMENU_H_
#define _JSEUIMENU_H_

#include "JSEUITpl.h"
#include "JSEUIMenuImpl.h"

namespace JSE { namespace UI {

class JSEUIMenu : public JSEUITpl<JSEUIMenu, JSEUIMenuImpl> {

    Q_OBJECT

public:
    static void SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void SetEvents(JSEUIMenu *self, JSEUIMenuImpl *selfImpl);

private:
    static void Proto_addMenu(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_removeMenu(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Set_text(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_text(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_visible(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_visible(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);

public slots:
    void On_click(void);

};

}}

#endif // _JSEUIMENU_H_