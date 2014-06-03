#ifndef _JSEUILINEEDIT_H_
#define _JSEUILINEEDIT_H_

#include "JSEUITpl.h"
#include "JSEUILineEditImpl.h"

namespace JSE { namespace UI {

class JSEUILineEdit : public JSEUITpl<JSEUILineEdit, JSEUILineEditImpl>
{

    Q_OBJECT

public:
    static void SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void SetEvents(JSEUILineEdit *self, JSEUILineEditImpl *selfImpl);

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
    static void Set_disabled(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_disabled(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);

public slots:
    void On_change(void);
};

}}

#endif // _JSEUILINEEDIT_H_