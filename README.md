# EasyCalculator
======================================================
在使用本程序之前,请至少保证窗口的一行能显示126个字符！
请保证stateTable.txt、readMe.txt存在根目录下！
本程序作者为李云帆(@CarpVexing),作为作业作于2020.12.27
------------------------------------------------------
这是一个计算器,以仿脚本处理的风格呈现交互UI
在这里,你可以输入常规运算算术表达式\逻辑运算表达式
程序可以在模式调整下产生最终值\类型结果\分析过程\符号表等
你可以直接输入类似"(1+2)*3","true||false&&true"的式子
也可以输入类似"a1=1+9"的式子以存储相应变量值
那么接下来就能利用变量,如"a1+12"直接进行计算
------------------------------------------------------
以下是命令符：
$help       打开帮助,即当前文档

$mode       切换类型转换模式,默认为严格模式,阻止大部分类型转换
            宽容模式会将所有可能的类型转换允许执行

$default    调整为默认输出格式,即只输出结果值
            不显示别的任何内容

$induction  切换过程显示模式,默认不显示分析过程
            切换后将词法分析、语法分析分析过程显示出来

$value      调整输出格式,最终输出结果时只显示值

$type       调整输出格式,最终输出结果时同时输出值与类型

$symbols    输出当前最新符号表
------------------------------------------------------
支持的运算符和优先级(由高到低)
1   运算符和常量    id, true, false, number
2   括号            (, )
3   一元运算        +, -, ！
4   算术运算        *, /, %
5   算术运算        +, -
6   关系运算        <, <=, >, >=
7   关系运算        ==, !=
8   逻辑与          &&
9   逻辑或          ||
10  赋值/存储       =
======================================================
