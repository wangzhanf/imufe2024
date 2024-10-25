<script setup lang="ts" name="Home">
    import { ref } from 'vue';
    import axios  from "axios";

    //准备数据结构
    let imgSrc = ref("https://cdn2.thecatapi.com/images/4lr.gif");
    let imgTitle = ref("标题");
    let count =ref(0);

    (()=>{
        let num = 0;
        function secondTips(){
            console.log(num++);
            setTimeout(secondTips,1000);
        }
        secondTips();
    })();

    //不断刷新请求网络数据
    let stopHandler = setInterval(() => {//匿名函数，箭头函数，lambda表达式
        let a = axios.get("https://api.thecatapi.com/v1/images/search?size=full").then((res)=>{
            // console.log(res); 
            imgSrc.value = res.data[0].url;          
            imgTitle.value = res.data[0].id;  
            if(count++ > 9)//限定请求次数,否则可能会被认为是攻击包被拉入黑名单
                clearInterval(stopHandler);
        });
    }, 50000);//50秒刷新
</script>
<template>
    <div class="zone">
        <img v-bind:src="imgSrc" />
        <h3>{{ imgTitle }}</h3>
    </div>
</template>
<style scoped>
    .zone{
        width: 80%;
        margin: 4em auto;
        text-align: center;
    }
    .zone img{
        width: 90%;
        border-radius: 10px;
    }
</style>