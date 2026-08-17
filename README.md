# Another Mind decomp (PS1)

## Set-up

Clone the repository, then run `git submodule update --init --recursive`

```shell
git clone git@github.com:halkuncode/anothermind-decomp.git --recursive &&\
cd anothermind-decomp
```

Install the necessary dependencies:

```shell
#Create the python virtual environment
make requirements

# Debian/Ubuntu
sudo add-apt-repository ppa:longsleep/golang-backports
sudo apt update
sudo apt install golang-go ninja-build 7zip bchunk binutils-mipsel-linux-gnu gcc-mipsel-linux-gnu

# Arch Linux
sudo pacman -S go ninja 7zip bchunk
yay mipsel-linux-gnu-binutils mipsel-linux-gnu-gcc
```


Create a /disks directory and place the required disk images within:

```shell
#Create the disks directory
mkdir disk

# Copy the following files into /disks
'disk/Another Mind (Japan).bin'
'disk/Another Mind (Japan).cue'
```

after this extract the data files:

```shell
make disk
```
