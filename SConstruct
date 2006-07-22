import os
from glob import glob

EnsureSConsVersion(0, 96, 91)

PACKAGE = 'libmusicbrainz3'
VERSION = '3.0.0dev'

opts = Options('build.options', ARGUMENTS)
opts.AddOptions(
    BoolOption('debug', 'Compile with debug symbols', 0),
    ('tools', 'Tools to use to build', 'default')
)

baseenv = Environment(options=opts)
Help(opts.GenerateHelpText(baseenv))

env = Environment(
    ENV=os.environ,
    options=opts,
    toolpath=['build/scons'],
    tools=Split(baseenv['tools']) + ['env_subst', 'dist', 'install']
)

env['PACKAGE'] = PACKAGE
env['VERSION'] = VERSION

env.Append(CPPPATH=['#.', '#include'])

if env['PLATFORM'] == 'win32':
    env.Append(CPPDEFINES=['WIN32', '_WINDOWS'])

if 'msvc' in env['TOOLS']:
    env.Append(CCFLAGS=['/GX', '/MD', '/W3', '/WX'])
else:
    env.Append(CCFLAGS=['-Wall', '-pedantic']) 
    
if env['debug']:
    if 'msvc' in env['TOOLS']:
        env.Append(CCFLAGS=['/Zi']) 
    else:
        env.Append(CCFLAGS=['-g']) 
else:
    env.Append(CPPDEFINES=['NDEBUG'])
    if 'msvc' in env['TOOLS']:
        env.Append(CCFLAGS=['/O2'])
    else:
        env.Append(CCFLAGS=['-O2']) 

Export('env') 

# Configuration file
env.EnvSubstFile('config.h',  'config.h.scons')

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

extra_dist_files = Split("""
    AUTHORS
    autogen.sh
    config.h.scons
    configure.ac
    COPYING
    Doxyfile.in
    ChangeLog
    INSTALL
    libmusicbrainz3.pc.in
    Makefile.am
    README
    SConstruct
    """)

env.DistFiles(glob("scons/*.py"))
env.DistFiles(extra_dist_files)

env.SConscript(Split("""
    examples/SConscript           
    include/SConscript           
    src/SConscript           
    test/SConscript           
    """))
    
env.Default('src')

