#ifndef _JSEMENULEAFIMPL_H_
#define _JSEMENULEAFIMPL_H_

#include <QtWidgets/QAction>

namespace JSE { namespace UI {

class JSEUIMenuLeafImpl : public QAction {

    Q_OBJECT

public:
    JSEUIMenuLeafImpl(QWidget *parent = nullptr);
    ~JSEUIMenuLeafImpl();

};

}}

#endif // _JSEMENULEAFIMPL_H_