#include "JSE.h"

#include "JSEUILabel.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUILabel::SetMethods(Isolate *&isolate, Handle<FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "Label"));
    
    JSE_UI_SET_ACCESSOR(tpl, "left", Get_left, Set_left);
    JSE_UI_SET_ACCESSOR(tpl, "top", Get_top, Set_top);
    JSE_UI_SET_ACCESSOR(tpl, "width", Get_width, Set_width);
    JSE_UI_SET_ACCESSOR(tpl, "height", Get_height, Set_height);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
    JSE_UI_SET_ACCESSOR(tpl, "text", Get_text, Set_text);
}

void JSEUILabel::SetEvents(JSEUILabel *self, JSEUILabelImpl *selfImpl)
{
    //JSE_UI_SET_EVENTS(self, On_click(), selfImpl, clicked());
    connect(selfImpl, SIGNAL(clicked()), self, SLOT(On_click()));
}

void JSEUILabel::Set_left(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    int left = value->Int32Value();

    labelImpl->move(left, labelImpl->pos().y());

    info.GetReturnValue().Set(left);
}

void JSEUILabel::Get_left(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(labelImpl->pos().x());
}

void JSEUILabel::Set_top(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    int top = value->Int32Value();

    labelImpl->move(labelImpl->pos().x(), top);

    info.GetReturnValue().Set(top);
}

void JSEUILabel::Get_top(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(labelImpl->pos().y());
}

void JSEUILabel::Set_width(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    int width = value->Int32Value();

    labelImpl->resize(width, labelImpl->size().height());
}

void JSEUILabel::Get_width(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(labelImpl->size().width());
}

void JSEUILabel::Set_height(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    int height = value->Int32Value();

    labelImpl->resize(labelImpl->size().width(), height);
}

void JSEUILabel::Get_height(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(labelImpl->size().height());
}

void JSEUILabel::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    bool visible = value->BooleanValue();

    if (visible)
    {
        labelImpl->show();
    }
    else
    {
        labelImpl->hide();
    }
}

void JSEUILabel::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(labelImpl->isVisible());
}

void JSEUILabel::Set_text(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    labelImpl->setText(*String::Utf8Value(value->ToString()));
}

void JSEUILabel::Get_text(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUILabelImpl *labelImpl = GetImpl(info);

    info.GetReturnValue().Set(String::NewFromUtf8(isolate, labelImpl->text().toLocal8Bit().constData()));
}

}}