#include <QCoreApplication>
#include <QDebug>
#include <QTest>
#include "../ArgumentParser.h"

class ArgumentParserTest : public QObject
{
    Q_OBJECT

private slots:
    // 每个测试前执行
    void initTestCase()
    {
        qDebug() << "开始测试ArgumentParser";
    }

    // 每个测试后执行
    void cleanupTestCase()
    {
        qDebug() << "测试完成";
    }

    // ====== 测试用例 ======

    void testAddArgument()
    {
        ArgumentParser parser;
        int id = parser.addArgument("--name", "姓名",
            ArgumentParser::ArgType::String, "默认值", true, {"-n"});
        QVERIFY(id >= 0);  // 验证返回有效的ID
    }

    void testParseString()
    {
        ArgumentParser parser;
        parser.addArgument("--name", "姓名",
            ArgumentParser::ArgType::String, "", true, {"-n"});

        // 模拟命令行参数
        // argv[0] 是程序名，argv[1] 开始是参数
        const char *argv[] = {"app", "--name", "张三"};
        parser.parse(3, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--name").toString(), QString("张三"));
    }

    void testParseInteger()
    {
        ArgumentParser parser;
        parser.addArgument("--age", "年龄",
            ArgumentParser::ArgType::Integer, 0, false, {"-a"});

        const char *argv[] = {"app", "--age", "25"};
        parser.parse(3, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--age").toInt(), 25);
    }

    void testParseFloat()
    {
        ArgumentParser parser;
        parser.addArgument("--height", "身高",
            ArgumentParser::ArgType::Float, 0.0, false, {"-h"});

        const char *argv[] = {"app", "--height", "1.75"};
        parser.parse(3, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--height").toDouble(), 1.75);
    }

    void testParseBool()
    {
        ArgumentParser parser;
        parser.addArgument("--verbose", "详细模式",
            ArgumentParser::ArgType::Bool, false, false, {"-v"});

        const char *argv[] = {"app", "--verbose"};
        parser.parse(2, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--verbose").toBool(), true);
    }

    void testDefaultValue()
    {
        ArgumentParser parser;
        parser.addArgument("--name", "姓名",
            ArgumentParser::ArgType::String, "默认用户", false, {"-n"});

        const char *argv[] = {"app"};  // 不传 --name
        parser.parse(1, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--name").toString(), QString("默认用户"));
    }

    void testRequired()
    {
        ArgumentParser parser;
        parser.addArgument("--name", "姓名",
            ArgumentParser::ArgType::String, "", true, {"-n"});

        const char *argv[] = {"app"};  // 缺少必需参数
        parser.parse(1, const_cast<char**>(argv));

        QVERIFY(!parser.checkRequired());  // 应该返回 false
    }

    void testAlias()
    {
        ArgumentParser parser;
        parser.addArgument("--name", "姓名",
            ArgumentParser::ArgType::String, "", true, {"-n"});

        const char *argv[] = {"app", "-n", "李四"};  // 用别名
        parser.parse(3, const_cast<char**>(argv));

        QCOMPARE(parser.getValue("--name").toString(), QString("李四"));
        QCOMPARE(parser.getValue("-n").toString(), QString("李四"));  // 别名也能查
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ArgumentParserTest tc;
    return QTest::qExec(&tc, argc, argv);
}

#include "test.moc"
