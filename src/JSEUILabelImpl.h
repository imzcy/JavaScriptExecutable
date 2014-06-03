#ifndef _JSEUILABELIMPL_H_
#define _JSEUILABELIMPL_H_

#include <QtWidgets/QLabel>

namespace JSE { namespace UI {

class JSEUILabelImpl : public QLabel{

    Q_OBJECT

public:
    JSEUILabelImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~JSEUILabelImpl();
};

}}

#endif // _JSEUILABELIMPL_H_