project('flex-reference-applications',
  'c',
  version: '1.2.0',
  meson_version: '>=0.61.2',
  default_options: [
    'c_std=gnu99',
    'warning_level=2',
    'werror=true',
    'buildtype=minsize',
 ]
)

if not meson.is_cross_build()
  error('Native builds not supported. Please ensure you have provided a cross file via \'--cross-file\'.')
endif

git_short_hash = run_command(['git', 'rev-parse', '--short', 'HEAD'], check: true).stdout().strip()

python = find_program('python3')

flex_sdk_proj = subproject('Flex-SDK', required: false)
if not flex_sdk_proj.found()
  error('Missing Flex-SDK subproject. Maybe you deleted it?')
endif
flex_sdk_dep = flex_sdk_proj.get_variable('flex_sdk_dep')
post_process_elf = flex_sdk_proj.get_variable('post_process_elf')

includes = []

apps = []
subdir('001_tracker')
subdir('002_sensor_4-20ma')
subdir('003_pulse_counter')

foreach app: apps
  id = app['id']
  app_name = app['name']
  c_files = app['c_files']

  foreach variant: app['variants']
    variant_name = variant['name']
    name = '@0@_@1@_@2@'.format(id, app_name, variant_name)

    elf = executable('@0@'.format(name),
        c_files,
        c_args: [
          '-DAPP_ID=@0@'.format(id),
          '-DGIT_SHORT_HASH="@0@"'.format(git_short_hash),
        ] + variant['c_args'],
        name_suffix: 'elf',
        include_directories: includes,
        dependencies: [ flex_sdk_dep, ],
    )

    bin = custom_target('@0@.bin'.format(name),
        output: [
          '@0@.bin.raw'.format(name),
          '@0@.app.bin'.format(name),
          '@0@.bin'.format(name),
        ],
        input: elf,
        build_by_default: true,
        command: [python, post_process_elf, '@INPUT@', '@OUTPUT0@', '@OUTPUT1@', '@OUTPUT2@' ],
    )
  endforeach
endforeach
