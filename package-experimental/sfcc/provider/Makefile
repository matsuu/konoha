
all:
	gcc cmpiOSBase_HelloProvider.c -c -lkonoha -lcmpiOSBase_Common -I/usr/include/sblim -I/usr/include/cmpi -DCMPI_VERSION=90 -fPIC -DPIC -Wall 
	gcc -shared -Wl -o libcmpiOSBase_HelloProvider.so cmpiOSBase_HelloProvider.o  -lcmpiOSBase_Common -Wl,--rpath -Wl,/usr/local/lib -lkonoha

exists:
	wbemcli ecn 'http://masa:konoha@localhost:5988/root/cimv2' | grep Hello

install:
	cp libcmpiOSBase_HelloProvider.so /usr/local/lib/

regist:
	sudo PATH="$$PATH:/usr/local/bin" sh /usr/share/sblim-cmpi-base/provider-register.sh -v -r mof/Linux_Hello.registration -m mof/Linux_Hello.mof

unregist:
	sudo PATH="$$PATH:/usr/local/bin" sh /usr/share/sblim-cmpi-base/provider-register.sh -v -r mof/Linux_Hello.registration -m mof/Linux_Hello.mof -d

clean:
	@rm -f ./*.{o,so}

test:
	gcc -g -O0 -o hello hello.c -lcmpisfcc -I/usr/include/cmpi -I/usr/include/cimc
