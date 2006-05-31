import os
import os.path
import sys
import glob

version = '3.0.0dev'

env = Environment(ENV=os.environ,
                  PACKAGE='libmusicbrainz',
                  VERSION=version,
                  toolpath=['scons'],
                  tools=['default', 'env_subst', 'dist', 'install'])

env.Append(CPPPATH=['#.', '#lib', '#include'])
env.Append(CPPDEFINES=[('VERSION', r'\"$VERSION\"')])

if sys.platform == 'win32':
    env.Append(CPPDEFINES=['WIN32'])
    
if 'msvc' in env.get('TOOLS', []):
	env.Append(CCFLAGS=['/O2', '/GX', '/MD', '/W3', '/WX']) 
    
if 'gcc' in env.get('TOOLS', []):
    env.Append(CCFLAGS=['-O2', '-g', '-Wall', '-pedantic']) 

Export('env') 

SConscript([
    'examples/SConscript',           
    'src/SConscript',           
    'test/SConscript',           
    ])  

# Configuration file
#env.EnvSubstFile('config.h',  'config.h.in')
env.EnvSubstFile('config_win32.h',  'config_win32.h.in')

# API documentation
docs = env.Command('docs/index.html', '', 'doxygen')
env.AlwaysBuild('docs/index.html')
env.EnvSubstFile('Doxyfile',  'Doxyfile.in')
env.Depends('docs/index.html', 'Doxyfile')
env.Clean('docs/index.html', 'docs')
env.Alias('docs', docs)

env.Replace(pkgconfigdir='$libdir/pkgconfig')
env.Alias('install', env.Install('$pkgconfigdir',
                                 env.EnvSubstFile('libmusicbrainz3.pc',
                                                  'libmusicbrainz3.pc.in')))

# Default targets
env.Default('src')

#env.Install(dir = '/usr/local/bin', source = ['foo', 'bar'])

dist_files = [
    'AUTHORS',
    'COPYING',
    'Doxyfile.in',
    'ChangeLog',
    'INSTALL',
    'README',
    'README.win32',
    'SConstruct',
    'TODO',
    'config_win32.h.in',
    'libmusicbrainz3.pc.in',
    ]
dist_files += glob.glob('scons/*.py')

env.DistFiles(dist_files)

