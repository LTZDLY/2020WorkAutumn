```flow
st=>start: 开始
ed=>end: 结束
in=>inputoutput: 输入表达式
op0=>operation: 转后缀表达式
op1=>operation: 后缀表达式求值
out=>inputoutput: 输出结果
cond=>condition: 是否继续？

st->in->op0->op1->cond
cond(yes)->in
cond(no)->out->ed
```