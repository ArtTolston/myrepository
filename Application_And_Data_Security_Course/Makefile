all: libsecureallocation.so

libsecureallocation.so: secure_allocation_lib.c secure_allocation_lib.h
	gcc secure_allocation_lib.c -o libsecureallocation.so -fPIC -shared -ldl -I secure_allocation_lib.h
clean:
	rm -rf *.so
