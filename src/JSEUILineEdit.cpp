#include "JSE.h"

#include "JSEUILineEdit.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUILineEdit::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "LineEdit"));
    
    JSE_UI_SET_ACCESSOR(tpl, "left", Get_left, Set_left);
    JSE_UI_SET_ACCESSOR(tpl, "top", Get_top, Set_top);
    JSE_UI_SET_ACCESSOR(tpl, "width", Get_width, Set_width);
    JSE_UI_SET_ACCESSOR(tpl, "height", Get_height, Set_height);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
    JSE_UI_SET_ACCESSOR(tpl, "text", Get_text, Set_text);
    JSE_UI_SET_ACCESSOR(tpl, "disabled", Get_disabled, Set_disabled);
}

void JSEUILineEdit::SetEvents(JSEUILineEdit *self, JSEUILineEditImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_change(), selfImpl, textChanged(const QString &));
}

void JSEUILineEdit::Set_left(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    int left = value->Int32Value();

    lineEditImpl->move(left, lineEditImpl->pos().y());

    info.GetReturnValue().Set(left);
}

void JSEUILineEdit::Get_left(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(lineEditImpl->pos().x());
}

void JSEUILineEdit::Set_top(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    int top = value->Int32Value();

    lineEditImpl->move(lineEditImpl->pos().x(), top);

    info.GetReturnValue().Set(top);
}

void JSEUILineEdit::Get_top(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(lineEditImpl->pos().y());
}

void JSEUILineEdit::Set_width(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    int width = value->Int32Value();

    lineEditImpl->resize(width, lineEditImpl->size().height());
}

void JSEUILineEdit::Get_width(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(lineEditImpl->size().width());
}

void JSEUILineEdit::Set_height(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    int height = value->Int32Value();

    lineEditImpl->resize(lineEditImpl->size().width(), height);
}

void JSEUILineEdit::Get_height(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(lineEditImpl->size().height());
}

void JSEUILineEdit::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    bool visible = value->BooleanValue();

    if (visible)
    {
        lineEditImpl->show();
    }
    else
    {
        lineEditImpl->hide();
    }
}

void JSEUILineEdit::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(lineEditImpl->isVisible());
}

void JSEUILineEdit::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    lineEditImpl->setText(*String::Utf8Value(value->ToString()));
}

void JSEUILineEdit::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, lineEditImpl->text().toLocal8Bit().constData()));
}

void JSEUILineEdit::Set_disabled(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    lineEditImpl->setDisabled(value->BooleanValue());
}

void JSEUILineEdit::Get_disabled(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILineEditImpl *lineEditImpl = GetImpl(info);

    info.GetReturnValue().Set(Boolean::New(isolate, !lineEditImpl->isEnabled()));
}

void JSEUILineEdit::On_change(void)
{
    Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "change", 0, nullptr);
}

}}