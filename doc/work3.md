```flow
st=>start: 开始
ed=>end: 结束
op0=>operation: 获取起点
op05=>operation: 传入坐标
cond0=>condition: 判断是否为终点
op1=>operation: 标记该点坐标
cond1=>condition: 判断是否可到达
cond2=>condition: 4个方向是否枚举完毕
op5=>operation: 枚举下一个方向
op3=>operation: 记录走过的路径
op4=>operation: 返回上一层
cond3=>condition: 是否为最外层
out=>inputoutput: 输出走过的路径

st->op0->op05->cond0
cond0(no)->op1->cond2
cond0(yes)->op3->op4->op2
cond2(yes)->cond3
cond2(no)->op5->op05
cond3(no)->op4->cond2
cond3(yes)->out->ed
```

```flow
st=>start: 开始
ed=>end: 结束
op=>operation: 初始化地图
in=>inputoutput: 选择地图
op1=>operation: 开始走迷宫
out=>inputoutput: 输出迷宫所有的路线及坐标

st->op->in->op1->out->ed
```