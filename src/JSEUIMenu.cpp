#include "JSE.h"

#include "JSEUIMenuLeaf.h"

#include "JSEUIMenu.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUIMenu::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "Menu"));

    JSE_SET_PROTOTYPE_METHOD(tpl, "addMenu", Proto_addMenu);

    JSE_UI_SET_ACCESSOR(tpl, "text", Get_text, Set_text);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
}

void JSEUIMenu::SetEvents(JSEUIMenu *self, JSEUIMenuImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_click(), selfImpl, aboutToShow());
}

void JSEUIMenu::Proto_addMenu(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    if (info.Length() < 1)
    {
        Exception::Error(String::NewFromUtf8(isolate, "Child menu not specified."));
        return;
    }
    
    Local<Object> objChild = info[0]->ToObject();

    // Check if it is MenuLeaf
    JSEUIMenuLeaf *childLeaf;
    if (nullptr != (childLeaf = JSEUIMenuLeaf::GetInternal(objChild)))
    {
        menuImpl->addAction(childLeaf->GetImpl());
        info.GetReturnValue().Set(Boolean::New(isolate, true));
        return;
    }

    QWidget *child = JSEUIBase::GetInternal(objChild);

    if (child == nullptr)
    {
        Exception::Error(String::NewFromUtf8(isolate, "Invalid UI object."));
        return;
    }

    JSEUIMenu *childMenu = dynamic_cast<JSEUIMenu *>(child);

    if (childMenu == nullptr)
    {
        Exception::Error(String::NewFromUtf8(isolate, "UI object is not a menu."));
        return;
    }

    menuImpl->addMenu(dynamic_cast<JSEUIMenuImpl *>(childMenu->pImpl));

    info.GetReturnValue().Set(Boolean::New(isolate, true));
    return;
}

void JSEUIMenu::Proto_removeMenu(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    if (info.Length() < 1)
    {
        Exception::Error(String::NewFromUtf8(isolate, "Child menu not specified."));
        return;
    }

    Local<Object> objChild = info[0]->ToObject();

    QWidget *child = JSEUIBase::GetInternal(objChild);

    if (child == nullptr)
    {
        Exception::Error(String::NewFromUtf8(isolate, "Invalid UI object."));
        return;
    }

    JSEUIMenu *childMenu = dynamic_cast<JSEUIMenu *>(child);

    if (childMenu == nullptr)
    {
        Exception::Error(String::NewFromUtf8(isolate, "UI object is not a menu."));
        return;
    }

    menuImpl->removeAction(dynamic_cast<JSEUIMenuImpl *>(childMenu->pImpl)->menuAction());

    info.GetReturnValue().Set(Boolean::New(isolate, true));
    return;
}

void JSEUIMenu::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    menuImpl->setTitle(*String::Utf8Value(value->ToString()));
}

void JSEUIMenu::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, menuImpl->title().toLocal8Bit().constData()));
}

void JSEUIMenu::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    menuImpl->setVisible(value->BooleanValue());
}

void JSEUIMenu::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIMenuImpl *menuImpl = GetImpl(info);

    info.GetReturnValue().Set(Boolean::New(isolate, menuImpl->isVisible()));
}

void JSEUIMenu::On_click(void)
{
    Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "click", 0, nullptr);
}

}}