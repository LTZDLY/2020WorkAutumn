```flow
st=>start: 开始
ed=>end: 结束
op1=>operation: 将图中所有的边降序排列
op2=>operation: 取出下一条边
cond0=>condition: 边的数量是否足够
cond1=>condition: 是否构成回路
op3=>operation: 将边加入最小生成树
out=>inputoutput: 输出最小生成树

st->op1->cond0
cond0(no)->op2
cond0(yes)->out->ed
op2->cond1
cond1(yes)->op2
cond1(no)->op3->cond0

```