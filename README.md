#CCSP2016

**所有基于文本的文件如果含有中文，必须用UTF-8编码。**

更详细的内容见[oi_tools](http://git.oschina.net/mulab/oi_tools)子工程的介绍。

在`git clone`的时候加上`--recursive`可以一并把这个子工程拿下来：
```
git clone --recursive git@git.oschina.net:mulab/CTT2016.git
```

已经clone下来但子工程是一个空文件的，用下列方式更新：
```
cd oi_tools
git submodule init
git submodule update
```

写题面的方法见oi_tools的说明，用下列方式预览题面：
```
python oi_tools/renderer.py uoj -p day1/题目名称
```
会以Markdown的形式生成到文件夹 `uoj` 中。看Markdown可以搜跨平台的Typora工具。

如果你的文件都装好了，可以用下列方式测试数据装得对不对以及在自己机器上测一下时间：
```
python oi_tools/packer.py test -p day1/题目名称
python oi_tools/tester.py -p day1/题目名称
```
测试结果将存放在results文件夹下。

按照下列格式装各文件：

```
probs.json	//必须有一个文件说明每场比赛题目的顺序，具体格式见后文
title.tex	//如果要输出NOI风格的pdf，需要在这里定义比赛的名字，否则不需要这个文件
oi_tools	//把工具包放在这个位置
day1		//第一层是不同天/场次，如果只有一场，仍然需要一个文件夹
day2		//这层目录下可以有没有用的目录
	day_title.tex	//如果要输出NOI风格的pdf，需要在这里定义这一天的名字、时间等
	interval		//第二层目录是题目
	drink
	nodes			//注意这层目录下不要出现除了下述目录以外的目录，否则会被当做测试选手
		prob.json	//必须有一个文件说明这道题目的信息
		assignment[.pdf]		//命题报告，一个文件或文件夹，单文件用pdf、pptx、html等可以直接看的格式，文件夹必须用.dir结尾，下同
		discussion[.pdf]		//讲题/题目讨论PPT，一个文件或文件夹
		solution[.docx]			//题解
		data			//一定包含一个评测用数据的文件夹
			nodes1.in	//文件一定用<题目名称><编号>.<后缀名>的格式命名
			nodes1.ans	//标准输出文件是.ans
			...
			nodes10.ans
			chk		//checker统一使用chk命名，需要编译的话提供一个同名文件夹。!TODO：这里未来会增加对不同评测环境的支持，用make <环境名称>生成对应环境的chk，没有makefile则用g++进行编译。
				chk.cpp			//如果用正常的g++命令编译，就这么放
				testlib.h		//可以有其他文件
		down	//一定包含一个下发文件夹
			nodes1.in	//对于非提交答案题，这是第一个样例；对于提交答案题，这是第一个下发的输入，注意评测和下发的输入可以不同，因此要两个地方都放上in
			nodes1.ans	//这里的编号和题面中的样例编号相同，题面中出现的样例也要在这里给出
			nodes2.in
			...
			decimal.cpp	//这道题没有这个啦，这个是要下发的代码，其他任何要下发的文件同理
			checker		//对于需要编译后下发的，仍然是提供一个文件夹
				checker.cpp	//和上面一样，正常编译就这样，否则提供makefile
				testlib.h
			sample_programs.dir	//极少的题目需要下发一个目录，规定这样的目录+.dir好了，下发时会删除.dir
				sample.cpp	//这些完全可以不放在目录中下发
				sample.pas
		gen		//如果出题人写了数据生成器，放在这里，不规定格式
		vfk		//每个出题人/验题人建立一个目录
		picks	//这是另一个验题人
			val 	//如果你写了数据检查器请放在这样命名的文件夹下，具体格式见后文
			data.test		//如果你不是出题人但是出了数据
			chk.test		//如果你写了checker的测试，装在这个文件夹下
			checker.test	//同理，不要问我同名怎么办
			n_log_n		//每个模拟选手的测试用一个文件夹装
				nodes.cpp或nodes1.ans	//这就是一个模拟选手，用标准IO
			Dinic	//另一个模拟选手，名称随意，不要匹配到上文和下文的名称就行
				nodes1.ans
				...
			hehe.dir	//如果你有其他文件夹，觉得想分享给大家，又不是模拟选手，用.dir
			rename.py	//可以有其他想要分享的文件
		description.md	//题面，用markdown+jinja模板做（可以纯markdown）
		resources		//题面中使用的外部资源，例如图片、html或tex的模板（对于md无法表示的东西，需要分别写html和tex）
			1.jpg		//和题面中名称相同的图片
		tables			//需要用到的表格
			data.json	//和题面中名称相同的表格，用json+jinja模板做（可以纯json）
lectures	//有讲座的活动（WC、APIO等），讲座的东西（包括集训队交流）
	picks	//装在一个自己名字命名的文件夹里面
	vfk		//名字应该不会重复吧2333
```

每道题目目录下要放一个 `prob.json`：（注意json文件不能包含注释，你可以去[这里](http://tool.oschina.net/codeformat/json)验证你的json文件是否合法）
```js
{
	"name" : "excellent",		//题目名称，目前要求和文件夹一样，可以不写
	"type" : "program",			//program传统，output提交答案，alternately交互
	"cnname" : "优秀的拆分",	//中文名称
	"time limit" : 1.5,			//时间限制，uoj会自动向上取整；TODO：如果不同环境限制不同，用{'noi' : 1.5, 'uoj' : 2.0}
	"memory limit" : "512 MB",	//空间限制，必须加上单位
	"test cases" : 20,			//测试点数量，TODO：如果不同测试点得分不同，或是打包评测，或是不按标准命名数据，则不加这一项
	"partial score" : false,	//是否有部分分，默认没有
	"compile" : {				//各个语言的编译开关
		"cpp" : "-O2 -lm",
		"c" : "-O2 -lm",
		"pas" : "-O2"
	},
	"sample count" : 3,			//样例的数量，提交答案题这里写0，如果要提供样例下发只在题面里引用就可以了
	"args" : [10, 30000],		//这是全局参数，由出题人自定义，也可以在题面中引用；TODO：未来会传给val
	"data" : [					//这是每个测试点的参数（也是由出题人自己定义）
		{
			"cases" : [1, 2],	//这是测试点1和2的公共参数
			"args" : [300, 1]	//这些测试点的参数，由出题人自定义，会传给val，也可以在题面中引用
		},
		{
			"cases" : [3, 4],
			"args" : [200, 1]
		},
		...
		{
			"cases" : [20],
			"args" : [30000, 0]
		}
	],
	"uoj id" : 3				//如果要使用上传到uoj的功能，需要填写这道题目的uoj题目id
}
```
