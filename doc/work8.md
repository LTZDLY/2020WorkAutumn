```flow
st=>start: 开始
ed=>end: 结束
in=>inputoutput: 输入要删除的点
cond=>condition: 边是否已经存在
cond1=>condition: 点是否存在
operr=>operation: 报错
op=>operation: 删除点
op1=>operation: 删除与该点相连的边

st->in->cond1
cond1(yes)->op1->op->ed
cond1(no)->operr->ed

```