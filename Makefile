default: atac.c
	cc atac.c -o atac

install: default atac
	mkdir -p ~/bin
	cp ./atac ~/bin/atac

clean:
	rm -r atac
