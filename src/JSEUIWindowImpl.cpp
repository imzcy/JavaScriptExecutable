#include "JSEUIWindowImpl.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>

namespace JSE { namespace UI {

JSEUIWindowImpl::JSEUIWindowImpl(QWidget *parent, Qt::WindowFlags flags)
{
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
}

JSEUIWindowImpl::~JSEUIWindowImpl()
{}

void JSEUIWindowImpl::resizeEvent(QResizeEvent *event)
{
    emit resized();
}

}}