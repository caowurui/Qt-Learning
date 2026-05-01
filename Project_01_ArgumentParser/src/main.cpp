#include <QCoreApplication>
#include <QDebug>
#include "ArgumentParser.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    // 1. 创建ArgumentParser实例
    ArgumentParser parser;


    // 2. 添加各种类型的参数
    parser.addArgument(
        "--name",
        "姓名",
        ArgumentParser::ArgType::String,
        "未知",
        true,
        {"-n"}
    );
    parser.addArgument(
        "--age",
        "年龄",
        ArgumentParser::ArgType::Integer,
        0,
        false,
        {"-a"}
    );
    parser.addArgument(
        "--height",
        "身高(米)",
        ArgumentParser::ArgType::Float,
        0.0,
        false,
        {"-h"}
    );
    parser.addArgument(
        "--verbose",
        "详细模式",
        ArgumentParser::ArgType::Bool,
        false,
        false,
        {"-v"}
    );


    // 3. 解析命令行参数
    if(!parser.parse(argc, argv)) {
        qDebug() << parser.generateHelp();
        return 1;
    }


    // 4. 输出解析结果
    qDebug() << "姓名:" << parser.getValue("--name").toString();
    qDebug() << "年龄:" << parser.getValue("--age").toInt();
    qDebug() << "身高:" << parser.getValue("--height").toDouble();
    qDebug() << "详细模式:" << parser.getValue("--verbose").toBool();


    return 0;
}
