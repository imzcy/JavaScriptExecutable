#ifndef _JSEUILINEEDITIMPL_H_
#define _JSEUILINEEDITIMPL_H_

#include <QtWidgets/QLineEdit>

namespace JSE { namespace UI {

class JSEUILineEditImpl : public QLineEdit{

    Q_OBJECT

public:
    JSEUILineEditImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~JSEUILineEditImpl();
};

}}

#endif // _JSEUILINEEDITIMPL_H_