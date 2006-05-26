import os, os.path

env = Environment(ENV = os.environ)
env.Tool('msvc') 
env.Append(CPPPATH = [ '#.', '#lib', '#include', '#include/musicbrainz3' ])
env.Append(CPPDEFINES = [ 'WIN32', 'DEBUG' ]) 
env.Append(CCFLAGS = [ '/EHsc', '/Zi', '/MDd' ]) 
env.Append(LINKFLAGS = [ '/NODEFAULTLIB:LIBC' ]) 

Export('env') 

SConscript([
    'lib/SConscript',           
    'test/SConscript',           
    ])  

docs = env.Command('docs/index.html', '', 'doxygen')
env.Alias('docs', docs)

env.Default('lib', 'test')
