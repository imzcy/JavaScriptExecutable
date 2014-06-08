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
    virtual void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void resized(void);
    void mouseMove(int left, int top);
    void mouseOut(void);

};

}}

#endif // _JSEUIWINDOWIMPL_H_