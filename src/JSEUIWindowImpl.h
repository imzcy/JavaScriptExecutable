#ifndef _JSEUIWINDOWIMPL_H_
#define _JSEUIWINDOWIMPL_H_

#include <QtWidgets/QMainWindow>

namespace JSE { namespace UI {

class JSEUIWindowImpl : public QMainWindow {

    Q_OBJECT

public:
    JSEUIWindowImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~JSEUIWindowImpl();

protected:
    virtual void JSEUIWindowImpl::resizeEvent(QResizeEvent *event);

signals:
    void resized(void);

};

}}

#endif // _JSEUIWINDOWIMPL_H_