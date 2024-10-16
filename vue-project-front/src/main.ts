import { createApp } from "vue";//导入 包   :  import  {变量名|函数名} from  "包名"
import  App  from "./App.vue";//导入 组件（根组件）
import  router  from  "./router/index";//导入 路由

import ElementPlus from 'element-plus'; //导入element-plus
import 'element-plus/dist/index.css';   //element-plus的基础样式包
import 'element-plus/theme-chalk/display.css'; //element-plus 断点类样式 


import * as ElementPlusIconsVue from '@element-plus/icons-vue'; //Element-plus  图标  包

let app = createApp(App);//创建一个vue的应用程序组件， 只应该创建  一次   app

for (const [key, component] of Object.entries(ElementPlusIconsVue)) {//循环遍历应用图标包
  app.component(key, component);//注册组件的过程
}

app.use(router).use(ElementPlus).mount("#app");//使用自定义的路由,使用了element框架,将app这个应用  挂载到   id为app的 元素上展示