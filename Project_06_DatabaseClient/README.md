# Project 06: Qt简易数据库客户端

## 📋 项目简介

创建一个图形化的数据库客户端，支持连接多种数据库，执行SQL查询，显示结果，数据可视化等。

## 🎯 项目要求

### 基础功能
1. **数据库连接**
   - 支持SQLite数据库
   - 支持MySQL数据库（可选）
   - 支持PostgreSQL数据库（可选）
   - 连接配置管理
   - 连接测试

2. **SQL查询**
   - 显示表结构
   - 执行SQL查询
   - 显示结果集
   - 执行DDL语句

3. **结果显示**
   - 表格显示结果
   - 分页显示
   - 排序功能
   - 刷新功能

### 进阶功能
1. **高级功能**
   - 复杂SQL语法高亮
   - SQL语法检查
   - 数据导入导出
   - SQL脚本执行

2. **数据管理**
   - 表数据编辑
   - 数据增删改查
   - 批量操作
   - 数据导出

3. **连接管理**
   - 多连接支持
   - 连接保存
   - 连接快捷方式
   - 连接信息管理

### 代码质量要求
1. 遵循Qt编码规范
2. 使用MVC模式
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_06_DatabaseClient/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    ├── ConnectionDialog.h          # 连接对话框头文件
    ├── ConnectionDialog.cpp        # 连接对话框实现
    ├── QueryEditor.h                # 查询编辑器头文件
    ├── QueryEditor.cpp              # 查询编辑器实现
    ├── QueryResultWidget.h         # 查询结果组件头文件
    ├── QueryResultWidget.cpp       # 查询结果组件实现
    ├── DatabaseManager.h           # 数据库管理器头文件
    ├── DatabaseManager.cpp         # 数据库管理器实现
    ├── ConnectionManager.h         # 连接管理器头文件
    ├── ConnectionManager.cpp       # 连接管理器实现
    ├── SchemaViewer.h              # 模式查看器头文件
    ├── SchemaViewer.cpp            # 模式查看器实现
    ├── SQLHighlighter.h            # SQL高亮器头文件
    ├── SQLHighlighter.cpp          # SQL高亮器实现
    ├── SQLParser.h                 # SQL解析器头文件
    ├── SQLParser.cpp               # SQL解析器实现
    ├── DataEditor.h                # 数据编辑器头文件
    ├── DataEditor.cpp              # 数据编辑器实现
    └── tests/
        ├── test_manager.cpp        # 管理器测试
        ├── test_parser.cpp         # 解析器测试
        └── test_highlighter.cpp    # 高亮器测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的QtSql模块深入
2. 多种数据库连接和操作
3. SQL语句解析
4. Qt的设计模式
5. 软件架构设计
6. UI设计原则
7. 复杂UI的实现

### 设计模式
1. MVC模式
2. 观察者模式
3. 单例模式（数据库管理）
4. 工厂模式（连接创建）
5. 命令模式（SQL执行）
6. 策略模式（不同的数据库策略）

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
./Project_06_DatabaseClient
```

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt SQL模块：https://doc.qt.io/qt-6/qtsql-index.html
- Qt设计模式：https://doc.qt.io/qt-6/designer-patterns.html
- SQL语法高亮：https://doc.qt.io/qt-6/qt-linguist-highlighter-example.html

## 💡 学习建议

1. 先实现SQLite连接和基本查询
2. 添加查询结果显示
3. 实现表结构查看
4. 添加SQL高亮功能
5. 扩展到其他数据库
6. 实现数据编辑功能
7. 优化UI和用户体验
8. 学习设计模式和架构设计

## ✅ 验收标准

- [ ] 可以连接SQLite数据库
- [ ] 可以执行基本SQL查询
- [ ] 显示查询结果
- [ ] 显示表结构
- [ ] SQL语法高亮
- [ ] 支持数据编辑
- [ ] 代码有良好注释
- [ ] 符合MVC设计模式
- [ ] 符合Qt编码规范
- [ ] 代码结构清晰

## 🗄️ 支持的数据库

### SQLite
- 完全支持
- 无需额外配置
- 文件数据库
- 适合学习和测试

### MySQL
- 完全支持
- 需要安装MySQL服务器
- C++连接器：MySQL Connector/C++

### PostgreSQL
- 完全支持
- 需要安装PostgreSQL服务器
- C++连接器：libpq

## 📝 SQL功能支持

### DDL语句
- CREATE TABLE
- ALTER TABLE
- DROP TABLE
- CREATE INDEX

### DML语句
- SELECT
- INSERT
- UPDATE
- DELETE

### DCL语句（可选）
- GRANT
- REVOKE
- COMMIT
- ROLLBACK
