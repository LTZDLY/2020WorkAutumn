```flow

st=>start: 开始
ed=>end: 结束
in1=>inputoutput: 输入P的值
in2=>inputoutput: 输入Q的值
cond1=>condition: P为0或1？
cond2=>condition: Q为0或1？
op1=>operation: 运算
out=>inputoutput: 输出结果
cond3=>condition: 是否再来一次？

st->in1->cond1
cond1(yes)->in2->cond2
cond1(no)->in1
cond2(yes)->op1->out->cond3
cond2(no)->in2
cond3(yes)->in1
cond3(no)->ed
```