#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QMap>
#include <QPair>

/**
 * @brief 命令行参数解析器
 *
 * 支持解析字符串、整数、浮点数和布尔类型的命令行参数
 */
class ArgumentParser
{
public:
    ArgumentParser();
    ~ArgumentParser();

    // 参数类型枚举
    enum class ArgType {
        String,
        Integer,
        Float,
        Bool
    };

    // 参数结构体
    struct Argument {
        QString name;          // 参数名称（如 -n, --name）
        QString description;   // 参数描述
        QVariant defaultValue; // 默认值
        ArgType type;          // 参数类型
        bool required;         // 是否必需
        QStringList aliases;   // 别名列表
        QString value;         // 当前值
    };

    /**
     * @brief 添加一个参数
     * @param name 参数名称
     * @param description 描述
     * @param type 类型
     * @param defaultValue 默认值
     * @param required 是否必需
     * @param aliases 别名
     * @return 参数ID
     */
    int addArgument(const QString &name,
                   const QString &description = "",
                   ArgType type = ArgType::String,
                   const QVariant &defaultValue = QVariant(),
                   bool required = false,
                   const QStringList &aliases = QStringList());

    /**
     * @brief 设置参数的验证规则
     * @param argId 参数ID
     * @param minValue 最小值（整数/浮点数）
     * @param maxValue 最大值（整数/浮点数）
     * @param regex 正则表达式（字符串）
     */
    void setValidation(int argId,
                      const QVariant &minValue = QVariant(),
                      const QVariant &maxValue = QVariant(),
                      const QString &regex = "");

    /**
     * @brief 解析命令行参数
     * @param argc 参数个数
     * @param argv 参数列表
     * @return 是否解析成功
     */
    bool parse(int argc, char *argv[]);

    /**
     * @brief 获取参数值
     * @param name 参数名称
     * @return 参数值
     */
    QVariant getValue(const QString &name) const;

    /**
     * @brief 检查参数是否存在
     * @param name 参数名称
     * @return 是否存在
     */
    bool hasValue(const QString &name) const;

    /**
     * @brief 检查是否设置了必需参数
     * @return 是否所有必需参数都已设置
     */
    bool checkRequired() const;

    /**
     * @brief 生成帮助信息
     * @return 帮助信息字符串
     */
    QString generateHelp() const;

    /**
     * @brief 获取程序名称
     * @return 程序名称
     */
    QString getProgramName() const;

    /**
     * @brief 设置程序名称
     * @param name 程序名称
     */
    void setProgramName(const QString &name);

private:
    /**
     * @brief 根据名称获取参数
     * @param name 参数名称
     * @return 参数ID，如果不存在返回-1
     */
    int findArgument(const QString &name) const;

    // 数据成员
    QString m_programName;
    QList<Argument> m_arguments;
    QMap<QString, int> m_nameToId;
    QMap<QString, int> m_aliasesToId;

    // 验证规则
    QMap<int, QPair<QVariant, QVariant>> m_validation; // min/max
    QMap<int, QString> m_validationRegex;
};

#endif // ARGUMENTPARSER_H
