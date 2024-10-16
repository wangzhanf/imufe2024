<script setup lang="ts" name="Login">
import { Check } from "@element-plus/icons-vue";//
import { ref ,type Ref } from "vue";
import { ElMessage } from 'element-plus';
import { useRouter ,type Router } from "vue-router";

let router:Router = useRouter();

//实现双向数据绑定
let username:Ref<string> = ref<string>("");
let password:Ref<string> = ref<string>("");

//定义登录函数
function checkLogin():void{
    if("admin" == username.value && "123456" == password.value){
        window.localStorage.setItem("isLogin","ok");// 登录成功，本地存储记录登录状态
        ElMessage.success('登录成功,3秒后自动跳转');//登录成功，提示信息
        setTimeout(() => {
            // window.location.href = "/home";
            router.replace("/home");
        }, 3000);//登录成功，跳转页面
    }else{
        ElMessage.error('用户名或者密码错误');//登录失败，提示错误信息
    }
}
</script>
<template>
  <el-row>
    <el-col :span="12" :offset="6">
      <el-input v-model="username" style="max-width: 100%" placeholder="Please input Username">
        <template #prepend>
          <el-icon>
            <User />
          </el-icon>
        </template>
      </el-input>
    </el-col>
  </el-row>
  <el-row>
    <el-col :span="12" :offset="6">
      <el-input v-model="password" type="password" style="max-width: 100%" placeholder="Please input Password">
        <template #prepend>
          <el-icon><RefreshLeft /></el-icon>
        </template>
      </el-input>
    </el-col>
  </el-row>
  <el-row>
    <el-col :span="12" :offset="6">
      <el-button v-on:click="checkLogin" style="width: 100%" type="success" :icon="Check"
        >登 录</el-button>
    </el-col>
  </el-row>
</template>
<style scoped>
.el-row {
  margin: 10px 0;
}
</style>
