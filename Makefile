.PHONY: all
all: disk build

.PHONY: build
build: bin/cc1-psx-272
	@./mako.sh build

.PHONY: clean
clean:
	@./mako.sh clean
	@rm -rf docs/html

.PHONY: docs doc
docs:
	@if command -v doxygen >/dev/null 2>&1; then \
		echo "Generating documentation with Doxygen..."; \
		doxygen docs/Doxyfile; \
		echo "Documentation generated in docs/html/index.html"; \
	else \
		echo "doxygen is not installed. Please install doxygen to generate documentation."; \
	fi

doc: docs


.PHONY: rebuild
rebuild:
	@./mako.sh clean
	@./mako.sh build

.PHONY: format
format:
	@./mako.sh format

.PHONY: submit
submit:
	@./mako.sh clean
	@./mako.sh build
	@./mako.sh format
	@git add config/ include/ src/

.PHONY: ctx
ctx:
ifndef FILE
	$(error Please specify a file: make ctx FILE=src/<file.c>)
endif
	python3 tools/m2ctx.py $(FILE)


.PHONY: check
check: build
	sha1sum disk/jp/SLPS_016.55 build/jp/another.exe



.PHONY: requirements
requirements:
	python3 -m venv .venv
	.venv/bin/pip3 install -r requirements.txt

.PHONY: disk
disk: disk/jp assets

.PHONY: assets
assets:
	python3 tools/extract_assets.py

disk/%.iso:
	bchunk "disk/$*.bin" "disk/$*.cue" "$@"
	mv "disk/$*.iso01.iso" "$@"
disk/jp: disk/Another\ Mind\ (Japan).iso
	7z x "$<" -y -o$@


build/jp/%.o: %
	ninja $@

bin/cc1-psx-272: bin/cc1-psx-272.gz
	sha256sum --check bin/cc1-psx-272.gz.sha256
	gzip -kcd $< > $@
	touch $@
	chmod +x $@

# just the one file for now may need to make this /$*.gz later
bin/cc1-psx-272.gz: bin/cc1-psx-272.gz.sha256
	wget -O $@ https://github.com/halkuncode/anothermind-decomp/releases/download/init/cc1-psx-272.gz