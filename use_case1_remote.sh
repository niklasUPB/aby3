var=1
while [ -e "./Results_1_remote/use_case1_remote_$1_$var" ]
do
	echo test123
	var=$(($var + 1))
done
#python3 build.py
cd bin
time --output=../Results_1_remote/use_case1_remote_$1_$var  -a -v ./use_case1_remote $1 $2 >> ../Results_1_remote/use_case1_remote_$1_$var
