all:
	gcc cmpiOSBase_DCareProvider.c -c -lkonoha -lcmpiOSBase_Common -I/usr/include/sblim -I/usr/include/cmpi -DCMPI_VERSION=90 -fPIC -DPIC -Wall 
	gcc -shared -Wl -o libcmpiOSBase_DCareProvider.so cmpiOSBase_DCareProvider.o  -lcmpiOSBase_Common -Wl,--rpath -Wl,/usr/local/lib -lkonoha

exists:
	wbemcli ecn 'http://masa:konoha@localhost:5988/root/cimv2' | grep DCare

install:
	cp libcmpiOSBase_DCareProvider.so /usr/local/lib/

regist:
	sudo PATH="$$PATH:/usr/local/bin" sh /usr/share/sblim-cmpi-base/provider-register.sh -v -r mof/DEOS_DCare.registration -m mof/DEOS_DCare.mof

unregist:
	sudo PATH="$$PATH:/usr/local/bin" sh /usr/share/sblim-cmpi-base/provider-register.sh -v -r mof/DEOS_DCare.registration -m mof/DEOS_DCare.mof -d

clean:
	@rm -f ./*.{o,so}

test:
	gcc -g -O0 -o hello hello.c -lcmpisfcc -I/usr/include/cmpi -I/usr/include/cimc