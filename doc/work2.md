```flow
st=>start: 开始
ed=>end: 结束
in=>inputoutput: 输入链表L1和L2，
初始化链表L3
op1=>operation: p = L1->_head;
cond0=>condition: p != nullptr?
cond=>condition: L2具有p->_val?
op2=>operation: L3插入节点p;
op3=>operation: p = p->_next;
op4=>operation: 输出L3
cond2=>condition: p->next == nullptr?
st->in->op1->cond0
cond0(no)->op4->ed
cond0(yes)->cond
cond(yes)->op2->op3
cond(no)->op3
op3->cond0
```

```flow

st=>start: 开始
ed=>end: 结束
op1=>operation: 初始化屏幕
op2=>inputoutput: 输入L1,L2
op3=>operation: 对L1和L2求交集存储到L3
op4=>inputoutput: 输出L3

st->op1->op2->op3->op4->ed


```