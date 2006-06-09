# based on scons/gnome.py from pygtk-scons
from SCons.Script.SConscript import SConsEnvironment
from SCons.Options import *
from SCons.Script import *
from SCons.Util import *
import os.path
import new

def InstallWithDestDir(self, dir_, source):
    target = os.path.join('${DESTDIR}', str(dir_))
    return SConsEnvironment.Install(self, dir_, source)

def InstallAsWithDestDir(self, target, source):
    target = os.path.join('${DESTDIR}', str(target))
    return SConsEnvironment.InstallAs(self, target, source)
    
def generate(env):
    env.EnsureSConsVersion(0, 96, 91)
    opts = Options(['install_options.cache'], ARGUMENTS)
    opts.Add(PathOption('prefix', 
        'Installation prefix', 
        '/usr/local', []))
    opts.Add(PathOption('exec_prefix', 
        'Installation prefix for executables and object code libraries', 
        '$prefix', []))
    opts.Add(PathOption('bindir', 
        'Installation prefix for user executables', 
        '$exec_prefix/bin', []))
    opts.Add(PathOption('datadir',
        'Installation prefix for read-only architecture-independent data', 
        '$prefix/share', []))
    opts.Add(PathOption('libdir',
        'Installation prefix for object code libraries', 
        '$exec_prefix/lib', []))
    opts.Add(PathOption('includedir',
        'Installation prefix for C header files', 
        '$prefix/include', []))
    opts.Add(PathOption('DESTDIR', 'Alternate root directory', '', []))
    opts.Update(env)
    opts.Save('install_options.cache', env)
    SConsEnvironment.Help(env, opts.GenerateHelpText(env))
    
    env.Install = new.instancemethod(InstallWithDestDir, env, env.__class__)
    env.InstallAs = new.instancemethod(InstallAsWithDestDir, env, env.__class__)
    
def exists(env):
	return True

