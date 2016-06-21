#include "blureinfoframe.h"
#include "separator.h"
#include "utils/baseutils.h"
#include <dwindowclosebutton.h>
#include <QLabel>
#include <QEvent>
#include <QDebug>

class SimpleFormLabel : public QLabel {
    Q_OBJECT
public:
    explicit SimpleFormLabel(const QString &t, QWidget *parent = 0)
        : QLabel(t, parent) {}
};

class SimpleFormField : public QLabel {
    Q_OBJECT
public:
    explicit SimpleFormField(const QString &t, QWidget *parent = 0)
        : QLabel(t, parent) {}
};

BlureInfoFrame::BlureInfoFrame(QWidget *parent, QWidget *source)
    : BlureFrame(parent, source)
{
    setBorderRadius(4);
    setBorderWidth(1);
    setBorderColor(QColor(255, 255, 255, 51));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);

    QFrame *tf = new QFrame;
    tf->setObjectName("InfoTopContent");
    tf->setContentsMargins(0, 0, 0, 0);
    m_topLayout = new QVBoxLayout(tf);
    m_topLayout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(tf);

    Separator *s = new Separator;
    s->setFixedHeight(1);
    layout->addSpacing(5);
    layout->addWidget(s);
    layout->addSpacing(5);

    m_infoLayout = new QFormLayout;
    m_infoLayout->setSpacing(13);
    m_infoLayout->setContentsMargins(8, 0, 8, 0);
    m_infoLayout->setLabelAlignment(Qt::AlignRight);
    layout->addLayout(m_infoLayout);
    layout->addStretch(1);

    setStyleSheet(utils::base::getFileContent(
                      ":/qss/resources/qss/BlureInfoFrame.qss"));
}

void BlureInfoFrame::setTopContent(QWidget *w)
{
    QLayoutItem *item;
    while (( item = m_topLayout->takeAt(0))) {
        if (item->widget())
            delete item->widget();
        delete item;
    }
    m_topLayout->addWidget(w, 1, Qt::AlignCenter);

    Dtk::Widget::DWindowCloseButton *cb = new Dtk::Widget::DWindowCloseButton(this);
    cb->setFixedSize(24, 24);
    cb->move(this->sizeHint().width() - cb->width() - 5, 0);
    connect(cb, &Dtk::Widget::DWindowCloseButton::clicked,
            this, &BlureInfoFrame::close);
}

void BlureInfoFrame::addInfoPair(const QString &title, const QString &value)
{
    SimpleFormLabel *tl = new SimpleFormLabel(title);
    tl->setAlignment(Qt::AlignRight);
    tl->setMinimumWidth(width() / 5 * 2);
    SimpleFormField *vl = new SimpleFormField(value);
    vl->setWordWrap(true);
    m_infoLayout->addRow(tl, vl);
}

void BlureInfoFrame::close()
{
    emit closed();
    BlureFrame::close();
}
