import os
import os.path
import sys

env = Environment(ENV = os.environ)
env.Append(CPPPATH = [ '#.', '#lib', '#include', '#include/musicbrainz3' ])
if sys.platform == 'win32':
    if 'msvc' in env.get('TOOLS', []):
	env.Append(CCFLAGS = [ '/EHsc', '/Zi', '/MDd' ]) 
        env.Append(LINKFLAGS = [ '/NODEFAULTLIB:LIBC' ]) 
    env.Append(CPPDEFINES = [ 'WIN32', 'DEBUG' ]) 
if 'gcc' in env.get('TOOLS', []):
    env.Append(CCFLAGS = [ '-Wall', '-pedantic' ]) 

Export('env') 

SConscript([
    'lib/SConscript',           
    'test/SConscript',           
    ])  

docs = env.Command('docs/index.html', '', 'doxygen')
env.AlwaysBuild('docs/index.html')
env.Alias('docs', docs)

env.Default('lib', 'test')
