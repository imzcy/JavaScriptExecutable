#ifndef _JSEUIWINDOW_H_
#define _JSEUIWINDOW_H_

#include "JSEUITpl.h"
#include "JSEUIWindowImpl.h"

namespace JSE { namespace UI {

class JSEUIWindow : public JSEUITpl<JSEUIWindow, JSEUIWindowImpl>
{

    Q_OBJECT

public:
    static void SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void SetEvents(JSEUIWindow *self, JSEUIWindowImpl *selfImpl);

private:
    static void Proto_maximize(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_minimize(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_alert(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_addMenu(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Set_width(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_width(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_height(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_height(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_visible(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_visible(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_title(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_title(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_maximizeButton(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_maximizeButton(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_minimizeButton(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_minimizeButton(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_minimumWidth(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_minimumWidth(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_minimumHeight(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_minimumHeight(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_maximumWidth(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_maximumWidth(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_maximumHeight(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_maximumHeight(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);

public slots:
    void On_resize(void);
};

}}

#endif // _JSEUIWINDOW_H_