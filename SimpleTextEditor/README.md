# SimpleTextEditor（简单文本编辑器）

东莞理工学院《Qt 应用程序开发》实验2 项目源码。

## 功能清单

- 文件：新建 / 打开 / 保存 / 另存为 / 退出，关闭前未保存提示，含 NUL 字节的非文本文件拒绝打开
- 编辑：撤销 / 重做 / 剪切 / 复制 / 粘贴 / 全选，动作使能状态与选区、剪贴板联动
- 搜索：查找下一个、单个替换、全部替换（非模态对话框，不挡编辑）
- 格式：字体、字号、字体颜色、背景颜色、自动换行、行号显示、定时自动保存（60 秒）
- 视图：工具栏、状态栏显隐切换；状态栏实时显示行列号
- 设置持久化：字体、颜色、换行、行号、工具栏/状态栏状态、窗口几何均用 QSettings 保存
- 编码：按 UTF-8 读写，检测到 U+FFFD 替换字符时回退本地编码（GBK）重新解码

## 构建

需要 Qt 5.12 + MinGW（或任一桌面套件）：

```bash
qmake SimpleTextEditor.pro
mingw32-make
```

## 目录说明

- `mainwindow.*` 主窗口（菜单、工具栏、状态栏、文件读写）
- `codeeditor.*` 行号栏（参考 Qt 官方 Code Editor Example）
- `finddialog.*` / `replacedialog.*` / `aboutdialog.*` 三个对话框
- `images/` 菜单与工具栏图标，来自 KDE Oxygen 图标集（LGPL）
- `resources.qrc` Qt 资源文件
