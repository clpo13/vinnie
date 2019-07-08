t_src = ['check_vinnie.c', '../src/vin.c']
t = executable('check_vinnie', t_src,
  dependencies : check_dep,
  include_directories : incdir,
  c_args : disable_gnu_warning)

test('vinnie functions', t)
