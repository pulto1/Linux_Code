libmymath.so:myadd.o mysub.o
	gcc -shared -o $@ $^

myadd.o:myadd.c
	gcc -fPIC -c $<

mysub.o:mysub.c
	gcc -fPIC -c $<

.PHONY:clean
clean:
	rm -rf output *.o libmymath.so

.PHONY:output
output:
	mkdir -p mylib/include
	mkdir -p mylib/lib
	cp *.h mylib/include
	cp *.so mylib/lib 
