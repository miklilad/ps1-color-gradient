# ps1-color-gradient
## What is it?
A C program for linear color gradient of a given text.

My main goal was to use it with PS1 to get a colorful looking prompt.

![Use with PS1](https://github.com/miklilad/sh-text-color-gradient/blob/master/img/1.png)

## Instalation

#### Prerequisites - make, gcc

Download or clone and type "make"

For examples use "make example"


## How to use

Program requires 3 arguments: **color1 color2 text_to_be_colored**

Colors are given in HSV format separated by comma so for example "250,100,100"
Note: Saturation and Value are percentages so max value is 100

Before the required arguments you can insert 2 optional ones: **\[-n] \[--hsv/--rgb]**

**-n** = insert non-printable characters (Required if you want to use it with the PS1 variable. It seems to work without it at first but prompt will wrap text in a weird way if you don't enable this)

**--hsv** = Make hsv gradient(DEFAULT)

**--rgb** = Make rgb gradient

## How to use with PS1

Place the compiled `gradient.out` and `.bash_prompt` file into your home directory and add the following code snippet into your `.bashrc` in the place where the PS1 is being set. 
<h5 a><strong><code>.bashrc</code></strong></h5>

```sh
if [ "$color_prompt" = yes ]; then
    source ~/.bash_prompt
else
```

If you don't have `make` or `gcc`, there's a binary in `precompiled.zip` file.
You can adjust the colors of your prompt by changing the values of `gradient.out` arguments in `.bash_prompt`

## Examples

![Examples](https://github.com/miklilad/sh-text-color-gradient/blob/master/img/2.png)
