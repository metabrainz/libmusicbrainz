# based on scons/gnome.py from pygtk-scons
from SCons.Script.SConscript import SConsEnvironment
from SCons.Script import *
from SCons.Util import *
from subprocess import Popen, PIPE
import os.path
import tempfile

def _get_sources(env, nodelist):
    sources = []
    for node in nodelist:
        if node.sources:
            sources.extend(_get_sources(env, node.sources))
        else:
            sources.append(env.File(node))
    return sources

def DistSources(env, node):
    env.DistFiles(_get_sources(env, node))

def DistFiles(env, files):
    assert isinstance(files, (list, tuple))
    DISTFILES = [env.File(fname) for fname in files]
    env.AppendUnique(DISTFILES=DISTFILES)

def make_distdir(target=None, source=None, env=None):
    distdir = env.subst('$DISTDIR')
    Execute(Delete(distdir))
    Execute(Mkdir(distdir))
    for fnode in env["DISTFILES"]:
        dirname, fname = os.path.split(str(fnode))
        if dirname:
            distdirname = os.path.join(distdir, dirname)
            if not os.path.exists(distdirname):
                Execute(Mkdir(distdirname))
        Execute(Copy(os.path.join(distdir, dirname, fname), str(fnode)))
    
def clean_distdir(target=None, source=None, env=None):
    distdir = env.subst('$DISTDIR')
    Execute(Delete(distdir))
    
def make_dist(target=None, source=None, env=None):
    return Popen([env['TAR'], "-zcf",
                  env.subst("${PACKAGE}-${VERSION}.tar.gz"),
                  env.subst('$DISTDIR')]).wait()
    
def make_distcheck(target=None, source=None, env=None):
    distdir = env.subst('$DISTDIR')
    distcheckinstdir = tempfile.mkdtemp('', env.subst('${PACKAGE}-${VERSION}-instdir-'))
    distcheckdestdir = tempfile.mkdtemp('', env.subst('${PACKAGE}-${VERSION}-destdir-'))
    instdirs = [os.path.join(distcheckinstdir, d) for d in
                'lib', 'share', 'bin', 'include']
    for dir_ in instdirs:
        Execute(Mkdir(dir_))

    cmd = env.subst("cd $DISTDIR && scons DESTDIR=%s prefix=%s"
                    " && scons check && scons install") %\
            (os.path.join(distcheckdestdir, ''), distcheckinstdir)
    status = Popen(cmd, shell=True).wait()
    if status:
        return status
    ## Check that inst dirs are empty (to catch cases of $DESTDIR not being honored
    for dir_ in instdirs:
        if os.listdir(dir_):
            raise SCons.Errors.BuildError(target, "%s not empy" % dir_)
    ## Check that something inside $DESTDIR was installed
    dir_ = os.path.join(distcheckdestdir, distcheckinstdir)
    if not os.path.exists(dir_):
        raise SCons.Errors.BuildError(target, "%s does not exist" % dir_)
    Execute(Delete(distcheckinstdir))
    Execute(Delete(distcheckdestdir))
    Execute(Delete(distdir))                  
                
def filter_sources(env, sources):
    return filter(lambda src: not src.endswith('.h'), sources)    
    
def generate(env):
    SConsEnvironment.DistSources = DistSources
    SConsEnvironment.DistFiles = DistFiles
    
    env['DISTDIR'] = "${PACKAGE}-${VERSION}"

    distdir_alias = env.Alias("distdir", None, make_distdir)
    dist_alias = env.Alias("dist", None, make_dist)
    env.Depends(dist_alias, distdir_alias)
    env.AddPostAction('dist', clean_distdir)
    distcheck_alias = env.Alias("distcheck", None, make_distcheck)
    env.Depends(distcheck_alias, distdir_alias)
    
    env.AlwaysBuild('dist')
    env.AlwaysBuild('distdir')
    env.AlwaysBuild('distcheck')
    
    env.Clean('distdir', clean_distdir)
    
    SConsEnvironment.FilterSources = filter_sources
    
def exists(env):
	return true

