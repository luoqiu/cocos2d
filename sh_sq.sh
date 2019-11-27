#!/bin/bash 


val=`find * 小学英语| grep wav`
let num=0
s2=""
let num2=0
for s in $val
do
echo $s
        array=(${s//\// })

        if [ "$s2" != "${array[1]}" ];then
                num=$[num+1]
                ./test.sh ${array[0]} $num ${array[1]}
                num2=0
                s2=${array[1]}
        fi
        num2=$[num2+1]
        ./test.sh  ${array[1]} $num2 ${array[2]}
done
