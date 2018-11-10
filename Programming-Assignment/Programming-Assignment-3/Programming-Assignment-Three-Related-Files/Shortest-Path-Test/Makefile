v: 
	./main --verbose -i BINARY < test-1.in >1.out
	diff 1.out test-1-verbose.out
	./main --verbose -i BINARY < test-2.in >2.out
	diff 2.out test-2-verbose.out


i:
	./main --implementation BINARY < test-1.in >1.out
	diff 1.out test-1-brief.out
	./main --implementation BINARY < test-2.in >2.out
	diff 2.out test-2-brief.out