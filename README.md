# **未名笔记**

<img src=".\img\2cad0cb112c52ebd3cae4c5afe5bf53.jpg" alt="2cad0cb112c52ebd3cae4c5afe5bf53" style="zoom:20%;" />

<center>
    一起蓝队
</center>

## 1. 程序功能介绍

未名笔记的功能构想来自windows自带记事本，在文本编辑与储存的基础上进行了一些改进，增加了诸如字体、颜色、文件归纳等功能，提供更为美观的用户界面。

#### 主界面

**主界面**左上角显示软件名称“未名笔记”。左侧显示的是文件夹，单击其中一个文件夹按钮会在右边显示文件夹的名字和文件夹中的文件，每行显示三个。文件的颜色和所属文件夹的颜色一致。

* 长按文件夹或文件，松开后可以**重命名**或**删除**。
* 点击加号按钮可以**新建**文件夹或文件。
* 若重命名或新建的文件已存在，或者未输入文件名，则弹出相应**提示**。

* 在搜索框中输入字符串，点击放大镜，即可**搜索**标题包含字符串的文件夹或文件，显示出来。

* 单击一个文件，进入该文件的文本编辑界面，会自动**读取**文件原本的内容，在文本编辑界面中显示。

<img src=".\img\image-20220630210124334.png" alt="image-20220630210124334" style="zoom: 67%;" />

#### 文本编辑界面

**文本编辑界面**，主要功能即是编辑和设计笔记具体内容。分割线上面是工具栏，主体部分是中间的七个图标，从左到右分别是“保存”、“打开文件”、“全部清除”、“撤销”、“重做”、“选择颜色”和“选择字体”。

中间核心部件即是笔记编辑界面的主要内容——文本编辑器，可以支持一些简单的文本编辑，输入相关笔记内容，输入之后点击“保存”按钮即可**选择保存位置**，和保存的文件标题（保存文件类型为txt或docx）。也可以选择打开一个目标txt或docx文件（通过第二个打开文件按钮即可实现）。

第三个橡皮按钮即是**清除**当前文本框中的所有内容，接下来**撤销**和**重做键**，实现的功能和一般APP中的功能类似。最后两个分别是**颜色**按钮和**字体**按钮，可以笔记内容中文本的字体和颜色。右上角的“**W**”和“铅笔”按钮也可以弹出一些**功能选项**。同时下方还设置了**状态栏**（记录一些信息等）和一个**悬浮窗口**。

<img src=".\img\image-20220630223016952.png" alt="image-20220630223016952" style="zoom:67%;" />

<center class="half">
    <img src=".\img\image-20220630222502774.png" width="300"/>
    <img src=".\img\image-20220630222526343.png" width="300"/>
    <p>
        两个悬浮窗口
    </p>
</center>

<img src=".\img\image-20220630222619205.png" alt="image-20220630222619205" style="zoom:67%;" />

<center>
    颜色选择窗口
</center>

左上角的“File”按实现的是退出功能，也连接着本文编辑窗口和新建文件文件夹窗口，点击file即退出当前编辑界面返回到上一层级的新建窗口。若点击“File”按钮，退出时**自动保存**到文档的原位置。

## 2. 项目各模块与类设计细节

#### NoNameNotes类

主界面由`QLayout`嵌套形成，构造函数中建立整体布局，水平方向分为三部分，`createLeft`和`createRight`分别绘制左右两侧的界面，中间是一条分隔线。

左侧和右侧结构类似，从上到下依次为标题，搜索框（含输入框和按钮两部分），文件或文件夹按钮，新建按钮。其中右侧的文件按钮是`QVBoxLayout`嵌套`QHBoxLayout`。

`readDoc()`函数在程序开始运行时执行一次，读取本地存储的文件夹和文件名。

`showFolders()`和`showFiles()`分别显示左侧的文件夹和右侧的文件界面。

`vector<Folder*> folders`成员变量存储所有`Folder`的指针，`currentFolderIdx`表示当前界面中显示的文件夹在`folders`中的下标。

#### MainWindow类

文本编辑界面分隔线上面的按钮实现都是通过新建C++类的方法实现的“按钮”（`QPushButton`）类，其父类是`QWidget`，实现的功能和Qt中`QPushButton`的功能一致，且添加了一些装饰图标资源等，然后通过信号与槽连接起来实现按键的功能。

主体部分是窗口的核心部件`QTextEdit`，实现基本文本编辑功能。最下方的状态栏是`QStatusBar`类，上面添加了两个标签（`QLabel`）类可填写相关信息，悬浮窗口是`QDockWidget`类。

文件的打开和保存，先通过`getOpenFileName`函数获取目标打开的文件路径等信息，再获取其中的文本内容将其显示在本文编辑窗口，保存同样，将文本编辑内容保存在目标路径的相应txt或docx文件中，通过`getSaveFileName`函数。撤销删除等操作，就是通过按钮连接相应槽函数对文本编辑框（`textEdit`）中的内容就行修改。字体颜色和类型的调整，通过颜色对话框和字体对话框，选中目标类型后通过`getColor`和`getFont`等函数获取相关信息对文本编辑框中的字体进行修改。

#### File类和Folder类

`File`：文件，包含文件名，可以`getName()`和`setName(name)`。

`Folder`：包含`name`,`id`,`color`属性，还包含存储文件的容器`vector<File*> files`。

二者用于NoNameNotes窗口的显示。

#### show.h中的new_edit、edit、exist、Empty类

主界面上有新建、编辑、提示对象已存在、提示名称不能为空四种对话框，分别是`new_edit`、`edit`、`exist`、和`Empty`对象，都继承自`QDialog`，构成相似。两个提示对话框的提示内容由`QLabel`构成。

在新建或重命名时，若新名称和现存文件重名，函数`showExist()`弹出对话框提示重复。若输入为空，函数`showEmpty()`弹出对话框提示字符串为空。

`edit`中对话框的自定义槽函数包括`emitDelete`（向选择界面发送删除信号），`SaveTag`将对话框中输入的内容存入文件, `SaveTag`包含`emitRenew`（向选择界面发送发送更新信号）。

主界面将`emitRenew`发送的信号与更新内存文件名称和界面文件显示的函数关联，并在此过程中判断输入是否符合要求。对象的名称从文件读取。

`emitDelete`发送的信号与删除内存文件名称和界面显示的函数关联。

最初对于新建和编辑选项的设计是菜单`QMenu`，但最终采用`QDialog`（包括仅提示的对话框也采用`QDialog`而非`QMessageBox`）的原因之一就是`QDialog`子类定义有很大自由，可添加的控件多样又不至于过于复杂，样式也更为丰富且操作简单，更容易贴合项目界面整体风格。

<center class="half">
    <img src=".\img\image-20220630204635079.png" width="300"/>
    <img src=".\img\image-20220630204810563.png" width="300"/>
    <p>
        new_edit和edit
    </p>
</center>

<center class="half">
    <img src=".\img\image-20220630204710562.png" width="300"/>
    <img src=".\img\image-20220630204710562.png" width="300"/>
    <p>
        exist和Empty
    </p>
</center>


## 3. 小组成员分工情况

##### 

* 主界面的实现
* 三人代码的拼接
* 程序运行录制和讲解

##### 

* 界面功能和艺术风格的设计与优化
* 四个对话框的实现
* 部分程序的拼接和优化

##### 

* 整个文本编辑界面所有功能的实现
* 程序logo的设计

## 4. 项目总结与思考感悟

##### 

设计未名笔记项目主要目的就是让记事本风格更加美观和实用，所以我们希望用Qt的功能实现一个更加美观更加便捷也更加实用的记事本项目，在实现这个项目的过程中遇到了很多问题也收获了很多知识。

文本编辑界面上，最开始希望对Qt中的按钮进行修饰，最初认为可以通过Qt中提供的绘画功能字形绘制每一个按钮的图标，但是在实现的过程中发现工作量巨大且不易实现，最后找到了更简单的操作，即通过添加资源文件的方式，自己添加一个C++ `QWidget`的子类，添加目标图片即可设计出按钮图标，并用过简单的信号与槽`connect`函数就可以实现按钮功能。

在进行文件保存和读取等功能的实现时，一些文本字符类型的转换函数也是去、Qt提供的强大功能，在这个过程中通过查找Qt帮助文档等查询相关函数的具体功能也学习到了不少有用的函数，这些函数极大地方便了编写程序也减少了工作量。

在颜色选择和字体选择功能上，目前实现的功能还是有很大欠缺的，只可以通过选中字体对文本框中左右文字进行改变，而不能改变某一个或某几个字的字体样式，颜色可以实现改变具体某一个或某几个字的颜色的功能。并且保存的时候只能以纯文本的形式保存笔记内容，无法记录其中文字的字体和颜色信息，这也是笔记目前存在的欠缺之处。下方的状态栏希望通过鼠标移动和键盘按下和释放按钮等实现文本框中字数和行数的实时更新，但是此项功能尚未实现，也是笔记的一个欠缺。

在制作未名笔记的过程中，其实不仅仅是收获了相应的具体的知识，也得到了一点做项目的心得和体会。最初在设计窗口的时候，我的做法是想到什么内容就添加什么内容，但是目标并不清晰，窗口也不是很简洁和美观，在设计的时候思路也是比较混乱的，导致前期浪费了很多的时间和精力却没有达到预期的效果。后来我们转变了方式和思路，先将目标的窗口内容进行构思，把构思内容勾画出来，并记录上响应信号和槽的连接对象和连接内容等，同时标记一些Qt中提供的函数，在敲写代码时候按照这张“图纸”进行设计，思路明显清晰了很多，也提高了编程的效率和速度，我想或许这一收获才是编写未名笔记更大的收获吧，不仅仅是学习到具体的编程知识，课业学会了一些编程的思路和方法。

##### 

最初对于新建和编辑选项的设计是菜单`QMenu`，但最终采用`QDialog`（包括仅提示的对话框也采用`QDialog`而非`QMessageBox`）的原因之一就是`QDialog`子类定义有很大自由， 可添加的控件多样又不至于过于复杂，样式也更为丰富且操作简单，更容易贴合项目界面整体风格。

而最初的files被设计为一个继承自`QLabel`的类`mylabel`，虽然只增加了数表点击这一个事件，现下看来非常简单，但因为是第一个手动继承的类而印象深刻。其概念上类似于一个贴在笔记本上的便签以分辨不同的本子，而技术动机则是因为受制于没有掌握布局下控件绝对大小的控制。这在后来带来了不少问题，比如失去了一系列`QPushiButton`的重要方法，而且很大地削弱了文件夹和文件两个部分的共同性。索性得到了及时纠正。

最初设计功能和界面样式的时候对Qt还一无所知，只在一个多学期初步见识了C++的强大功能后对未来的成果抱有美妙的幻想，但操作过程证明Qt很大程度上相当于另一门语言。这是我接触的第一个多文件项目，并在很长一段时间内对文件之间的关系不明所以，但经过了最开始的抵触之后我发现还有很多Qt还有很多基本元素是我所熟悉的，带来微妙的他乡故知之感。

这个项目给我印象最深的是一个自主探索未知的过程，而探索并不总是愉快的。学以致用回馈人以极大的满足感，但哪怕是为了一个特定目标而探索的过程，学也不总能只用。学习某一控件或函数从茫然不知所以到初见曙光，最后发现并不能应用到这个目标里。当一个陌生事物建立在另一个陌生事物的基础之上，搭建起来的是个摇摇欲坠的知识体系，也许不久之后就会悄然崩塌。但搭建的过程绝不能说没有意义，如果强身健体的能效暂且不论，至少管中窥豹般看见了罗马是怎么建成的。

##### 

这是我第一次接触这么大代码量和源文件数量的项目，作为组长，首先需要考虑的是组员的分工。最初由于还不了解项目具体实现的细节，导致分工不太合理。主界面左右的结构其实可以用同一种方式实现，却分配给了两个人分别实现，实现方式完全不同，导致画风、功能不一致，难以在其基础上增加新功能，于是中途改变了分工，抛弃了右侧原有的实现（期中前）由我实现左右两边相似的界面。李思澜同学实现新建、重命名和删除界面的对话框。因此杜佳琪的任务量稍大。这样的失误导致团队效率变低，以后面对大型的项目，一定要花费心思做到高效合理的任务分配。另外，在项目的设计中类名没有规定清楚，导致我和杜佳琪的界面用的类名相同，让最后合并代码的时候出现了一些麻烦。

在代码的封装方面，我做得还不够好。比如，左侧文件夹的显示有三种：初始显示的文件夹，新建的文件夹和搜索出来的文件夹，三者本可以封装在一个函数里，通过调用函数实现显示，我却没有封装，在三个地方赋值粘贴了几乎一样的代码，导致代码可读性变差，在修改的时候还需要同时修改三处。意识到这一点后，我在右边文件的显示上吸取了教训，用一个`showFiles`函数来显示文件。

在这个项目中，对我来说最大的收获不是学到了Qt的某函数、某控件（因为这些可能很快就忘了），而是一个大型项目的协作经验。我学到了如何使用github，如何有效的进行团队内的交流，熟悉了多文件编程，熟悉了面向对象编程的封装特性，收获了宝贵的经验。
