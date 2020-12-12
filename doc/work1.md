```flow
  
st=>start: 开始
in=>inputoutput: 输入插入位置
inval=>inputoutput: 输入节点数据
cond=>condition: 位置是否合法
con=>condition: i < n?
opf=>operation: 插入新节点
opend=>end: 结束
opt=>operation: i++; p = p->next;

opp=>operation: Int i = 0
e=>end
st->in->cond
cond(yes)->inval->opp->con
cond(no)->in
con(no)->opf->opend
con(yes)->opt->con
```

```flow
  
st=>start: 开始
ed=>end: 结束
ederror=>end: 数据有误，抛出异常
opin=>operation: 输入需删除学号
opt=>operation: 删除节点
cond=>condition: 是否找到

st->opin->cond
cond(yes)->opt->ed
cond(no)->ederror
```

```flow
  
st=>start: 开始
ed=>end: 结束
ederror=>end: 数据有误，抛出异常
opin=>operation: 输入需查找学号
opt=>operation: 返回节点
cond=>condition: 是否找到

st->opin->cond
cond(yes)->opt->ed
cond(no)->ederror
```
```flow
  
st=>start: 开始
ed=>end: 结束
ederror=>end: 数据有误，抛出异常
opin=>operation: 输入需更改的学号
in=>inputoutput: 输入更改后节点数据
opt=>operation: 修改并返回节点
cond=>condition: 是否找到

st->opin->cond
cond(yes)->in->opt->ed
cond(no)->ederror
```

```flow
  
st=>start: 开始
ed=>end: 结束
op=>operation: p = this->_head;
opa=>operation: p = p->_next;
cond=>condition: p == nullptr?
out=>inputoutput: 输出节点

st->op->cond
cond(yes)->ed
cond(no)->out->opa->cond
```
```flow

st=>start: 开始
ed=>end: 结束
op1=>operation: 初始化屏幕
op2=>operation: 初始化链表
in=>inputoutput: 输入操作码
cond=>condition: 操作码合法?
op3=>operation: 执行对应操作

st->op1->op2->in->cond
cond(yes)->op3->in
cond(no)->ed

```