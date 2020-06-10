project(
    'laikawm', 
    'c', 'cpp',
    version: '0.0.1',
    default_options: ['c_std=c11', 'cpp_std=c++17']
)

build_args = [
    '-DWLR_USE_UNSTABLE',
    '-g'
]

subdir('protocol')
inc = include_directories('include')

project_source_files = [
  'util.cpp',
  'color.cpp',
  'cursor.cpp',
  'input.cpp',
  'keyboard.cpp',
  'output.cpp',
  'render.cpp',
  'layers.cpp',
  'selection.cpp',
  'server.cpp',
  'surface.cpp',
  'view.cpp',
  'view_operations.cpp',
  'window_decoration.cpp',
  'laikawm.cpp'
]

project_dependencies = [
  dependency('wlroots'),
  dependency('wayland-client'),
  dependency('wayland-server'),
  dependency('xkbcommon'),
  dependency('gdk-pixbuf-2.0'),
  dependency('cairo'),
  dependency('pango'),
  dependency('pangocairo'),
  dependency('librsvg-2.0'),
  dependency('expat'),
  client_protos
]

project_target = executable(
  meson.project_name(),
  project_source_files,
  dependencies: project_dependencies,
  include_directories: inc,  
  c_args: build_args,
  cpp_args: build_args
)