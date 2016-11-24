cnt=0
while true; do
	let "cnt = $cnt + 1"
	./val <ticket_chooser$cnt.in
	if [ $cnt -ge 10 ] ; then break; fi
done
