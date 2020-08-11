#!/usr/bin/sh

hsv_to_rgb() {
    calc="
    define abs(x) {
        if (x<0) return -x;
        return x;
    }
    scale=10;
    h=$1/60;
    s=$2/100;
    v=$3/100;
    c=v*s;
    scale=0;
    x=c*(1-abs(h%2-1));
    m=v-c;
    hi=(h/1)%6;
    if (hi == 0) {r=c;g=x;b=0};
    if (hi == 1) {r=x;g=c;b=0};
    if (hi == 2) {r=0;g=c;b=x};
    if (hi == 3) {r=0;g=x;b=c};
    if (hi == 4) {r=x;g=0;b=c};
    if (hi == 5) {r=c;g=0;b=x};
    ((r+m)*255)/1;
    ((g+m)*255)/1;
    ((b+m)*255)/1
    "
    echo $(echo $calc | bc)
}

parse_color() {
    h=$(echo $1 | cut -d ',' -f1)
    s=$(echo $1 | cut -d ',' -f2)
    v=$(echo $1 | cut -d ',' -f3)
    echo $h $s $v
}

nth() {
    calc="
    scale=10;
    inc=($2-$1)/$3;
    scale=0;
    ($1+inc*$4)/1;
    "
    echo $(echo $calc | bc)
}

convert() {
    output=""
    count=-1
    for word in $text; do
        count=$(($count + $(echo $word | wc -m) - 1))
    done
    n=0
    for word in $text; do
        letters=$(echo $word | grep -o .)
        for letter in $letters; do
            h=$(nth $1 $4 $count $n)
            s=$(nth $2 $5 $count $n)
            v=$(nth $3 $6 $count $n)
            col=$(hsv_to_rgb $h $s $v)
            r=$(echo $col | cut -d ' ' -f1)
            g=$(echo $col | cut -d ' ' -f2)
            b=$(echo $col | cut -d ' ' -f3)
            output="$output\033[38;2;$r;$g;${b}m$letter"
            n=$((n+1))
        done
        output="$output "
    done
    echo $output
}

if [ $# -eq 3 ]; then 
    text=$3
    color1=$(parse_color $1)
    color2=$(parse_color $2)
    echo $(convert $color1 $color2)
    else
    echo "Use following format:"
    echo '\t"H,S,V" "H,S,V" "text to be colored"'
fi
