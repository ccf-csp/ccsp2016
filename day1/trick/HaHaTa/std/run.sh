g++ trick.cpp -o part1
cnt=0
while true; do
	let "cnt = $cnt + 1"
	time ./part1 <$cnt.in >$cnt.ans
	diff $cnt.out $cnt.ans >diff_log -Bb
	if [ $? -ne 0 ] ; then echo Testdata $cnt Wrong Answer
	else echo Testdata $cnt Accepted! ; fi
	rm -rf $cnt.ans
	if [ $cnt -ge 15 ] ; then break; fi
done
rm -rf part1
rm -rf diff_log
