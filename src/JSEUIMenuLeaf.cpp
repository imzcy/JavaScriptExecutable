#include "JSE.h"

#include "JSEUIWindowImpl.h"

#include "JSEUIMenuLeaf.h"

using namespace v8;

namespace JSE { namespace UI {

JSEUIMenuLeaf::JSEUIMenuLeaf(void)
{
    static class MagicNumberHelper
    {
    public:
        MagicNumberHelper(void *&MagicNumber)
        {
            MagicNumber = this;
        }
    } magicNumberHelper(MagicNumber);
}

void JSEUIMenuLeaf::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "MenuLeaf"));

    JSE_UI_SET_ACCESSOR(tpl, "text", Get_text, Set_text);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
}

void JSEUIMenuLeaf::SetEvents(JSEUIMenuLeaf *self, JSEUIMenuLeafImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_click(), selfImpl, triggered());
}

void JSEUIMenuLeaf::WeakCallback(const WeakCallbackData<Object, JSEUIMenuLeaf> &data)
{
    Isolate *isolate = data.GetIsolate();
    HandleScope scope(isolate);
    JSEUIMenuLeaf *widget = data.GetParameter();
    widget->objThis.ClearWeak();
    widget->objThis.Reset();
    if (widget->pImpl != nullptr)
    {
        // Detach all children
        const QObjectList &children = widget->pImpl->children();
        for (auto iter = children.cbegin(); iter != children.cend(); iter++)
        {
            (*iter)->setParent(nullptr);
        }
        // Delete itself
        widget->pImpl->deleteLater();
    }
    for (auto iter = widget->EventListeners.cbegin(); iter != widget->EventListeners.cend(); iter++)
    {
        for (auto viter = iter->second.cbegin(); viter != iter->second.cend(); viter++)
        {
            (**viter).Reset();
            delete (*viter);
        }
    }
    delete widget;
}

void JSEUIMenuLeaf::Initialize(const Handle<v8::Object> &objExport, const char *name)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, New);
    tpl->InstanceTemplate()->SetInternalFieldCount(2);

    JSE_SET_PROTOTYPE_METHOD(tpl, "appendTo", Proto_appendTo);
    JSE_SET_PROTOTYPE_METHOD(tpl, "addEventListener", Proto_addEventListener);
    JSEUIMenuLeaf::SetMethods(isolate, tpl);

    objExport->Set(v8::String::NewFromUtf8(isolate, name), tpl->GetFunction());
}

JSEUIMenuLeafImpl *JSEUIMenuLeaf::GetImpl(void)
{
    return pImpl;
}

void *JSEUIMenuLeaf::MagicNumber = nullptr;

void JSEUIMenuLeaf::New(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    if (args.IsConstructCall())
    {
        JSEUIMenuLeaf *widget = new JSEUIMenuLeaf();
        JSEUIMenuLeafImpl *widgetImpl = new JSEUIMenuLeafImpl();

        JSEUIMenuLeaf::SetEvents(widget, widgetImpl);

        widget->pImpl = widgetImpl;

        v8::Handle<v8::Object> objThis = args.This();
        objThis->SetAlignedPointerInInternalField(0, widget);
        objThis->SetAlignedPointerInInternalField(1, MagicNumber);
        widget->objThis.Reset(isolate, objThis);
        widget->objThis.SetWeak(widget, WeakCallback);
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        args.GetReturnValue().Set(v8::Exception::SyntaxError(v8::String::NewFromUtf8(isolate, "Window must be called as a constructor.")));
    }
}

void JSEUIMenuLeaf::Invoke(JSEUIMenuLeaf *self, std::string evt, int argc, Handle<Value> *argv)
{
    if (self->EventListeners.count(evt) == 0)
    {
        return;
    }
    for (auto iter = self->EventListeners[evt].cbegin(); iter != self->EventListeners[evt].cend(); iter++)
    {
        Local<Function>::New(Isolate::GetCurrent(), **iter)->Call(Local<Object>::New(Isolate::GetCurrent(), self->objThis), argc, argv);
    }
}

JSEUIMenuLeaf *JSEUIMenuLeaf::GetInternal(Local<Object> &obj)
{
    if (obj->InternalFieldCount() != 2)
    {
        return nullptr;
    }
    if (obj->GetAlignedPointerFromInternalField(1) != MagicNumber)
    {
        return nullptr;
    }

    return static_cast<JSEUIMenuLeaf *>(obj->GetAlignedPointerFromInternalField(0));
}

template <typename T>
JSEUIMenuLeafImpl *JSEUIMenuLeaf::GetImpl(T &info)
{
    return static_cast<JSEUIMenuLeaf *>(info.This()->GetAlignedPointerFromInternalField(0))->pImpl;
}

void JSEUIMenuLeaf::Proto_appendTo(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeaf *widget = static_cast<JSEUIMenuLeaf *>(args.This()->GetAlignedPointerFromInternalField(0));

    if (args.Length() == 0)
    {
        widget->pImpl->setParent(nullptr);
        args.GetReturnValue().Set(Boolean::New(isolate, true));
        return;
    }

    if (args.Length() > 1)
    {
        args.GetReturnValue().Set(Exception::Error(String::NewFromUtf8(isolate, "There is one optional parameter.")));
        return;
    }

    Local<Object> objParent = args[0]->ToObject();

    JSEUIBase *parent = JSEUIBase::GetInternal(objParent);

    if (parent == nullptr)
    {
        args.GetReturnValue().Set(Exception::Error(String::NewFromUtf8(isolate, "Invalid parent object.")));
        return;
    }

    widget->objParent.Reset(isolate, objParent);

    // Special case: JSEUIWindow, need to append to centralWidget()

    JSEUIWindowImpl *parentWindow = dynamic_cast<JSEUIWindowImpl *>(parent->GetImpl());
    if (parentWindow != nullptr)
    {
        widget->pImpl->setParent(parentWindow->centralWidget());
    }
    else
    {
        widget->pImpl->setParent(parent->GetImpl());
    }

    args.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIMenuLeaf::Proto_addEventListener(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeaf *widget = static_cast<JSEUIMenuLeaf *>(args.This()->GetAlignedPointerFromInternalField(0));

    if (args.Length() != 2)
    {
        args.GetReturnValue().Set(Exception::Error(String::NewFromUtf8(isolate, "There must be exact two parameters.")));
        return;
    }

    if (args[0]->IsString() == false)
    {
        args.GetReturnValue().Set(Exception::TypeError(String::NewFromUtf8(isolate, "Argument 1 must be a string.")));
        return;
    }

    if (args[1]->IsFunction() == false)
    {
        args.GetReturnValue().Set(Exception::TypeError(String::NewFromUtf8(isolate, "Argument 2 must be a function.")));
        return;
    }

    Persistent<Function> *callback = new Persistent<Function>;
    callback->Reset(isolate, Local<Function>::Cast(args[1]));
    if (widget->EventListeners.count(*String::Utf8Value(args[0]->ToString())) == 0)
    {
        // Create new listener vector
        std::vector<Persistent<Function> *> listeners;
        listeners.push_back(callback);
        widget->EventListeners[*String::Utf8Value(args[0]->ToString())] = listeners;
    }
    else
    {
        // Push to existing listener vector
        widget->EventListeners[*String::Utf8Value(args[0]->ToString())].push_back(callback);
    }

    args.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIMenuLeaf::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeafImpl *menuLeafImpl = GetImpl(info);

    menuLeafImpl->setText(*String::Utf8Value(value->ToString()));
}

void JSEUIMenuLeaf::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeafImpl *menuLeafImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, menuLeafImpl->text().toLocal8Bit().constData()));
}

void JSEUIMenuLeaf::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeafImpl *menuLeafImpl = GetImpl(info);

    menuLeafImpl->setVisible(value->BooleanValue());
}

void JSEUIMenuLeaf::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuLeafImpl *menuLeafImpl = GetImpl(info);

    info.GetReturnValue().Set(Boolean::New(isolate, menuLeafImpl->isVisible()));
}

void JSEUIMenuLeaf::On_click(void)
{
    Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "click", 0, nullptr);
}

}}