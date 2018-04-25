project('vinnie', 'c',
  version : '0.1.0',
  license : 'MIT',
  default_options : ['warning_level=3',
                     'c_std=c11'])

conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('name', meson.project_name())
configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

incdir = include_directories('include')

src = ['src/vinnie.c']
exe = executable('vinnie', src,
  include_directories : incdir,
  install : true)
  
test('basic', exe, args : ['--v'])
