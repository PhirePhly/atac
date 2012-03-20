default:
	cc atac.c -o atac

install: default
	cp ./atac ~/bin/atac

clean:
	rm -r atac
