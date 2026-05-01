# Project 07: Qt游戏引擎基础

## 📋 项目简介

创建一个简单的游戏引擎框架，支持精灵动画、碰撞检测、摄像机系统、资源管理等。

## 🎯 项目要求

### 基础功能
1. **精灵系统**
   - 精灵加载
   - 精灵渲染
   - 精灵动画
   - 精灵变换

2. **碰撞检测**
   - 矩形碰撞（AABB）
   - 圆形碰撞
   - 精灵碰撞

3. **摄像机系统**
   - 平滑移动
   - 边界限制
   - 缩放

4. **资源管理**
   - 图片加载
   - 动画序列加载
   - 音效加载
   - 资源缓存

### 进阶功能
1. **场景管理**
   - 场景切换
   - 场景层次
   - 场景持久化

2. **输入系统**
   - 键盘输入
   - 鼠标输入
   - 触摸输入

3. **游戏循环**
   - 固定时间步长
   - 帧率控制
   - 暂停/继续

4. **UI系统**
   - 2D UI渲染
   - UI事件处理
   - 按钮、文本、图片UI

### 代码质量要求
1. 遵循Qt编码规范
2. 使用MVC模式
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_07_GameEngine/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── GameApp.h                   # 游戏应用头文件
    ├── GameApp.cpp                 # 游戏应用实现
    ├── GameLoop.h                  # 游戏循环头文件
    ├── GameLoop.cpp                # 游戏循环实现
    ├── SceneManager.h              # 场景管理器头文件
    ├── SceneManager.cpp            # 场景管理器实现
    ├── Sprite.h                    # 精灵头文件
    ├── Sprite.cpp                  # 精灵实现
    ├── SpriteRenderer.h            # 精灵渲染器头文件
    ├── SpriteRenderer.cpp          # 精灵渲染器实现
    ├── Animation.h                 # 动画头文件
    ├── Animation.cpp               # 动画实现
    ├── AnimationSequence.h         # 动画序列头文件
    ├── AnimationSequence.cpp       # 动画序列实现
    ├── CollisionDetection.h        # 碰撞检测头文件
    ├── CollisionDetection.cpp      # 碰撞检测实现
    ├── AABB.h                      # AABB碰撞头文件
    ├── AABB.cpp                    # AABB碰撞实现
    ├── CircleCollision.h           # 圆形碰撞头文件
    ├── CircleCollision.cpp         # 圆形碰撞实现
    ├── Camera.h                    # 摄像机头文件
    ├── Camera.cpp                  # 摄像机实现
    ├── InputHandler.h               # 输入处理器头文件
    ├── InputHandler.cpp             # 输入处理器实现
    ├── ResourceManager.h           # 资源管理器头文件
    ├── ResourceManager.cpp         # 资源管理器实现
    ├── Scene.h                     # 场景头文件
    ├── Scene.cpp                   # 场景实现
    ├── UIElement.h                 # UI元素头文件
    ├── UIElement.cpp               # UI元素实现
    ├── Button.h                    # 按钮头文件
    ├── Button.cpp                  # 按钮实现
    ├── tests/
    │   ├── test_sprite.cpp         # 精灵测试
    │   ├── test_collision.cpp      # 碰撞测试
    │   └── test_camera.cpp         # 摄像机测试
    └── examples/
        ├── demo1.cpp               # 示例1：基础精灵
        ├── demo2.cpp               # 示例2：动画演示
        └── demo3.cpp               # 示例3：碰撞演示
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的QtGui模块深入
2. 图形渲染和绘制
3. OpenGL基础（可选）
4. 坐标系统和变换
5. 游戏循环和帧率控制
6. 碰撞检测算法
7. 资源管理
8. 游戏架构设计
9. 性能优化技术

### 设计模式
1. MVC模式
2. 观察者模式
3. 单例模式（资源管理）
4. 策略模式（碰撞检测）
5. 对象池模式（可选）
6. 命令模式（输入处理）

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
./Project_07_GameEngine examples/demo1
```

### 运行示例
```bash
./Project_07_GameEngine examples/demo1  # 基础精灵
./Project_07_GameEngine examples/demo2  # 动画演示
./Project_07_GameEngine examples/demo3  # 碰撞演示
```

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Widgets OpenGL：https://doc.qt.io/qt-6/qt-quickcontrols2-visualtest.html
- 游戏开发教程：
  - 《Game Engine Architecture》
  - 《Real-Time Rendering》
  - 《Game Programming Patterns》
- 免费游戏引擎：
  - 极地兀鹫引擎
  - 射击游戏引擎

## 💡 学习建议

1. 先理解游戏循环和帧率控制
2. 实现基础的精灵加载和渲染
3. 实现摄像机系统
4. 实现碰撞检测
5. 添加动画系统
6. 实现资源管理
7. 添加场景管理
8. 实现UI系统
9. 优化性能
10. 学习高级图形技术

## ✅ 验收标准

- [ ] 可以加载和显示精灵
- [ ] 可以实现动画
- [ ] 可以检测碰撞
- [ ] 摄像机系统正常工作
- [ ] 资源管理正常
- [ ] 场景切换正常
- [ ] 输入系统正常
- [ ] UI元素可以显示和交互
- [ ] 代码有良好注释
- [ ] 符合MVC设计模式
- [ ] 符合Qt编码规范
- [ ] 代码结构清晰

## 🎮 功能演示

### 示例1：基础精灵
- 加载精灵图片
- 显示精灵
- 移动精灵
- 键盘控制

### 示例2：动画演示
- 加载动画序列
- 播放动画
- 动画速度控制
- 动画状态管理

### 示例3：碰撞演示
- AABB碰撞检测
- 圆形碰撞检测
- 碰撞响应
- 多物体碰撞

## 📊 性能优化

### 渲染优化
- 批量渲染
- 资源预加载
- 减少状态切换
- 使用纹理图集

### 内存优化
- 对象池模式
- 资源缓存
- 智能指针管理
- 延迟加载

### 算法优化
- 优化碰撞检测算法
- 空间划分（四叉树、八叉树）
- LOD技术
- 遮挡剔除

## 🚧 进阶功能

### 高级图形
- 粒子系统
- 光照效果
- 阴影
- 后处理

### 高级功能
- 物理引擎集成
- 网络同步
- 存档系统
- 关卡编辑器
