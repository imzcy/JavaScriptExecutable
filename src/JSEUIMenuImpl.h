#ifndef _JSEUIMENUIMPL_H_
#define _JSEUIMENUIMPL_H_

#include <QtWidgets/QMenu>

namespace JSE { namespace UI {

class JSEUIMenuImpl : public QMenu {

    Q_OBJECT

public:
    JSEUIMenuImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~JSEUIMenuImpl();

};

}}

#endif // _JSEUIMENUIMPL_H_