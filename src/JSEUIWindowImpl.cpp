#include "JSE.h"

#include "JSEUIWindowImpl.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLayout>
#include <QtGui/qevent.h>

namespace JSE { namespace UI {

JSEUIWindowImpl::JSEUIWindowImpl(QWidget *parent, Qt::WindowFlags flags)
{
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    app->installEventFilter(this);
}

JSEUIWindowImpl::~JSEUIWindowImpl()
{}

void JSEUIWindowImpl::resizeEvent(QResizeEvent *event)
{
    emit resized();
}

bool JSEUIWindowImpl::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
    {
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
        int left = mEvent->x();
        int top = mEvent->y();
        QWidget *wObj = dynamic_cast<QWidget *>(obj);
        while (wObj != nullptr)
        {
            QPoint pos = wObj->pos();
            left += pos.x();
            top += pos.y();
            wObj = dynamic_cast<QWidget *>(wObj->parent());

            if (dynamic_cast<void *>(wObj) == dynamic_cast<void *>(this))
            {
                QPoint pos = this->centralWidget()->pos();
                QSize size = this->centralWidget()->size();
                left -= pos.x();
                top -= pos.y();
                if (left >= 0 && top >= 0 && left < size.width() && top < size.height())
                {
                    emit mouseMove(left, top);
                }
                break;
            }
        }
        break;
    }
    case QEvent::Leave:
    {
        if (dynamic_cast<void *>(obj) == dynamic_cast<void *>(this))
        {
            emit mouseOut();
        }
        break;
    }
    default:
        // noop
        ;
    }
    return false;
}

}}