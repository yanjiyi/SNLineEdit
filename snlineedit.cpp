#include "snlineedit.h"

SNLineEdit::SNLineEdit(QWidget *parent) :
    QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(m_interval);
    this->setFocusPolicy(Qt::ClickFocus);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateInserter()));
}

SNLineEdit::SNLineEdit(const QString &placeHolder, QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(m_interval);
    this->m_placeHolder = placeHolder;
    this->setFocusPolicy(Qt::ClickFocus);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateInserter()));
}

SNLineEdit::~SNLineEdit()
{

}

QString SNLineEdit::Inserter() const
{
    return m_Inserter;
}

void SNLineEdit::setInserter(QString value)
{
    m_Inserter = value;
    emit InserterChanged(value);
    update();
}

QString SNLineEdit::Value() const
{
    return m_value;
}

void SNLineEdit::setValue(QString value)
{
    m_value = value;
    emit ValueChanged(value);
    update();
}

int SNLineEdit::InserterInterval() const
{
    return m_interval;
}

void SNLineEdit::setInserterInterval(int interval)
{
    m_interval = interval;
    if(timer!=nullptr)
    {
        timer->stop();
        disconnect(timer,SIGNAL(timeout()),this,SLOT(updateInserter()));
        delete timer;
    }

    timer = new QTimer(this);
    timer->setInterval(m_interval);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateInserter()));

    if(m_focus)
        timer->start();

    emit InserterIntervalChanged(interval);
}

QFont SNLineEdit::textFont() const
{
    return m_font;
}

void SNLineEdit::setTextFont(QFont font)
{
    m_font = font;
    emit textFontChanged(font);

    update();
}

QColor SNLineEdit::backgroundColor() const
{
    return m_default_color;
}

void SNLineEdit::setBackgroundColor(QColor color)
{
    m_default_color = color;
    emit backgroundColorChanged(color);
    update();
}

QColor SNLineEdit::InserterColor() const
{
    return m_inserter_color;
}

void SNLineEdit::setInserterColor(QColor color)
{
    m_inserter_color = color;
    emit InserterColorChanged(color);
    update();
}

QString SNLineEdit::InserterSe() const
{
    return m_Inserter_Se;
}

void SNLineEdit::setInserterSe(QString Se)
{
    m_Inserter_Se = Se;
    emit InserterSeChanged(Se);
    update();
}

bool SNLineEdit::passwordMode() const
{
    return m_password_mode;
}

void SNLineEdit::setPasswordMode(bool value)
{
    m_password_mode = value;
    emit passwordModeChanged(value);
    update();
}

QColor SNLineEdit::textColor() const
{
    return m_text_color;
}

void SNLineEdit::setTextColor(QColor color)
{
    m_text_color = color;
    emit textColorChanged(color);
    update();
}

QString SNLineEdit::placeHolder() const
{
    return m_placeHolder;
}

void SNLineEdit::setPlaceHolder(QString placeHolder)
{
    m_placeHolder = placeHolder;
    emit placeHolderChanged(placeHolder);
    update();
}


void SNLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key()!=Qt::Key_Backspace)
    {
        m_value += event->text();
    }else{
        m_value = m_value.mid(0,m_value.length()-1);
    }

    emit ValueChanged(m_value);
    update();
}

void SNLineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(),m_default_color);

    if(m_value.isEmpty()||m_value.length()==0||m_value=="")
    {
        QColor placeHolderColor = m_text_color;
        placeHolderColor.setAlpha(100);
        painter.setPen(placeHolderColor);
        painter.setFont(m_font);
        painter.drawText(rect(),m_placeHolder);
    }

    QFontMetrics metrics(m_font);

    if(m_focus)
    {
        m_font.setBold(true);
        if(!m_inserter_shouldbe_add){
            painter.setFont(m_font);
            painter.setPen(m_inserter_color);
            painter.drawText(width()-metrics.width(m_Inserter_Se),0,metrics.width(m_Inserter_Se),height(),0,m_Inserter_Se);
        }

        if(m_inserter_shouldbe_add)
        {
            painter.setFont(m_font);
            painter.setPen(m_inserter_color);
            painter.drawText(width()-metrics.width(m_Inserter_Se),0,metrics.width(m_Inserter_Se),height(),0,m_Inserter);
        }

        m_font.setBold(false);

        if(!m_password_mode)
            m_drawString = m_value;
        else {
            m_drawString.clear();
            for(int i = 0;i<m_value.length();i++)
            {
                m_drawString += "*";
            }
        }

//        bool overflow = metrics.width(m_drawString) > width();
        bool overflow = metrics.width(m_drawString) > (width()-metrics.width(m_Inserter_Se));
        while(overflow)
        {
            m_drawString = m_drawString.remove(0,1);

//            overflow = metrics.width(m_drawString) > width();
            overflow = metrics.width(m_drawString) > (width()-metrics.width(m_Inserter_Se));
        }

        painter.setFont(m_font);
        painter.setPen(m_text_color);
//        painter.drawText(rect(),m_drawString);
        painter.drawText(0,0,width()-metrics.width(m_Inserter_Se),height(),0,m_drawString);
    }

    if(!m_focus)
    {
        if(!m_password_mode)
            m_drawString = m_value;
        else{
            m_drawString.clear();
            for(int i = 0;i<m_value.length();i++)
            {
                m_drawString += "*";
            }
        }

        m_font.setBold(false);
        painter.setFont(m_font);
        painter.setPen(m_text_color);
        painter.drawText(0,0,width()-metrics.width(m_Inserter_Se),height(),0,m_drawString);
    }
}

void SNLineEdit::focusInEvent(QFocusEvent *event)
{
    m_focus = true;
    if(timer!=nullptr)
        timer->start();
}

void SNLineEdit::focusOutEvent(QFocusEvent *event)
{
    m_focus = false;
    if(timer!=nullptr)
        timer->stop();

    m_inserter_shouldbe_add = false;
    update();
}

void SNLineEdit::updateInserter()
{
    m_inserter_shouldbe_add = !m_inserter_shouldbe_add;
    update();
}


