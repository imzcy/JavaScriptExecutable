#include "JSE.h"

#include "JSEUITextEdit.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUITextEdit::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
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

void JSEUITextEdit::SetEvents(JSEUITextEdit *self, JSEUITextEditImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_change(), selfImpl, textChanged(const QString &));
}

void JSEUITextEdit::Set_left(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    int left = value->Int32Value();

    textEditImpl->move(left, textEditImpl->pos().y());

    info.GetReturnValue().Set(left);
}

void JSEUITextEdit::Get_left(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(textEditImpl->pos().x());
}

void JSEUITextEdit::Set_top(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    int top = value->Int32Value();

    textEditImpl->move(textEditImpl->pos().x(), top);

    info.GetReturnValue().Set(top);
}

void JSEUITextEdit::Get_top(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(textEditImpl->pos().y());
}

void JSEUITextEdit::Set_width(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    int width = value->Int32Value();

    textEditImpl->resize(width, textEditImpl->size().height());
}

void JSEUITextEdit::Get_width(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(textEditImpl->size().width());
}

void JSEUITextEdit::Set_height(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    int height = value->Int32Value();

    textEditImpl->resize(textEditImpl->size().width(), height);
}

void JSEUITextEdit::Get_height(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(textEditImpl->size().height());
}

void JSEUITextEdit::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    bool visible = value->BooleanValue();

    if (visible)
    {
        textEditImpl->show();
    }
    else
    {
        textEditImpl->hide();
    }
}

void JSEUITextEdit::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(textEditImpl->isVisible());
}

void JSEUITextEdit::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    textEditImpl->setText(*String::Utf8Value(value->ToString()));
}

void JSEUITextEdit::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, textEditImpl->toPlainText().toLocal8Bit().constData()));
}

void JSEUITextEdit::Set_disabled(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    textEditImpl->setDisabled(value->BooleanValue());
}

void JSEUITextEdit::Get_disabled(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUITextEditImpl *textEditImpl = GetImpl(info);

    info.GetReturnValue().Set(Boolean::New(isolate, !textEditImpl->isEnabled()));
}

void JSEUITextEdit::On_change(void)
{
    Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "change", 0, nullptr);
}

}}