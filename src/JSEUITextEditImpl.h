#ifndef _JSEUITEXTEDITIMPL_H_
#define _JSEUITEXTEDITIMPL_H_

#include <QtWidgets/QTextEdit>

namespace JSE {
    namespace UI {

        class JSEUITextEditImpl : public QTextEdit{

            Q_OBJECT

        public:
            JSEUITextEditImpl(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
            ~JSEUITextEditImpl();
        };

    }
}

#endif // _JSEUITEXTEDITIMPL_H_