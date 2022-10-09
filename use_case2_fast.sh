var=1
while [ -e "./Results_2_fast/use_case2_fast_local_$1_$var" ]
do
	echo test123
	var=$(($var + 1))
done
#python3 build.py
cd bin
time --output=../Results_2_fast/use_case2_fast_local_$1_$var  -a -v ./use_case2_fast $1 $2 >> ../Results_2_fast/use_case1_fast_local_$1_$var
