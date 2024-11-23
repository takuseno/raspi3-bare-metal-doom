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

# create work directory
RUN mkdir /work
WORKDIR /work
