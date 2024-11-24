FROM ubuntu:22.04

# Install QEMU and clang
RUN apt update && \
    apt install -y --no-install-recommends qemu qemu-kvm libvirt-daemon \
        libvirt-clients bridge-utils virt-manager qemu-system-arm \
        qemu-efi-aarch64 qemu-efi-arm qemu-system-arm wget curl bzip2 \
        build-essential unzip coreutils file texinfo libgmp-dev zlib1g \
        zlib1g-dev qemu-system-gui clang llvm lld && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /tmp/*

# Build binutils
RUN wget https://ftpmirror.gnu.org/binutils/binutils-2.30.tar.gz && \
    wget https://gcc.gnu.org/pub/gcc/infrastructure/isl-0.18.tar.bz2 && \
    tar -xzf binutils-2.30.tar.gz && \
    tar -xjf isl-0.18.tar.bz2 && \
    rm *.tar.* && \
    cd binutils-* && \
    ln -s ../isl-* isl && \
    cd .. && \
    mkdir aarch64-binutils && \
    cd aarch64-binutils && \
    ../binutils-*/configure --prefix=/usr/local/cross-compiler --target=aarch64-elf \
        --enable-shared --enable-threads=posix --enable-libmpx --with-system-zlib --with-isl --enable-__cxa_atexit \
        --disable-libunwind-exceptions --enable-clocale=gnu --disable-libstdcxx-pch --disable-libssp --enable-plugin \
        --disable-linker-build-id --enable-lto --enable-install-libiberty --with-linker-hash-style=gnu --with-gnu-ld\
        --enable-gnu-indirect-function --disable-multilib --disable-werror --enable-checking=release --enable-default-pie \
        --enable-default-ssp --enable-gnu-unique-object && \
    make -j4 && \
    make install
ENV PATH=$PATH:/usr/local/cross-compiler/bin

# create work directory
RUN mkdir /work
WORKDIR /work
