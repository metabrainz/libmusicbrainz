# based on scons/gnome.py from pygtk-scons
from SCons.Script import *
from SCons.Util import *
import os.path

def env_subst(target, source, env):
    assert len(target) == 1
    assert len(source) == 1
    target_file = file(str(target[0]), "w")
    source_file = file(str(source[0]), "r")

    text = env.subst(source_file.read())
    # Autoconf-like substs
    for key, value in env.items():
        if isinstance(value, str) or isinstance(value, unicode):
            text = text.replace('@%s@' % (key,), value)
        
    target_file.write(text)
    target_file.write("\n")
    
    target_file.close()
    st = os.stat(str(source[0]))
    os.chmod(str(target[0]), stat.S_IMODE(st[stat.ST_MODE]) | stat.S_IWRITE)

def generate(env):
    env['BUILDERS']['EnvSubstFile'] = SCons.Builder.Builder(action=env_subst)

def exists(env):
	return true

