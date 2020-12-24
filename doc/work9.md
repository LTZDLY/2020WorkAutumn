```flow

st=>start: 开始
ed=>end: 结束
in=>inputoutput: 输入课程文件路径
op1=>operation: 录入课程数据
op2=>operation: 根据数据绘制有向图
op3=>operation: 根据有向图进行拓扑排序
op4=>operation: 根据拓扑排序绘制课程表
out=>inputoutput: 输出课程表

st->op1->op2->op3->op4->out->ed

```