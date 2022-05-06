#include "snlineedit.h"
#include "snlineeditplugin.h"

#include <QtPlugin>

SNLineEditPlugin::SNLineEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SNLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SNLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SNLineEditPlugin::createWidget(QWidget *parent)
{
    return new SNLineEdit(parent);
}

QString SNLineEditPlugin::name() const
{
    return QLatin1String("SNLineEdit");
}

QString SNLineEditPlugin::group() const
{
    return QLatin1String("");
}

QIcon SNLineEditPlugin::icon() const
{
    return QIcon();
}

QString SNLineEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SNLineEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SNLineEditPlugin::isContainer() const
{
    return false;
}

QString SNLineEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SNLineEdit\" name=\"sNLineEdit\">\n</widget>\n");
}

QString SNLineEditPlugin::includeFile() const
{
    return QLatin1String("snlineedit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(snlineeditplugin, SNLineEditPlugin)
#endif // QT_VERSION < 0x050000
