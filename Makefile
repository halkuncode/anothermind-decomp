.PHONY: all
all: disk build

.PHONY: build
build: bin/cc1-psx-272
	@./mako.sh build

.PHONY: clean
clean:
	@./mako.sh clean


.PHONY: rebuild
rebuild:
	@./mako.sh clean
	@./mako.sh build

.PHONY: check
check: build
	sha1sum disk/jp/SLPS_016.55 build/jp/main.exe



.PHONY: requirements
requirements:
	python3 -m venv .venv
	.venv/bin/pip3 install -r requirements.txt

.PHONY: disk
disk: disk/jp

disk/%.iso:
	bchunk "disk/$*.bin" "disk/$*.cue" "$@"
	mv "disk/$*.iso01.iso" "$@"
disk/jp: disk/Another\ Mind\ (Japan).iso
	7z x "$<" -o$@


build/jp/%.o: %
	ninja $@

bin/cc1-psx-272: bin/cc1-psx-272.gz
	sha256sum --check bin/cc1-psx-272.gz.sha256
	gzip -kcd $< > $@
	touch $@
	chmod +x $@

bin/cc1-psx-272.gz: bin/cc1-psx-272.gz.sha256
	wget -O $@ https://github.com/Xeeynamo/ff7-decomp/releases/download/init/cc1-psx-272.gz