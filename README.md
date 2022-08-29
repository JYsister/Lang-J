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

你可以用 `in xxx,yyy,zzz` 的形式（等价于 C++ 的 `cin>>xxx>>yyy>>zzz;`，其中 xxx,yyy,zzz 均为变量）。

### 注释：`note`

你可以用形如 `note xxx` 的形式来进行注释。

### 结束：`DONE.`

在程序结束时必须写上这句话。

### 循环：`repeat...done`

你可以用形如
```plain
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

## 错误&正确程序示例

```plain
out '1'
```
错误：无 `out 'x'` 的形式。
正确形式：
```plain
out "1"
```

---

```plain
out "12","32","123"
```
错误：无 `out "x","y","z"` 的形式。
正确形式：
```plain
out "12"
out "32"
out "123"
```

---

```plain
newvar 114514,\Karry5307/,$water235$,note,in
```
错误：不合法变量。
正确形式：
```plain
newvar _114514,_Karry5307_,_water235_,note_,IN
```

---

```plain
delvar xyz
```
错误：删除不存在的变量。
正确形式：
```plain
newvar xyz
delvar xyz
```

---

```plain
newvar x
in x
repeat x
out x
out "\n"
done
```
错误：循环次数为变量。
正确形式：
```plain
newvar x
in x
repeat 114514
out x
out "\n"
done
```

---

```plain
newvar x
in x
repeat 5
out x
out "\n"
```
错误：`repeat` 语句没有对应的 `done`。
正确形式：
```plain
newvar x
in x
repeat 5
out x
out "\n"
done
```

---

```plain
repeat 5
newvar x
in x
out x
out "\n"
done
```
错误：循环内定义的变量没有删除。
正确形式：
```plain
repeat 5
newvar x
in x
out x
out "\n"
delvar x
done
```
