# Requirements
For Ubuntu 24.04 LTS
### 1. Install Dependencies
```sh
sudo apt update
sudo apt install -y build-essential git qemu-system-riscv64 gcc-riscv64-linux-gnu
```
### 2. Clone this repository
```sh
git clone https://github.com/UoA-CS340-SE370-OSDev/xv6-c-student.git
```

### Build and Run
To launch xv6-riscv run:
```sh
make qemu
```

To exit, press `Ctrl` + `a` and then `x`.

