#ifndef SNLINEEDIT_H
#define SNLINEEDIT_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include <QFont>
#include <QPainter>
#include <QFontMetrics>

class SNLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString Inserter READ Inserter WRITE setInserter NOTIFY InserterChanged) //插入符-属性
    Q_PROPERTY(QString InserterSe READ InserterSe WRITE setInserterSe NOTIFY InserterSeChanged)
    Q_PROPERTY(QString Value READ Value WRITE setValue NOTIFY ValueChanged) //输入内容-属性
    Q_PROPERTY(int InserterInterval READ InserterInterval WRITE setInserterInterval NOTIFY InserterIntervalChanged)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont NOTIFY textFontChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor InserterColor READ InserterColor WRITE setInserterColor NOTIFY InserterColorChanged)
    Q_PROPERTY(bool passwordMode READ passwordMode WRITE setPasswordMode NOTIFY passwordModeChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
public:
    SNLineEdit(QWidget *parent = 0);
    SNLineEdit(const QString & placeHolder,QWidget * parent = 0);
    virtual ~SNLineEdit();

    QString Inserter() const;
    void setInserter(QString value);

    QString Value() const;
    void setValue(QString value);

    int InserterInterval() const;
    void setInserterInterval(int interval);

    QFont textFont() const;
    void setTextFont(QFont font);

    QColor backgroundColor() const;
    void setBackgroundColor(QColor color);

    QColor InserterColor() const;
    void setInserterColor(QColor color);

    QString InserterSe() const;
    void setInserterSe(QString Se);

    bool passwordMode() const;
    void setPasswordMode(bool value);

    QColor textColor() const;
    void setTextColor(QColor color);

signals:
    void InserterChanged(QString value); //插入符改变信号
    void ValueChanged(QString value); //用户输入改变信号
    void InserterIntervalChanged(int interval);
    void textFontChanged(QFont font);
    void backgroundColorChanged(QColor color);
    void InserterColorChanged(QColor color);
    void InserterSeChanged(QString Se);
    void passwordModeChanged(bool value);
    void textColorChanged(QColor color);

protected:
    QString m_placeHolder;
    QString m_value;
    QString m_Inserter = "<";
    QString m_Inserter_Se = "<<";
    QString m_drawString;
    QFont m_font;
    QColor m_default_color = QColor(165,69,141,30);
    QColor m_inserter_color = QColor(253,192,165);
    QColor m_text_color = QColor(0,0,0);
    int m_interval = 800;
    bool m_inserter_shouldbe_add = false;
    bool m_focus = false;
    bool m_password_mode = false;
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
protected slots:
    void updateInserter();

protected:
    QTimer * timer;
};

#endif // SNLINEEDIT_H
