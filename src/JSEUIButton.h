#ifndef _JSEUIBUTTON_H_
#define _JSEUIBUTTON_H_

#include "JSEUITpl.h"
#include "JSEUIButtonImpl.h"

namespace JSE { namespace UI {

class JSEUIButton : public JSEUITpl<JSEUIButton, JSEUIButtonImpl>
{

    Q_OBJECT

public:
    static void SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void SetEvents(JSEUIButton *self, JSEUIButtonImpl *selfImpl);

private:
    static void Proto_click(const v8::FunctionCallbackInfo<v8::Value> &args);
    
    static void Set_left(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_left(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_top(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_top(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_width(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_width(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_height(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_height(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_visible(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_visible(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_text(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_text(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);

public slots:
    void On_click(void);

};

}}

#endif // _JSEUIBUTTON_H_