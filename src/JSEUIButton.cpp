#include "JSE.h"

#include "JSEUIButton.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUIButton::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "Button"));

    JSE_SET_PROTOTYPE_METHOD(tpl, "click", Proto_click);
    
    JSE_UI_SET_ACCESSOR(tpl, "left", Get_left, Set_left);
    JSE_UI_SET_ACCESSOR(tpl, "top", Get_top, Set_top);
    JSE_UI_SET_ACCESSOR(tpl, "width", Get_width, Set_width);
    JSE_UI_SET_ACCESSOR(tpl, "height", Get_height, Set_height);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
    JSE_UI_SET_ACCESSOR(tpl, "text", Get_text, Set_text);
}

void JSEUIButton::SetEvents(JSEUIButton *self, JSEUIButtonImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_click(), selfImpl, clicked());
}

void JSEUIButton::Proto_click(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    buttonImpl->Click();

    info.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIButton::Set_left(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    int left = value->Int32Value();

    buttonImpl->move(left, buttonImpl->pos().y());

    info.GetReturnValue().Set(left);
}

void JSEUIButton::Get_left(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(Integer::New(isolate, buttonImpl->pos().x()));
}

void JSEUIButton::Set_top(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    int top = value->Int32Value();

    buttonImpl->move(buttonImpl->pos().x(), top);

    info.GetReturnValue().Set(top);
}

void JSEUIButton::Get_top(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(Integer::New(isolate, buttonImpl->pos().y()));
}

void JSEUIButton::Set_width(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    int width = value->Int32Value();

    buttonImpl->resize(width, buttonImpl->size().height());
}

void JSEUIButton::Get_width(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(Integer::New(isolate, buttonImpl->size().width()));
}

void JSEUIButton::Set_height(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    int height = value->Int32Value();

    buttonImpl->resize(buttonImpl->size().width(), height);
}

void JSEUIButton::Get_height(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(Integer::New(isolate, buttonImpl->size().height()));
}

void JSEUIButton::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    bool visible = value->BooleanValue();

    if (visible)
    {
        buttonImpl->show();
    }
    else
    {
        buttonImpl->hide();
    }
}

void JSEUIButton::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(Boolean::New(isolate, buttonImpl->isVisible()));
}

void JSEUIButton::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    buttonImpl->setText(*String::Utf8Value(value->ToString()));
}

void JSEUIButton::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIButtonImpl *buttonImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, buttonImpl->text().toLocal8Bit().constData()));
}

void JSEUIButton::On_click(void)
{
    v8::Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "click", 0, nullptr);
}

}}