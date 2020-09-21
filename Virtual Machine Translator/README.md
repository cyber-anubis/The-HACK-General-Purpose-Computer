# Project 7 & 8:

**When we want to excute the points program written in Jack language -OOP high level language- which computes the distance between the given point and the origin (0,0) in a 2D system, a lot has to be done in order to make it happen**

![3](https://user-images.githubusercontent.com/33065305/90672096-e593fd00-e255-11ea-9867-243e48313703.png)

Describing the first steps toward building a compiler for a typical object based high-level language. I will approach this substantial task in two stages, each spanning two projects. High-level programs will first be translated into an intermediate code (projects 10–11), and the intermediate code will then be translated into
machine language (projects 7–8). This two-tier translation model is a rather old idea
that goes back to the 1970s. Recently, it made a significant comeback following its
adoption by modern languages like Java and C#.

The basic idea is as follows: Instead of running on a real platform, the intermediate
code is designed to run on a Virtual Machine. The VM is an abstract computer
that does not exist for real, but can rather be realized on other computer platforms.
There are many reasons why this idea makes sense, one of which being code transportability.
Since the VM may be implemented with relative ease on multiple target
platforms, VM-based software can run on many processors and operating systems
without having to modify the original source code. The VM implementations can be
realized in several ways, by software interpreters, by special-purpose hardware, or by
translating the VM programs into the machine language of the target platform.
This project presents a typical VM architecture, modeled after the Java Virtual
Machine (JVM) paradigm. As usual, we focus on two perspectives. First, we motivate
and specify the VM abstraction. Next, we implement it over the Hack platform.
Our implementation entails writing a program called VM translator, designed to
translate VM code into Hack assembly code. 

A virtual machine model typically has a language, in which one can write VM
programs. The VM language that we present here consists of four types of commands:
arithmetic, memory access, program flow, and subroutine calling commands.The result is a full-scale virtual machine that will
serve as the backend of the compiler that we will build in projects 10–11.

The virtual machine that emerges from this effort illustrates many important ideas
in computer science. First, the notion of having one computer emulating another is
a fundamental idea in the field, tracing back to Alan Turing in the 1930s. Over the
years it had many practical implications, for example, using an emulator of an old
generation computer running on a new platform in order to achieve upward code
compatibility. More recently, the virtual machine model became the centerpiece
of two competing mainstreams—the Java architecture and the .NET infrastructure.
These software environments are rather complex, and one way to gain an inside view
of their underlying structure is to build a simple version of their VM cores, as we do
here.

Another important topic embedded in this project is stack processing. The stack
is a fundamental and elegant data structure that comes to play in many computer
systems and algorithms. Since the VM presented in this chapter is stack-based, it
provides a working example of this remarkably versatile data structure.


![0](https://user-images.githubusercontent.com/33065305/90673505-2856d480-e258-11ea-8141-e2ac1e077fd7.png)
![image](https://user-images.githubusercontent.com/33065305/90673718-6ce27000-e258-11ea-999a-6ac2d0185b03.png)

## The Stack Machine Model
![image](https://user-images.githubusercontent.com/33065305/90674052-e0847d00-e258-11ea-9309-2640b632e10f.png)

![image](https://user-images.githubusercontent.com/33065305/90674306-3d803300-e259-11ea-884e-aa6544ca9fe2.png)

![image](https://user-images.githubusercontent.com/33065305/90674265-2fcaad80-e259-11ea-9ef5-124d17bc8ea6.png)

![image](https://user-images.githubusercontent.com/33065305/90674209-14f83900-e259-11ea-9c24-50c332f5cac6.png)

![image](https://user-images.githubusercontent.com/33065305/90674244-22152800-e259-11ea-9960-6d70092baf01.png)


