#!/bin/bash
a=""
for i in {0..999}
do
    : '
    if [ $i -lt 10 ]
    then
        a="00${i}"
    else
        if [ $i -lt 100 ]
        then
            a="0${i}"
        else
            a="${i}"
        fi
    fi
    '

    a = "${i}"

    ./mon < ./testy/in/mont${a}.in > mon.out

    ./spr ./testy/in/mont${a}.in ./mon.out ./testy/out/mont${a}.out

done