```flow
st=>start: 开始
ed=>end: 结束
in=>inputoutput: 输入数据
cond0=>condition: 堆中是否有大于1个数据
op0=>operation: 插入堆
op1=>operation: 取出堆中前两个元素
op2=>operation: 相加并放回堆中
out=>inputoutput: 输出每次放回堆中的元素之和

st->in->op0->cond0
cond0(yes)->op1->op2->cond0
cond0(no)->out->ed

```