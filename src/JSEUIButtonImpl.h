#ifndef _JSEUIBUTTONIMPL_H_
#define _JSEUIBUTTONIMPL_H_

#include <QtWidgets/QPushButton>

namespace JSE { namespace UI {

class JSEUIButtonImpl : public QPushButton{

    Q_OBJECT

public:
    JSEUIButtonImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~JSEUIButtonImpl();

public:
    void Click(void);
};

}}

#endif // _JSEUIBUTTONIMPL_H_