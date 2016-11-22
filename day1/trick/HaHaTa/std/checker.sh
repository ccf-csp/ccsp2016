g++ val.cpp -o val
cnt=0
while true; do
	let "cnt = $cnt + 1"
	echo Testdata $cnt:
	./val <$cnt.in
	echo
	if [ $cnt -ge 15 ] ; then break; fi
done
rm -rf val
