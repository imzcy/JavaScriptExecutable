#include "JSEUIWindowImpl.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLayout>

namespace JSE { namespace UI {

JSEUIWindowImpl::JSEUIWindowImpl(QWidget *parent, Qt::WindowFlags flags)
{
    this->setLayout(new QHBoxLayout());
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