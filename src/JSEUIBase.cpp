#include "JSEUIBase.h"

using namespace v8;

namespace JSE { namespace UI {

JSEUIBase::JSEUIBase(void)
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
    
void JSEUIBase::WeakCallback(const WeakCallbackData<Object, JSEUIBase> &data)
{
    Isolate *isolate = data.GetIsolate();
    HandleScope scope(isolate);
    JSEUIBase *widget = data.GetParameter();
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

JSEUIBase *JSEUIBase::GetImpl(void)
{
    return static_cast<JSEUIBase *>(pImpl);
}

void JSEUIBase::Initialize(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    JSE_SET_PROTOTYPE_METHOD(tpl, "appendTo", Proto_appendTo);
    JSE_SET_PROTOTYPE_METHOD(tpl, "addEventListener", Proto_addEventListener);
}

void JSEUIBase::Invoke(JSEUIBase *self, std::string evt, int argc, Handle<Value> *argv)
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

JSEUIBase *JSEUIBase::GetInternal(Local<Object> &obj)
{
    if (obj->InternalFieldCount() != 2)
    {
        return nullptr;
    }
    if (obj->GetAlignedPointerFromInternalField(1) != MagicNumber)
    {
        return nullptr;
    }

    return static_cast<JSEUIBase *>(obj->GetAlignedPointerFromInternalField(0));
}

void *JSEUIBase::MagicNumber = nullptr;
    
void JSEUIBase::Proto_appendTo(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIBase *widget = static_cast<JSEUIBase *>(args.This()->GetAlignedPointerFromInternalField(0));

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

    JSEUIBase *parent = GetInternal(objParent);

    if (parent == nullptr)
    {
        args.GetReturnValue().Set(Exception::Error(String::NewFromUtf8(isolate, "Invalid parent object.")));
        return;
    }

    widget->objParent.Reset(isolate, objParent);

    // Special case: JSEUIWindow, need to append to centralWidget()

    JSEUIWindowImpl *parentWindow = dynamic_cast<JSEUIWindowImpl *>(parent->pImpl);
    if (parentWindow != nullptr)
    {
        widget->pImpl->setParent(parentWindow->centralWidget());
    }
    else
    {
        widget->pImpl->setParent(parent->pImpl);
    }

    widget->pImpl->setVisible(true);
        
    args.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIBase::Proto_addEventListener(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIBase *widget = static_cast<JSEUIBase *>(args.This()->GetAlignedPointerFromInternalField(0));

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

}}