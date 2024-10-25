<!-- 编写业务逻辑，数据 -->
<script setup lang="ts" name="App">

//默认进入login
import { useRouter , type Router } from "vue-router";//导包
import Home from "./views/Home.vue";
let router:Router = useRouter();//取得路由器     变量名:变量的类型  
if("ok" == window.localStorage.getItem("isLogin")){
    router.push("/home");//跳转路由
}else{
    router.push("/login");//跳转路由
}
//退出登录函数
function logout():void{
    window.localStorage.clear();//清除本地存储
    router.push("/login");
}

let aa = "<Star />";


</script>
<!-- 页面组织结构 -->
<template>
    <div class="common-layout">
    <el-container>
      <el-header>
        微信
      </el-header>
      <el-main>
        <!-- 挖洞， 展示路由组件 -->
        <router-view />
      </el-main>
      <el-footer>
        <el-row :gutter="20">
        <el-col :span="6">
            <el-icon v-html="aa"></el-icon>
            <div class="hidden-sm-and-down">Star</div>
        </el-col>
        <el-col :span="6">
            <router-link v-bind:to='{
                name: `home`
            }'>
            <el-icon><Grid /></el-icon>
            <div class="hidden-sm-and-down">
                Home
            </div>
            </router-link>
        </el-col>
        <el-col :span="6">
            <el-icon><Histogram /></el-icon>
            <div class="hidden-sm-and-down">Histogram</div>
        </el-col>
        <el-col :span="6">
            <el-icon v-on:click="logout"><Setting /></el-icon>
            <div class="hidden-sm-and-down">Setting</div>
        </el-col>
    </el-row>
      </el-footer>
    </el-container>
  </div>
</template>

<!-- 样式区间 -->
<style scoped>
    .a{

    }
</style>