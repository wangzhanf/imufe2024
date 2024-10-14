名称:Tcp 服务端
描述:
前置知识:
后续综合的项目:
主要知识点: Qt中QTcpServer  和QTcpSocket分离设计,Qt中不是bind方法而是listen方法进行绑定
步骤:
    1. 布局一个界面
        注意加载  network模块
        引入 QTcpServer 头文件
    2. 建立全局的QTcpServer对象并初始化
    3. 服务器的多事件的绑定
    4. 客户端
    5. 注意编码(防止乱码的产生)问题
