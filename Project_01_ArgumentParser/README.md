# Project 01: Qt命令行参数解析器

## 📋 项目简介

创建一个简单的命令行参数解析器，支持解析带有类型的信息（字符串、整数、浮点数），并生成帮助文档。

## 🎯 项目要求

### 基础功能
1. **参数类型支持**
   - 字符串参数
   - 整数参数
   - 浮点数参数
   - 布尔参数（flag）

2. **参数特性**
   - 支持设置参数的默认值
   - 支持设置参数的描述信息
   - 支持设置参数的必需性
   - 支持参数别名

3. **帮助文档**
   - 自动生成帮助信息
   - 显示所有参数及其说明
   - 显示使用示例

### 进阶功能
1. **参数验证**
   - 整数范围验证
   - 浮点数范围验证
   - 字符串正则验证

2. **输出格式化**
   - 彩色输出（可选）
   - 结构化输出（JSON/XML）
   - 详细/简洁模式

### 代码质量要求
1. 遵循Qt编码规范
2. 代码结构清晰
3. 有适当的注释
4. 支持单元测试

## 📂 项目结构

```
Project_01_ArgumentParser/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── ArgumentParser.h            # 头文件
    ├── ArgumentParser.cpp          # 实现文件
    └── tests/
        └── test.cpp                # 单元测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的元对象系统（MOC）
2. 信号与槽机制
3. Qt的字符串处理
4. 命令行参数解析
5. Qt的资源系统
6. 单元测试框架

### 设计模式
1. 命令模式（可选）
2. 观察者模式（可选）
3. 策略模式（可选）

## 🚀 启动步骤

### 编译
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 运行
```bash
cd build
./Project_01_ArgumentParser --help
./Project_01_ArgumentParser -n "TestName" -v 3.14 --verbose
```

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Core模块：https://doc.qt.io/qt-6/qcoreapplication.html
- C++标准库：<iostream>, <string>, <vector>, <map>

## 💡 学习建议

1. 先理解Qt的基本结构
2. 逐步实现功能，不要一次性完成所有特性
3. 阅读Qt源码中的类似实现（如QCommandLineParser）
4. 写单元测试来验证你的实现
5. 优化代码结构和可读性

## ✅ 验收标准

- [ ] 可以解析不同类型的参数
- [ ] 可以设置默认值
- [ ] 可以生成帮助信息
- [ ] 有完整的单元测试
- [ ] 代码有良好注释
- [ ] 符合Qt编码规范
