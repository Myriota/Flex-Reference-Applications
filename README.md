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

# Messages Per Day

By default, 4 message per day and 8 message per day reference applications are
compiled. Additional "message per day" configuration can be added to the build
by adding an additional variant configuration to the `'variants'` array in
`./<APPLICATION_FOLDER>/meson.build`. A variant configuration uses the
following template:

```
  {
    'name': '<x>_messages',
    'c_args': [
      '-DMESSAGES_PER_DAY=<x>'
    ],
  },
```

> [!IMPORTANT]
> Replace '<x>' in the template with the desired message per day.

# Visualisation

A pre-configured Tago.io dashboard is provided for displaying the reported
messages. Follow the instructions on the [Developer Site](support.myriota.com)
under 'Visualise Your Data'.

# Unpacking data

The `message_store.py` script supplied by
[Flex SDK](https://github.com/Myriota/Flex-SDK) can be used to query user
messages delivered from the device via satellite. These messages can be then be
supplied to the corresponding `unpack.py` script of the application running
on the aforementioned device.

```shell
python ./subprojects/Flex-SDK/scripts/message_store.py query <MODULEID> | python ./<APPLICATION_FOLDER>/unpack.py
```

E.g.

```shell
python ./subprojects/Flex-SDK/scripts/message_store.py query 00be8292d1 | python ./001_tracker/unpack.py
```

# Pre-Built Binaries

Pre-built binaries are available on the
[Device Manager Portal](https://devicemanager.myriota.com/binaries) under the
"Download Binaries" menu.
