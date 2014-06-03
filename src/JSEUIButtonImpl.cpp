#include "JSEUIButtonImpl.h"

namespace JSE { namespace UI {

JSEUIButtonImpl::JSEUIButtonImpl(QWidget *parent, Qt::WindowFlags flags)
{

}

JSEUIButtonImpl::~JSEUIButtonImpl()
{}

void JSEUIButtonImpl::Click(void)
{
    emit clicked();
}

}}