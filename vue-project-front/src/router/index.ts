import { createRouter, createWebHistory } from 'vue-router';
import Login from "@/views/Login.vue";

const router = createRouter({//创建路由器
  history: createWebHistory(import.meta.env.BASE_URL),//设置路由类型
  routes: [//路由规则   ，  键值对的表示
      {
        path: '/login',//推荐路径尽量使用小写字母
        name: 'login',
        component: Login
      },
      // {
      //   path: '/',
      //   component: Login
      // },
      {
        path: '/home',
        name: 'home',
        component: () => import('@/views/Home.vue')
      }

  ]
})

export default router