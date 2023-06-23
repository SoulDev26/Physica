project('physica', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

#add_project_arguments('-cpp_std=c++20', language : 'cpp')
libphysica_src = [
  'src/world.cpp',
  'src/body.cpp',
  'src/chunck.cpp'
]

libfmt = dependency('fmt', version : '>=10.0.0')

libphysica_args = []

if get_option('buildtype').startswith('debug')
  libphysica_args += '-DPHYSICA_DEBUG'
endif

libphysica = static_library('physica', 'physica.cpp', libphysica_src,
  dependencies : libfmt,
  cpp_args : libphysica_args)

physica_test = executable(
  'physica_test', 'physica_test.cpp',
  link_with : libphysica
)
