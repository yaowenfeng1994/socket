## 文件描述符
**1.linux启动后，会默认打开3个文件描述符，分别是：标准输入standard input 0,正确输出standard output 1,错误输出：error output 2
  以后打开文件后。新增文件绑定描述符 可以依次增加。 一条shell命令执行，都会继承父进程的文件描述符。因此，所有运行的shell命令，
  都会有默认3个文件描述符。**

## 语法问题
**2. warning ISO C++11 does not allow conversion from string literal to 'char *'
代码中是这样子的char *p = "hello world"; C++11以后的标准应该不允许这样的格式，"hello world"是字面常量，用一个指针p去指向它，
事实上没有办法通过p去改变字面常量的。const char *p = "hello world"; 是没有问题的，同样也就限制了通过p来改变字符串值了。**
