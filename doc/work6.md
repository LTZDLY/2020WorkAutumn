```flow

st=>start: 开始
ed=>end: 结束
op1=>operation: 初始化屏幕
op2=>operation: 初始化树
in=>inputoutput: 输入操作码
cond=>condition: 操作码合法?
op3=>operation: 执行对应操作

st->op1->op2->in->cond
cond(yes)->op3->in
cond(no)->ed

```