#ifndef _JSEUITPL_H_
#define _JSEUITPL_H_

#include "JSEUIBase.h"

namespace JSE { namespace UI {

template <typename Widget, typename WidgetImpl>
class JSEUITpl : public JSEUIBase
{
public:
    static void Initialize(const v8::Handle<v8::Object> &objExport, const char *name)
    {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);

        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, New);
        tpl->InstanceTemplate()->SetInternalFieldCount(2);

        JSEUIBase::Initialize(isolate, tpl);
        Widget::SetMethods(isolate, tpl);

        objExport->Set(v8::String::NewFromUtf8(isolate, name), tpl->GetFunction());
    }
    WidgetImpl *GetImpl(void)
    {
        return dynamic_cast<WidgetImpl *>(this->pImpl);
    }

protected:
    static void New(const v8::FunctionCallbackInfo<v8::Value> &args)
    {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);

        if (args.IsConstructCall())
        {
            Widget *widget = new Widget();
            WidgetImpl *widgetImpl = new WidgetImpl();
            
            Widget::SetEvents(widget, widgetImpl);

            widget->pImpl = widgetImpl;

            v8::Handle<v8::Object> objThis = args.This();
            objThis->SetAlignedPointerInInternalField(0, widget);
            objThis->SetAlignedPointerInInternalField(1, reinterpret_cast<void *>(MagicNumber));
            widget->objThis.Reset(isolate, objThis);
            widget->objThis.SetWeak(static_cast<JSEUIBase *>(widget), WeakCallback);
            args.GetReturnValue().Set(args.This());
        }
        else
        {
            args.GetReturnValue().Set(v8::Exception::SyntaxError(v8::String::NewFromUtf8(isolate, "Window must be called as a constructor.")));
        }
    }
    template <typename T>
    static Widget *GetInternal(T &info)
    {
        return static_cast<Widget *>(info.This()->GetAlignedPointerFromInternalField(0));
    }
    template <typename T>
    static WidgetImpl *GetImpl(T &info)
    {
        return static_cast<Widget *>(info.This()->GetAlignedPointerFromInternalField(0))->GetImpl();
    }

};

}}

#endif // _JSEUITPL_H_