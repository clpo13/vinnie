t = executable('check_vinnie', 'check_vinnie.c',
  dependencies : check_dep,
  link_with : libvin,
  include_directories : incdir,
  c_args : disable_gnu_warning)

test('vinnie functions', t)
