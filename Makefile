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
