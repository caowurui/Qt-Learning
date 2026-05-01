# Project 02: Qt文本编辑器

## 📋 项目简介

创建一个支持基本文本编辑、文件保存和简单语法高亮的文本编辑器。

## 🎯 项目要求

### 基础功能
1. **文本编辑**
   - 多行文本编辑
   - 光标移动
   - 文本选择
   - 剪切、复制、粘贴
   - 删除和撤销

2. **文件操作**
   - 打开文件
   - 保存文件
   - 另存为
   - 新建文件
   - 自动保存（可选）

3. **基本UI**
   - 菜单栏
   - 工具栏
   - 状态栏
   - 文件标签页

### 进阶功能
1. **语法高亮**
   - 关键词高亮
   - 字符串高亮
   - 注释高亮
   - 自动检测语言类型

2. **编辑增强**
   - 自动换行
   - 行号显示
   - 括号匹配
   - 查找和替换

3. **快捷键**
   - Ctrl+S 保存
   - Ctrl+O 打开
   - Ctrl+N 新建
   - Ctrl+Z 撤销
   - Ctrl+Y 重做

### 代码质量要求
1. 遵循Qt编码规范
2. 使用MVC模式
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_02_TextEditor/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    ├── EditorWidget.h              # 编辑器组件头文件
    ├── EditorWidget.cpp            # 编辑器组件实现
    ├── SyntaxHighlighter.h         # 语法高亮头文件
    ├── SyntaxHighlighter.cpp       # 语法高亮实现
    ├── HighlighterRules.h          # 高亮规则配置
    ├── HighlighterRules.cpp        # 高亮规则实现
    └── tests/
        ├── test_editor.cpp         # 编辑器测试
        └── test_highlighter.cpp    # 高亮器测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的GUI框架（QWidget, QPushButton, QLabel等）
2. Qt的事件系统（事件循环、事件过滤器）
3. Qt的布局管理（QHBoxLayout, QVBoxLayout等）
4. Qt的文档模型（QTextDocument, QTextCursor）
5. Qt的文件I/O
6. Qt的正则表达式
7. Qt的快捷键处理
8. Qt的状态栏和菜单

### 设计模式
1. MVC模式
2. 观察者模式
3. 命令模式（撤销/重做）
4. 单例模式（可选）

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
./Project_02_TextEditor
```

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Widgets模块：https://doc.qt.io/qt-6/qtwidgets-index.html
- QTextDocument：https://doc.qt.io/qt-6/qtextdocument.html
- QTextCursor：https://doc.qt.io/qt-6/qtextcursor.html
- Qt事件系统：https://doc.qt.io/qt-6/eventsandsignals.html

## 💡 学习建议

1. 先实现基本的文本编辑功能
2. 再添加文件操作功能
3. 最后实现语法高亮
4. 学习Qt的事件处理机制
5. 理解Qt的文档模型
6. 尝试优化代码结构

## ✅ 验收标准

- [ ] 可以编辑多行文本
- [ ] 可以打开和保存文件
- [ ] 实现基本的快捷键
- [ ] 实现语法高亮
- [ ] 代码有良好注释
- [ ] 符合MVC设计模式
- [ ] 符合Qt编码规范
