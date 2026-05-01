# Project 05: Qt任务管理器

## 📋 项目简介

创建一个跨平台的任务管理器，支持任务的增删改查、优先级设置、截止日期提醒、拖拽排序等。

## 🎯 项目要求

### 基础功能
1. **任务管理**
   - 添加任务
   - 删除任务
   - 编辑任务
   - 标记完成/未完成
   - 搜索任务

2. **任务属性**
   - 任务标题
   - 任务描述
   - 截止日期
   - 优先级（高、中、低）
   - 创建时间

3. **任务分类**
   - 支持标签
   - 支持分类
   - 颜色标记

### 进阶功能
1. **拖拽排序**
   - 拖拽重新排序
   - 拖拽移动到其他列表

2. **提醒功能**
   - 截止日期提醒
   - 提前提醒设置
   - 提醒通知

3. **数据持久化**
   - 自动保存
   - 数据备份
   - 数据恢复

### 代码质量要求
1. 遵循Qt编码规范
2. 使用MVC模式
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_05_TaskManager/
├── CMakeLists.txt
├── README.md
├── database/
│   └── schema.sql                 # 数据库模式
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    ├── TaskModel.h                 # 任务模型头文件
    ├── TaskModel.cpp               # 任务模型实现
    ├── TaskItemWidget.h            # 任务项组件头文件
    ├── TaskItemWidget.cpp          # 任务项组件实现
    ├── TaskListWidget.h            # 任务列表组件头文件
    ├── TaskListWidget.cpp          # 任务列表组件实现
    ├── TaskDialog.h                # 任务编辑对话框头文件
    ├── TaskDialog.cpp              # 任务编辑对话框实现
    ├── TagModel.h                  # 标签模型头文件
    ├── TagModel.cpp                # 标签模型实现
    ├── TagWidget.h                 # 标签组件头文件
    ├── TagWidget.cpp               # 标签组件实现
    ├── TaskDatabase.h              # 数据库操作头文件
    ├── TaskDatabase.cpp            # 数据库操作实现
    └── tests/
        ├── test_model.cpp          # 模型测试
        └── test_database.cpp       # 数据库测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的模型视图框架
2. Qt的QtSql模块
3. SQLite数据库操作
4. Qt的数据模型（QAbstractItemModel）
5. Qt的拖放系统
6. Qt的定时器
7. Qt的日期和时间处理
8. Qt的对话框和布局管理

### 设计模式
1. MVC模式
2. 观察者模式
3. 单例模式（数据库实例）
4. 适配器模式（数据适配）

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
./Project_05_TaskManager
```

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt SQL模块：https://doc.qt.io/qt-6/qtsql-index.html
- QSqlDatabase：https://doc.qt.io/qt-6/qsqldatabase.html
- QSqlQuery：https://doc.qt.io/qt-6/qsqlquery.html
- Qt模型视图：https://doc.qt.io/qt-6/model-view-programming.html

## 💡 学习建议

1. 先实现基本的任务CRUD操作
2. 添加数据库持久化
3. 实现任务列表显示
4. 添加拖拽排序功能
5. 实现标签系统
6. 添加提醒功能
7. 优化用户体验

## ✅ 验收标准

- [ ] 可以添加、删除、编辑任务
- [ ] 可以标记任务完成状态
- [ ] 数据持久化到数据库
- [ ] 支持搜索和过滤
- [ ] 支持拖拽排序
- [ ] 支持标签系统
- [ ] 显示截止日期提醒
- [ ] 代码有良好注释
- [ ] 符合MVC设计模式
- [ ] 符合Qt编码规范

## 🗄️ 数据库设计

```sql
CREATE TABLE tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    description TEXT,
    due_date INTEGER,
    priority INTEGER DEFAULT 0,
    is_completed INTEGER DEFAULT 0,
    created_at INTEGER NOT NULL,
    updated_at INTEGER NOT NULL
);

CREATE TABLE tags (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    color TEXT
);

CREATE TABLE task_tags (
    task_id INTEGER NOT NULL,
    tag_id INTEGER NOT NULL,
    PRIMARY KEY (task_id, tag_id),
    FOREIGN KEY (task_id) REFERENCES tasks(id),
    FOREIGN KEY (tag_id) REFERENCES tags(id)
);
```
