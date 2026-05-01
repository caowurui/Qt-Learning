#include "ArgumentParser.h"
#include <QCommandLineParser>
#include <QDebug>

ArgumentParser::ArgumentParser()
{
    m_programName = "Project_01_ArgumentParser";
}

ArgumentParser::~ArgumentParser()
{
}

int ArgumentParser::addArgument(const QString &name,
                               const QString &description,
                               ArgType type,
                               const QVariant &defaultValue,
                               bool required,
                               const QStringList &aliases)
{
    Argument arg;
    arg.name = name;
    arg.description = description;
    arg.type = type;
    arg.defaultValue = defaultValue;
    arg.required = required;
    arg.aliases = aliases;
    arg.value = defaultValue.toString();

    int id = m_arguments.size();
    m_arguments.append(arg);

    // 存储名称映射
    m_nameToId[name] = id;

    // 存储别名映射
    for (const QString &alias : aliases) {
        m_aliasesToId[alias] = id;
    }

    return id;
}

void ArgumentParser::setValidation(int argId,
                                   const QVariant &minValue,
                                   const QVariant &maxValue,
                                   const QString &regex)
{
    if (argId >= 0 && argId < m_arguments.size()) {
        m_validation[argId] = QPair<QVariant, QVariant>(minValue, maxValue);
        m_validationRegex[argId] = regex;
    }
}

bool ArgumentParser::parse(int argc, char *argv[])
{
    bool flag=false;
    Argument last;
    for(int i = 1; i < argc; ++i) {
        QString arg(argv[i]);
        if(arg.startsWith("--") || arg.startsWith("-")) {
            int id = findArgument(arg);
            if(id >= 0 && id < m_arguments.size()) {
                last = m_arguments[id];
                if(last.type == ArgType::Bool) {
                    m_arguments[id].value = "true";
                    flag=false;
                } else {
                    flag=true;
                }
            } else {
                qDebug() << "未知参数:" << arg;
                return false;
            }
        } else if(flag) {
            m_arguments[findArgument(last.name)].value = arg;
            flag=false;
        } else {
            qDebug() << "无效参数:" << arg;
            return false;
        }
    }
    return true;
}

QVariant ArgumentParser::getValue(const QString &name) const
{
    int id = findArgument(name);
    if (id >= 0 && id < m_arguments.size()) {
        return m_arguments[id].value;
    }
    return QVariant();
}

bool ArgumentParser::hasValue(const QString &name) const
{
    int id = findArgument(name);
    if (id >= 0 && id < m_arguments.size()) {
        return !m_arguments[id].value.isEmpty();
    }
    return false;
}

bool ArgumentParser::checkRequired() const
{
    for (const Argument &arg : m_arguments) {
        if (arg.required && arg.value==arg.defaultValue.toString()) {
            return false;
        }
    }
    return true;
}

QString ArgumentParser::generateHelp() const
{
    QString help;
    help += "Usage: " + m_programName + " [options]\n\n";
    help += "Options:\n";

    for (const Argument &arg : m_arguments) {
        help += "  " + arg.name;

        // 添加别名
        if (!arg.aliases.isEmpty()) {
            help += ", " + arg.aliases.join(", ");
        }

        // 添加默认值
        if (!arg.defaultValue.isNull()) {
            help += " [" + arg.defaultValue.toString() + "]";
        }

        help += "\n";
        help += "    " + arg.description + "\n";
        help += "\n";
    }

    return help;
}

QString ArgumentParser::getProgramName() const
{
    return m_programName;
}

void ArgumentParser::setProgramName(const QString &name)
{
    m_programName = name;
}

int ArgumentParser::findArgument(const QString &name) const
{
    // 先尝试精确匹配
    if (m_nameToId.contains(name)) {
        return m_nameToId[name];
    }

    // 尝试别名匹配
    if (m_aliasesToId.contains(name)) {
        return m_aliasesToId[name];
    }

    return -1;
}
