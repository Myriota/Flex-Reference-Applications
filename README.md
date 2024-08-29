# Flex Reference Applications

Reference Applications for Myriota's [Flex-SDK](https://github.com/Myriota/Flex-SDK).

> [!IMPORTANT]
> These reference applications are for `reference` use only they are not
> production ready.

# Development Environment

The reference applications share a development environment with Flex SDK. You
can find the instructions to setup a environment [here](https://flex-docs.myriota.com/)

# Build Instructions

First download the `Flex-SDK` with:
```shell
meson subprojects download Flex-SDK
```

Second download the `libflex` binaries with
```shell
python subprojects/Flex-SDK/scripts/download_binaries.py
```

Third configure the build:
```shell
meson --cross-file ./flex-crossfile.ini build
```

Forth perform the build:
```shell
meson compile -C build
```

> [!IMPORTANT]
> For further details and instructions for building and programming
> the reference applications refer to the
> [docs](https://flex-docs.myriota.com/)
