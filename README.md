# sh-text-color-gradient
## What is it?
~~Shell script~~ C program for linear color gradient of a given text.
(I tried doing it all in shell, which was a really poor choice. It took 0,7 second just to load a directory. I don't know maybe I'm just bad with shell)

My main goal was to use it with PS1 to get a **sick** looking prompt.
And by sick I mean so it literally makes me sick.

![Use with PS1](https://github.com/miklilad/sh-text-color-gradient/blob/master/1.png)

## Instalation

#### Prerequisites - make, gcc

Download or clone and type "make"

For examples use "make example"


## How to use

Program requires 3 arguments to be given: **color1 color2 text_to_be_colored**

Colors are given in HSV format separeted by comma so for example "250,100,100"
Note: Saturation and Value are percantages so max value is 100

Before the required arguments you can insert 2 optional ones: **\[-n] \[--hsv/--rgb]**

-n = insert nonprintable characters (Required if you want to use it with PS1 variable. It seems to be working without it at first but prompt will wrap text in a weird way if you don't enable this)

--hsv = Make hsv gradient(DEFAULT)

--rgb = Make rgb gradient

Rather than explaining I think it will be much easier to understand if you look at the examples below.

## Examples

![Examples](https://github.com/miklilad/sh-text-color-gradient/blob/master/2.png)
