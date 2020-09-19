
## Lab Assignments

- [x] C Programming Lab
- [ ] Data Lab
    - [x] bitXor
    - [x] tmin
    - [x] isTmax
- [ ] Bomb Lab
- [ ] Attack Lab
- [ ] Cache Lab
- [x] [Shell Lab](https://github.com/carlclone/CMU-15-213/tree/master/labs/labs/05-shell-lab-lab)
- [ ] Malloc Lab
- [x] [Proxy Lab](https://github.com/carlclone/CMU-15-213/tree/master/labs/labs/07-proxy-lab/readme.md)

# Lab5 Shell Lab

2020/07/11 ~ 2020/07/19

参考资料:

- CSAPP3e Chapter 8
- [Lab Guide](http://csapp.cs.cmu.edu/3e/shlab.pdf)

```
https://zhuanlan.zhihu.com/p/28695244
https://zhuanlan.zhihu.com/p/89224358
https://zhuanlan.zhihu.com/p/119034923
https://zhuanlan.zhihu.com/p/58362429
https://www.bilibili.com/read/cv2962007/
https://zhuanlan.zhihu.com/p/34167162
```



# Lab1 Data Lab  (to be continue...)

[sof - xor](https://stackoverflow.com/questions/14526584/what-does-the-xor-operator-do)
[wiki - xor](https://en.wikipedia.org/wiki/Exclusive_or)

```
摘抄自谷歌搜索首页

在talent plan的作业里也有看到xor的使用

What is XOR operation?
XOR is a binary operation, it stands for "exclusive or", that is to say the resulting bit evaluates to one if only exactly one of the bits is set. ... Properties: The operation is commutative, associative and self-inverse. It is also the same as addition modulo 2
```

> 相关章节笔记

[读薄 CSAPP,数据表示](https://wdxtub.com/csapp/thin-csapp-1/2016/04/16/)

二进制里的集合运算经常用于各种项目(比如 redis)里的状态压缩表示

> xor 

回家的路上一个一个试出来的 ,后来看了这篇[总结](https://skylark-workshop.xyz/blog/csapp-datalab-new/),知道了德摩根定理和xor 的实现公式

`not(not a and not b) = a or b (i.e. ~(~x & ~y) = x | y) (De Morgan's laws) and (x or y) and not(x and y) = x xor y`

> tmin

对补码表示的理解 , 看图 , 图来自[读薄 CSAPP](https://wdxtub.com/csapp/thin-csapp-1/2016/04/16/)

![twoscomplement](https://raw.githubusercontent.com/carlclone/CMU-15-213/master/notes/twoscomplement.png)

> isTmax

xor 相当于二进制里的!=号, !取反则是二进制里的等号

# Lab0 C Lab

[wiki - c programming](https://en.wikibooks.org/wiki/C_Programming)
[makefile cheatsheet](https://devhints.io/makefile)

clion代码提示需要cmake , File -> new cmake project from source

`随记: 做Lab形成的一个好习惯:先写和看test case ,再实现(最好过完完整的case再开始写) , 可以说test case的数量就是进度条长度`

最基础的 Lab0 也花了那么长时间,

1.对 C 实在是太不熟悉了

2.就连数组也是指针形式的

3.每次分配完内存,如果失败了,要连前面分配过的一起释放

4.画图定义伪代码测试用例,4大神器,养成条件反射吧 (面试时做算法题脑子一空,把这些也给忘了)

5. sizeof 返回的是地址长度, strlen 返回的是不包含\0的字节长度

# 资料

[更好的选择 CS61C](https://inst.eecs.berkeley.edu//~cs61c/sp15/) 

> 二补数bai（2's complement）是一种用二进制表示有号数的方法，也是du一种将数字的zhi正负号变号的方式，常在计dao算机科学中使用。在中国大陆地区通常称作补码。 一个数字的二补数就是将该数字作位反相计算（即一补数），再将结果加 1，即为该数字的二补数。在二补数系统中，一个负数就是用其对应正数的二补数来表示。 

[2020年 213系列的课表](https://www.cs.cmu.edu/~213/index.html)

[往年的课表]()

[CSAPP书本上的Lab Start Code]()

[CMU15-122 这门课的前置课程]()




### 批量下载http文件目录

wget

已经下载到code文件夹中
