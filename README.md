# Lang-J

为本人闲着无聊搞出来的成品。

## 食用指北
### 输出：`out`

用 `out "xxx"` 或 `out xxx` 的形式（字符串中可添加转义字符）。

### 新建变量：`newvar`

用 `newvar x,y,z` 的形式新建变量（变量名要求同 C++）。

### 删除变量：`delvar`

用 `delvar x,y,z` 的形式删除变量（变量名要求同 C++）。

**注意：对于循环内的变量，在循环末尾必须删掉。**

### 输入：`in`

你可以用 `in xxx,yyy,zzz` 的形式（等价于 C++ 的 `cin>>xxx>>yyy>>zzz;`，其中 xxx,yyy,zzz 均为字符串）。

### 注释：`note`

你可以用形如 `note xxx` 的形式来进行注释。

### 结束：`DONE.`

在程序结束时必须写上这句话。

### 循环：`repeat...done`

你可以用形如
```
repeat t
newvar x
in x
out x
out "\n"
delvar x
done
```
的形式进行循环（可嵌套，t 处目前仅能使用数字）

## 题库

~~[Link.](https://www.luogu.com.cn/training/136096)~~ 已废弃。

## 编辑&解释程序

项目中的是各项版本的编辑&解释程序。
