#include "JSE.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLayout>

#include "JSEUIMenu.h"
#include "JSEUIWindow.h"

using namespace v8;

namespace JSE { namespace UI {

void JSEUIWindow::SetMethods(v8::Isolate *&isolate, v8::Handle<v8::FunctionTemplate> &tpl)
{
    tpl->SetClassName(String::NewFromUtf8(isolate, "Window"));

    JSE_SET_PROTOTYPE_METHOD(tpl, "maximize", Proto_maximize);
    JSE_SET_PROTOTYPE_METHOD(tpl, "minimize", Proto_minimize);
    JSE_SET_PROTOTYPE_METHOD(tpl, "alert", Proto_alert);
    JSE_SET_PROTOTYPE_METHOD(tpl, "addMenu", Proto_addMenu);

    JSE_UI_SET_ACCESSOR(tpl, "width", Get_width, Set_width);
    JSE_UI_SET_ACCESSOR(tpl, "height", Get_height, Set_height);
    JSE_UI_SET_ACCESSOR(tpl, "visible", Get_visible, Set_visible);
    JSE_UI_SET_ACCESSOR(tpl, "title", Get_title, Set_title);
    JSE_UI_SET_ACCESSOR(tpl, "maximizeButton", Get_maximizeButton, Set_maximizeButton);
    JSE_UI_SET_ACCESSOR(tpl, "minimizeButton", Get_minimizeButton, Set_minimizeButton);
    JSE_UI_SET_ACCESSOR(tpl, "minimumWidth", Get_minimumWidth, Set_minimumWidth);
    JSE_UI_SET_ACCESSOR(tpl, "minimumHeight", Get_minimumHeight, Set_minimumHeight);
    JSE_UI_SET_ACCESSOR(tpl, "maximumWidth", Get_maximumWidth, Set_maximumWidth);
    JSE_UI_SET_ACCESSOR(tpl, "maximumHeight", Get_maximumHeight, Set_maximumHeight);
}

void JSEUIWindow::SetEvents(JSEUIWindow *self, JSEUIWindowImpl *selfImpl)
{
    JSE_UI_SET_EVENTS(self, On_resize(), selfImpl, resized());
}

void JSEUIWindow::Proto_maximize(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->showMaximized();

    info.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIWindow::Proto_minimize(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->showMinimized();

    info.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIWindow::Proto_alert(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    QMessageBox::information(windowImpl, windowImpl->windowTitle(), *String::Utf8Value(info[0]->ToString()), QMessageBox::Ok);
}

void JSEUIWindow::Proto_addMenu(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

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

    windowImpl->menuBar()->addMenu(childMenu->GetImpl());

    info.GetReturnValue().Set(Boolean::New(isolate, true));
}

void JSEUIWindow::Set_width(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    if (!windowImpl->isVisible())
    {
        windowImpl->layout()->update();
    }
    windowImpl->layout()->activate();

    QSize windowImplSize = windowImpl->size();
    QSize centralWidgetSize = windowImpl->centralWidget()->size();

    int dWidth = windowImplSize.width() - centralWidgetSize.width();

    int width = value->Int32Value() + dWidth;

    windowImpl->resize(width, windowImpl->size().height());
}

void JSEUIWindow::Get_width(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->size().width());
}

void JSEUIWindow::Set_height(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    if (!windowImpl->isVisible())
    {
        windowImpl->layout()->update();
    }
    windowImpl->layout()->activate();

    QSize windowImplSize = windowImpl->size();
    QSize centralWidgetSize = windowImpl->centralWidget()->size();

    int dHeight = windowImplSize.height() - centralWidgetSize.height();

    int height = value->Int32Value() + dHeight;

    windowImpl->resize(windowImpl->size().width(), height);
}

void JSEUIWindow::Get_height(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->centralWidget()->size().height());
}

void JSEUIWindow::Set_visible(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    bool visible = value->BooleanValue();

    if (visible)
    {
        windowImpl->show();
    }
    else
    {
        windowImpl->hide();
    }
}

void JSEUIWindow::Get_visible(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->isVisible());
}

void JSEUIWindow::Set_title(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->setWindowTitle(*String::Utf8Value(value->ToString()));

    info.GetReturnValue().Set(*String::Utf8Value(value->ToString()));
}

void JSEUIWindow::Get_title(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->windowTitle().constData());
}

void JSEUIWindow::Set_maximizeButton(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    bool maximizeButton = value->BooleanValue();

    bool visible = windowImpl->isVisible();
    
    if (maximizeButton)
    {
        windowImpl->setWindowFlags(windowImpl->windowFlags() | Qt::WindowMaximizeButtonHint);
    }
    else
    {
        windowImpl->setWindowFlags(windowImpl->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    }

    windowImpl->setVisible(visible);

    info.GetReturnValue().Set(*String::Utf8Value(value->ToString()));
}

void JSEUIWindow::Get_maximizeButton(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->windowFlags() & Qt::WindowMaximizeButtonHint);
}

void JSEUIWindow::Set_minimizeButton(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    bool maximizeButton = value->BooleanValue();

    bool visible = windowImpl->isVisible();

    if (maximizeButton)
    {
        windowImpl->setWindowFlags(windowImpl->windowFlags() | Qt::WindowMinimizeButtonHint);
    }
    else
    {
        windowImpl->setWindowFlags(windowImpl->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    }

    windowImpl->setVisible(visible);

    info.GetReturnValue().Set(*String::Utf8Value(value->ToString()));
}

void JSEUIWindow::Get_minimizeButton(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->windowFlags() & Qt::WindowMinimizeButtonHint);
}

void JSEUIWindow::Set_minimumWidth(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->setMinimumWidth(value->Int32Value());

    info.GetReturnValue().Set(value);
}

void JSEUIWindow::Get_minimumWidth(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->minimumWidth());
}

void JSEUIWindow::Set_minimumHeight(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->setMinimumHeight(value->Int32Value());

    info.GetReturnValue().Set(value);
}

void JSEUIWindow::Get_minimumHeight(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->minimumHeight());
}

void JSEUIWindow::Set_maximumWidth(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->setMaximumWidth(value->Int32Value());

    info.GetReturnValue().Set(value);
}

void JSEUIWindow::Get_maximumWidth(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->maximumWidth());
}

void JSEUIWindow::Set_maximumHeight(Local<String> prop, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    windowImpl->setMaximumHeight(value->Int32Value());

    info.GetReturnValue().Set(value);
}

void JSEUIWindow::Get_maximumHeight(Local<String> prop, const PropertyCallbackInfo<Value> &info)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    JSEUIWindowImpl *windowImpl = GetImpl(info);

    info.GetReturnValue().Set(windowImpl->maximumHeight());
}

void JSEUIWindow::On_resize(void)
{
    Isolate *isolate = Isolate::GetCurrent();
    Locker locker(isolate);
    HandleScope scope(isolate);

    Invoke(this, "resize", 0, nullptr);
}

}}