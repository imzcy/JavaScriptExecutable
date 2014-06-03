#ifndef _JSEUIMENULEAF_H_
#define _JSEUIMENULEAF_H_

#include <map>
#include <vector>
#include <string>

#include <v8.h>

#include "JSEUIBase.h"

#include "JSEUIMenuLeafImpl.h"

namespace JSE { namespace UI {

class JSEUIMenuLeaf : public QObject {

    Q_OBJECT

public:
    JSEUIMenuLeaf(void);
    static void SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl);
    static void SetEvents(JSEUIMenuLeaf *self, JSEUIMenuLeafImpl *selfImpl);
    static void WeakCallback(const v8::WeakCallbackData<v8::Object, JSEUIMenuLeaf> &data);
    static void Initialize(const v8::Handle<v8::Object> &objExport, const char *name);
    static JSEUIMenuLeaf *GetInternal(v8::Local<v8::Object> &obj);
    JSEUIMenuLeafImpl *GetImpl(void);

protected:
    static void *MagicNumber;
    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Invoke(JSEUIMenuLeaf *self, std::string evt, int argc, v8::Handle<v8::Value> *argv);
    template <typename T>
    static JSEUIMenuLeafImpl *GetImpl(T &info);

private:
    static void Proto_appendTo(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Proto_addEventListener(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Set_text(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_text(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void Set_visible(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
    static void Get_visible(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value> &info);

    std::map <std::string, std::vector<v8::Persistent<v8::Function> *>> EventListeners;
    JSEUIMenuLeafImpl *pImpl;
    v8::Persistent<v8::Object> objParent;
    v8::Persistent<v8::Object> objThis;

public slots:
    void On_click(void);

};

}}

#endif // _JSEUIMENULEAF_H_