```flow

st=>start: 开始
ed=>end: 结束
op0=>inputoutput: 读取数组
out=>inputoutput: 输出数组
op1=>operation: i = 0;
cond1=>condition: arr[i]>arr[i+1]?
ops=>operation: swap(arr[i],arr[i+1]);
opf=>operation: 竖flag
opi=>operation: i++;
cond2=>condition: 到末尾？
cond3=>condition: flag倒着？
op3=>operation: 推flag

st->op0->op1->cond1
cond1(yes)->ops->opf->opi->cond2
cond1(no)->opi
cond2(yes)->cond3
cond2(no)->cond1
cond3(yes)->out->ed
cond3(no)->op3->op1
```