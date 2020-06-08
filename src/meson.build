project(
    'laikawm', 
    'c',
    version: '0.0.1',
    default_options: ['c_std=c11']
)

build_args = [
    '-DWLR_USE_UNSTABLE',
    '-g'
]

subdir('protocol')
inc = include_directories('include')

project_source_files = [
  'cursor.c',
  'input.c',
  'keyboard.c',
  'output.c',
  'render.c',
  'selection.c',
  'server.c',
  'surface.c',
  'view.c',
  'view_operations.c',
  'laikawm.c'
]

project_dependencies = [
  dependency('wlroots'),
  dependency('wayland-server'),
  dependency('xkbcommon'),
  client_protos
]

project_target = executable(
  meson.project_name(),
  project_source_files,
  dependencies: project_dependencies,
  include_directories: inc,
  c_args: build_args
)